/**
* @Author: Sun Xiaofan <sxf>
* @Date:   2016-11-14
* @Email:  sunxfancy@gmail.com
* @Last modified by:   sxf
* @Last modified time: 2016-11-14
* @License: MIT License
*/


#include <iostream>

#include "cmdline.hpp"
#include "submit.hpp"

int main(int argc, char* argv[]) {
    cmdline::parser parser;
    Submit submit;

    // parser.add<string>("run", 'r', "Run jobfile");
    parser.add("show", 's', "Show working queue now");

    parser.set_program_name("submit");
    parser.footer("filename args...");
    parser.parse_check(argc, argv);

    if (parser.exist("show")) {
        submit.show();
        return 0;
    }

    if (parser.rest().size() == 0)
    {
        std::cerr << parser.usage();
        exit(0);
    }
    

    auto& rest = parser.rest();
    char** new_argv = new char*[rest.size()];
    int i = 0;
    for (auto& s : rest) {
        new_argv[i++] = (char*) s.c_str();
    }
    
    submit.sub(i, new_argv);

    delete[] new_argv;

    return 0;
}
