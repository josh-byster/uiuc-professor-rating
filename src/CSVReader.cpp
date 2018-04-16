#include "CSVReader.h"
#include <fstream>
#include <iostream>
std::vector<std::vector<std::string>> CSVReader::getData() {

    std::ifstream file(filename);
    std::vector<std::vector<std::string>> rows;
    std::string line = "";
    if(file.fail()){
        std::cerr << "Error: " << strerror(errno);
    } else {
        while(getline(file,line)){
            std::cout<<line<<std::endl;
        }
    }
    

    return rows;
    
}