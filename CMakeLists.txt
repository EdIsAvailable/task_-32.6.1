cmake_minimum_required(VERSION 3.10.0)
project(task_32.6.1 VERSION 0.1.0 LANGUAGES C CXX)

# Найти пакет Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Включить текущую директорию в пути поиска заголовочных файлов
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Добавить все исходные файлы для сборки
add_executable(task_32.6.1 
    ClassThatUsesDB.cpp 
    ClassThatUsesDBTest.cpp 
    main.cpp
    # Если у вас есть другие .cpp файлы, добавьте их сюда
)

# Связать с Google Test и Google Mock
target_link_libraries(task_32.6.1 
    ${GTEST_LIBRARIES} 
    ${GTEST_MAIN_LIBRARIES}
    gmock 
    gmock_main
    pthread  # Обычно требуется для GTest
)

# Включить тестирование
include(CTest)
enable_testing()

# Добавить тесты
add_test(NAME AllTests COMMAND task_32.6.1)