#ifndef MOCK_DBCONNECTION_H
#define MOCK_DBCONNECTION_H

#include "DBConnection.h"
#include <gmock/gmock.h>

/**
 * Мок-класс для DBConnection
 */
class MockDBConnection : public DBConnection {
public:
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(bool, close, (), (override));
    MOCK_METHOD(std::vector<std::string>, execQuery, (const std::string&), (override));
};

#endif // MOCK_DBCONNECTION_H
