#include "DataBase.h"

#include <filesystem>
#include <algorithm>
#include <string>
#include <cctype>

#include "Log.hpp"

int DataBase::getRecipesCallback(void *data, int argc, char** argv, char** azColName){
    if(argc <= 0){
        return -1;
    }

    for(int i = 0; i < argc; i += 4){
        Recipe recipe;
        recipe.id = atoi(argv[i]);
        recipe.name = argv[i+1];
        recipe.reference = argv[i+2];
        recipe.tags = argv[i+3];
        m_selectedRecipes.emplace_back(recipe);
    }
    return 0;
}

int DataBase::getRowsCallback(void *data, int argc, char** argv, char** azColName){
    m_recipeID = std::stoi(argv[0]);
    return 0;
}

DataBase::DataBase() : FILE_NAME("recipe.db"){
    
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
    std::string query = "INSERT INTO recipes(NAME, REFERENCE, TAGS)" \
                    "VALUES ('" + toLower(recipe.name) + "','" +toLower(recipe.reference) + "','" + toLower(recipe.tags) + "');"; 
    
    return executeSQL(query, nullptr, nullptr);
}

bool DataBase::searchRecipe(const std::string& name){
    m_selectedRecipes.clear();
    std::string query = "SELECT * FROM recipes WHERE name = '"  + name + "';";
    executeSQL(query, getRecipesCallback, nullptr);
    return m_selectedRecipes.size() > 0;
}

bool DataBase::updateRecipe(const Recipe& recipe){
    std::string query = "UPDATE recipes " \
                         "SET name = '" + recipe.name + "', " \
                         "reference = '" + recipe.reference + "', " \
                         "tags = '" + recipe.tags + "' "\
                         "WHERE id = " + std::to_string(recipe.id) +";"
    ;

    return executeSQL(query, nullptr, nullptr);
}

void DataBase::selectRecipeWithTags(const std::vector<std::string>& _vec){
    m_selectedRecipes.clear();
    std::string query = "SELECT * FROM recipes WHERE tags LIKE ";
    for(unsigned int i = 0; i < _vec.size(); ++i){
            query += "'%" + _vec[i] + "%'";
            if(i < _vec.size() - 1){
                query += " AND tags LIKE ";
            }
    }
    
    executeSQL(query, getRecipesCallback, nullptr);
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

bool DataBase::executeSQL(const std::string& _query, int(*callback)(void*, int, char**, char**), void* _data) const{
    char* error = nullptr;
    Log::info("Executing SQL: " + _query);
    int result = sqlite3_exec(m_db, _query.c_str(), callback, _data, &error);
    if(result != SQLITE_OK){
        Log::error(error);
        sqlite3_free(error);
        return false;
    }

    return true;
}
