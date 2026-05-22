# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iall_hpp

# Папки
SRC_DIR = all_cpp
OBJ_DIR = obj
HPP_DIR = all_hpp

# Исходные файлы (все .cpp в папке all_cpp)
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Добавляем main.cpp из текущей папки
MAIN_SRC = main.cpp
ALL_SRCS = $(MAIN_SRC) $(SRCS)

# Объектные файлы: main.o в корне, остальные в папке obj/
MAIN_OBJ = main.o
OTHER_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS = $(MAIN_OBJ) $(OTHER_OBJS)

# Имя исполняемого файла
TARGET = delivery.exe

# Цель по умолчанию
all: $(TARGET)

# Создание папки для объектных файлов
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Компиляция main.cpp
$(MAIN_OBJ): main.cpp $(HPP_DIR)/*.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция остальных .cpp (из папки all_cpp)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HPP_DIR)/*.hpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(OBJ_DIR)

# Пересборка
rebuild: clean all

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run
