#include "DataBase.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cctype>

static int callback(void *data, int argc, char** argv, char** azColName){
    std::cout << (const char*)data << std::endl;
    for(int i = 0; i < argc; ++i){
        std::string arg = argv[i] ? argv[i] : "NULL";
        std::cout <<azColName[i] << ": " + arg << std::endl;
    }
    std::cout << "-----" << '\n';
    return 0;
}

DataBase::DataBase():
    FILE_NAME("recipe.db"){
    recipeID = 0; //todo load current index from database
    std::filesystem::path path{FILE_NAME};
    if(!std::filesystem::exists(path)){
        std::cout << "Setting up new database" << '\n';
        setupNewDataBase();
    }else{
        std::cout << "opening old db " << '\n';
        sqlite3_open(FILE_NAME.c_str(), &m_db);
    }
}

DataBase::~DataBase(){
    sqlite3_close(m_db);
}

void DataBase::setupNewDataBase(){
    sqlite3_open(FILE_NAME.c_str(), &m_db);
    std::cout << "Creating tables...";
    std::string sql = "CREATE TABLE IF NOT EXISTS recipes ("
                                "id INTEGER PRIMARY KEY autoincrement,"
                                "name TEXT NOT NULL,"
                                "tags TEXT NOT NULL,"
                                "UNIQUE(name));";
    if(!executeSQL(sql, nullptr)){
        return;
    }
    std::cout << "complete" << std::endl;
}

const std::string toLower(const std::string& _str){
    std::string data = _str;
    std::transform(data.begin(), data.end(), data.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return data;
}

void DataBase::insertRecipe(const std::string& _name, const std::string& _tags){

    std::string sql = "INSERT INTO recipes(NAME,TAGS)" \
                      "VALUES ('" + toLower(_name) +"', '" + toLower(_tags) + "');";
    
    executeSQL(sql, callback);
}

void DataBase::selectRecipeWithTags(const std::vector<std::string>& _vec){
    std::string sql = "SELECT * FROM recipes WHERE tags LIKE ";
    for(unsigned int i = 0; i < _vec.size(); ++i){
        std::string tag = "'%" + _vec[i] + "%'";
        sql += tag;
        if(i < _vec.size() - 1){
            sql += " AND tags LIKE ";
        }
    }
    executeSQL(sql, callback);
}


void DataBase::selectAllRecipe(){
    std::string sql = "SELECT * from recipes";
    executeSQL(sql, callback);
}

const bool DataBase::executeSQL(const std::string& _sql, int(*callback)(void*, int, char**, char**)) const{
    char* error = nullptr;
    const char* data = "CALLBACK\n";
    int result = sqlite3_exec(m_db, _sql.c_str(), callback, (void*)data, &error);
    if(result != SQLITE_OK){
        std::cerr << "Error: " << error << std::endl;
        sqlite3_free(error);
        return false;
    }

    return true;
}