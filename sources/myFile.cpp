#include <header.hpp>


using json = nlohmann::json;

struct Students {
    std::string Name;
    std::variant<int, std :: string> Group;
    double Avg;
    std::variant<std :: string> Debt;
};

int main (){
    std :: string jsonPath = "/home/alesandr/CLionProjects/lab01/lab-01-parser/sources/Students.json";
    std::ifstream file{jsonPath};
    if (!file) {
        throw std::runtime_error{"unable to open json: " + jsonPath};
    }
    else {
        std :: cout << "С кайфом" << std :: endl;
    }
    json data;
    file >> data;
    std :: vector <json> vec;
    data["items"].get_to(vec);
    int nMax;
    int gMax = 5;
    int dNum;
    int dArNum = 0;
    for (int i=0; i<3; i++){
        if (vec.at(i)["debt"].is_array()) {
            dNum = vec.at(i)["debt"].size();
            std :: cout << dNum << "\n";
            while (dNum) {
                dNum /= 10;
                dArNum++;
            }
        }
    }
    int dMax = 6 + dArNum;
    std :: string sMax[3];
    for (int i=0; i<3; i++){
        sMax[i]=vec.at(i)["name"];
        if (int(sMax[i].length())>nMax)
            nMax = sMax[i].length();
    }
    for (int i=0; i<3; i++){
        if (vec.at(i)["group"].is_string()) {
            sMax[i] = std::string{vec.at(i)["group"]};
            if (int(sMax[i].length()) > gMax)
                gMax = sMax[i].length();
        }
    }
    for (int i=0; i<3; i++){
        if (vec.at(i)["debt"].is_string()) {
            sMax[i] = std::string{vec.at(i)["debt"]};
            if (int(sMax[i].length()) > dMax)
                dMax = sMax[i].length();
        }
    }
    std::cout << std :: left << "| " << std::setw(nMax) << "name" << " | " << std::setw(gMax) << "group"<< " |" << std::setw(4) << "avg"<< " | " << std::setw(dMax) << "debt"<< " |\n";
    for (int i=0; i<3; i++){
        Students d;
        std::cout << std :: setfill('-') << std :: right << "|" << std::setw(nMax+3) <<"|" << std::setw(gMax+3) << "|" << std::setw(6) << "|" << std::setw(dMax+4) << "|\n" << std :: setfill(' ') ;
        d.Name=vec.at(i)["name"];
        try {
            d.Group = std :: string{vec.at(i)["group"]};
        }
        catch(const std :: exception&) {
            d.Group = int(vec.at(i)["group"]);
        }
        try {
            d.Avg=double(vec.at(i)["avg"]);
        }
        catch(const std :: exception&) {
            double d1;
            std :: string s1 = vec.at(i)["avg"];
            std::stringstream ss;
            ss << s1;
            ss >> d1;
            d.Avg=d1;
        }
        std :: cout << std :: left << "| " << std::setw(nMax);
        std :: cout << d.Name << " | " ;
        try {
            std :: cout << std::setw(gMax) << std :: get<std :: string>(d.Group) << " |";
        }
        catch(const std :: exception&) {
            std :: cout << std :: get<int>(d.Group) << " |";
        }
        std :: cout << std ::  setprecision(3) << std::setw(4) << d.Avg << " | ";
        if (vec.at(i)["debt"].is_string()) {
            d.Debt = vec.at(i)["debt"];
            std::cout << std::setw(dMax) << std::get<std::string>(d.Debt) << " |\n";
        }
        if (vec.at(i)["debt"].is_null()) {
            std::cout << std::setw(dMax) << "null" << " |\n";
        }
        if (vec.at(i)["debt"].is_array()) {
            std::cout << std::setw(dArNum) << vec.at(i)["debt"].size() << std::setw(dMax-dArNum)<< " items"<< " |\n";
        }
    }
}

