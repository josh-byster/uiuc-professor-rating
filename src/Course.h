#ifndef COURSE_H
#define COURSE_H 
#include <string>
#include <vector>
#include <iostream>
#include "Section.h"
struct Course {
        Course(std::string row);
        Section section;
        std::string courseTitle;
        std::vector<int> gradesGiven;
        std::string instructorName;
        std::string getNextItemInLine(std::string& line);

};
#endif