#ifndef _DataBase
#define _DataBase

#include <string>
#include <vector>

#include "EventBus.hpp"

#include "sqlite3.h"

class DataBase : public EventHandler<AddRecipeEvent>, EventHandler<SearchRecipeEvent>,
    public EventHandler<ModifyRecipeEvent>{
public:
    DataBase(EventBus* eventBus);
    ~DataBase();
    bool insertRecipe(const Recipe& recipe) const;
    bool searchRecipe(const std::string& name);
    bool updateRecipe(const Recipe& recipe);

    void selectAllRecipe();
    void selectRecipeWithTags(const std::vector<std::string>& _vec);
    void selectRandomRecipeWithTags(const std::vector<std::string>& _vec) const;

public:
    ////////////////////////////////////////
    /// EventHandlers
    void onEvent(const AddRecipeEvent& event) override;
    void onEvent(const SearchRecipeEvent& event) override;
    void onEvent(const ModifyRecipeEvent& event) override;
    ////////////////////////////////////////

private:
    sqlite3* m_db;
    const std::string FILE_NAME;
    inline static int m_recipeID;

    EventBus* m_eventBus;

    inline static std::vector<Recipe> m_selectedRecipes;

    void setupNewDataBase();
    void setRecipeID() const;

    bool executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**), void* _data) const;
    static int getRowsCallback(void *data, int argc, char** argv, char** azColName);
    static int getRecipesCallback(void *data, int argc, char** argv, char** azColName);
};

#endif
