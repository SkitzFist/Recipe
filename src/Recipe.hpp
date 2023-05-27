#ifndef _Recipe
#define _Recipe

#include <string>

struct Recipe
{
    int id;
    std::string name;
    std::string reference;
    std::string tags;

    Recipe(int _id, const std::string &_name, const std::string &_reference, const std::string &_tags) : id(_id), name(_name), reference(_reference), tags(_tags) {}
    Recipe()
    {
        id = 0;
        name = "";
        reference = "";
        tags = "";
    }
};

#endif  
