#include <iostream>
#include <string>
#include <ctime>

using namespace std;

enum JobType {
    PICK_UP, PUT_IN
};

// Creating a class named Queue.
class Job {
private:
    int _id;
    int _packageId;
    int _row;
    int _col;
    bool _haveTime;
    bool _haveLocation;
    std::time_t _time;
    JobType _jobType;
public:

    static int jobCount;

    // Constructor - set front and rear as -1.
    // We are assuming that for an empty Queue, both front and rear will be -1.
    Job(std::string jobType, int row, int col, int year = -1, int month = -1, int day = -1, int hour = -1,
        int min = -1, int sec = -1);

    Job(int packageId, std::string jobType, int year = -1, int month = -1, int day = -1, int hour = -1, int min = -1,
        int sec = -1);

    bool haveTime();

    bool haveLocation();

    int getId();

    int getRow();

    int getCol();

    int getPackageId();

    std::string getJobType();

    std::tm *getTimeInfo();

    std::time_t getTime();

    friend std::ostream &operator<<(std::ostream &os, Job &job);

    ~Job();

};

/*
 *  Helper
 */

std::time_t make_time(int year, int month, int day, int hour = -1, int min = -1, int sec = -1);