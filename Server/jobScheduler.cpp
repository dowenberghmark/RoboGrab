#include "jobScheduler.hpp"

bool comp(Job a, Job b) {
    return difftime(a.getTime(), b.getTime()) < 0;
}

JobScheduler::JobScheduler() {

}

JobScheduler::~JobScheduler() {

}

void JobScheduler::addJob(Job job) {

    if (job.haveTime()) {
        if (this->_jobListDate.size() == 0) {
            this->_jobListDate.push_back(job);
            return;
        }

        if (difftime(job.getTime(), this->_jobListDate.back().getTime()) > 0) {
            this->_jobListDate.push_back(job);
            return;
        }

        if (difftime(this->_jobListDate.front().getTime(), job.getTime()) > 0) {
            this->_jobListDate.insert(this->_jobListDate.begin(), job);
            return;
        }

        std::vector<Job>::iterator it = std::lower_bound(this->_jobListDate.begin(), this->_jobListDate.end(), job,
                                                         comp); // find proper position in descending order
        this->_jobListDate.insert(it, job); // insert before iterator it

        return;


    }

    this->_jobList.push_back(job);

}


Job JobScheduler::getJob() {

    if (this->_jobListDate.size() > 0) {
        Job jobDate = this->_jobListDate.front();
        std::time_t now;

        time(&now);
        if (difftime(now, jobDate.getTime()) >= 0) {
            this->_jobListDate.erase(this->_jobListDate.begin());
            return jobDate;
        }

    }

    Job job = this->_jobList.front();
    this->_jobList.erase(this->_jobList.begin());

    return job;
}

int
JobScheduler::addJob(std::string jobType, int row, int col, int year, int month, int day, int hour,
                     int min,
                     int sec) {
    if (row < 0 || col < 0) {
        return -1;
    }
    Job job(jobType, row, col, year, month, day, hour, min, sec);
    this->addJob(job);
    return job.getId();
}


int JobScheduler::addJob(int packageId, std::string jobType, int year, int month, int day, int hour,
                         int min,
                         int sec) {
    if (packageId < 0) {
        return -1;
    }
    Job job(packageId, jobType, year, month, day, hour, min, sec);
    this->addJob(job);
    return job.getId();
}


unsigned long JobScheduler::getSize() {
    return this->_jobList.size();
}

unsigned long JobScheduler::getDateSize() {
    return this->_jobListDate.size();
}

bool JobScheduler::haveJob() {

    if ((this->getDateSize() <= 0) && (this->getSize() <= 0))
        return false;

    if (this->getSize() > 0)
        return true;

    if (this->_jobListDate.size() > 0) {
        Job jobDate = this->_jobListDate.front();
        std::time_t now;

        time(&now);
        if (difftime(now, jobDate.getTime()) <= 0) {
            return false;
        }

    }

    return true;

}


