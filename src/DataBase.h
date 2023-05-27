#ifndef _DataBase
#define _DataBase

#include <string>
#include <vector>

#include "sqlite3.h"

class DataBase{
public:
    struct Recipe
    {
        int id;
        std::string name;
        std::string reference;
        std::string tags;

        Recipe(int _id, const std::string &_name, const std::string &_reference, const std::string &_tags) : id(_id), name(_name), reference(_reference), tags(_tags) {}
        Recipe(){
            id = 0;
            name = "";
            reference = "";
            tags = "";
        }
    };

public:
    DataBase();
    ~DataBase();
    bool insertRecipe(const Recipe& recipe) const;
    bool searchRecipe(const std::string& name);
    bool updateRecipe(const Recipe& recipe);

    void selectAllRecipe();
    void selectRecipeWithTags(const std::vector<std::string>& _vec);
    void selectRandomRecipeWithTags(const std::vector<std::string>& _vec) const;

public:

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
