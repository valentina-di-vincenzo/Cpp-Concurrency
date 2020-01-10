//
// Created by Valentina Di Vincenzo on 2019-07-13.
//

#include "include.h"

void JobScheduler::printJobs() {
    cout << "JOBS PENDING: " << endl << flush;
    for ( auto e : *threadSafe_pendingJobs ) {
        cout << e.id << " " << flush;
    }
    cout << endl << flush;
}
void JobScheduler::printPool() {

    cout << "[INFO] Thread nel pool" << endl << "KEY\tELEMENT\n" << endl << flush;
    for ( int i=0; i< threadPool.size(); i++ ) {
        thread& t = threadPool.find(i)->second;
        cout << threadPool.find(i)->first << "\t" << t.get_id() << endl << flush;
    }
    cout << endl << flush;

}


void JobScheduler::start() {

    /* ------------- THREADS CREATION --------------*/
    unsigned int number_threads = thread::hardware_concurrency() + 1;
    cout << "[INFO] Number of threads: " << number_threads << endl;
    for ( int i = 0; i < number_threads; i++) {

        thread t(loop_work, i, threadSafe_pendingJobs, threadSafe_completedJobs, mutex_pending, mutex_completed, cv, done);
        threadPool.insert(pair<int, thread> {i, move(t)});

    }

    //printPool();

    /* ----------- SCHEDULE NEW TASK ---------- */

    auto start_time = chrono::system_clock::now();

    while ( !jobs.empty() ) {
        int time_next_job = jobs.top().start_time;
        Job next_job = jobs.top();
        string toPrint =  "[NEW JOB]\t id: " + to_string(next_job.id) + "\tstart_time " + to_string(next_job.start_time) + "\n";
        cout << toPrint << flush;
        auto time_to_wakeup = start_time + chrono::milliseconds(time_next_job);
        this_thread::sleep_until(time_to_wakeup);
        jobs.pop();
        lock_guard<mutex> lg(*mutex_pending);
        threadSafe_pendingJobs->push_back(next_job);
        cv->notify_one();
        printJobs();
    }

    done->store(true);
}

JobScheduler::~JobScheduler() {
    /* ------- END POOL ------ */
    for ( int i=0; i < threadPool.size(); i++ ) {
        thread& t = threadPool.find(i)->second;
        t.join();
        cout << "Thread " << threadPool.find(i)->first << " terminated." << endl;
    }
}
