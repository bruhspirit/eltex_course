TARGET = task6-3
LIBRARY = libdiff.so libdiv.so libsum.so libmult.so

.PHONY: all build clean run

all: clean build

build: $(LIBRARY) $(TARGET)

libdiff.so: diff.o
	gcc -shared -o $@ $<

libdiv.so: div.o
	gcc -shared -o $@ $<

libsum.so: sum.o
	gcc -shared -o $@ $<

libmult.so: mult.o
	gcc -shared -o $@ $<

diff.o: diff.c
	gcc -fPIC -c diff.c

div.o: div.c
	gcc -fPIC -c div.c

sum.o: sum.c
	gcc -fPIC -c sum.c

mult.o: mult.c  
	gcc -fPIC -c mult.c

$(TARGET): task6-3.c $(LIBRARY)
	gcc -rdynamic -o $(TARGET) task6-3.c -L. -ldiff -ldiv -lsum -lmult

clean:
	rm -rf $(TARGET) $(LIBRARY) *.o

run: $(TARGET)
	./$(TARGET)