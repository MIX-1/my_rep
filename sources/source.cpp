#include <header.hpp>


using json = nlohmann::json;

struct Student {
    std::string Name;
    std::any Group;
    double Avg;
    std::any Debt;
};

int main (){
    std :: cout << "эй ты напиши путь, реально";
    std :: string jsonPath;
    std :: cin >> jsonPath;
    std::ifstream file{jsonPath};
//    void from_json(const json& j, Student& s) {
//        j.at("name").get_to(s.Name);
//        j.at("group").get_to(s.Group);
//        j.at("avg").get_to(s.Avg);
//        j.at("debt").get_to(s.Debt);
//    }
    if (!file) {
        throw std::runtime_error{"unable to open json: " + jsonPath};
    }

    json data;
    file >> data;

    std::vector<Student> students;
//    for (auto const& student : data.at("items")) {
//        students.push_back(Student{student});
//    }
}