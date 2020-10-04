// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <any>
#include "iostream"
#include <nlohmann/json.hpp>
#include <vector>
#include <variant>
#include <iomanip>
#include <fstream>
#include <sstream>
using json = nlohmann::json;
using string = std :: string;
using any = std :: any;
using std :: cout;
using std :: setw;
using std :: runtime_error;
using std :: setfill;
using std :: any_cast;
struct Students {
    string Name;
    any Group;
    any Avg;
    any Debt;
};

class JsonParser {
private:
    string jsonPath;
    std::ifstream file;
    json data;
    int itemsNum = 0;
    std :: vector <json> vec;
    std :: vector <Students> students;
    int nMax = 0;
    int gMax = 5;
    int dNum = 0;
    int dArNum = 0;
    int dMax =6;

public:
    void open();

    void maxLength();

    void enter();

    void table_print();
};

#endif // INCLUDE_HEADER_HPP_
