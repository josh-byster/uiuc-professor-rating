#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
#include "SemesterClass.h"
#include "Constants.h"

struct Course {
    Course(std::string row);

    SemesterClass semesterClass;
    std::string courseTitle;
    std::vector<int> gradesGiven;
    std::string instructorName;

    std::string getNextItemInLine(std::string &line);

    double getGPA() const;

    double getNumStudents() const;

    bool operator>(const Course &other) const;

    bool operator<(const Course &other) const;

};

// Comparator as https://stackoverflow.com/a/5733353/3813411
struct compareCourse {
    bool operator()(const Course &first, const Course &second) const {
        return first.semesterClass < second.semesterClass;
    }
};


#endif