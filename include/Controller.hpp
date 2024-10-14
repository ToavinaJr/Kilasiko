#pragma once

#include <string>
#include <regex>

class Controller
{
public:
    bool isValidEmail(const std::string &email);
    std::string trim(const std::string &str);
    bool isValidDate(const std::string &date);
};