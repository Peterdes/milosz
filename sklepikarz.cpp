#include "sklepikarz.h"
#include "pole.h"
#include <random>

uniform_real_distribution<float> Sklepikarz::dist(0.0, 1.0);

Sklepikarz::Sklepikarz(float dostawy, mt19937& gen, queue<string> *const komunikaty,
	   int ruch, int sila, int maxZdrowie, int zdrowie)
: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _dostawy(dostawy), _gen(gen)
{ init(); }

Sklepikarz::Sklepikarz(float dostawy, queue<string> *const komunikaty, mt19937& gen)
: Rozwiniete(
	komunikaty,
	50,	//ruch
	uniform_int_distribution<int>(50,100)(gen),	//sila (zahartowani ci sklepikarze)
	uniform_int_distribution<int>(50,100)(gen)	//zdrowie
  ), _dostawy(dostawy), _gen(gen)
{ init(); }

Sklepikarz::Sklepikarz(mt19937& gen, queue<string> *const komunikaty,
	   int ruch, int sila, int maxZdrowie, int zdrowie)
: Rozwiniete(komunikaty, ruch, sila, maxZdrowie, zdrowie), _dostawy(0.01), _gen(gen)
{ init(); }

Sklepikarz::Sklepikarz(queue<string> *const komunikaty, mt19937& gen)
: Rozwiniete(
	komunikaty,
	50,	//ruch
	uniform_int_distribution<int>(50,100)(gen),	//sila (zahartowani ci sklepikarze)
	uniform_int_distribution<int>(50,100)(gen)	//zdrowie
  ), _dostawy(0.1), _gen(gen) { init(); }

Sklepikarz::~Sklepikarz() { }

void Sklepikarz::init()
{
	if(dist(_gen) < 0.5)
	{
		_maZbroje = true;
		_zbroja = dist(_gen);
	}
	else _maZbroje = false;
	
	if(dist(_gen) < 0.5)
	{
		_maBron = true;
		_bron = dist(_gen);
	}
	else _maBron = false;
	if(dist(_gen) < 0.5)
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
	if(dist(_gen) < _dostawy)
	{
		_maZbroje = true;
		_zbroja = dist(_gen);
	}
	if(dist(_gen) < _dostawy)
	{
		_maBron = true;
		_bron = dist(_gen);
	}
	if(dist(_gen) < _dostawy)
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
				"Otrzymales zbroje " + to_string(_zbroja) + "!"));
	}
	if(_maBron && inne->wezBron(_bron))
	{
		_maBron = false;
		if(inne->milosz())
			_komunikaty->push( string(
				"Otrzymales bron " + to_string(_bron) + "!"));
	}
	if(_maPrezent && inne->wezPrezent())
	{
		_maPrezent = false;
		if(inne->milosz())
			_komunikaty->push( string(
				"Otrzymales prezent!"));
	}
}
