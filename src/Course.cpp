#include "Course.h"

/**
 * Constructs a course from a row in the CSV file 
 */
Course::Course(std::string row) {

    unsigned int year = std::stoi(getNextItemInLine(row));
    std::string term = getNextItemInLine(row);

    // get one extra line since it's YearTerm and it's unnecessary 
    getNextItemInLine(row);
    std::string subject = getNextItemInLine(row);

    unsigned int courseNumber = std::stoi(getNextItemInLine(row));

    semesterClass = SemesterClass(year, term, subject, courseNumber);
    courseTitle = getNextItemInLine(row);

    for (int i = 0; i < NUM_GRADES_IN_ARR; i++) {
        gradesGiven.push_back(std::stoi(getNextItemInLine(row)));
    }

    instructorName = getNextItemInLine(row);
}

/**
 * Get the next entry for the current row in the CSV file.
 * Does all the specific formatting.
 */
std::string Course::getNextItemInLine(std::string &row) {
    std::string item;
    if (row.at(0) == '"') {
        // we need to ignore commas since it's a string (instructor or course name) that may have commas
        row.erase(0, 1);
        item = row.substr(0, row.find('\"'));
        row.erase(0, row.find('\"') + 1);
        // we may need to remove an extra comma if the course name has a comma
        if (row.length() > 0 && row.at(0) == ',') {
            row.erase(0, 1);
        }
    } else {
        item = row.substr(0, row.find(','));
        row.erase(0, row.find(',') + 1);
    }
    return item;
}

/**
 * Get the GPA for this course. Computes this as a weighted average.
 */
double Course::getGPA() const {
    double GPAStudents = 0;
    int studentCount = 0;

    for (int i = 0; i < NUM_GRADES_IN_ARR - 1; i++) {
        GPAStudents += GRADES_TO_GPA[i] * gradesGiven[i];
        studentCount += gradesGiven[i];
    }

    return GPAStudents / studentCount;
}

/**
 * Get the number of students in a course.
 */
double Course::getNumStudents() const {
    int studentCount = 0;

    for (int i = 0; i < NUM_GRADES_IN_ARR - 1; i++) {
        studentCount += gradesGiven[i];
    }

    return studentCount;
}

bool Course::operator>(const Course &other) const {
    return this->semesterClass > other.semesterClass;
}

bool Course::operator<(const Course &other) const {
    return this->semesterClass < other.semesterClass;
}