#ifndef SECTION_H
#define SECTION_H
#include <string>

struct Section {
    unsigned int year;
    std::string term;
    std::string subject;
    unsigned int courseNumber;
    Section() {}
    Section(unsigned int year, std::string term, std::string subject, unsigned int courseNumber) : year(year), term(term), subject(subject), courseNumber(courseNumber) {}
    bool operator==(const Section &other) const {
        return (year == other.year && term == other.term 
        && subject == other.subject && courseNumber == other.courseNumber);
    }

};

//Adapted from the following StackOverflow answer:
//https://stackoverflow.com/a/17017281/3813411
namespace std {
    template <>
  struct hash<Section>
  {
    std::size_t operator()(const Section& value) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return (hash<int>()(value.year) + hash<string>()(value.term) + hash<int>()(value.courseNumber));
    }
  };

}

#endif