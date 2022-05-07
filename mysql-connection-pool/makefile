.PHONY : clean

TARGET := mysql_connection_pool_test
CC := g++
RM := rm -rf

all : $(TARGET)
	./$(TARGET)

$(TARGET) : main.cc
	$(CC) $^ -o $@

clean :
	$(RM) $(TARGET)

