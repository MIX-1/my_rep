// Copyright 2020 MIX-1 <daniloniL1@yandex.ru>

#include <gtest/gtest.h>
#include "JsonParser.hpp"

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}
//Correct_File
TEST(Check_Work_Of_File, Opening) {
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
    string jsonFile_test_true = "Students_test.json";
    std :: ofstream students_test;
    students_test.open(jsonFile_test_true);
    students_test << string_test_true;
    students_test.close();
    JsonParser j;
    bool statement = j.file_opening(jsonFile_test_true);
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
//Errors_File
TEST(Check_Errors_Of_File, Opening_bad) {
    string jsonPath_test_false = "../sources/Students_bad.jso";
    string err_res = "Couldn't open json file";
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
    string err_res = "Your json file is empty";
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
    string err_res = "The items field is not an array";
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
    string err_res = "The data in _meta is not"
                     " equal to the length of the items array";
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
    j.extraction_data_from_json();
    j.maxLength();
    int nMax_test = j.get_nMax();
    int gMax_test = j.get_gMax();
    int dMax_test = j.get_dMax();
    EXPECT_EQ(nMax_test, 13);
    EXPECT_EQ(gMax_test, 6);
    EXPECT_EQ(dMax_test, 7);
}
//Struct
TEST(Check_Enter, Enter_to_struct) {
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
    j.extraction_data_from_json();
    j.maxLength();
    bool statement = j.enter();
    EXPECT_TRUE(statement);
}
//Struct_False
TEST(Check_Struct_False_Variants, Check_group) {
    string string1_test_false =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": 10.39,
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    string string2_test_false =\
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
      "group": [
        "1",
        "2",
        "3"
      ],
      "avg": 4,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    string string3_test_false =\
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
      "group": null,
      "avg": 4,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    JsonParser j;
    string err_res = "Invalid data type in the group field";
    j.parse_string_to_json(string1_test_false);
    j.extraction_data_from_json();
    j.maxLength();
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
    j.parse_string_to_json(string2_test_false);
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
    j.parse_string_to_json(string3_test_false);
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
}
TEST(Check_Struct_False_Variants, Check_avg) {
    string string1_test_false =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": [
        "4",
        "4.34",
        "4.12"
      ],
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    string string2_test_false =\
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
      "avg": null,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    JsonParser j;
    string err_res = "Invalid data type in the avg field";
    j.parse_string_to_json(string1_test_false);
    j.extraction_data_from_json();
    j.maxLength();
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
    j.parse_string_to_json(string2_test_false);
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
}
TEST(Check_Struct_False_Variants, Check_debt) {
    string string1_test_false =\
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
      "debt": 2.5
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    string string2_test_false =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": 2
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    }
  ],
  "_meta": {
    "count": 2
  }
})";
    JsonParser j;
    string err_res = "Invalid data type in the debt field";
    j.parse_string_to_json(string1_test_false);
    j.extraction_data_from_json();
    j.maxLength();
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
    j.parse_string_to_json(string2_test_false);
    try{
        j.enter();
    } catch (std::runtime_error& error) {
        EXPECT_EQ(error.what(), err_res);
    }
}
//Table
TEST(Check_Work_Of_Print_Table, Check_Printable_Table) {
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
    string string_test_table_true =\
R"(|---------------|--------|-----|---------|
| name          | group  |avg  | debt    |
|---------------|--------|-----|---------|
| Ivanov Petr   | 1      |4.25 | null    |
|---------------|--------|-----|---------|
| Sidorov Ivan  | 31     |4    | C++     |
|---------------|--------|-----|---------|
| Pertov Nikita | IU8-31 |3.33 | 3 items |
|---------------|--------|-----|---------|

)";
    JsonParser j;
    j.parse_string_to_json(string_test_true);
    j.extraction_data_from_json();
    j.maxLength();
    j.enter();
    std::stringstream ref_stream;
    j.table_print(ref_stream);
    string table_res = j.get_table_final();
    EXPECT_EQ(string_test_table_true, table_res);
}

