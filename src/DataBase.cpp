#include "DataBase.h"

#include <filesystem>
#include <algorithm>
#include <string>
#include <cctype>

#include "Log.hpp"

int DataBase::getRecipesCallback(void *data, int argc, char** argv, char** azColName){
    for(int i = 1; i < argc; i += 4){
        Recipe recipe;
        recipe.name = argv[i];
        recipe.reference = argv[i+1];
        recipe.tags = argv[i+2];
        m_selectedRecipes.emplace_back(recipe);
    }
    return 0;
}

int DataBase::getRowsCallback(void *data, int argc, char** argv, char** azColName){
    m_recipeID = std::stoi(argv[0]);
    return 0;
}

DataBase::DataBase(EventBus* eventBus) :
    EventHandler<AddRecipeEvent>(getNewId()), FILE_NAME("recipe.db"){
    
    std::filesystem::path path{FILE_NAME};
    if(!std::filesystem::exists(path)){
        Log::info("Setting upp new database");
        m_recipeID = 0;
        setupNewDataBase();
    }else{
        Log::info("Opening database");
        sqlite3_open(FILE_NAME.c_str(), &m_db);
        setRecipeID();
    }

    eventBus->registerHandler<AddRecipeEvent>(this);
}

DataBase::~DataBase(){
    sqlite3_close(m_db);
}

const std::string toLower(const std::string& _str){
    std::string data = _str;
    std::transform(data.begin(), data.end(), data.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return data;
}

bool DataBase::insertRecipe(const Recipe& recipe) const{
    m_selectedRecipes.clear();
    std::string sql = "INSERT INTO recipes " \
                      "VALUES ('" + toLower(recipe.name) + "', '" + toLower(recipe.reference) + "'," + toLower(recipe.tags) + ")'";
    std::string s = "INSERT INTO recipes(NAME, REFERENCE, TAGS)" \
                    "VALUES ('" + toLower(recipe.name) + "','" +toLower(recipe.reference) + "','" + toLower(recipe.tags) + "');"; 
    
    return executeSQL(s, nullptr, nullptr);
}

void DataBase::selectRecipeWithTags(const std::vector<std::string>& _vec){
    m_selectedRecipes.clear();
    std::string sql = "SELECT * FROM recipes WHERE tags LIKE ";
    for(unsigned int i = 0; i < _vec.size(); ++i){
            sql += "'%" + _vec[i] + "%'";
            if(i < _vec.size() - 1){
                sql += " AND tags LIKE ";
            }
    }
    
    executeSQL(sql, getRecipesCallback, nullptr);
}


void DataBase::selectAllRecipe(){
    std::string sql = "SELECT * FROM recipes";
    executeSQL(sql, getRecipesCallback, nullptr);
    for(std::size_t i = 0; i < m_selectedRecipes.size(); ++i){
        Log::info(std::to_string(i) +  ":");
        Recipe recipe = m_selectedRecipes[i];
        Log::info("\tname: " + recipe.name);
        Log::info("Ref: " + recipe.reference);
        Log::info("Tags: " + recipe.tags);
    }   
}

void DataBase::selectRandomRecipeWithTags(const std::vector<std::string>& _vec) const{
    m_selectedRecipes.clear();
    std::string sql = "SELECT * FROM RECIPES WHERE tags LIKE ";
        for(unsigned int i = 0; i < _vec.size(); ++i){
            sql += "'%" + _vec[i] + "%'";
            if(i < _vec.size() - 1){
                sql += " AND tags LIKE ";
            }
        }
        sql += " ORDER BY RANDOM() LIMIT 1;";
        executeSQL(sql, getRecipesCallback, nullptr);
}

void DataBase::setupNewDataBase(){
    sqlite3_open(FILE_NAME.c_str(), &m_db);
    Log::info("\tSetting up tables");
    std::string sql = "CREATE TABLE IF NOT EXISTS recipes ("
                                "id INTEGER PRIMARY KEY autoincrement,"
                                "name TEXT NOT NULL,"
                                "reference TEXT NOT NULL,"
                                "tags TEXT NOT NULL,"
                                "UNIQUE(name));";
    if(!executeSQL(sql, nullptr, nullptr)){
        return;
    }
    Log::info("\tComplete");
}



void DataBase::setRecipeID() const{
    std::string sql = "SELECT COUNT(*) FROM RECIPES";
    executeSQL(sql, getRowsCallback, nullptr);
}

bool DataBase::executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**), void* _data) const{
    char* error = nullptr;
    Log::info("Executing SQL: " + _sql);
    int result = sqlite3_exec(m_db, _sql.c_str(), callback, _data, &error);
    if(result != SQLITE_OK){
        Log::error(error);
        sqlite3_free(error);
        return false;
    }

    return true;
}

void DataBase::onEvent(const AddRecipeEvent& event){
    Log::info("AddRecipe Event");
    insertRecipe(event.recipe);
}
