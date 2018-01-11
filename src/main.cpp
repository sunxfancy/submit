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


int main(int argc, char const *argv[]) {
    cmdline::parser parser;
    parser.add<string>("run", 'r', "Run jobfile");
    parser.add("share", "");
    parser.add("show", 's', "Show working queue now");

    parser.set_program_name("submit");
    parser.parse_check(argc, argv);
    if (parser.rest().size() == 0)
    {
        std::cerr << parser.usage();
        exit(0);
    }

    

    return 0;
}
