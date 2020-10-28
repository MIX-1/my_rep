// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <any>
#include <string>
#include "iostream"
#include <nlohmann/json.hpp>
#include <vector>
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
    std::ifstream file;
    json data;
    int itemsNum = 0;
    std :: vector <json> vec;
    std :: vector <Students> students;
    int nMax = 0;
    int gMax = 5;
    int dNum = 0;
    int dArNum = 0;
    int dMax = 6;
    std :: stringstream table_final;

public:
    bool file_opening(const string& jsonPath);

    void parse_string_to_json(const string& string_test);

    bool file_emptynis();

    bool file_arrayning();

    bool file_equalityning();

    void reserving_vector_items();

    void maxLength();

    int get_nMax() const;

    int get_gMax() const;

    int get_dMax() const;

    any get_enter_group(const int& num);

    any get_enter_avg(const int& num);

    any get_enter_debt(const int& num);

    bool enter();

    void table_print();

    string get_table_final();
};
#endif // INCLUDE_HEADER_HPP_
