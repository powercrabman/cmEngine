#include <iostream>
#include <fstream>
#include "../Libraries/json/json.hpp"
using json = nlohmann::json;


int main()
{
    json js = {};
    js["Hello"] = 10;
    std::cout << js;

    return 0;
}
