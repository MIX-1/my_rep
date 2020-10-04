// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <header.hpp>

void JsonParser::open() {
    cout << "Введите путь к json файлу\n";
    std :: cin >> jsonPath;
    file.open(jsonPath);
    if (!file)
        throw runtime_error{"Не открывается json файл по адресу: " + jsonPath};
    else
        cout << "Json файл по адресу " + jsonPath + " открыт удачно\n";
    file >> data;
    if (data.empty())
        throw runtime_error{"Ваш json файл оказался пустым"};
    if (!data["items"].is_array())
        throw runtime_error{"Поле items не является массивом"};
    itemsNum = data["_meta"]["count"];
    vec.reserve(static_cast<int>(itemsNum));
    data["items"].get_to(vec);
    if (itemsNum != static_cast<int>(vec.size()))
        throw runtime_error{"Данные в _meta не равны длинне массива items"};
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
void JsonParser::enter() {
    students.reserve(static_cast<int>(itemsNum));
    for (int i=0; i < itemsNum; i++){
        vec[i]["name"].get_to(students[i].Name);
        if (vec.at(i)["group"].is_string()){
            string gS;
            vec[i]["group"].get_to(gS);
            students[i].Group = string{gS};
        } else if (vec.at(i)["group"].is_number_integer()) {
            int gI;
            vec[i]["group"].get_to(gI);
            students[i].Group = static_cast<int>(gI);
        } else {
            throw runtime_error("Неверный тип данных в поле group.");
        }
        bool aB1 = vec.at(i)["avg"].is_number_float();
        bool aB2 = vec.at(i)["avg"].is_number_integer();
        bool aB = aB1 || aB2;
        if (aB){
            double aD;
            vec[i]["avg"].get_to(aD);
            students[i].Avg = static_cast<double>(aD);
        } else if (vec.at(i)["avg"].is_string()){
            string aS;
            vec[i]["avg"].get_to(aS);
            students[i].Avg = string{aS};
        } else {
            throw runtime_error("Неверный тип данных в поле avg.");
        }
        if (vec.at(i)["debt"].is_string()) {
            string dS;
            vec[i]["debt"].get_to(dS);
            students[i].Debt = string{dS};
        } else if (vec.at(i)["debt"].is_null()) {
            students[i].Debt = string{"null"};
        } else if (vec.at(i)["debt"].is_array()) {
            dNum = vec.at(i)["debt"].size();
        } else {
            throw runtime_error("Неверный тип данных в поле debt.");
        }
    }
}
void JsonParser::table_print() {
    cout << setfill('-') << std :: right << "|" << setw(nMax+3);
    cout <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4);
    cout << "|\n" << setfill(' ');
    cout << std :: left << "| " << setw(nMax) << "name" << " | " << setw(gMax);
    cout << "group"<< " |" << setw(4) << "avg"<< " | " << setw(dMax);
    cout << "debt" << " |\n";
    for (int i=0; i < itemsNum; i++){
        cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|";
        cout << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n";
        cout << setfill(' ');
        cout << std :: left << "| "<< setw(nMax) << students[i].Name << " | ";
        if (vec.at(i)["group"].is_string()) {
            cout << setw(gMax) << any_cast<string>(students[i].Group) << " |";
        } else if (vec.at(i)["group"].is_number_integer()) {
            cout << setw(gMax) << any_cast<int>(students[i].Group) << " |";
        }
        bool aB1 = vec.at(i)["avg"].is_number_float();
        bool aB2 = vec.at(i)["avg"].is_number_integer();
        bool aB = aB1 || aB2;
        if (aB){
            cout << std ::  setprecision(3) << setw(4);
            cout << any_cast<double>(students[i].Avg) << " | ";
        } else if (vec.at(i)["avg"].is_string()) {
            cout << std ::  setprecision(3) << setw(4);
            cout << any_cast<string>(students[i].Avg) << " | ";
        }
        if (vec.at(i)["debt"].is_string() || vec.at(i)["debt"].is_null()) {
            cout << setw(dMax) << any_cast<string>(students[i].Debt) << " |\n";
        } else if (vec.at(i)["debt"].is_array()) {
            cout << setw(dArNum) << dNum << setw(dMax-dArNum);
            cout << " items" << " |\n";
        }
    }
    cout << std :: setfill('-') << std :: right << "|" << setw(nMax+3) <<"|";
    cout << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4);
    cout << "|\n" << std :: setfill(' ');
}
