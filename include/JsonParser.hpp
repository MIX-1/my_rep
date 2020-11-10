// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_JSONPARSER_HPP_
#define INCLUDE_JSONPARSER_HPP_
#pragma once
#include <any>
#include <string>
#include <iostream>
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
    int itemsNum;
    std :: vector <json> vec;
    std :: vector <Students> students;
    int nMax;
    int gMax;
    int dNum;
    int dArNum;
    int dMax;
    const int Ten;
    const int Three;
    const int Avg_name_space;
    const int Avg_space;
    std :: stringstream table_final;
    const string FieldName[7];

public:

    JsonParser ()
    : itemsNum(0),
    nMax(0),
    gMax(5),
    dNum(0),
    dArNum(0),
    dMax(6),
    Ten{10},
    Three{3},
    Avg_name_space{6},
    Avg_space{4},
    FieldName{"items", "name", "group", "avg", "debt", "_meta", "count"}
    {
    }

    bool file_opening(const string& jsonPath);

    void parse_string_to_json(const string& string_test);

    bool file_emptynis();

    bool file_arrayning();

    bool file_equalityning();

    void extraction_data_from_json();

    void maxLength();

    int get_nMax() const;

    int get_gMax() const;

    int get_dMax() const;

    any get_enter_group(const int& num);

    any get_enter_avg(const int& num);

    any get_enter_debt(const int& num);

    bool enter();

    void table_print(std::ostream& out);

    string get_table_final();
};
#endif // INCLUDE_JSONPARSER_HPP_
