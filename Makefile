CC = g++
CPPFLAGS = -std=c++11 -Wall -ggdb

all: objects dunnoui

objects: gra.o pole.o stworzenie.o prymitywne.o rozwiniete.o milosz.o

dunnoui: objects dunnoui.cpp
	$(CC) $(CPPFLAGS) dunnoui.cpp *.o -o dunnoui

clean:
	rm dunnoui
	rm *.o
