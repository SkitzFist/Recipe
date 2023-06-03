#ifndef _DataBase
#define _DataBase

#include <vector>

#include "Transmission/EventBus.hpp"
#include "Recipe.hpp"
#include "sqlite3.h"

class DataBase: public EventHandler<AddRecipeEvent>, public EventHandler<ModifyRecipeEvent>{

public:
    DataBase(EventBus* eventBus);
    ~DataBase();

    bool insertRecipe(const Recipe& recipe) const;
    bool searchRecipe(const std::string& name);
    bool modifyRecipe(const Recipe& recipe);

    void selectAllRecipe();
    void selectRecipeWithTags(const std::vector<std::string>& _vec);
    void selectRandomRecipeWithTags(const std::vector<std::string>& _vec) const;

public:

private:
    EventBus* m_eventBus;
    sqlite3* m_db;
    const std::string FILE_NAME;
    inline static int m_recipeID;

    inline static std::vector<Recipe> m_selectedRecipes;

    void setupNewDataBase();
    void setRecipeID() const;

    bool executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**), void* _data) const;
    static int getRowsCallback(void *data, int argc, char** argv, char** azColName);
    static int getRecipesCallback(void *data, int argc, char** argv, char** azColName);

    
    //______________EventHandlers_______________________//
    void onEvent(const AddRecipeEvent& event) override;
    void onEvent(const ModifyRecipeEvent& event) override;
    //________________________________________________//
};

#endif
