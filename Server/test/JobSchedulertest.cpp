//
// Created by Sam Hoang on 5/29/17.
//
#include "jobScheduler.hpp"

//int Job::jobCount = 0;


int Job::jobCount = 0;

int main() {


    JobScheduler jobScheduler;

    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 12, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 13, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 11, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 14, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 10, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 15, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 9, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 16, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 8, 35);

    jobScheduler.addJob(1, "PICK_UP", 2016, 5, 30, 8, 35);
    jobScheduler.addJob(2, "PICK_UP", 2016, 5, 30, 8, 35);
    jobScheduler.addJob(3, "PICK_UP", 2016, 5, 30, 8, 35);
    jobScheduler.addJob(4, "PICK_UP", 2016, 5, 30, 8, 35);


    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 5, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 20, 35);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 8, 36);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 7, 36);
    jobScheduler.addJob("PUT_IN", 2, 4, 2016, 5, 30, 11, 36);


    for (; jobScheduler.haveJob();) {
        unsigned long size = jobScheduler.getSize();
        unsigned long sizeDate = jobScheduler.getDateSize();
        Job job = jobScheduler.getJob();

        std::cout << job;
    }


}