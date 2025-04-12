#ifndef CLASS_THAT_USES_DB_H
#define CLASS_THAT_USES_DB_H

#include "DBConnection.h"
#include <string>
#include <vector>

/**
 * Класс, использующий подключение к базе данных
 */
class ClassThatUsesDB {
private:
    DBConnection* dbConnection;
    bool isConnected;

public:
    /**
     * Конструктор
     */
    ClassThatUsesDB();
    
    /**
     * Установить объект подключения к базе данных
     * @param connection указатель на объект типа DBConnection
     */
    void setDBConnection(DBConnection* connection);
    
    /**
     * Открыть соединение с базой данных
     * @return true если соединение успешно открыто, false в противном случае
     */
    bool openConnection();
    
    /**
     * Закрыть соединение с базой данных
     * @return true если соединение успешно закрыто, false в противном случае
     */
    bool closeConnection();
    
    /**
     * Использовать соединение для выполнения запроса
     * @param query строка запроса к базе данных
     * @return вектор строк с результатами запроса
     */
    std::vector<std::string> useConnection(const std::string& query);
    
    /**
     * Проверить, открыто ли соединение
     * @return true если соединение открыто, false в противном случае 
     */
    bool isConnectionOpen() const;
};

#endif // CLASS_THAT_USES_DB_H
