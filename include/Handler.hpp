#pragma once

#include <cstdlib>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "User.hpp"


class Handler
{
    public:
        std::map<std::string, std::string> getData() const;
        std::vector<std::string> split(const std::string &str, const char &delimiter) const;
        std::string urlDecode(const std::string &url) const;
        std::string generateId()const;

    private:
        std::string query() const;
        
};
