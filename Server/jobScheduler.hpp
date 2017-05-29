#include <iostream>
#include <vector>
#include "job.hpp"

using namespace std;

// Creating a class named Queue.
class JobScheduler {
private:
    vector<Job> _jobList;
    vector<Job> _jobListDate;

public:
    // Constructor - set front and rear as -1.
    // We are assuming that for an empty Queue, both front and rear will be -1.
    explicit JobScheduler();

    ~JobScheduler();

    void addJob(Job job);

    int addJob(std::string jobType, int row, int col, int year = -1, int month = -1, int day = -1, int hour = -1,
               int min = -1,
               int sec = -1);

    int
    addJob(int packageId, std::string jobType, int year = -1, int month = -1, int day = -1, int hour = -1, int min = -1,
           int sec = -1);

    Job getJob();

    unsigned long getSize();

    unsigned long getDateSize();

    bool haveJob();
};
