#include <header.hpp>

void JsonParser::open() {
    cout << "Введите путь к json файлу\n";
    std :: cin >> jsonPath;
    file.open(jsonPath);
    if (!file)
        throw runtime_error{"Не удалось открыть json файл по следующему адресу: " + jsonPath};
    else
        cout << "Json файл по адресу " + jsonPath + " открыт удачно\n";
    file >> data;
    if(data.empty())
        throw runtime_error{"Извините, ваш json файл оказался пустым"};
    if(!data["items"].is_array())
        throw runtime_error{"Извините, поле items не является массивом"};
    itemsNum = data["_meta"]["count"];
    vec.reserve(int(itemsNum));
    data["items"].get_to(vec);
    if(itemsNum!=int(vec.size()))
        throw runtime_error{"Извините, данные в _meta не равны длинне массива items"};
}
void JsonParser::maxLength() {
    for (int i=0; i<itemsNum; i++){
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
    for (int i=0; i<itemsNum; i++){
        sMax[i]=vec.at(i)["name"];
        if (int(sMax[i].length()) > nMax)
            nMax = sMax[i].length();
    }
    for (int i=0; i<itemsNum; i++){
        if (vec.at(i)["group"].is_string()) {
            sMax[i] = string{vec.at(i)["group"]};
            if (int(sMax[i].length()) > gMax)
                gMax = sMax[i].length();
        }
    }
    for (int i=0; i<itemsNum; i++){
        if (vec.at(i)["debt"].is_string()) {
            sMax[i] = string{vec.at(i)["debt"]};
            if (int(sMax[i].length()) > dMax)
                dMax = sMax[i].length();
        }
    }
}
void JsonParser::enter() {
    students.reserve(int(itemsNum));
    for (int i=0;i<itemsNum; i++){
        vec[i]["name"].get_to(students[i].Name);
        if(vec.at(i)["group"].is_string()){
            string gS;
            vec[i]["group"].get_to(gS);
            students[i].Group=string{gS};
        }
        else if(vec.at(i)["group"].is_number_integer()){
            int gI;
            vec[i]["group"].get_to(gI);
            students[i].Group=int(gI);
        }
        else
            throw runtime_error("Вы допустили ошибку в одном из полей group. Неверный тип данных.");
        if(vec.at(i)["avg"].is_number_float()||vec.at(i)["avg"].is_number_integer()){
            double aD;
            vec[i]["avg"].get_to(aD);
            students[i].Avg=double(aD);
        }
        else if(vec.at(i)["avg"].is_string()){
            string aS;
            vec[i]["avg"].get_to(aS);
            students[i].Avg=string{aS};
        }
        else
            throw runtime_error("Вы допустили ошибку в одном из полей avg. Неверный тип данных.");
        if(vec.at(i)["debt"].is_string()){
            string dS;
            vec[i]["debt"].get_to(dS);
            students[i].Debt=string{dS};
        }
        else if(vec.at(i)["debt"].is_null())
            students[i].Debt=string{"null"};
        else if(vec.at(i)["debt"].is_array())
            dNum = vec.at(i)["debt"].size();
        else
            throw runtime_error("Вы допустили ошибку в одном из полей debt. Неверный тип данных.");
    }
}
void JsonParser::table_print() {
    cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << setfill(' ');
    cout << std :: left << "| " << setw(nMax) << "name" << " | " << setw(gMax) << "group"<< " |" << setw(4) << "avg"<< " | " << setw(dMax) << "debt" << " |\n";
    for (int i=0;i<itemsNum; i++){
        cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << setfill(' ');
        cout << std :: left << "| "<< setw(nMax) << students[i].Name << " | " ;
        if(vec.at(i)["group"].is_string())
            cout << setw(gMax) << any_cast<string>(students[i].Group) << " |";
        else if(vec.at(i)["group"].is_number_integer())
            cout << setw(gMax) << any_cast<int>(students[i].Group) << " |";
        if(vec.at(i)["avg"].is_number_float()||vec.at(i)["avg"].is_number_integer())
            cout << std ::  setprecision(3) << setw(4) << any_cast<double>(students[i].Avg) << " | ";
        else if(vec.at(i)["avg"].is_string())
            cout << std ::  setprecision(3) << setw(4) << any_cast<string>(students[i].Avg) << " | ";
        if(vec.at(i)["debt"].is_string() || vec.at(i)["debt"].is_null())
            cout << setw(dMax) << any_cast<string>(students[i].Debt) << " |\n";
        else if(vec.at(i)["debt"].is_array())
            cout << setw(dArNum) << dNum << setw(dMax-dArNum)<< " items"<< " |\n";
    }
    cout << std :: setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << std :: setfill(' ');
}
//class JsonParser
//{
//private:
//    string jsonPath;
//    std::ifstream file;
//    json data;
//    int itemsNum = 0;
//    std :: vector <json> vec;
//    std :: vector <Students> students;
//    int nMax = 0;
//    int gMax = 5;
//    int dNum = 0;
//    int dArNum = 0;
//    int dMax =6;
//public:
//    void open(){
//        cout << "Введите путь к json файлу\n";
//        std :: cin >> jsonPath;
//        file.open(jsonPath);
//        if (!file)
//            throw runtime_error{"Не удалось открыть json файл по следующему адресу: " + jsonPath};
//        else
//            cout << "Json файл по адресу " + jsonPath + " открыт удачно\n";
//        file >> data;
//        if(data.empty())
//            throw runtime_error{"Извините, ваш json файл оказался пустым"};
//        if(!data["items"].is_array())
//            throw runtime_error{"Извините, поле items не является массивом"};
//        itemsNum = data["_meta"]["count"];
//        vec.reserve(int(itemsNum));
//        data["items"].get_to(vec);
//        if(itemsNum!=int(vec.size()))
//            throw runtime_error{"Извините, данные в _meta не равны длинне массива items"};
//    }
//    void maxLength(){
//        for (int i=0; i<itemsNum; i++){
//            if (vec.at(i)["debt"].is_array()) {
//                dNum = vec.at(i)["debt"].size();
//                while (dNum){
//                    dNum /= 10;
//                    dArNum++;
//                }
//            }
//        }
//        dMax += dArNum;
//        std :: vector <string> sMax(itemsNum);
//        for (int i=0; i<itemsNum; i++){
//            sMax[i]=vec.at(i)["name"];
//            if (int(sMax[i].length()) > nMax)
//                nMax = sMax[i].length();
//        }
//        for (int i=0; i<itemsNum; i++){
//            if (vec.at(i)["group"].is_string()) {
//                sMax[i] = string{vec.at(i)["group"]};
//                if (int(sMax[i].length()) > gMax)
//                    gMax = sMax[i].length();
//            }
//        }
//        for (int i=0; i<itemsNum; i++){
//            if (vec.at(i)["debt"].is_string()) {
//                sMax[i] = string{vec.at(i)["debt"]};
//                if (int(sMax[i].length()) > dMax)
//                    dMax = sMax[i].length();
//            }
//        }
//    }
//    void enter(){
//        students.reserve(int(itemsNum));
//        for (int i=0;i<itemsNum; i++){
//            vec[i]["name"].get_to(students[i].Name);
//            if(vec.at(i)["group"].is_string()){
//                string gS;
//                vec[i]["group"].get_to(gS);
//                students[i].Group=string{gS};
//            }
//            else if(vec.at(i)["group"].is_number_integer()){
//                int gI;
//                vec[i]["group"].get_to(gI);
//                students[i].Group=int(gI);
//            }
//            else
//                throw runtime_error("Вы допустили ошибку в одном из полей group. Неверный тип данных.");
//            if(vec.at(i)["avg"].is_number_float()||vec.at(i)["avg"].is_number_integer()){
//                double aD;
//                vec[i]["avg"].get_to(aD);
//                students[i].Avg=double(aD);
//            }
//            else if(vec.at(i)["avg"].is_string()){
//                string aS;
//                vec[i]["avg"].get_to(aS);
//                students[i].Avg=string{aS};
//            }
//            else
//                throw runtime_error("Вы допустили ошибку в одном из полей avg. Неверный тип данных.");
//            if(vec.at(i)["debt"].is_string()){
//                string dS;
//                vec[i]["debt"].get_to(dS);
//                students[i].Debt=string{dS};
//            }
//            else if(vec.at(i)["debt"].is_null())
//                students[i].Debt=string{"null"};
//            else if(vec.at(i)["debt"].is_array())
//                dNum = vec.at(i)["debt"].size();
//            else
//                throw runtime_error("Вы допустили ошибку в одном из полей debt. Неверный тип данных.");
//        }
//    }
//    void table_print(){
//        cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << setfill(' ');
//        cout << std :: left << "| " << setw(nMax) << "name" << " | " << setw(gMax) << "group"<< " |" << setw(4) << "avg"<< " | " << setw(dMax) << "debt" << " |\n";
//        for (int i=0;i<itemsNum; i++){
//            cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << setfill(' ');
//            cout << std :: left << "| "<< setw(nMax) << students[i].Name << " | " ;
//            if(vec.at(i)["group"].is_string())
//                cout << setw(gMax) << any_cast<string>(students[i].Group) << " |";
//            else if(vec.at(i)["group"].is_number_integer())
//                cout << setw(gMax) << any_cast<int>(students[i].Group) << " |";
//            if(vec.at(i)["avg"].is_number_float()||vec.at(i)["avg"].is_number_integer())
//                cout << std ::  setprecision(3) << setw(4) << any_cast<double>(students[i].Avg) << " | ";
//            else if(vec.at(i)["avg"].is_string())
//                cout << std ::  setprecision(3) << setw(4) << any_cast<string>(students[i].Avg) << " | ";
//            if(vec.at(i)["debt"].is_string() || vec.at(i)["debt"].is_null())
//                cout << setw(dMax) << any_cast<string>(students[i].Debt) << " |\n";
//            else if(vec.at(i)["debt"].is_array())
//                cout << setw(dArNum) << dNum << setw(dMax-dArNum)<< " items"<< " |\n";
//        }
//        cout << std :: setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << std :: setfill(' ');
//    }
//};
// /home/alesandr/CLionProjects/lab01/lab-01-parser/sources/Students.json
