#include <iostream>
#include <string>
#include "submit.hpp"
#include "config.h"
using namespace std;

const char* help_msg =  "Submit " RELEASE_VERSION "\n" 
                        "Usage:\tsub [options] executable [args...]\n\n"
                            "\t--show / -s\t\t\tShow task queue\n"
                            "\t--help / -h / -?\t\tPring help message\n"
                        ;


int main(int argc, char* argv[]) {
    Submit submit;

    if (argc <= 1) { printf("%s", help_msg); return 0; }

    string arg1 = argv[1];
    if (arg1 == "-s" || arg1 == "--show") {
        submit.show();
        return 0;
    }

    if (arg1 == "-h" || arg1 == "-?" || arg1 == "--help") {
        printf("%s", help_msg);
        return 0;
    }
    
    if (arg1[0]=='-') {
        printf("%s", help_msg);
        return 0;
    }

    submit.sub(argc-1, argv+1);

    return 0;
}
