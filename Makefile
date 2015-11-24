test:
	-make build
	-make run
	-make purge

go:
	-make build
	-make run

build:
	g++ -c main.cpp
	g++ main.o -o app -lsfml-graphics -lsfml-window -lsfml-system -lbox2d -g -v

run:
	./app

purge:
	-rm app
	-rm test.o