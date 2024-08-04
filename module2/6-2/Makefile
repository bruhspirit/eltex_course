TARGET = task6-2
LIBRARY = libtest.so

.PHONY: all build clean run

all: clean build

build: $(LIBRARY) $(TARGET)

$(LIBRARY): functions.o
	gcc -shared -o $(LIBRARY) functions.o

functions.o: functions.c
	gcc -fPIC -c functions.c

$(TARGET): task6-2.c $(LIBRARY)
	gcc -rdynamic -o $(TARGET) task6-2.c -L. -ltest

clean:
	rm -rf $(TARGET) $(LIBRARY) functions.o

run: $(TARGET)
	./$(TARGET)