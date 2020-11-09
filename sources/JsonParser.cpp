// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <JsonParser.hpp>

bool JsonParser::file_opening(const string& jsonPath) {
    file.open(jsonPath);
    if (!file){
        throw runtime_error{"Couldn't open json file"};
    } else {
        cout << "Json file at " + jsonPath + " opened successfully\n";
        file >> data;
        file.close();
        return true;
    }
}
void JsonParser::parse_string_to_json(const string& string_test) {
    data = json::parse(string_test);
}
bool JsonParser::file_emptynis() {
    if (data.empty()){
        throw runtime_error{"Your json file is empty"};
    } else {
        return true;
    }
}
bool JsonParser::file_arrayning() {
    if (!data[FieldName[0]].is_array()) {
        throw runtime_error{"The items field is not an array"};
    } else {
        return true;
    }
}
void JsonParser::extraction_data_from_json() {
    itemsNum = data[FieldName[5]][FieldName[6]];
    data[FieldName[0]].get_to(vec);
}
bool JsonParser::file_equalityning() {
    extraction_data_from_json();
    if (itemsNum != static_cast<int>(vec.size())){
        throw runtime_error{"The data in _meta is not"
                            " equal to the length of the items array"};
    } else {
        return true;
    }
}
void JsonParser::maxLength() {
    for (int i=0; i < itemsNum; ++i){
        if (vec.at(i)[FieldName[4]].is_array()) {
            dNum = vec.at(i)[FieldName[4]].size();
            while (dNum){
                dNum /= Ten;
                dArNum++;
            }
        }
    }
    dMax += dArNum;
    std :: vector <string> sMax(itemsNum);
    for (int i=0; i < itemsNum; ++i){
        sMax[i] = vec.at(i)[FieldName[1]];
        if (static_cast<int>(sMax[i].length()) > nMax)
            nMax = sMax[i].length();
    }
    for (int i=0; i < itemsNum; ++i){
        if (vec.at(i)[FieldName[2]].is_string()) {
            sMax[i] = string{vec.at(i)[FieldName[2]]};
            if (static_cast<int>(sMax[i].length()) > gMax)
                gMax = sMax[i].length();
        }
    }
    for (int i=0; i < itemsNum; ++i){
        if (vec.at(i)[FieldName[4]].is_string()) {
            sMax[i] = string{vec.at(i)[FieldName[4]]};
            if (static_cast<int>(sMax[i].length()) > dMax)
                dMax = sMax[i].length();
        }
    }
}
int JsonParser::get_nMax() const {
    return nMax;
}
int JsonParser::get_gMax() const {
    return gMax;
}
int JsonParser::get_dMax() const {
    return dMax;
}
any JsonParser::get_enter_group(const int& num) {
    if (vec.at(num)[FieldName[2]].is_string()){
        return string{vec[num][FieldName[2]]};
    } else if (vec.at(num)[FieldName[2]].is_number_integer()) {
        return static_cast<int>(vec[num][FieldName[2]]);
    } else {
        throw runtime_error("Invalid data type in the group field");
    }
}
any JsonParser::get_enter_avg(const int &num) {
    bool aB1 = vec.at(num)[FieldName[3]].is_number_float();
    bool aB2 = vec.at(num)[FieldName[3]].is_number_integer();
    bool aB = aB1 || aB2;
    if (aB){
        return static_cast<double>(vec[num][FieldName[3]]);
    } else if (vec.at(num)[FieldName[3]].is_string()){
        return string{vec[num][FieldName[3]]};
    } else {
        throw runtime_error("Invalid data type in the avg field");
    }
}

any JsonParser::get_enter_debt(const int &num) {
    if (vec.at(num)[FieldName[4]].is_string()) {
        return string{vec[num][FieldName[4]]};
    } else if (vec.at(num)[FieldName[4]].is_null()) {
        return nullptr;
    } else if (vec.at(num)[FieldName[4]].is_array()) {
        dNum = vec[num][FieldName[4]].size();
        return string{" "};
    } else {
        throw runtime_error("Invalid data type in the debt field");
    }
}
bool JsonParser::enter() {
    for (int i=0; i != itemsNum; ++i){
        students.push_back({vec[i][FieldName[1]],
                            get_enter_group(i),
                            get_enter_avg(i),
                            get_enter_debt(i)});
    }
    return true;
}
void JsonParser::table_print(std::ostream& out) {
    std :: stringstream tab;
    tab << setfill('-') << std :: right << "|" << setw(nMax+Three);
    tab <<"|" << setw(gMax+Three) << "|" << setw(Avg_name_space) << "|";
    tab << setw(dMax+Avg_space) << "|\n" << setfill(' ');
    tab << std :: left << "| " << setw(nMax) << FieldName[1] << " | " <<
    setw(gMax);
    tab << FieldName[2]<< " |" << setw(Avg_space) << FieldName[3] << " | ";
    tab << setw(dMax) << FieldName[4] << " |\n";
    for (int i=0; i < itemsNum; ++i) {
        tab << setfill('-') << std :: right << "|" << setw(nMax+Three) <<"|";
        tab << setw(gMax+Three) << "|" << setw(Avg_name_space) << "|";
        tab << setw(dMax+Avg_space) << "|\n" << setfill(' ');
        tab << std :: left << "| "<< setw(nMax) << students[i].Name << " | ";
        if (vec.at(i)[FieldName[2]].is_string()) {
            tab << setw(gMax) << any_cast<string>(students[i].Group) << " |";
        } else if (vec.at(i)[FieldName[2]].is_number_integer()) {
            tab << setw(gMax) << any_cast<int>(students[i].Group) << " |";
        }
        bool aB1 = vec.at(i)[FieldName[3]].is_number_float();
        bool aB2 = vec.at(i)[FieldName[3]].is_number_integer();
        bool aB = aB1 || aB2;
        if (aB){
            tab << std ::  setprecision(Three) << setw(Avg_space);
            tab << any_cast<double>(students[i].Avg) << " | ";
        } else if (vec.at(i)[FieldName[3]].is_string()) {
            tab << std ::  setprecision(Three) << setw(Avg_space);
            tab << any_cast<string>(students[i].Avg) << " | ";
        }
        if (vec.at(i)[FieldName[4]].is_string()) {
            tab << setw(dMax) << any_cast<string>(students[i].Debt) << " |\n";
        } else if (vec.at(i)[FieldName[4]].is_array()) {
            tab << setw(dArNum) << dNum << setw(dMax-dArNum);
            tab << " items" << " |\n";
        } else if (vec.at(i)[FieldName[4]] == nullptr) {
            tab << setw(dMax) << "null" << " |\n";
        }
    }
    tab << std :: setfill('-') << std :: right << "|";
    tab << setw(nMax+Three) <<"|";
    tab << setw(gMax+Three) << "|" << setw(Avg_name_space) << "|";
    tab << setw(dMax+Avg_space) << "|\n" << std :: setfill(' ');
    cout << tab.str();
    table_final << tab.str() << std :: endl;
    out << tab.str();
}
string JsonParser::get_table_final() {
    return table_final.str();
}
