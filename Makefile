CC=g++

CFLAGS=$(shell pkg-config --cflags opencv) 
LIBS=$(shell pkg-config --libs opencv) 

OBJS= main.o  chess.o chess1.o
DEMOTARGET=main 



main.o:	main.cpp
	$(CC) -c $<  -std=c++11	

chess.o:	chess.cpp
	$(CC) -c $<  -std=c++11	
		
chess1.o:	chess1.cpp
	$(CC) -c $<  -std=c++11		



main:	$(OBJS)
	$(CC) -o $@ $^ -L/usr/lib/x86_64-linux-gnu -ldl -lstdc++  -std=c++11 -lpthread $(LIBS)

chess:	chess.o
	$(CC) -o $@ $^ -L/usr/lib/x86_64-linux-gnu -ldl -lstdc++  -std=c++11 -lpthread $(LIBS)
	
chess1:	chess1.o
	$(CC) -o $@ $^ -L/usr/lib/x86_64-linux-gnu -ldl -lstdc++  -std=c++11 -lpthread $(LIBS)


clean:
	-rm -r -f   $(DEMOTARGET) *.o DOXYGENDOC  *.txt

doc:
	doxygen Doxyfile 


all:	$(DEMOTARGET)
	make clean  && make main

run:	main	
	./main

