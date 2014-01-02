#include "bard.h"
#include "pole.h"
#include "gra.h"
#include <algorithm>

Bard::Bard(const Gra * gra, Pole * skarb, queue<string> *const komunikaty,
	   int ruch, int sila, int maxZdrowie, int zdrowie)
: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _skarb(skarb), _gra(gra)
{}

Bard::Bard(const Gra * gra, Pole * skarb, queue<string> *const komunikaty, mt19937& gen)
: Rozwiniete(
	komunikaty,
	50,	//ruch
	uniform_int_distribution<int>(1,100)(gen),	//sila
	uniform_int_distribution<int>(40,70)(gen)	//zdrowie
  ),
_skarb(skarb), _gra(gra) {}

Bard::~Bard() {}

const string Bard::wyglad("Bard");

const string& Bard::przedstaw() const
{
	return wyglad;
}

bool Bard::ruszSie()
{
	return false;
}

void Bard::rozmawiaj(Stworzenie * inne)
{
	if(inne->milosz())
	{
		if(inne->dajPrezent())
		{
			_skarb->pokazSkarb();
			int x = _gra->x(*_skarb);
			int y = _gra->y(*_skarb);
			_komunikaty->push( string(
				"Lalala skaaarb " + to_string(x) + ", " + to_string(y)) );
		}
		else _komunikaty->push(string("Bez prezentu nie ma koncertu."));
	}
}

bool Bard::ruszSie(Kierunek kier)
{
	return wejdz(pole()->obok(kier));
}
