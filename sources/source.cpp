// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <header.hpp>

bool JsonParser::file_opening(const string& jsonPath) {
    file.open(jsonPath);
    if (!file){
        throw runtime_error{"Не удалось открыть json файл"};
    } else {
        cout << "Json файл по адресу " + jsonPath + " открыт удачно\n";
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
        throw runtime_error{"Ваш json файл оказался пустым"};
    } else {
        return true;
    }
}
bool JsonParser::file_arrayning() {
    if (!data["items"].is_array()) {
        throw runtime_error{"Поле items не является массивом"};
    } else {
        return true;
    }
}
void JsonParser::extraction_data_from_json() {
    itemsNum = data["_meta"]["count"];
    data["items"].get_to(vec);
}
bool JsonParser::file_equalityning() {
    extraction_data_from_json();
    if (itemsNum != static_cast<int>(vec.size())){
        throw runtime_error{"Данные в _meta не равны длинне массива items"};
    } else {
        return true;
    }
}
void JsonParser::maxLength() {
    for (int i=0; i < itemsNum; i++){
        if (vec.at(i)["debt"].is_array()) {
            dNum = vec.at(i)["debt"].size();
            while (dNum){
                dNum /= 10;
                dArNum++;
            }
        }
    }
    dMax += dArNum;
    std :: vector <string> sMax(itemsNum);
    for (int i=0; i < itemsNum; i++){
        sMax[i] = vec.at(i)["name"];
        if (static_cast<int>(sMax[i].length()) > nMax)
            nMax = sMax[i].length();
    }
    for (int i=0; i < itemsNum; i++){
        if (vec.at(i)["group"].is_string()) {
            sMax[i] = string{vec.at(i)["group"]};
            if (static_cast<int>(sMax[i].length()) > gMax)
                gMax = sMax[i].length();
        }
    }
    for (int i=0; i < itemsNum; i++){
        if (vec.at(i)["debt"].is_string()) {
            sMax[i] = string{vec.at(i)["debt"]};
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
    if (vec.at(num)["group"].is_string()){
        return string{vec[num]["group"]};
    } else if (vec.at(num)["group"].is_number_integer()) {
        return static_cast<int>(vec[num]["group"]);
    } else {
        throw runtime_error("Неверный тип данных в поле group.");
    }
}
any JsonParser::get_enter_avg(const int &num) {
    bool aB1 = vec.at(num)["avg"].is_number_float();
    bool aB2 = vec.at(num)["avg"].is_number_integer();
    bool aB = aB1 || aB2;
    if (aB){
        return static_cast<double>(vec[num]["avg"]);
    } else if (vec.at(num)["avg"].is_string()){
        return string{vec[num]["avg"]};
    } else {
        throw runtime_error("Неверный тип данных в поле avg.");
    }
}

any JsonParser::get_enter_debt(const int &num) {
    if (vec.at(num)["debt"].is_string()) {
        return string{vec[num]["debt"]};
    } else if (vec.at(num)["debt"].is_null()) {
        return string{"null"};
    } else if (vec.at(num)["debt"].is_array()) {
        dNum = vec[num]["debt"].size();
        return string{" "};
    } else {
        throw runtime_error("Неверный тип данных в поле debt.");
    }
}
bool JsonParser::enter() {
    for (int i=0; i != itemsNum; i++){
        students.push_back({vec[i]["name"],
                            get_enter_group(i),
                            get_enter_avg(i),
                            get_enter_debt(i)});
    }
    return true;
}
void JsonParser::table_print() {
    std :: stringstream tab;
    cout << setfill('-') << std :: right << "|" << setw(nMax+3);
    cout <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4);
    cout << "|\n" << setfill(' ');
    tab << setfill('-') << std :: right << "|" << setw(nMax+3);
    tab <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4);
    tab << "|\n" << setfill(' ');
    cout << std :: left << "| " << setw(nMax) << "name" << " | " << setw(gMax);
    cout << "group"<< " |" << setw(4) << "avg"<< " | " << setw(dMax);
    cout << "debt" << " |\n";
    tab << std :: left << "| " << setw(nMax) << "name" << " | " << setw(gMax);
    tab << "group"<< " |" << setw(4) << "avg"<< " | " << setw(dMax);
    tab << "debt" << " |\n";
    for (int i=0; i < itemsNum; i++) {
        cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|";
        cout << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n";
        cout << setfill(' ');
        cout << std :: left << "| "<< setw(nMax) << students[i].Name << " | ";
        tab << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|";
        tab << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n";
        tab << setfill(' ');
        tab << std :: left << "| "<< setw(nMax) << students[i].Name << " | ";
        if (vec.at(i)["group"].is_string()) {
            cout << setw(gMax) << any_cast<string>(students[i].Group) << " |";
            tab << setw(gMax) << any_cast<string>(students[i].Group) << " |";
        } else if (vec.at(i)["group"].is_number_integer()) {
            cout << setw(gMax) << any_cast<int>(students[i].Group) << " |";
            tab << setw(gMax) << any_cast<int>(students[i].Group) << " |";
        }
        bool aB1 = vec.at(i)["avg"].is_number_float();
        bool aB2 = vec.at(i)["avg"].is_number_integer();
        bool aB = aB1 || aB2;
        if (aB){
            cout << std ::  setprecision(3) << setw(4);
            cout << any_cast<double>(students[i].Avg) << " | ";
            tab << std ::  setprecision(3) << setw(4);
            tab << any_cast<double>(students[i].Avg) << " | ";
        } else if (vec.at(i)["avg"].is_string()) {
            cout << std ::  setprecision(3) << setw(4);
            cout << any_cast<string>(students[i].Avg) << " | ";
            tab << std ::  setprecision(3) << setw(4);
            tab << any_cast<string>(students[i].Avg) << " | ";
        }
        if (vec.at(i)["debt"].is_string() || vec.at(i)["debt"].is_null()) {
            cout << setw(dMax) << any_cast<string>(students[i].Debt) << " |\n";
            tab << setw(dMax) << any_cast<string>(students[i].Debt) << " |\n";
        } else if (vec.at(i)["debt"].is_array()) {
            cout << setw(dArNum) << dNum << setw(dMax-dArNum);
            cout << " items" << " |\n";
            tab << setw(dArNum) << dNum << setw(dMax-dArNum);
            tab << " items" << " |\n";
        }
    }
    cout << std :: setfill('-') << std :: right << "|" << setw(nMax+3) <<"|";
    cout << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4);
    cout << "|\n" << std :: setfill(' ');
    tab << std :: setfill('-') << std :: right << "|" << setw(nMax+3) <<"|";
    tab << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4);
    tab << "|\n" << std :: setfill(' ');
    table_final << tab.str() << std :: endl;
}
string JsonParser::get_table_final() {
    return table_final.str();
}

