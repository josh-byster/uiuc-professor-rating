#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Constants.h"

/**
 * Get a vector of courses from the CSV file stored in instance variable "filename'
 */
std::vector<Course> CSVReader::getCourseData() {

    std::ifstream file(filename);
    std::vector<Course> courses;
    std::string line = "";

    if(file.fail()){
        std::cerr << "Error: " << strerror(errno);
    } else {
        // iterate once because the headers are in the first line
        getline(file,line);
        while(getline(file,line)){
            // some lines are incomplete, and they thus have less commas. So we should exclude them.
            if(std::count(line.begin(), line.end(), ',') == NUM_COMMAS){
                courses.push_back(Course(line));
            }
        }
    }
    
    std::cout<<courses.size()<< " courses loaded from file."<<std::endl;
    return courses;
}