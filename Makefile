
output: as.o
	g++ as.o -o output
event.o:as.cpp
	g++ -c as.cpp
clean:
	rm *.o output
