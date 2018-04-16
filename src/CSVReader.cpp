#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include "Course.h"
#include <algorithm>
#include "Constants.h"
std::vector<Course> CSVReader::getData() {

    std::ifstream file(filename);
    std::vector<Course> courses;
    std::string line = "";
    if(file.fail()){
        std::cerr << "Error: " << strerror(errno);
    } else {
        // iterate once because the headers are in the first line
        getline(file,line);
        while(getline(file,line)){
            std::cout<<std::count(line.begin(), line.end(), ',')<<std::endl;
            if(std::count(line.begin(), line.end(), ',') == NUM_COMMAS){
                courses.push_back(Course(line));
            }
        }
    }
    

    return courses;
    
}