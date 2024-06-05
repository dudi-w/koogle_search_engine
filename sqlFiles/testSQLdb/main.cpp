#include <iostream>
#include <sqlite3.h>

// // Function to execute SQL queries
// int executeQuery(sqlite3* db, const char* query) {
//     char* errMsg;
//     int result = sqlite3_exec(db, query, 0, 0, &errMsg);
    
//     if(result != SQLITE_OK){
//         std::cerr << "SQLite Error: " << errMsg << std::endl;
//         sqlite3_free(errMsg);
//     }

//     return result;
// }

// int main() {
//     sqlite3* db;
//     int openResult = sqlite3_open("example.sqlite", &db);

//     if (openResult != SQLITE_OK) {
//         std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
//         return openResult;
//     }

//     // Step 1: Create a Person table
//     const char* createTableQuery = "CREATE TABLE IF NOT EXISTS Person (ID INTEGER PRIMARY KEY, NAME TEXT, AGE INTEGER);";
//     int createTableResult = executeQuery(db, createTableQuery);

//     if (createTableResult != SQLITE_OK) {
//         sqlite3_close(db);
//         return createTableResult;
//     }

//     // Step 2: Insert data into the Person table
//     const char* insertDataQuery = "INSERT INTO Person (NAME, AGE) VALUES ('John Doe', 23), ('Jane Smith', 36);";
//     int insertDataResult = executeQuery(db, insertDataQuery);

//     if (insertDataResult != SQLITE_OK) {
//         sqlite3_close(db);
//         return insertDataResult;
//     }

//     // Clean up and close the database
//     sqlite3_close(db);

//     std::cout << "Database operations completed successfully." << std::endl;

//     return 0;
// }


#include <iostream>
#include <sqlite3.h>
#include <vector>

// Callback function for SELECT queries
int selectCallback(void* data, int argc, char** argv, char** colNames){
    std::vector<std::string> row;
    for(int i = 0; i < argc; ++i){
        row.push_back(colNames[i]);
        row.push_back(argv[i] ? argv[i] : "NULL");
    }
    std::vector<std::vector<std::string>>* res = static_cast<std::vector<std::vector<std::string>>*>(data);
    res->push_back(row);
    return 0;
}

// Function to execute SQL queries
int executeQuery(sqlite3* db, const char* query) {
    char* errMsg;
    int result = sqlite3_exec(db, query, 0, 0, &errMsg);
    
    if (result != SQLITE_OK) {
        std::cerr << "SQLite Error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    return result;
}


int main() {
    sqlite3* db;
    int openResult = sqlite3_open("example2.sqlite", &db);

    if (openResult != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return openResult;
    }

    // Step 1: Create a Person table
    // const char* createTableQuery = "CREATE TABLE IF NOT EXISTS Person (ID INTEGER PRIMARY KEY, NAME TEXT, AGE INTEGER);";
    // int createTableResult = executeQuery(db, createTableQuery);

    // if (createTableResult != SQLITE_OK) {
    //     sqlite3_close(db);
    //     return createTableResult;
    // }

    // Step 2: Insert data into the Person table
    const char* insertDataQuery = "INSERT INTO Person (NAME, AGE) VALUES ('John Doe', 25), ('Jane Smith', 30);";
    int insertDataResult = executeQuery(db, insertDataQuery);

    if (insertDataResult != SQLITE_OK) {
        sqlite3_close(db);
        return insertDataResult;
    }

    // // Step 3: Select and display data from the Person table
    // const char* selectDataQuery = "SELECT * FROM Person where name like \"dudi\";";
    // int selectDataResult = executeQuery(db, selectDataQuery);

    // if (selectDataResult != SQLITE_OK) {
    //     sqlite3_close(db);
    //     return selectDataResult;
    // }

    // // Use a callback function to display the selected data
    // const char* errorMsg = "Error executing SELECT query";
    // std::vector<std::vector<std::string>> res;
    // int callbackResult = sqlite3_exec(db, selectDataQuery, selectCallback, &res, 0);
    // for(auto const& row : res){
    //     for(auto const& cell : row){
    //         std::cout<<" : "<<cell<<std::flush;
    //     }
    //     std::cout<<std::endl;
    // }
    // std::cout<<"res.size() "<<res.size()/*<<"\tres[0].size() "<<res[0].size()*/<<std::endl;

    // if (callbackResult != SQLITE_OK) {
    //     std::cerr << errorMsg << std::endl;
    // }

    

    // Clean up and close the database
    sqlite3_close(db);

    std::cout << "Database operations completed successfully." << std::endl;

    return 0;
}
