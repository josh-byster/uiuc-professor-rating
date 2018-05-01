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

//---------------------------SECTION--------------------------
//Spot testing
TEST_CASE("Simple test of getting GPA"){
    setup();
    SemesterClass s(2012,"Fall","BIOE",504);
    REQUIRE(isWithinTolerance(testFrame.getSemesterClassGPA(s), 3.64));
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

//---------------------------SECTION--------------------------
//Testing for consistency in dataframe setup
TEST_CASE("Test that every instructor has some valid name"){
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

//---------------------------SECTION--------------------------
//Testing search functionality
TEST_CASE("Check that the instructor search results are limited correctly"){
    for(int i = 0; i < 10; i++){
        std::vector<std::string> matches = testFrame.getInstructorMatchesByName("smith", i);
        REQUIRE(matches.size() == i);
    }
}

TEST_CASE("Check that the instructor search results are actually contain the string"){
    for(int i = 1; i < 10; i++){
        std::vector<std::string> matches = testFrame.getInstructorMatchesByName("smith", i);
        for(const std::string& match : matches){
            // Checking everything but first letter since capitalization may be different
            REQUIRE(match.find("mith") != std::string::npos);
        }
    }
}

//---------------------------SECTION--------------------------
//Testing rankings
TEST_CASE("Check that for one instructor for a course, rank is correct"){
    SemesterClass discreteStructures(2017,"Fall","CS",173);
    std::pair<int,int> rank = testFrame.getInstructorRankForSemesterClass(discreteStructures,"Fleck, Margaret M");
    REQUIRE(rank.first == 1);
    REQUIRE(rank.second == 1);
}

TEST_CASE("Check that for every course, every instructor falls in the rank"){
    for(const std::pair<SemesterClass,std::vector<Course>>& classPair : testFrame.getSemesterClassMap()){
        for(const Course& course : classPair.second){
            std::pair<int,int> rank = testFrame.getInstructorRankForSemesterClass(classPair.first,course.instructorName);
            REQUIRE(rank.first > 0);
            REQUIRE(rank.second <= classPair.second.size());
        }

    }
}

TEST_CASE("Test that the ranks are correctly ordered"){
    for(const std::pair<SemesterClass,std::vector<Course>>& classPair : testFrame.getSemesterClassMap()){
        std::vector<std::pair<std::string,double>> rankings = testFrame.getInstructorRanksForSemesterClass(classPair.first);
        for(int i = 1; i < rankings.size(); i++){
            REQUIRE(rankings[i-1].second >= rankings[i].second);
        }
    }
}

//---------------------------SECTION--------------------------
// Testing GPA excluding instructor
TEST_CASE("Edge case when calculating GPA excluding instructor & no other instructors are teaching"){
    SemesterClass discreteStructures(2015,"Fall","CS",173);
    REQUIRE(0 == testFrame.getGPAExcludingInstructor(discreteStructures,"Fleck, Margaret M"));
}

TEST_CASE("Test GPA excluding instructor is correct"){
    const std::unordered_map<SemesterClass,std::vector<Course>>& semesterClassMap = testFrame.getSemesterClassMap();
    SemesterClass financialPlanning(2017,"Fall","ACE",240);
    double gpaExcludingCraig = testFrame.getGPAExcludingInstructor(financialPlanning,"Lemoine, Craig");
    double otherInstructorGPA = semesterClassMap.at(financialPlanning)[0].getGPA();
    if(semesterClassMap.at(financialPlanning)[0].instructorName == "Lemoine, Craig"){
        otherInstructorGPA = semesterClassMap.at(financialPlanning)[1].getGPA();
    }
    REQUIRE(isWithinTolerance(gpaExcludingCraig,otherInstructorGPA));
}



/**
 * ---------------------------SECTION--------------------------
 * The following tests are extremely important, as not having a strict-ordering
 * relation defined will cause errors in comptuation.
 */
TEST_CASE("Test SemesterClass ordering #1"){
    SemesterClass first(2016,"Fall","ANSC",250);
    SemesterClass second(2017,"Fall","ANSC",250);
    REQUIRE(first < second);
}

TEST_CASE("Test SemesterClass ordering #2"){
    SemesterClass first(2017,"Spring","ANSC",250);
    SemesterClass second(2017,"Fall","ANSC",250);
    REQUIRE(first < second);
}

TEST_CASE("Test SemesterClass ordering #3"){
    SemesterClass first(2017,"Fall","ANSC",250);
    SemesterClass second(2017,"Fall","ANSC",251);
    REQUIRE(first < second);
}

TEST_CASE("Test SemesterClass ordering #4"){
    SemesterClass first(2017,"Fall","ANSC",250);
    SemesterClass second(2017,"Fall","BTW",250);
    REQUIRE(first < second);
}

TEST_CASE("GPA is within a correct range for all courses"){
    for(const std::pair<SemesterClass,std::vector<Course>>& classPair : testFrame.getSemesterClassMap()){
        for(const Course& course : classPair.second){
            REQUIRE(course.getGPA() > 0);
            REQUIRE(course.getGPA() <= 4.0);
        }
    }
}

TEST_CASE("Test SemesterClass equality"){
    int assertions = 0;
    int limit = 30000;
    for(const std::pair<SemesterClass,std::vector<Course>>& firstClass : testFrame.getSemesterClassMap()){
        for(const std::pair<SemesterClass,std::vector<Course>>& secondClass : testFrame.getSemesterClassMap()){
            // Checking if-and-only-if conditions.
            // !(a < b) && !(b < a) iff a == b
            // is the check for the map's strict-ordering 
            if(firstClass.first == secondClass.first){
                REQUIRE(!(firstClass.first < secondClass.first));
                REQUIRE(!(secondClass.first < firstClass.first));
                assertions+=2;
            } else {
                bool isDifferent = !(firstClass.first < secondClass.first) 
                || !(secondClass.first < firstClass.first);
                REQUIRE(isDifferent);
                assertions+=1;
            }
        }
        if(assertions >= limit){
            break;
        }
    }
}
