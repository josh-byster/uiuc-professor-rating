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
      DataFrame(std::string filepath);
      DataFrame() {}
      std::map<SemesterClass,std::vector<Course>> getSemesterClassMapByInstructor(std::string professorName) const;  
      std::vector<std::string> getProfessorMatchesByName(std::string professorName, size_t limit) const;
      double getSemesterClassGPA(SemesterClass semesterClass) const;
      double getGPAByCourseVector(std::vector<Course> gpaVector) const;
      double getGPAExcludingInstructor(SemesterClass semesterClass, std::string excludedInstructor) const;
      std::vector<std::pair<std::string,double>> getInstructorRanksForSemesterClass(SemesterClass semesterClass) const;
      std::pair<int,int> getInstructorRankForSemesterClass(SemesterClass semesterClass, std::string professorName) const;
      const std::unordered_set<std::string>& getAllInstructorNames() const;
      const std::unordered_map<std::string,std::vector<Course>>& getInstructorCourseMap() const;
      const std::unordered_map<SemesterClass,std::vector<Course>>& getSemesterClassMap() const;
    private:
      std::unordered_map<std::string,std::vector<Course>> instructorCourseMap;
      std::unordered_map<SemesterClass, std::vector<Course>> semesterClassMap;
      std::unordered_set<std::string> instructorNames;

};

bool sortByGPA(const std::pair<std::string,double>& a, const std::pair<std::string,double>& b);


#endif