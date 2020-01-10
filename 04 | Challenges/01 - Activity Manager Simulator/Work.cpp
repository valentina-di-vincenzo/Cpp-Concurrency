//
// Created by Valentina Di Vincenzo on 2019-07-13.
//

#include "include.h"

void loop_work(int id, shared_ptr<deque<Job>> threadSafe_pendingJobs, const shared_ptr<vector<Job>>& threadSafe_completedJobs, const shared_ptr<mutex>& mutex_pending, const shared_ptr<mutex>& mutex_completed, const shared_ptr<condition_variable>& cv, const shared_ptr<atomic_bool>& done) {


    /* ---- CHECK BOOL FOR TERMINATION ---- */
    while ( !done->load() || !threadSafe_pendingJobs->empty() ) {
        cout << id << " i am in" << endl << flush;

        // 1. wait for a new job
        unique_lock<mutex> ul(*mutex_pending);
        cout << id << " waiting" << endl << flush;
        cv->wait(ul, [&] { return !threadSafe_pendingJobs->empty(); });

        // 2. get the job
        Job new_job = threadSafe_pendingJobs->front();
        cout << id << " EXECUTES JOB " << new_job.id << endl << flush;
        threadSafe_pendingJobs->pop_front();
        ul.unlock();

        // 3. elaborate the job
        auto duration = new_job.duration;
        this_thread::sleep_for(chrono::milliseconds(duration));

        // 4. move the job in the completedJobs
        lock_guard<mutex> lg(*mutex_completed);
        threadSafe_completedJobs->push_back(new_job);

    }
}
