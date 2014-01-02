CC = g++
CPPFLAGS = -std=c++11 -Wall -ggdb

all: objects dunnoui

objects: gra.o stworz pol

pol: pola.o pole.o

stworz: stworzenie.o prym rozw

prym: prymitywne.o

rozw: rozwiniete.o znachorka.o bard.o sklepikarz.o poszukiwacz.o milosz.o

dunnoui: objects dunnoui.cpp
	$(CC) $(CPPFLAGS) dunnoui.cpp *.o -o dunnoui

clean:
	rm dunnoui
	rm *.o

