#include <iostream>
#include <string>
#include <format>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

std::string getTypeOfValue(json value) {
    if (value.is_array()) return "array";
    if (value.is_boolean()) return "boolean";
    if (value.is_null()) return "null";
    if (value.is_number_integer()) return "integer";
    if (value.is_number_float()) return "double";
    if (value.is_string()) return "string";
    if (value.is_object()) return "object";

    return "Unknown";
}

int main()
{
    json temp;
    string_view tbl1 = "tbl_test_info";
    string_view tbl2 = "tbl_test_info2";
    json j;
    j["use"] = true;
    j["id"] = 1;
    temp[tbl1].emplace_back(j);
    json j2;
    j2["use"] = true;
    j2["id"] = 2;
    temp[tbl2].emplace_back(j2);
    json j3;
    j3["use"] = false;
    j3["id"] = 3;
    temp[tbl1].emplace_back(j3);
    std::cout << "Hello World!\n";
}