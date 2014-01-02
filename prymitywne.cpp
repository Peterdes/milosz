#include "prymitywne.h"
#include "pole.h"
#include <random>
#include <algorithm>

using namespace std;

Prymitywne::Prymitywne(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
: Stworzenie(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Prymitywne::Prymitywne(queue<string> *const komunikaty, mt19937& gen)
: Stworzenie(
	komunikaty,
	70,	//ruch
	min(geometric_distribution<int>(0.04)(gen), 100),	//sila
	uniform_int_distribution<int>(5, 40)(gen)) {}		//zdrowie

Prymitywne::~Prymitywne() {}

bool Prymitywne::inteligentny() const
{
	return false;
}

bool Prymitywne::czlowiek() const
{
	return false;
}

bool Prymitywne::ruszSie()
{
	int k = 0;
	while(ruch() > 0 && k != 4 && pole() != nullptr)
	{
		int ruchy = losujRuchy();
		for(k = 0; k < 4 && ruch() > 0; ++k)
		{
			int kier = ruchy % 4;
			ruchy >>= 2;
			if(! pole()->obok(Kierunek(kier))->puste())
				if(ruszSie(Kierunek(kier)))
					break;
		}
		if(k == 4)
		{
			ruchy = losujRuchy();
			for(k = 0; k < 4 && ruch() > 0; ++k)
			{
				int kier = ruchy % 4;
				ruchy >>= 2;
				if(ruszSie(Kierunek(kier)))
					break;
			}
		}
	}
	return false;
}

Agresywne::Agresywne(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
: Prymitywne(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Agresywne::Agresywne(queue<string> *const komunikaty, mt19937& gen)
: Prymitywne(komunikaty, gen) {}

Agresywne::~Agresywne() {}

const string Agresywne::wyglad("Agresywne");

const string& Agresywne::przedstaw() const
{
	return wyglad;
}

bool Agresywne::ruszSie(Kierunek kier)
{
	Pole * docelowe = pole()->obok(Kierunek(kier));
	if(! docelowe->puste())
		return walcz(docelowe->stworzenie());
	else return wejdz(docelowe);
}

Wybredne::Wybredne(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
: Prymitywne(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Wybredne::Wybredne(queue<string> *const komunikaty, mt19937& gen)
: Prymitywne(komunikaty, gen) {}

Wybredne::~Wybredne() {}

const string Wybredne::wyglad("Wybredne");

const string& Wybredne::przedstaw() const
{
	return wyglad;
}

bool Wybredne::ruszSie(Kierunek kier)
{
	Pole * docelowe = pole()->obok(Kierunek(kier));
	if(! docelowe->puste())
	{
		if(docelowe->stworzenie()->czlowiek())
			return walcz(docelowe->stworzenie());
		else return false;
	}
	else return wejdz(docelowe);
}

Tchorzliwe::Tchorzliwe(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
: Prymitywne(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Tchorzliwe::Tchorzliwe(queue<string> *const komunikaty, mt19937& gen)
: Prymitywne(komunikaty, gen) {}

Tchorzliwe::~Tchorzliwe() {}

const string Tchorzliwe::wyglad("Tchorzliwe");

const string& Tchorzliwe::przedstaw() const
{
	return wyglad;
}

bool Tchorzliwe::ruszSie(Kierunek kier)
{
	Pole * docelowe = pole()->obok(Kierunek(kier));
	if(! docelowe->puste())
	{
		Stworzenie * cel = docelowe->stworzenie();
		if(cel->zdrowie() * 2 < cel->maxZdrowie())
			return walcz(cel);
		else return false;
	}
	else return wejdz(docelowe);
}

Neutralne::Neutralne(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
: Prymitywne(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Neutralne::Neutralne(queue<string> *const komunikaty, mt19937& gen)
: Prymitywne(komunikaty, gen) {}

Neutralne::~Neutralne() {}

const string Neutralne::wyglad("Neutralne");

const string& Neutralne::przedstaw() const
{
	return wyglad;
}

bool Neutralne::ruszSie(Kierunek kier)
{
	return wejdz(pole()->obok(Kierunek(kier)));
}
