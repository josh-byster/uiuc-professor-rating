#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <vector>
#include <unordered_set>
#include "Course.h"
#include "CSVReader.h"
#include <unordered_map>
class DataFrame {
    public:
      DataFrame(std::string filename);
      DataFrame() {}
      std::vector<Course> getCoursesByInstructor(std::string professorName);  
      std::vector<std::string> getProfessorMatchesByName(std::string professorName, size_t limit);
    private:
      std::unordered_map<std::string,std::vector<Course>> instructorCourseMap;
      std::unordered_map<Section, std::vector<Course>> sectionMap;
      std::unordered_set<std::string> instructorNames;

};


#endif