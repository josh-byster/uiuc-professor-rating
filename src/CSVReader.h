//Note: this functionality is based loosely on the following 
//tutorial: http://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
#include <string>
#include <iostream>
#include <vector>
class CSVReader {
    
    public:
        CSVReader(std::string filename) : filename(filename) { };
        std::vector<std::vector<std::string>> getData();
    private:
        std::string filename;
        
};