#include "rozwiniete.h"
#include "pole.h"
#include "gra.h"
#include "randengine.h"
#include <algorithm>
#include <iostream>

class Gra;

Rozwiniete::Rozwiniete(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
	: Stworzenie(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Rozwiniete::~Rozwiniete() {}

bool Rozwiniete::ruszSie()
{
	int t = 0;
	while(ruch() > 0 && t != 4 && pole() != nullptr)
	{
		std::array<Kierunek,4> ruchy = losujRuchy();
		t = 0;
		for(auto & k : ruchy)
		{
			if(ruszSie(k))
				break;
			++t;
		}
	}
	return false;
}

bool Rozwiniete::inteligentny() const
{
	return true;
}

bool Rozwiniete::czlowiek() const
{
	return true;
}


std::uniform_real_distribution<float> Sklepikarz::dist(0.0, 1.0);

Sklepikarz::Sklepikarz(float dostawy, RandEngine& gen, queue<string> *const komunikaty,
					   int ruch, int sila, int maxZdrowie, int zdrowie)
	: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _dostawy(dostawy), _gen(gen)
{ init(); }

Sklepikarz::Sklepikarz(float dostawy, queue<string> *const komunikaty, RandEngine& gen)
	: Rozwiniete(
		  komunikaty,
		  50,	//ruch
		  gen(std::uniform_int_distribution<int>(50,100)),	//sila (zahartowani ci sklepikarze)
		  gen(std::uniform_int_distribution<int>(50,100))	//zdrowie
		  ), _dostawy(dostawy), _gen(gen)
{ init(); }

Sklepikarz::Sklepikarz(RandEngine& gen, queue<string> *const komunikaty,
					   int ruch, int sila, int maxZdrowie, int zdrowie)
	: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _dostawy(0.01), _gen(gen)
{ init(); }

Sklepikarz::Sklepikarz(queue<string> *const komunikaty, RandEngine& gen)
	: Rozwiniete(
		  komunikaty,
		  50,	//ruch
		  gen(std::uniform_int_distribution<int>(50,100)),	//sila (zahartowani ci sklepikarze)
		  gen(std::uniform_int_distribution<int>(50,100))	//zdrowie
		  ), _dostawy(0.05), _gen(gen) { init(); }

Sklepikarz::~Sklepikarz() { }

void Sklepikarz::init()
{
	if(_gen(dist) < 0.5)
	{
		_maZbroje = true;
		_zbroja = _gen(dist);
	}
	else _maZbroje = false;

	if(_gen(dist) < 0.5)
	{
		_maBron = true;
		_bron = _gen(dist);
	}
	else _maBron = false;
	if(_gen(dist) < 0.5)
	{
		_maPrezent = true;
	}
	else _maPrezent = false;
}

const string Sklepikarz::wyglad("Sklepikarz");

const string& Sklepikarz::przedstaw() const
{
	return wyglad;
}

bool Sklepikarz::ruszSie()
{
	if(_gen(dist) < _dostawy)
	{
		_maZbroje = true;
		_zbroja = _gen(dist);
	}
	if(_gen(dist) < _dostawy)
	{
		_maBron = true;
		_bron = _gen(dist);
	}
	if(_gen(dist) < _dostawy)
		_maPrezent = true;
	return false;
}

bool Sklepikarz::ruszSie(Kierunek kier)
{
	return wejdz(pole()->obok(kier));
}

void Sklepikarz::rozmawiaj(Stworzenie * inne)
{
	if(_maZbroje && inne->wezZbroje(_zbroja))
	{
		_maZbroje = false;
		if(inne->milosz())
			_komunikaty->push( string(
								   "Otrzymales zbroje " + std::to_string(_zbroja) + "!"));
	}
	if(_maBron && inne->wezBron(_bron))
	{
		_maBron = false;
		if(inne->milosz())
			_komunikaty->push( string(
								   "Otrzymales bron " + std::to_string(_bron) + "!"));
	}
	if(_maPrezent && inne->wezPrezent())
	{
		_maPrezent = false;
		if(inne->milosz())
			_komunikaty->push( string(
								   "Otrzymales prezent!"));
	}
}



Znachorka::Znachorka(queue<string> *const komunikaty,
					 int ruch, int sila, int maxZdrowie, int zdrowie)
	: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie)
{}

Znachorka::Znachorka(queue<string> *const komunikaty, RandEngine& gen)
	: Rozwiniete(
		  komunikaty,
		  30,	//ruch
		  gen(std::uniform_int_distribution<int>(30,60)),	//sila (duża, bo truje)
		  gen(std::uniform_int_distribution<int>(30,60))	//zdrowie
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



Bard::Bard(const Gra * gra, Pole * skarb, queue<string> *const komunikaty,
		   int ruch, int sila, int maxZdrowie, int zdrowie)
	: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _skarb(skarb), _gra(gra)
{}

Bard::Bard(const Gra * gra, Pole * skarb, queue<string> *const komunikaty, RandEngine& gen)
	: Rozwiniete(
		  komunikaty,
		  50,	//ruch
		  gen(std::uniform_int_distribution<int>(1,100)),	//sila
		  gen(std::uniform_int_distribution<int>(40,70))	//zdrowie
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
								   "Lalala skaaarb " + std::to_string(x)
								   + ", " + std::to_string(y)) );
		}
		else _komunikaty->push(string("Bez prezentu nie ma koncertu."));
	}
}

bool Bard::ruszSie(Kierunek kier)
{
	return wejdz(pole()->obok(kier));
}



Poszukiwacz::Poszukiwacz(float zbroja, float bron, queue<string> *const komunikaty,
						 int ruch, int sila, int maxZdrowie, int zdrowie)
	: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _zbroja(zbroja), _bron(bron)
{}

Poszukiwacz::Poszukiwacz(RandEngine& gen, queue<string> *const komunikaty,
						 int ruch, int sila, int maxZdrowie, int zdrowie)
	: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie),
	  _zbroja(gen(std::uniform_real_distribution<float>(0.0, 1.0))),
	  _bron(gen(std::uniform_real_distribution<float>(0.0, 1.0)))
{}

Poszukiwacz::Poszukiwacz(queue<string> *const komunikaty, RandEngine& gen)
	: Rozwiniete(
		  komunikaty,
		  100,	//ruch
		  gen(std::uniform_int_distribution<int>(1,100)),	//sila
		  gen(std::uniform_int_distribution<int>(1,100))	//zdrowie
		  ),
	  _zbroja(gen(std::uniform_real_distribution<float>(0.0, 1.0))),
	  _bron(gen(std::uniform_real_distribution<float>(0.0, 1.0)))
{}

Poszukiwacz::~Poszukiwacz() {}

const string Poszukiwacz::wyglad("Poszukiwacz");

const string& Poszukiwacz::przedstaw() const
{
	return wyglad;
}

bool Poszukiwacz::ruszSie()
{
	int t = 0;
	while(ruch() > 0 && t != 4 && pole() != nullptr)
	{
		std::array<Kierunek,4> ruchy = losujRuchy();
		t = 0;
		for(auto & k : ruchy)
		{
			if(ruszSie(k))
				break;
			++t;
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
