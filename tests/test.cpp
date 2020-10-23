// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <gtest/gtest.h>
#include "header.hpp"

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}
TEST(Check_Work_Of_File, Opening) {
    string jsonPath_test_true = "../sources/Students.json";
    JsonParser j;
    bool statement = j.file_opening(jsonPath_test_true);
    EXPECT_TRUE(statement);
}
TEST(Check_Work_Of_File, Emptynis) {
    string string_test_true =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    JsonParser j;
    j.parse_string_to_json(string_test_true);
    bool statement = j.file_emptynis();
    EXPECT_TRUE(statement);
}
TEST(Check_Work_Of_File, Arrayning) {
    string string_test_true =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    JsonParser j;
    j.parse_string_to_json(string_test_true);
    bool statement = j.file_arrayning();
    EXPECT_TRUE(statement);
}
TEST(Check_Work_Of_File, Equalityning) {
    string string_test_true =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    JsonParser j;
    j.parse_string_to_json(string_test_true);
    bool statement = j.file_equalityning();
    EXPECT_TRUE(statement);
}
//Errors
TEST(Check_Errors_Of_File, Opening_bad) {
    string jsonPath_test_false = "../sources/Students_bad.jso";
    string err_res = "Не удалось открыть json файл";
    JsonParser j;
    try{
        j.file_opening(jsonPath_test_false);
    } catch (std::runtime_error& error) {
    EXPECT_EQ(error.what(), err_res);
    }
}
TEST(Check_Errors_Of_File, Emptynis_bad) {
    string string_test_false =\
R"({
})";
    string err_res = "Ваш json файл оказался пустым";
    JsonParser j;
    j.parse_string_to_json(string_test_false);
    try{
        j.file_emptynis();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
}
TEST(Check_Errors_Of_File, Arrayning_bad) {
    string string_test_false =\
R"({
  "items": null,
  "_meta": {
    "count": 3
  }
})";
    string err_res = "Поле items не является массивом";
    JsonParser j;
    j.parse_string_to_json(string_test_false);
    try{
        j.file_arrayning();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
}
TEST(Check_Errors_Of_File, Equalityning_bad) {
    string string_test_false =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 4
  }
})";
    string err_res = "Данные в _meta не равны длинне массива items";
    JsonParser j;
    j.parse_string_to_json(string_test_false);
    try{
        j.file_equalityning();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
}
//Length
TEST(Check_Length, Count_Max_Length) {
    string string_test_true =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
    JsonParser j;
    j.parse_string_to_json(string_test_true);
    j.reserving_vector_items();
    j.maxLength();
    int nMax_test = j.get_nMax();
    int gMax_test = j.get_gMax();
    int dMax_test = j.get_dMax();
    EXPECT_EQ(nMax_test, 13);
    EXPECT_EQ(gMax_test, 6);
    EXPECT_EQ(dMax_test, 7);
}
//Struct
