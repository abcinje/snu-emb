run.x : main.o
	g++ -O3 -Wall -Wno-deprecated -g -I/usr/local/systemc-2.3.3/include/ -L/usr/local/systemc-2.3.3/lib-linux64/ -o run.x main.o -lsystemc -lm

main.o : main.cpp
	g++ -O3 -Wall -Wno-deprecated -g -I/usr/local/systemc-2.3.3/include/ -c main.cpp

clean:
	rm -f main.o run.x wave.vcd
