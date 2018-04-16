#include "Course.h"

Course::Course(std::string row){
    year = std::stoi(getNextItemInLine(row));
    term = getNextItemInLine(row);
    subject = getNextItemInLine(row);
    // get one extra line since it's YearTerm and it's unnecessary 
    getNextItemInLine(row);
    courseNumber = std::stoi(getNextItemInLine(row));
    courseTitle = getNextItemInLine(row);

    for(int i = 0; i < 14; i++){
        gradesGiven.push_back(std::stoi(getNextItemInLine(row)));
    }

    instructorName = getNextItemInLine(row);
    std::cout<<instructorName<<std::endl;

}

std::string Course::getNextItemInLine(std::string& row){
    std::string item;
    if(row.at(0) == '"'){
        // we need to ignore commas since it's a string (instructor or course name) that may have commas
        row.erase(0,1);
        item = row.substr(0,row.find("\""));
        std::cout<<item<<std::endl;
        row.erase(0,row.find("\"")+1);
        // we may need to remove an extra comma
        if(row.length() > 0 && row.at(0) == ','){
           row.erase(0,1); 
        }
    } else {
        item = row.substr(0,row.find(","));
        row.erase(0,row.find(",")+1);
    }
    return item;
}