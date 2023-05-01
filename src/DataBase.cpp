#include "DataBase.h"

#include <iostream>
#include <filesystem>
#include <algorithm>
#include <string>
#include <cctype>

int DataBase::getRecipesCallback(void *data, int argc, char** argv, char** azColName){
    for(int i = 0; i < argc; i+=3){
        Recipe recipe;
        recipe.name = argv[i+1];
        recipe.tags = argv[i+2];
        m_selectedRecipes.emplace_back(recipe);        
    }
    return 0;
}

int DataBase::getRowsCallback(void *data, int argc, char** argv, char** azColName){
    m_recipeID = std::stoi(argv[0]);
    return 0;
}

DataBase::DataBase(EventBus* eventBus):
    FILE_NAME("recipe.db"){
    
    std::filesystem::path path{FILE_NAME};
    if(!std::filesystem::exists(path)){
        std::cout << "Setting upp new databse\n";
        m_recipeID = 0;
        setupNewDataBase();
    }else{
        std::cout << "Opening database\n";
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

bool DataBase::insertRecipe(const std::string& _name, const std::string& _tags) const{

    std::string sql = "INSERT INTO recipes(NAME,TAGS)" \
                      "VALUES ('" + toLower(_name) +"', '" + toLower(_tags) + "');";
    
    return executeSQL(sql, nullptr, nullptr);
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
    std::string sql = "SELECT * from recipes";
    executeSQL(sql, getRecipesCallback, nullptr);
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
        std::cout << sql << '\n';
        executeSQL(sql, getRecipesCallback, nullptr);
        for(Recipe recipe : m_selectedRecipes){
            std::cout << recipe.name << '\n';
            std::cout << recipe.tags << '\n';
        }
}

void DataBase::setupNewDataBase(){
    sqlite3_open(FILE_NAME.c_str(), &m_db);
    std::cout << "Creating tables...";
    std::string sql = "CREATE TABLE IF NOT EXISTS recipes ("
                                "id INTEGER PRIMARY KEY autoincrement,"
                                "name TEXT NOT NULL,"
                                "tags TEXT NOT NULL,"
                                "UNIQUE(name));";
    if(!executeSQL(sql, nullptr, nullptr)){
        return;
    }
    std::cout << "complete" << std::endl;
}



void DataBase::setRecipeID() const{
    std::string sql = "SELECT COUNT(*) FROM RECIPES";
    executeSQL(sql, getRowsCallback, nullptr);
}

bool DataBase::executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**), void* _data) const{
    char* error = nullptr;
    int result = sqlite3_exec(m_db, _sql.c_str(), callback, _data, &error);
    if(result != SQLITE_OK){
        std::cerr << "Error: " << error << std::endl;
        sqlite3_free(error);
        return false;
    }

    return true;
}
