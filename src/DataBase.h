#ifndef _DataBase
#define _DataBase

#include <string>
#include <vector>

#include "EventBus.hpp"

#include "sqlite3.h"

struct Recipe
{
    std::string name;
    std::string tags;
};

class DataBase{
public:
    DataBase(EventBus* eventBus);
    ~DataBase();
    bool insertRecipe(const std::string& _name, const std::string& _tags) const;
    void selectAllRecipe();
    void selectRecipeWithTags(const std::vector<std::string>& _vec);
    void selectRandomRecipeWithTags(const std::vector<std::string>& _vec) const;

private:
    sqlite3* m_db;
    const std::string FILE_NAME;
    inline static int m_recipeID;

    inline static std::vector<Recipe> m_selectedRecipes;

    void setupNewDataBase();
    void setRecipeID() const;

    bool executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**), void* _data) const;
    static int getRowsCallback(void *data, int argc, char** argv, char** azColName);
    static int getRecipesCallback(void *data, int argc, char** argv, char** azColName);
};

#endif
