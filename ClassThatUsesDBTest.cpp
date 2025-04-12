#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ClassThatUsesDB.h"
#include "MockDBConnection.h"
#include <memory>

// Тестовый класс
class ClassThatUsesDBTest : public ::testing::Test {
protected:
    std::unique_ptr<MockDBConnection> mockConnection;
    std::unique_ptr<ClassThatUsesDB> classUnderTest;

    void SetUp() override {
        mockConnection = std::make_unique<MockDBConnection>();
        classUnderTest = std::make_unique<ClassThatUsesDB>();
        classUnderTest->setDBConnection(mockConnection.get());
    }

    void TearDown() override {
        classUnderTest.reset();
        mockConnection.reset();
    }
};

// Тест на открытие соединения
TEST_F(ClassThatUsesDBTest, OpenConnectionSuccessfully) {
    // Arrange
    EXPECT_CALL(*mockConnection, open())
        .WillOnce(testing::Return(true));

    // Act
    bool result = classUnderTest->openConnection();

    // Assert
    EXPECT_TRUE(result);
    EXPECT_TRUE(classUnderTest->isConnectionOpen());
}

// Тест на ошибку открытия соединения
TEST_F(ClassThatUsesDBTest, OpenConnectionFailure) {
    // Arrange
    EXPECT_CALL(*mockConnection, open())
        .WillOnce(testing::Return(false));

    // Act
    bool result = classUnderTest->openConnection();

    // Assert
    EXPECT_FALSE(result);
    EXPECT_FALSE(classUnderTest->isConnectionOpen());
}

// Тест на закрытие соединения
TEST_F(ClassThatUsesDBTest, CloseConnectionSuccessfully) {
    // Arrange
    EXPECT_CALL(*mockConnection, open())
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*mockConnection, close())
        .WillOnce(testing::Return(true));
    classUnderTest->openConnection();

    // Act
    bool result = classUnderTest->closeConnection();

    // Assert
    EXPECT_TRUE(result);
    EXPECT_FALSE(classUnderTest->isConnectionOpen());
}

// Тест на ошибку закрытия соединения
TEST_F(ClassThatUsesDBTest, CloseConnectionFailure) {
    // Arrange
    EXPECT_CALL(*mockConnection, open())
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*mockConnection, close())
        .WillOnce(testing::Return(false));
    classUnderTest->openConnection();

    // Act
    bool result = classUnderTest->closeConnection();

    // Assert
    EXPECT_FALSE(result);
    EXPECT_TRUE(classUnderTest->isConnectionOpen());
}

// Тест на выполнение запроса
TEST_F(ClassThatUsesDBTest, UseConnectionSuccessfully) {
    // Arrange
    std::vector<std::string> expectedResults = {"row1", "row2", "row3"};
    std::string testQuery = "SELECT * FROM test_table";
    
    EXPECT_CALL(*mockConnection, open())
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*mockConnection, execQuery(testQuery))
        .WillOnce(testing::Return(expectedResults));
    
    classUnderTest->openConnection();

    // Act
    std::vector<std::string> results = classUnderTest->useConnection(testQuery);

    // Assert
    EXPECT_EQ(results, expectedResults);
}

// Тест на выполнение запроса без открытого соединения
TEST_F(ClassThatUsesDBTest, UseConnectionWithoutOpenConnection) {
    // Arrange
    std::string testQuery = "SELECT * FROM test_table";
    
    // Не вызываем openConnection()
    
    // Act
    std::vector<std::string> results = classUnderTest->useConnection(testQuery);

    // Assert
    EXPECT_TRUE(results.empty());
}

// Тест на случай когда DBConnection не установлен
TEST_F(ClassThatUsesDBTest, OperationsWithNullConnection) {
    // Arrange
    ClassThatUsesDB classWithNullConnection;
    
    // Act & Assert
    EXPECT_FALSE(classWithNullConnection.openConnection());
    EXPECT_FALSE(classWithNullConnection.closeConnection());
    EXPECT_TRUE(classWithNullConnection.useConnection("any query").empty());
}
