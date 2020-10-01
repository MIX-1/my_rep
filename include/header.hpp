// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include "iostream"
#include <nlohmann/json.hpp>
#include <vector>
#include <variant>
#include <iomanip>
#include <fstream>
#include <sstream>
using json = nlohmann::json;
using string = std :: string;
using std :: cout;
using std :: setw;
using std :: runtime_error;
using std :: setfill;

struct Students {
    string Name;
    std::variant<int, string> Group;
    double Avg;
    std::variant<std :: string> Debt;
};
#endif // INCLUDE_HEADER_HPP_
