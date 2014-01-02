#include "znachorka.h"
#include "pole.h"

Znachorka::Znachorka(queue<string> *const komunikaty,
	   int ruch, int sila, int maxZdrowie, int zdrowie)
: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie)
{}

Znachorka::Znachorka(queue<string> *const komunikaty, mt19937& gen)
: Rozwiniete(
	komunikaty,
	30,	//ruch
	uniform_int_distribution<int>(30,60)(gen),	//sila (duża, bo truje)
	uniform_int_distribution<int>(30,60)(gen)	//zdrowie
  ) {}

Znachorka::~Znachorka() {}

const string Znachorka::wyglad("Znachorka");

const string& Znachorka::przedstaw() const
{
	return wyglad;
}

bool Znachorka::ruszSie()
{
	//a tam, ustawimy znachorkę w miejscu
	return false;
}

bool Znachorka::ruszSie(Kierunek kier)
{
	return wejdz(pole()->obok(kier));
}

void Znachorka::rozmawiaj(Stworzenie * inne)
{
	if(inne->dajPrezent())
	{
		inne->ulecz();
		if(inne->milosz())
			_komunikaty->push(string("Dzieki, tu sa ziolka."));
	}
	else if(inne->milosz())
		_komunikaty->push(string("Nie ma nic za darmo!"));
}
