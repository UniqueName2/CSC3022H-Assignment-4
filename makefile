CCX=g++
CPPFLAGS=-std=c++11 -g
EXE_NAME=imageops
FILES=Image.o driver.o

$(EXE_NAME): $(FILES)
	$(CCX) -o imageops Image.o driver.o $(CPPFLAGS)

driver.o: driver.cpp
	$(CCX) -c -o driver.o driver.cpp $(CPPFLAGS)

Image.o: Image.cpp Image.h
	$(CCX) -c -o Image.o Image.cpp $(CPPFLAGS) 

tests:
	$(CCX) -c -o Image.o Image.cpp $(CPPFLAGS)
	$(CCX) -c -o test.o test.cpp $(CPPFLAGS)
	$(CCX) -o testImg test.o Image.o $(CPPFLAGS)

run-tests:
	./testImg

clean:
	rm -f *.o $(EXE_NAME)