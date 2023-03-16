#include <iostream>
#include "DataBase.h"

int main(){
    DataBase dataBase;
    std::vector<std::string> tags;
    tags.emplace_back("fish");
    tags.emplace_back("vegetarian");
    tags.emplace_back("quick");
    tags.emplace_back("cheap");
    tags.emplace_back("expensive");

    std::cout << "inserted all recipes" << std::endl;
    std::vector<std::string> v;
    v.emplace_back("fish");

    dataBase.selectRandomRecipeWithTags(v);


    return 0;
}