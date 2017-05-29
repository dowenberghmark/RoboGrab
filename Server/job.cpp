#include "job.hpp"

std::time_t make_time(int year, int month, int day, int hour, int min, int sec) {

    std::tm tm = {0};
    tm.tm_year = year - 1900; // years count from 1900
    tm.tm_mon = month - 1;    // months count from January=0
    tm.tm_mday = day;         // days count from 1

    if (hour >= 0) {
        tm.tm_hour = hour;
    }

    if (min >= 0) {
        tm.tm_min = min;
    }

    if (sec >= 0) {
        tm.tm_sec = sec;
    }

    std::time_t time = std::mktime(&tm);
    return time;
}


Job::~Job() {

}

int Job::getId() {
    return this->_id;
}

Job::Job(std::string jobType, int row, int col, int year, int month, int day, int hour,
         int min, int sec) : _row(row), _col(col), _packageId(-1) {

    this->_haveTime = false;

    if (year >= 0) {
        this->_haveTime = true;
            this->_time = make_time(year, month, day, hour,
                                    min, sec);
    }


    this->jobCount++;
    this->_haveLocation = true;
    this->_id = Job::jobCount;
    if (!jobType.compare("PUT-IN")) {
        this->_jobType = PUT_IN;
    } else {
        this->_jobType = PICK_UP;
    }
}

Job::Job(int packageId, std::string jobType, int year, int month, int day, int hour, int min,
         int sec) : _row(-1), _col(-1), _packageId(packageId) {


    this->_haveTime = false;

    if (year >= 0) {
        this->_haveTime = true;
        this->_time = make_time(year, month, day, hour,
                                min, sec);
    }

    this->jobCount++;
    this->_haveLocation = false;
    this->_id = Job::jobCount;
    if (!jobType.compare("PUT-IN")) {
        this->_jobType = PUT_IN;
    } else {
        this->_jobType = PICK_UP;
    }
}

int Job::getRow() {
    return this->_row;
}

int Job::getCol() {
    return this->_col;
}

int Job::getPackageId() {
    return _packageId;
}

std::string Job::getJobType() {
    if (this->_jobType == PUT_IN) {
        return "PUT-IN";
    } else {
        return "PICK-UP";
    }
}

std::ostream &operator<<(std::ostream &os, Job &job) {

    os << job.getId() << " ";

    if (job.haveTime()) {
        os << asctime(job.getTimeInfo());
    }

    os << "\t\t\t" << job.getJobType();

    os << " Package(";

    if (!job.haveLocation()) {
        os << job.getPackageId() << ") \n";
    } else {
        os << job.getRow() << "," << job.getCol() << ") \n";
    }

    return os;
}

bool Job::haveTime() {
    return this->_haveTime;
}

bool Job::haveLocation() {
    return this->_haveLocation;
}

std::tm *Job::getTimeInfo() {
    std::time_t time = this->_time;

    std::tm *timeinfo = localtime(&time);

    return timeinfo;
}

std::time_t Job::getTime() {
    return this->_time;
}
