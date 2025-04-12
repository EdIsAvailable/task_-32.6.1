#include "ClassThatUsesDB.h"

ClassThatUsesDB::ClassThatUsesDB() : dbConnection(nullptr), isConnected(false) {}

void ClassThatUsesDB::setDBConnection(DBConnection* connection) {
    dbConnection = connection;
}

bool ClassThatUsesDB::openConnection() {
    if (dbConnection == nullptr) {
        return false;
    }
    isConnected = dbConnection->open();
    return isConnected;
}

bool ClassThatUsesDB::closeConnection() {
    if (dbConnection == nullptr || !isConnected) {
        return false;
    }
    bool result = dbConnection->close();
    if (result) {
        isConnected = false;
    }
    return result;
}

std::vector<std::string> ClassThatUsesDB::useConnection(const std::string& query) {
    if (dbConnection == nullptr || !isConnected) {
        return {};
    }
    return dbConnection->execQuery(query);
}

bool ClassThatUsesDB::isConnectionOpen() const {
    return isConnected;
}
