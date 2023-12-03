#include <iostream>
#include <sqlite3.h>

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
    int openResult = sqlite3_open("example.sqlite", &db);

    if (openResult != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return openResult;
    }

    // Step 1: Create a Person table
    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS Person (ID INTEGER PRIMARY KEY, NAME TEXT, AGE INTEGER);";
    int createTableResult = executeQuery(db, createTableQuery);

    if (createTableResult != SQLITE_OK) {
        sqlite3_close(db);
        return createTableResult;
    }

    // Step 2: Insert data into the Person table
    const char* insertDataQuery = "INSERT INTO Person (NAME, AGE) VALUES ('John Doe', 23), ('Jane Smith', 36);";
    int insertDataResult = executeQuery(db, insertDataQuery);

    if (insertDataResult != SQLITE_OK) {
        sqlite3_close(db);
        return insertDataResult;
    }

    // Clean up and close the database
    sqlite3_close(db);

    std::cout << "Database operations completed successfully." << std::endl;

    return 0;
}
