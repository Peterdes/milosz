CC = g++
CPPFLAGS = -std=c++11 -Wall -ggdb

all: objects dunnoui

objects: gra.o pola.o pole.o stworzenie.o prymitywne.o rozwiniete.o znachorka.o bard.o sklepikarz.o poszukiwacz.o milosz.o

dunnoui: objects dunnoui.cpp
	$(CC) $(CPPFLAGS) dunnoui.cpp *.o -o dunnoui

clean:
	rm dunnoui
	rm *.o
