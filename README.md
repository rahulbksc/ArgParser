# ArgParser
C++ library for easy parsing of command line arguments

The primary goal for this library is simplicity. I was tired of writing the same arg parsing loop over and over and I wanted something I could use to quickly get started with a new project. 

Other command line argument parsers offer the ability to validate arguments or enforce a schema. I started down that path, but ultimately decided those options needlessly complicated the library. Often you need to do compound checks to validate the arguments the user is giving you and that is hard to offer in a generic way. So, having the argument parser do part of the validation and then writing custom code for the rest ends up resulting in unclear code.

Due to its focus on simplicity, ArgParser doesn't prevent you from doing silly things like requesting a string argument be returned as an int. I may add some code to handle this situation in the future, but for now it is assumed that the user will give you proper argument types.

ArgParser currently supports
- std::string
- int
- double
- char
- bool

It expects parameters to have 1 or more leading dashes (-). The value for the parameter can either come after a single equals (=) sign or a space. If the value comes after a space then it can't have a leading dash. These different styles can be mixed within the same set of arguments with no problems.

Here is an example of using ArgParser

Assume a command line of  
(program_name -infile=test_file.dat -num_recs 2000 --delimiter=| --speedFactor 9.5 -verbose)

```
#include "ArgParser.hpp"
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    std::string inputFileName;
    int recordsToRead = 1000; // This will be the default if the user doesn't override it
    char delimiter = ',';
    double speed = 1.0;
    bool verbose = false;

    ArgParser parser(argc, argv);
    
    // The get method will return false if the requested parameter isn't present
    if (!parser.get("infile", inputFileName))
    {
      std::cout << "ERROR: infile parameter is required" << std::endl;
      exit(1);
    }
    
    parser.get("num_recs", recordsToRead);
    parser.get("delimiter", delimiter);
    parser.get("speedFactor", speed);
    parser.get("verbose", verbose);
    
    std::cout << "inputFilename: " << inputFileName << std::endl;
    std::cout << "recordsToRead: " << recordsToRead << std::endl;
    std::cout << "delimiter: " << delimiter << std::endl;
    std::cout << "speed: " << speed << std::endl;
    std::cout << "verbose: " << verbose << std::endl;

    return 0;
}
```

Possible ToDos  
 - [ ] Add support for more types  
 - [ ] Add safety checks to prevent returning types that don't make sense  

I don't expect the API to change as I want to keep it this easy to use. However, I may add more features as I start to use this library in projects and discover gaps or 'nice to haves'. 

Please report any bugs as a GitHub issue.
