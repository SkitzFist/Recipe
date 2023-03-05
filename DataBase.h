#ifndef _DataBase
#define _DataBase

#include <string>
#include <vector>

#include "sqlite3.h"

class DataBase{
public:
    DataBase();
    ~DataBase();
    void insertRecipe(const std::string& _name, const std::string& _tags);
    void selectAllRecipe();
    void selectRecipeWithTags(const std::vector<std::string>& _vec);

private:
    sqlite3* m_db;
    const std::string FILE_NAME;
    void setupNewDataBase();
    const bool executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**)) const;

    int recipeID;
};

#endif