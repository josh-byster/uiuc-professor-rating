#ifndef SEMESTERCLASS_H
#define SEMESTERCLASS_H
#include <string>
#include <functional>
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
    bool operator==(const SemesterClass &other) const;
    bool operator!=(const SemesterClass &other) const;
    bool operator>(const SemesterClass &other) const;
    bool operator<(const SemesterClass &other) const;

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