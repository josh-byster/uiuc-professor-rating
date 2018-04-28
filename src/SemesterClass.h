#ifndef SEMESTERCLASS_H
#define SEMESTERCLASS_H
#include <string>

struct SemesterClass {
    unsigned int year;
    std::string term;
    std::string subject;
    unsigned int courseNumber;
    SemesterClass() {}
    SemesterClass(unsigned int year, std::string term, std::string subject, unsigned int courseNumber) : year(year), term(term), subject(subject), courseNumber(courseNumber) {}
    bool operator==(const SemesterClass &other) const {
        return (year == other.year && term == other.term 
        && subject == other.subject && courseNumber == other.courseNumber);
    }
    bool operator!=(const SemesterClass &other) const {
        return !(*this == other);
    }
    bool operator>(const SemesterClass &other) const { // greater will be newer (so if this > other, "this" occured after other)
        if(this->year > other.year){
          return true;
        }
        if(this->year == other.year && this->term == "Fall" && other.term == "Spring"){
          return true;
        }
        return this->subject > other.subject || (this->subject == other.subject && this->courseNumber > other.courseNumber);
    }
    bool operator<(const SemesterClass &other) const {
        if(this->year < other.year){
          return true;
        }
        if(this->year == other.year && this->term == "Spring" && other.term == "Fall"){
          return true;
        }
        return this->subject < other.subject || (this->subject == other.subject && this->courseNumber < other.courseNumber);
    }

};

//Adapted from the following StackOverflow answer:
//https://stackoverflow.com/a/17017281/3813411
namespace std {
    template <>
  struct hash<SemesterClass>
  {
    std::size_t operator()(const SemesterClass& value) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return (hash<int>()(value.year) + hash<string>()(value.term) + hash<int>()(value.courseNumber) + hash<string>()(value.subject));
    }
  };

}



#endif