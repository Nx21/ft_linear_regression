#ifndef FT_STOD_HPP
#define FT_STOD_HPP

#include <string>
#include <iostream>
#include <algorithm>
#include <cstdlib>

inline double ft_stod(const std::string &s)
{
    if (s.find_first_not_of("0123456789.-+") != s.npos ||
        std::count(s.begin(), s.end(), '.') > 1) {
        std::cerr << "Error: Invalid number format '" << s << "'" << std::endl;
        exit(1);
    }
    try {
        return std::stod(s);
    } catch (const std::exception& e) {
        std::cerr << "Error: Cannot convert '" << s << "' to number" << std::endl;
        exit(1);
    }
}

#endif
