#ifndef COURSE_H
#define COURSE_H 
#include <string>
#include <vector>
#include <iostream>
#include "Section.h"
class Course {

    public:
        Course(std::string row);
        unsigned int getYear();
        std::string getTerm();
        std::string getSubject();
    private:
        Section section;
        std::string courseTitle;
        std::vector<int> gradesGiven;
        std::string instructorName;
        std::string getNextItemInLine(std::string& line);

};
#endif