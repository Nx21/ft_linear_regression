#ifndef TRIM_HPP
#define TRIM_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

void ltrim(std::string &s, std::string w)
{
    size_t start = s.find_first_not_of(w);
    s = (start == std::string::npos) ? "" : s.substr(start);
}
 
void rtrim(std::string &s, std::string w)
{
    size_t end = s.find_last_not_of(w);
    s =  (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
void trim(std::string &s, std::string w)
{
    rtrim(s,w);
    ltrim(s,w);
}

#endif
