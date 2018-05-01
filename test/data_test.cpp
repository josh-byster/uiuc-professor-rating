#include "catch.hpp"
#include "../src/Course.h"
#include "../src/CSVReader.h"
#include "../src/DataFrame.h"
#include "../src/SemesterClass.h"
#include "../src/Constants.h"
#include <cmath>

DataFrame testFrame;
void setup(){
    testFrame = DataFrame(FILE_PATH);
}
bool isWithinTolerance(double a, double b){
    return std::abs(a-b) < EPSILON;
}
TEST_CASE("Simple test of getting GPA"){
    setup();
    SemesterClass s(2012,"Fall","BIOE",504);
    REQUIRE(isWithinTolerance(testFrame.getSemesterClassGPA(s), 3.64));
}

TEST_CASE("Test that every professor has some valid name"){
    for(const std::string& name : testFrame.getAllInstructorNames()){
        REQUIRE(name.find(", ") != std::string::npos);
    }
}

TEST_CASE("Test that every course in the semester class map is correctly set up"){
    for(const std::pair<SemesterClass,std::vector<Course>>& classPair : testFrame.getSemesterClassMap()){
        for(const Course& course : classPair.second){
            REQUIRE(classPair.first == course.semesterClass);
        }
    }
}

TEST_CASE("Test that there are the same amount of courses in both maps"){
    int semesterClassMapSize = 0;
    int instructorMapSize = 0;
    for(const std::pair<SemesterClass,std::vector<Course>>& classPair : testFrame.getSemesterClassMap()){
        semesterClassMapSize+=classPair.second.size();
    }
    for(const std::pair<std::string,std::vector<Course>>& instructorPair : testFrame.getInstructorCourseMap()){
        instructorMapSize+=instructorPair.second.size();
    }
    REQUIRE(semesterClassMapSize == instructorMapSize);
}

TEST_CASE("Spot check for course number"){
    SemesterClass test(2012,"Fall","BTW",250);
    REQUIRE(20 == testFrame.getSemesterClassMap().at(test).size());
}

TEST_CASE("Spot check GPA by instructor"){
   SemesterClass test(2012,"Fall","BTW",250);
   std::string exampleNames[3] = {"Wetter, Timothy S","Kelly, Daniel","Vredenburg, Jason"};
   double correspondingGPA[3] = {3.565,3.462,3.5491};
   for(int i = 0; i < 3; i++){
       double computedGPA = testFrame.getGPAByCourseVector(testFrame.getSemesterClassMapByInstructor(exampleNames[i]).at(test)); 
       REQUIRE(isWithinTolerance(computedGPA,correspondingGPA[i]));
   }
   
}

TEST_CASE("Check that the instructor search results are limited correctly"){
    for(int i = 0; i < 10; i++){
        std::vector<std::string> matches = testFrame.getProfessorMatchesByName("smith", i);
        REQUIRE(matches.size() == i);
    }
}

TEST_CASE("Check that the instructor search results are actually contain the string"){
    for(int i = 1; i < 10; i++){
        std::vector<std::string> matches = testFrame.getProfessorMatchesByName("smith", i);
        for(const std::string& match : matches){
            // Checking everything but first letter since capitalization may be different
            REQUIRE(match.find("mith") != std::string::npos);
        }
    }
}

TEST_CASE("Check that for one instructor for a course, rank is correct"){
    SemesterClass discreteStructures(2017,"Fall","CS",173);
    std::pair<int,int> rank = testFrame.getInstructorRankForSemesterClass(discreteStructures,"Fleck, Margaret M");
    REQUIRE(rank.first == 1);
    REQUIRE(rank.second == 1);
}

TEST_CASE("Check that for every course, every professor falls in the rank"){
    for(const std::pair<SemesterClass,std::vector<Course>>& classPair : testFrame.getSemesterClassMap()){
        for(const Course& course : classPair.second){
            std::pair<int,int> rank = testFrame.getInstructorRankForSemesterClass(classPair.first,course.instructorName);
            REQUIRE(rank.first > 0);
            REQUIRE(rank.second <= classPair.second.size());
        }

    }
}

TEST_CASE("Check that instructor course map is correct"){
    // Note that even though this is a triple for loop, it's still O(n) on
    // the number of lines in the CSV file
    for(const std::string& name : testFrame.getAllInstructorNames()){
        for(const std::pair<SemesterClass,std::vector<Course>>& classPair 
        : testFrame.getSemesterClassMapByInstructor(name)){
            for(const Course& course : classPair.second){
                REQUIRE(name == course.instructorName);
                REQUIRE(classPair.first == course.semesterClass);
            }
        }
    }
}

TEST_CASE("Edge case when calculating GPA excluding instructor & no other instructors are teaching"){
    SemesterClass discreteStructures(2015,"Fall","CS",173);
    REQUIRE(0 == testFrame.getGPAExcludingInstructor(discreteStructures,"Fleck, Margaret M"));
}