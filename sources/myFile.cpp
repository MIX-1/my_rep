#include <header.hpp>

int main(){
    cout << "Введите путь к json файлу\n";
    string jsonPath;
    std :: cin >> jsonPath;
    std::ifstream file{jsonPath};
    if (!file)
        throw runtime_error{"Не удалось открыть json файл по следующему адресу: " + jsonPath};
    else
        cout << "Json файл по адресу " + jsonPath + " открыт удачно\n";
    json data;
    file >> data;
    if(data.empty())
        throw runtime_error{"Извините, ваш json файл оказался пустым"};
    if(!data["items"].is_array())
        throw runtime_error{"Извините, поле items не является массивом"};
    int itemsNum = data["_meta"]["count"];
    std :: vector <json> vec(itemsNum);
    data["items"].get_to(vec);
    if(itemsNum!=int(vec.size()))
        throw runtime_error{"Извините, данные в _meta не равны длинне массива items"};
    int nMax = 0;
    int gMax = 5;
    int dNum;
    int dArNum = 0;
    for (int i=0; i<itemsNum; i++){
        if (vec.at(i)["debt"].is_array()) {
            dNum = vec.at(i)["debt"].size();
            while (dNum) {
                dNum /= 10;
                dArNum++;
            }
        }
    }
    int dMax = 6 + dArNum;
    std :: vector <string> sMax(itemsNum);
    for (int i=0; i<itemsNum; i++){
        sMax[i]=vec.at(i)["name"];
        if (int(sMax[i].length()) > nMax)
            nMax = sMax[i].length();
    }
    for (int i=0; i<itemsNum; i++){
        if (vec.at(i)["group"].is_string()) {
            sMax[i] = std::string{vec.at(i)["group"]};
            if (int(sMax[i].length()) > gMax)
                gMax = sMax[i].length();
        }
    }
    for (int i=0; i<itemsNum; i++){
        if (vec.at(i)["debt"].is_string()) {
            sMax[i] = std::string{vec.at(i)["debt"]};
            if (int(sMax[i].length()) > dMax)
                dMax = sMax[i].length();
        }
    }
    cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << setfill(' ');
    cout << std :: left << "| " << setw(nMax) << "name" << " | " << setw(gMax) << "group"<< " |" << setw(4) << "avg"<< " | " << setw(dMax) << "debt" << " |\n";
    for (int i=0;i<itemsNum; i++){
        Students d;
        cout << setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << setfill(' ');
// Ввод:
        if(!vec.at(i)["name"].is_string())
            throw std::runtime_error("invalid name_value ");
        d.Name=vec.at(i)["name"];
        if(vec.at(i)["group"].is_string())
            d.Group = string{vec.at(i)["group"]};
        else if(vec.at(i)["group"].is_number_integer())
            d.Group = int(vec.at(i)["group"]);
        else
            throw runtime_error("Вы допустили ошибку в одном из полей group. Неверный тип данных.");
        if(vec.at(i)["avg"].is_number_float()||vec.at(i)["avg"].is_number_integer())
            d.Avg=double(vec.at(i)["avg"]);
        else if(vec.at(i)["avg"].is_string()){
            double d1;
            string s1 = vec.at(i)["avg"];
            std::stringstream ss;
            ss << s1;
            ss >> d1;
            d.Avg=d1;
        }
        else
            throw runtime_error("Вы допустили ошибку в одном из полей avg. Неверный тип данных.");
//Вывод:
        cout << std :: left << "| "<< setw(nMax) << d.Name << " | " ;
        if(vec.at(i)["group"].is_string())
            cout << setw(gMax) << std :: get<string>(d.Group) << " |";
        else
            cout << setw(gMax) << std :: get<int>(d.Group) << " |";
        cout << std ::  setprecision(3) << setw(4) << d.Avg << " | ";
        if(vec.at(i)["debt"].is_string()){
            d.Debt = vec.at(i)["debt"];
            cout << std::setw(dMax) << std::get<std::string>(d.Debt) << " |\n";
        }
        else if(vec.at(i)["debt"].is_null())
            cout << setw(dMax) << "null" << " |\n";
        else if(vec.at(i)["debt"].is_array())
            cout << setw(dArNum) << vec.at(i)["debt"].size() << setw(dMax-dArNum)<< " items"<< " |\n";
    }
    cout << std :: setfill('-') << std :: right << "|" << setw(nMax+3) <<"|" << setw(gMax+3) << "|" << setw(6) << "|" << setw(dMax+4) << "|\n" << std :: setfill(' ') ;
    // /home/alesandr/CLionProjects/lab01/lab-01-parser/sources/Students.json
}

