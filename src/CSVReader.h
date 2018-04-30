//Note: this functionality is based loosely on the following 
//tutorial: http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <iostream>
#include <vector>
#include "Course.h"

class CSVReader {
    public:
        CSVReader(std::string filename) : filename(filename) { };
        std::vector<Course> getCourseData();
    private:
        std::string filename;  
};

#endif