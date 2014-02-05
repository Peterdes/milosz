#include "milosz.h"
#include "pole.h"

Milosz::Milosz(RandEngine& gen, queue<string> *const komunikaty)
: Poszukiwacz(gen, komunikaty, 100,
	      30, //sila
	      100, 50), _prezent(false)
{}

Milosz::~Milosz() {}

const string Milosz::wyglad("Milosz");

const string& Milosz::przedstaw() const
{
	return wyglad;
}

bool Milosz::ruszSie()
{
	return false;
}

bool Milosz::ruszSie(Kierunek kier)
{
	if(pole() == nullptr)
		return false;
	
	Pole * docelowe = pole()->obok(kier);
	
	if(_pktyRuchu < docelowe->ruch())
	{
		_komunikaty->push(string("Za malo punktow ruchu."));
		return false;
	}
	if(! docelowe->dostepne())
	{
		_komunikaty->push(string("Nie mozesz tam wejsc."));
		return false;
	}
	
	if(docelowe->puste())
	{
		return wejdz(docelowe);
	}
	if(docelowe->stworzenie()->inteligentny())
	{
		docelowe->stworzenie()->rozmawiaj(this);
		_pktyRuchu -= docelowe->ruch();
		return true;
	}
	else return walcz(docelowe->stworzenie());
}

bool Milosz::dajPrezent()
{
	if(_prezent)
	{
		_prezent = false;
		return true;
	}
	else return false;
}

bool Milosz::wezPrezent()
{
	_prezent = true;
	return true;
}

bool Milosz::prezent() const
{
	return _prezent;
}

bool Milosz::milosz() const
{
	return true;
}
