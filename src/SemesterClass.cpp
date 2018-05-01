#include "SemesterClass.h"


bool SemesterClass::operator==(const SemesterClass &other) const {
    return (year == other.year && term == other.term
            && subject == other.subject && courseNumber == other.courseNumber);
}

bool SemesterClass::operator!=(const SemesterClass &other) const {
    return !(*this == other);
}

bool SemesterClass::operator>(const SemesterClass &other) const {
    if (this->year > other.year) {
        return true;
    }
    return this->subject > other.subject
           || (this->subject == other.subject
               && this->courseNumber > other.courseNumber);
}

/**
 * Operator< overload, such that if this < other, this,
 * when sorted chronologically and alphabetically, should occur before other.
 * @param other the other SemesterClass
 */
bool SemesterClass::operator<(const SemesterClass &other) const {
    if (*this == other) {
        return false;
    }
    if (this->year < other.year) {
        return true;
    }
    if (this->year > other.year) {
        return false;
    }
    if (this->year == other.year) {
        if (this->term < other.term) {
            return true;
        }
        if (this->term > other.term) {
            return false;
        }
    }
    if (this->year == other.year && this->term == other.term) {
        if (this->subject < other.subject) {
            return true;
        }
        if (this->subject > other.subject) {
            return false;
        }
        if (this->subject == other.subject) {
            return this->courseNumber < other.courseNumber;
        }
    }
    return false;
}

