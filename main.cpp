#include <iostream>
#include "DataBase.h"

int main(){
    DataBase dataBase;

    dataBase.insertRecipe("macka", "macka, enkelt, snabbt");
    dataBase.insertRecipe("äpple", "frukt, enkelt, snabbt");
    dataBase.insertRecipe("äPPle", "frukt, enkelt, snabbt");
    dataBase.insertRecipe("fruktskål", "frukt, lång tid, vegetarisk");
    dataBase.insertRecipe("Pannkakor", "enkelt, vegetarisk");
    

    std::vector<std::string> vec;
    vec.emplace_back("frukt");
    vec.emplace_back("enkelt");

    dataBase.selectRecipeWithTags(vec);

    return 0;
}