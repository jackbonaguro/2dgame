test:
	-make build
	-make run
	-make purge

go:
	-make build
	-make run

build:
	g++ -c main.cpp -std=c++11
	g++ main.o -o main.exe -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -lbox2d -g -v

run:
	./main.exe

purge:
	-rm main.exe
	-rm main.o