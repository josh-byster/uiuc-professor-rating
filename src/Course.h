#ifndef COURSE_H
#define COURSE_H 
#include <string>
#include <vector>
#include <iostream>
#include "Section.h"
#include "Constants.h"
struct Course {
        Course(std::string row);
        Section section;
        std::string courseTitle;
        std::vector<int> gradesGiven;
        std::string instructorName;
        std::string getNextItemInLine(std::string& line);
        double getGPA();

};
#endif