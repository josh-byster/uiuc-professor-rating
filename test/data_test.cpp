#include "catch.hpp"
#include "../src/Course.h"
#include "../src/CSVReader.h"
#include "../src/DataFrame.h"
#include "../src/SemesterClass.h"
#include "../src/Constants.h"

DataFrame d;
void setup(){
    d = DataFrame(FILE_PATH);
}
bool isWithinTolerance(double a, double b, double epsilon){
    return (a-b) < epsilon;
}
TEST_CASE("Hello"){
    setup();
    REQUIRE(d.getSemesterClassGPA(SemesterClass(2012,"Fall","BIOE",504)) == 3.64);
}