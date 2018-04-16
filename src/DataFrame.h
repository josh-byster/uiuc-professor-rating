#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <vector>
#include "Course.h"
#include "CSVReader.h"
#include <unordered_map>
class DataFrame {
    public:
      DataFrame(std::string filename);
      std::vector<Course> getCoursesByProfessor(std::string professorName);  
      
    private:
      std::unordered_map<std::string,std::vector<Course>> instructorCourseMap;
      std::unordered_map<Section, std::vector<Course>> sectionMap;
      std::vector<std::string> instructorNames;

};


#endif