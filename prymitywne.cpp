#include "prymitywne.h"
#include "pole.h"
#include "randengine.h"
#include <algorithm>

Prymitywne::Prymitywne(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
	: Stworzenie(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Prymitywne::Prymitywne(queue<string> *const komunikaty, RandEngine& gen)
	: Stworzenie(
		  komunikaty,
		  70,	//liczba punktów ruchu stworzenia prymitywnego
		  std::min(gen(std::geometric_distribution<int>(0.04)), 100),	//sila
		  gen(std::uniform_int_distribution<int>(5, 40))) {}		//zdrowie

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
	int t = 0;
	while(ruch() > 0 && t != 4 && pole() != nullptr)
	{
		std::array<Kierunek,4> ruchy = losujRuchy();
		t = 0;
		for(auto & k : ruchy)
		{
			if(! pole()->obok(k)->puste())
				if(ruszSie(k))
					break;
			++t;
		}
		if(t == 4)
		{
			ruchy = losujRuchy();
			t = 0;
			for(auto & k : ruchy)
			{
				if(ruszSie(k))
					break;
				++t;
			}
		}
	}
	return false;
}

Agresywne::Agresywne(queue<string> *const komunikaty, RandEngine& gen)
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

Wybredne::Wybredne(queue<string> *const komunikaty, RandEngine& gen)
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

Tchorzliwe::Tchorzliwe(queue<string> *const komunikaty, RandEngine& gen)
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

Neutralne::Neutralne(queue<string> *const komunikaty, RandEngine& gen)
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
