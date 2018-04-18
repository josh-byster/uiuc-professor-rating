#include "DataFrame.h"


DataFrame::DataFrame(std::string filename){
    CSVReader reader(filename);
    std::vector<Course> courseData = reader.getData();
    for(auto course : courseData){
        sectionMap[course.section].push_back(course);
        instructorCourseMap[course.instructorName].push_back(course);
        instructorNames.insert(course.instructorName);
    }
    
}

std::map<Section,std::vector<Course>> DataFrame::getSectionMapByInstructor(std::string professorName) const{
    std::map<Section,std::vector<Course>> sectionMap;
    std::vector<Course> courseList = instructorCourseMap.at(professorName);
    for(Course course : courseList){
        sectionMap[course.section].push_back(course);
    }
    return sectionMap;
}

std::vector<std::string> DataFrame::getProfessorMatchesByName(std::string professorName, size_t limit) const{
    std::vector<std::string> matches;
    for(std::string instructor : instructorNames){
        std::string instructorLowercase(instructor.size(),'x');
        std::transform(instructor.begin(),instructor.end(),instructorLowercase.begin(),::tolower);
        if(instructorLowercase.find(professorName) != std::string::npos){
            matches.push_back(instructor);
            if(matches.size() == limit){
                return matches;
            }
        }
    }
    return matches;
}

double DataFrame::getSectionGPA(Section section) const{
    double gpaStudents = 0;
    int totalStudents = 0;
    for(const Course& course : sectionMap.at(section)){
        gpaStudents+=course.getGPA()*course.getNumStudents();
        totalStudents+=course.getNumStudents();
    }
    return gpaStudents / totalStudents;
}