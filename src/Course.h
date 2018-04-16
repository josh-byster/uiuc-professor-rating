#ifndef COURSE_H
#define COURSE_H 
#include <string>
#include <vector>
#include <iostream>
class Course {

    public:
        Course(std::string row);

    private:
        unsigned int year;
        std::string term;
        std::string subject;
        unsigned int courseNumber;
        std::string courseTitle;
        std::vector<int> gradesGiven;
        std::string instructorName;
        std::string getNextItemInLine(std::string& line);

};
#endif