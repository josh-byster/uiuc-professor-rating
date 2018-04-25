#include "DataFrame.h"


DataFrame::DataFrame(std::string filename){
    CSVReader reader(filename);
    std::vector<Course> courseData = reader.getData();
    for(auto course : courseData){
        semesterClassMap[course.semesterClass].push_back(course);
        instructorCourseMap[course.instructorName].push_back(course);
        instructorNames.insert(course.instructorName);
    }
    
}

std::map<SemesterClass,std::vector<Course>> DataFrame::getSemesterClassMapByInstructor(std::string professorName) const{
    std::map<SemesterClass,std::vector<Course>> semesterClassMap;
    std::vector<Course> courseList = instructorCourseMap.at(professorName);
    for(Course course : courseList){
        semesterClassMap[course.semesterClass].push_back(course);
    }
    return semesterClassMap;
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

double DataFrame::getSemesterClassGPA(SemesterClass semesterClass) const{
    return getGPAByCourseVector(semesterClassMap.at(semesterClass));
}

double DataFrame::getGPAExcludingInstructor(SemesterClass semesterClass, std::string excludedInstructor) const {
    std::vector<Course> courseList;
    for(Course course : semesterClassMap.at(semesterClass)){
        if(course.instructorName != excludedInstructor){
            courseList.push_back(course);
        }
    }
    return getGPAByCourseVector(courseList);
}
std::vector<std::pair<std::string,double>> DataFrame::getInstructorRanksForSemesterClass(SemesterClass semesterClass) const {
    std::map<std::string,std::vector<Course>> currentInstructorCourseMap;
    for(Course course : semesterClassMap.at(semesterClass)){
        currentInstructorCourseMap[course.instructorName].push_back(course);
    }
    std::map<std::string,double> instructorGPAMap;
    for(std::pair<std::string,std::vector<Course>> instructorCourseListPair : currentInstructorCourseMap){
        instructorGPAMap[instructorCourseListPair.first] = getGPAByCourseVector(instructorCourseListPair.second);
    }
    std::vector<std::pair<std::string,double>> sortedProfessorGPAList;
    for(std::pair<std::string,double> instructorGPAPair : instructorGPAMap){
        sortedProfessorGPAList.push_back(instructorGPAPair);
    }
    std::sort(sortedProfessorGPAList.begin(),sortedProfessorGPAList.end(),sortByGPA);
    return sortedProfessorGPAList;
}
bool sortByGPA(const std::pair<std::string,double>& a, const std::pair<std::string,double>& b){
    return(a.second < b.second);
}
double DataFrame::getGPAByCourseVector(std::vector<Course> gpaVector) const{
    double gpaStudents = 0;
    int totalStudents = 0;
    for(const Course& course : gpaVector){
        gpaStudents+=course.getGPA()*course.getNumStudents();
        totalStudents+=course.getNumStudents();
    }
    if(totalStudents == 0){
        return 0;
    }
    return gpaStudents / totalStudents;
}