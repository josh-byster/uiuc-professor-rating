#include "Course.h"

Course::Course(std::string row){
    unsigned int year = std::stoi(getNextItemInLine(row));
    std::string term = getNextItemInLine(row);
    getNextItemInLine(row);
    std::string subject = getNextItemInLine(row);
    // get one extra line since it's YearTerm and it's unnecessary 
    
    unsigned int courseNumber = std::stoi(getNextItemInLine(row));
    
    semesterClass = SemesterClass(year,term,subject,courseNumber);
    courseTitle = getNextItemInLine(row);
    // std::cout<<"YEAR: "<<year<< " TERM: "<<term<< " SUBJECT: "<<subject<<"CNUMBER: "<<courseNumber<<std::endl;
    // std::cout<<std::hash<SemesterClass>()(semesterClass)<<std::endl;
    for(int i = 0; i < 14; i++){
        gradesGiven.push_back(std::stoi(getNextItemInLine(row)));
    }

    instructorName = getNextItemInLine(row);

}

std::string Course::getNextItemInLine(std::string& row){
    std::string item;
    if(row.at(0) == '"'){
        // we need to ignore commas since it's a string (instructor or course name) that may have commas
        row.erase(0,1);
        item = row.substr(0,row.find("\""));
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

double Course::getGPA() const{
    double qualityPoints = 0;
    int studentCount = 0;

    for(int i = 0; i < 13; i++){
        qualityPoints+= GRADES_TO_GPA[i] * gradesGiven[i];
        studentCount += gradesGiven[i];
    }

    return qualityPoints / studentCount;
}

double Course::getNumStudents() const{
    int studentCount = 0;

    for(int i = 0; i < 13; i++){
        studentCount += gradesGiven[i];
    }

    return studentCount;
}