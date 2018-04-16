#include "CSVReader.h"
#include <fstream>

std::vector<std::vector<std::string>> CSVReader::getData() {

    std::ifstream file(filename);

    std::vector<std::vector<std::string>> rows;
    std::string line = "";
    
    while(getline(file,line)){

    }
}