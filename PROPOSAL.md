
#### Introduction

I would like to propose a "teacher auditing application" that I can use to look up certain statistics about professors at UIUC.
This will be using some of Wade Fagen-Ulmschneider's data along with possibly RateMyProfessors.com as a stretch goal. I would like to have the interface be relatively simple: a search functionality in which we can look up each professor and then pull relevant data from the CSV that Wade created with all data.

#### Frameworks Used

I would like to use some framework that enables parsing of CSV data. I will likely use either C++: Minimalistic CSV Streams (found here: https://www.codeproject.com/Articles/741183/Cplusplus-Minimalistic-CSV-Streams) or Boost Tokenizer to do this. I may also need to use a Framework to do some form of autocompletion for typing names.

#### Background

I've done some work in Python regarding parsing CSV data and computing statistics. I think that despite it being more difficult in C++, I think it will be easier with OpenFrameworks to incorporate the user interface.