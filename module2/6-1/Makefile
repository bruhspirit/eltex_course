TARGET = ./task6-1

.PHONY: all, build, clean, run

$(TARGET):
	gcc -c functions.o functions.c
	ar rcs libtest.a functions.o
	gcc task6-1.c -o task6-1 -L . libtest.a

all:clean build
build:$(TARGET)
clean:
	rm -rf $(TARGET)
run:
	$(TARGET)