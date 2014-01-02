#include "poszukiwacz.h"
#include "pole.h"
#include <iostream>

using namespace std;

Poszukiwacz::Poszukiwacz(float zbroja, float bron, queue<string> *const komunikaty,
	   int ruch, int sila, int maxZdrowie, int zdrowie)
: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _zbroja(zbroja), _bron(bron)
{}

Poszukiwacz::Poszukiwacz(mt19937& gen, queue<string> *const komunikaty,
	   int ruch, int sila, int maxZdrowie, int zdrowie)
: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie),
  _zbroja(uniform_real_distribution<float>(0.0, 1.0)(gen)),
  _bron(uniform_real_distribution<float>(0.0, 1.0)(gen))
{}

Poszukiwacz::Poszukiwacz(queue<string> *const komunikaty, mt19937& gen)
: Rozwiniete(
	komunikaty,
	100,	//ruch
	uniform_int_distribution<int>(1,100)(gen),	//sila
	uniform_int_distribution<int>(1,100)(gen)	//zdrowie
  ),
  _zbroja(uniform_real_distribution<float>(0.0, 1.0)(gen)),
  _bron(uniform_real_distribution<float>(0.0, 1.0)(gen))
{}

Poszukiwacz::~Poszukiwacz() {}

const string Poszukiwacz::wyglad("Poszukiwacz");

const string& Poszukiwacz::przedstaw() const
{
	return wyglad;
}

bool Poszukiwacz::ruszSie()
{
	int k = 0;
	while(ruch() > 0 && k != 4 && pole() != nullptr)
	{
		int ruchy = losujRuchy();
		for(k = 0; k < 4 && ruch() > 0; ++k)
		{
			int kier = ruchy % 4;
			ruchy >>= 2;
			if(ruszSie(Kierunek(kier)))
				break;
		}
		
		if(pole() == nullptr) break;
		
		if(pole()->skarb())
		{
			_komunikaty->push(string("Poszukiwacz znalazl skarb!"));
			_komunikaty->push(string("Przegrana!"));
			return true;
		}
	}
	return false;
}

bool Poszukiwacz::ruszSie(Kierunek kier)
{
	Pole * docelowe = pole()->obok(kier);
	if(docelowe->puste())
		return wejdz(docelowe);
	if(docelowe->stworzenie()->inteligentny())
	{
		if(_pktyRuchu < docelowe->ruch())
			return false;
		else
		{
			docelowe->stworzenie()->rozmawiaj(this);
			_pktyRuchu -= docelowe->ruch();
			return true;
		}
	}
	else return walcz(docelowe->stworzenie());
}

float Poszukiwacz::zbroja() const
{
	return _zbroja;
}

float Poszukiwacz::bron() const
{
	return _bron;
}

void Poszukiwacz::rozmawiaj(Stworzenie * inne)
{
	if(inne->milosz())
		_komunikaty->push(string("Poszukiwacz Cie ignoruje."));
}

bool Poszukiwacz::wezZbroje(float zbroja)
{
	_zbroja = zbroja;
	return true;
}

bool Poszukiwacz::wezBron(float bron)
{
	_bron = bron;
	return true;
}
