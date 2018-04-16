#include "DataFrame.h"


DataFrame::DataFrame(std::string filename){
    CSVReader reader(filename);
    std::vector<Course> courseData = reader.getData();
    for(auto course : courseData){
        sectionMap[course.section].push_back(course);
        instructorCourseMap[course.instructorName].push_back(course);
        instructorNames.insert(course.instructorName);
    }

    // std::vector<Course> testData = instructorCourseMap["Hecht, Gary W"];
    // for(Course c : testData){
    //     std::cout<<c.courseTitle<<std::endl;
    // } 
    std::cout<<"TRYing hash: "<<std::hash<Section>()(Section(2017, "Fall", "MATH", 241))<<std::endl;
    std::vector<Course> testData = sectionMap[Section(2017, "Fall", "MATH", 241)];
    for(Course c : testData){
        std::cout<<c.instructorName<<" GPA: "<<c.getGPA()<<std::endl;
    } 
}

std::vector<Course> DataFrame::getCoursesByInstructor(std::string professorName){
    return instructorCourseMap[professorName];
}

std::vector<std::string> DataFrame::getProfessorMatchesByName(std::string professorName, size_t limit){
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

double DataFrame::getSectionGPA(Section section){
    double gpaStudents = 0;
    int totalStudents = 0;
    for(const Course& course : sectionMap[section]){
        gpaStudents+=course.getGPA()*course.getNumStudents();
        totalStudents+=course.getNumStudents();
    }
    return gpaStudents / totalStudents;
}