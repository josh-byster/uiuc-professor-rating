#ifndef DATAFRAME_H
#define DATAFRAME_H
#include <vector>
#include <unordered_set>
#include <algorithm>
#include "Course.h"
#include "CSVReader.h"
#include <unordered_map>
#include <map>
class DataFrame {
    public:
      DataFrame(std::string filename);
      DataFrame() {}
      std::map<Section,std::vector<Course>> getSectionMapByInstructor(std::string professorName) const;  
      std::vector<std::string> getProfessorMatchesByName(std::string professorName, size_t limit) const;
      double getSectionGPA(Section section) const;
    private:
      std::unordered_map<std::string,std::vector<Course>> instructorCourseMap;
      std::unordered_map<Section, std::vector<Course>> sectionMap;
      std::unordered_set<std::string> instructorNames;

};


#endif