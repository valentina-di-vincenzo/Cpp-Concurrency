//
// Created by Valentina Di Vincenzo on 2019-07-13.
//

#ifndef LAB_4_INCLUDE_H
#define LAB_4_INCLUDE_H

#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <map>
#include <condition_variable>
#include <future>
#include <atomic>
#include <memory>

#define QUANTO_TIME 3000

using namespace std;


/* --------------- JOB ----------------- */
class Job {
public:
    Job(int id, int start_time, int duration) {
        this->id = id;
        this->start_time = start_time;
        this->duration = duration;
    }
    int id;
    int duration;
    int start_time;
    int execution_time;
    int wait_time;
    int completion_time;

};


// Used in the priority queue
struct compareJobs {
    bool operator() (const Job& job1, const Job& job2) {
        return  job1.start_time > job2.start_time;
    }
};

/* ------------- JOB SCHEDULER ---------- */

class JobScheduler {

private:
    priority_queue<Job, deque<Job>, compareJobs> jobs;
    map<int, thread> threadPool;
    const int quanto { QUANTO_TIME };
    void printPool();
    void printJobs();

    /* ---------- MULTI THREADING ----------- */

    shared_ptr<deque<Job>> threadSafe_pendingJobs = make_shared<deque<Job>>();
    shared_ptr<vector<Job>> threadSafe_completedJobs = make_shared<vector<Job>>();
    shared_ptr<condition_variable> cv = make_shared<condition_variable>();
    shared_ptr<mutex> mutex_pending = make_shared<mutex>();
    shared_ptr<mutex> mutex_completed = make_shared<mutex>();
    shared_ptr<atomic_bool> done = make_shared<atomic_bool>(false);

public:
    void submit(Job j) { jobs.push(j); };
    void start();
    ~JobScheduler ();

};

/* --------- WORK FUNCTION ----------- */
void loop_work(int id, shared_ptr<deque<Job>> threadSafe_pendingJobs, const shared_ptr<vector<Job>>& threadSafe_completedJobs, const shared_ptr<mutex>& mutex_pending, const shared_ptr<mutex>& mutex_completed, const shared_ptr<condition_variable>& cv, const shared_ptr<atomic_bool>& done);



#endif //LAB_4_INCLUDE_H

