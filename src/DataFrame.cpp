#include "DataFrame.h"

/**
 * Constructs a DataFrame given a CSV file
 * @param filename  the path to the CSV file
 */
DataFrame::DataFrame(std::string filepath){
    CSVReader reader(filepath);
    std::vector<Course> courseData = reader.getCourseData();
    for(auto course : courseData){
        semesterClassMap[course.semesterClass].push_back(course);
        instructorCourseMap[course.instructorName].push_back(course);
        instructorNames.insert(course.instructorName);
    }
}

/**
 * Get an ordered map from SemesterClass objects to courses filtered by instructor.
 * This gets a map of every course that this specific instructor has taught along with the 
 * values of the map being the courses taught by that instructor specifically.
 * 
 * @param instructorName the exactname of the instructor to query
 */
std::map<SemesterClass,std::vector<Course>> DataFrame::getSemesterClassMapByInstructor(std::string instructorName) const{
    std::map<SemesterClass,std::vector<Course>> semesterClassMap;
    std::vector<Course> courseList = instructorCourseMap.at(instructorName);
    for(Course course : courseList){
        semesterClassMap[course.semesterClass].push_back(course);
    }
    return semesterClassMap;
}

/**
 * Gets a list of instructors by search query.
 * 
 * @param instructorName the search query entered by the user (lowercase).
 * @param limit   the max amount of results that should be returned to be displayed.
 */
std::vector<std::string> DataFrame::getInstructorMatchesByName(std::string instructorName, size_t limit) const{
    std::vector<std::string> matches;
    if(limit == 0){
        return matches;
    }
    for(std::string instructor : instructorNames){
        // construct a string full of 'x' placeholders, which we will replace
        // with the lowercase version of the instructor name
        std::string instructorLowercase(instructor.size(),'x');
        std::transform(instructor.begin(),instructor.end(),instructorLowercase.begin(),::tolower);
        
        if(instructorLowercase.find(instructorName) != std::string::npos){
            matches.push_back(instructor);
            // if we hit the limit, return the vector
            if(matches.size() == limit){
                return matches;
            }
        }

    }
    return matches;
}

/**
 * Gets the GPA for the entire SemesterClass, so this is the 
 * combined (weighted) GPA of every instructor.
 * 
 * @param semesterClass the SemesterClass object that we are getting the GPA for.
 */
double DataFrame::getSemesterClassGPA(SemesterClass semesterClass) const{
    return getGPAByCourseVector(semesterClassMap.at(semesterClass));
}

/**
 * Gets the weighted GPA for a SemesterClass excluding a specific instructor.
 * Used in order to compare the GPA of an instructor to the GPA of the other instructors
 * for that specific SemesterClass.
 * 
 * @param semesterClass the SemesterClass object to retrieve courses for
 * @param excludedInstructor    the name of the instructor to exclude 
 */
double DataFrame::getGPAExcludingInstructor(SemesterClass semesterClass, std::string excludedInstructor) const {
    std::vector<Course> courseList;
    for(Course course : semesterClassMap.at(semesterClass)){
        if(course.instructorName != excludedInstructor){
            courseList.push_back(course);
        }
    }
    return getGPAByCourseVector(courseList);
}

/**
 * Gets a vector, sorted in order from easiest to most difficult, 
 * of instructors for a SemesterClass.
 * 
 * @param semesterClass the specific semesterClass object
 */
std::vector<std::pair<std::string,double>> DataFrame::getInstructorRanksForSemesterClass(SemesterClass semesterClass) const {
    std::map<std::string,std::vector<Course>> currentInstructorCourseMap;
    
    for(Course course : semesterClassMap.at(semesterClass)){
        currentInstructorCourseMap[course.instructorName].push_back(course);
    }

    // construct a map from instructors to their GPA for the specific SemesterClass
    std::map<std::string,double> instructorGPAMap;
    for(std::pair<std::string,std::vector<Course>> instructorCourseListPair : currentInstructorCourseMap){
        instructorGPAMap[instructorCourseListPair.first] = getGPAByCourseVector(instructorCourseListPair.second);
    }

    // construct a vector that contains the values of the above map but sorted by GPA
    std::vector<std::pair<std::string,double>> sortedinstructorGPAList;
    for(std::pair<std::string,double> instructorGPAPair : instructorGPAMap){
        sortedinstructorGPAList.push_back(instructorGPAPair);
    }

    // sort using the sortByGPA method, which is a custom-defined sorting method
    std::sort(sortedinstructorGPAList.begin(),sortedinstructorGPAList.end(),sortByGPA);
    return sortedinstructorGPAList;
}

/**
 * Get the rank of an instructor relative to n instructors
 * for the specific SemesterClass (1 = easiest, n = hardest).
 * Returns -1 if the instructor isn't found.
 * 
 * @param semesterClass the specific SemesterClass for which we're querying
 * @param instructorName the name of the instructor to get the rank for
 */
std::pair<int,int> DataFrame::getInstructorRankForSemesterClass(SemesterClass semesterClass, std::string instructorName) const {
    std::vector<std::pair<std::string,double>> instructorRankByGPA = getInstructorRanksForSemesterClass(semesterClass);
    int rank = -1;
    for(unsigned i = 0; i < instructorRankByGPA.size(); i++) {
        if(instructorRankByGPA[i].first == instructorName){
            rank = i+1;
        }
    }
    return std::pair<int,int>(rank,instructorRankByGPA.size());
}

/**
 * Custom strict ordering of pairs to get the GPA in descending order (highest to lowest GPA).
 */
bool sortByGPA(const std::pair<std::string,double>& a, const std::pair<std::string,double>& b){
    return (a.second > b.second);
}

/**
 * Get the weighted GPA from a course vector 
 * (sections with higher amounts of students get a higher respectiveweight).
 * 
 * @param gpaVector the vector of courses to compute the GPA from
 */
double DataFrame::getGPAByCourseVector(std::vector<Course> gpaVector) const{
    double gpaStudents = 0;
    int totalStudents = 0;
    for(const Course& course : gpaVector){
        gpaStudents+=course.getGPA()*course.getNumStudents();
        totalStudents+=course.getNumStudents();
    }
    if(totalStudents == 0){
        return 0;
    }
    return gpaStudents / totalStudents;
}


/**
 * Returns an unordered set of instructors by reference, since it
 * is only used in testing. 
 */
const std::unordered_set<std::string>& DataFrame::getAllInstructorNames() const{
    return instructorNames;
}

/**
 * Returns the map from instructors to all the courses they taught.
 * Returns a constant refrerence since it's used only in testing.
 */
const std::unordered_map<std::string,std::vector<Course>>& DataFrame::getInstructorCourseMap() const{
    return instructorCourseMap;
}

/**
 * Returns the map from SemesterClasses to all the courses/instructors that taught
 * that class that semester.
 * Returns a constant reference because it's only used in testing.
 */
const std::unordered_map<SemesterClass,std::vector<Course>>& DataFrame::getSemesterClassMap() const{
    return semesterClassMap;
}