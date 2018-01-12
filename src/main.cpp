#include <iostream>
#include <string>
#include "submit.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    Submit submit;

    string arg1 = argv[1];
    if (arg1 == "-s" || arg1 == "--show") {
        submit.show();
        return 0;
    }
    
    submit.sub(argc-1, argv+1);

    return 0;
}
