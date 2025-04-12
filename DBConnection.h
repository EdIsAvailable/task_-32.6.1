#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <string>
#include <vector>

/**
 * Интерфейс для подключения к базе данных
 */
class DBConnection {
public:
    virtual ~DBConnection() = default;
    
    /**
     * Открыть соединение с базой данных
     * @return true если соединение успешно открыто, false в противном случае
     */
    virtual bool open() = 0;
    
    /**
     * Закрыть соединение с базой данных
     * @return true если соединение успешно закрыто, false в противном случае
     */
    virtual bool close() = 0;
    
    /**
     * Выполнить запрос к базе данных
     * @param query строка запроса к базе данных
     * @return вектор строк с результатами запроса
     */
    virtual std::vector<std::string> execQuery(const std::string& query) = 0;
};

#endif // DBCONNECTION_H
