#include "DataFrame.h"
DataFrame::DataFrame(std::string filename){
    CSVReader reader(filename);
    std::vector<Course> courseData = reader.getData();
    for(auto course : courseData){
        sectionMap[course.section].push_back(course);
        instructorCourseMap[course.instructorName].push_back(course);
        instructorNames.push_back(course.instructorName);
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