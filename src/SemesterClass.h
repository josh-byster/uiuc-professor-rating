#ifndef SEMESTERCLASS_H
#define SEMESTERCLASS_H
#include <string>

struct SemesterClass {
    unsigned int year;
    enum Term {SPRING = 0, SUMMER = 1, FALL = 2};
    Term term;
    std::string subject;
    unsigned int courseNumber;
    SemesterClass() {}
    SemesterClass(unsigned int year, std::string term, std::string subject, unsigned int courseNumber) : year(year), subject(subject), courseNumber(courseNumber) {
      if(term == "Spring"){
        this->term = SPRING;
      }
      if(term == "Summer"){
        this->term = SUMMER;
      }
      if(term == "Fall"){
        this->term = FALL;
      }
    }
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
        return this->subject > other.subject || (this->subject == other.subject && this->courseNumber > other.courseNumber);
    }
    bool operator<(const SemesterClass &other) const {
        if(*this == other){
          return false;
        }
        if(this->year < other.year){
          return true;
        }
        if(this->year > other.year){
          return false;
        }
        if(this->year == other.year){
          if(this->term<other.term){
            return true;
          }
          if(this->term>other.term){
            return false;
          }
        }
        if(this->year == other.year && this->term == other.term){
          if(this->subject < other.subject){
            return true;
          }
          if(this->subject > other.subject){
            return false;
          }
          if(this->subject == other.subject){
            return this->courseNumber<other.courseNumber;
          }
        }
        std::cout<<"WE HAVE AN ISSUE"<<std::endl;
        return false;
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

      return (hash<int>()(value.year) * hash<int>()(value.term) + hash<int>()(value.courseNumber) + hash<string>()(value.subject));
    }
  };

}



#endif