#include "stworzenie.h"
#include "pole.h"
#include <ctime>
#include <cstdlib>

Stworzenie::Stworzenie(queue<string> *const komunikaty, 
		       int ruch, int sila, int maxZdrowie, int zdrowie)
: _pktyRuchu(ruch), _maxRuchu(ruch), 
_pktyZdrowia(zdrowie), _maxZdrowia(maxZdrowie),
_sila(sila), _komunikaty(komunikaty), _pole(0)
{
	if(zdrowie == 0) _pktyZdrowia = _maxZdrowia;
}

Stworzenie::~Stworzenie() {}

int Stworzenie::maxRuch() const
{
	return _maxRuchu;
}

int Stworzenie::ruch() const
{
	return _pktyRuchu;
}

int Stworzenie::maxZdrowie() const
{
	return _maxZdrowia;
}

int Stworzenie::zdrowie() const
{
	return _pktyZdrowia;
}

int Stworzenie::sila() const
{
	return _sila;
}

bool Stworzenie::martwy() const
{
	return _pktyZdrowia <= 0;
}

float Stworzenie::zbroja() const
{
	return 0.0;
}

float Stworzenie::bron() const
{
	return 0.0;
}

bool Stworzenie::milosz() const
{
	return false;
}

Pole * Stworzenie::pole()
{
	return _pole;
}

Pole const * Stworzenie::pole() const
{
	return _pole;
}

int Stworzenie::wspolrzedne() const
{
	return _pole->wspolrzedne();
}

bool Stworzenie::postaw(Pole * pole)
{
	if(pole == nullptr || pole->postaw(this))
	{
		if(_pole != nullptr)
			_pole->czysc();
		_pole = pole;
		return true;
	}
	else return false;
}

void Stworzenie::oberwij(int obrazenia)
{
	_pktyZdrowia -= obrazenia;
	if(_pktyZdrowia <= 0)
	{
		_pktyZdrowia = 0;
		if(milosz())
			_komunikaty->push( "Umarles!" );
		postaw(nullptr);
	}
}

int Stworzenie::obrazenia(Stworzenie * ofiara)
{
	return int(float(_sila) * float(_pktyZdrowia) / 100.0 
		* (1.0 + bron()) * (1.0 - ofiara->zbroja()));
}

bool Stworzenie::walcz(Stworzenie * przeciwnik)
{
	Pole * docelowe = przeciwnik->pole();
	
	if(_pktyRuchu < przeciwnik->pole()->ruch())
		return false;
	int obraz1 = obrazenia(przeciwnik);
	int obraz2 = przeciwnik->obrazenia(this);
	
	if(przeciwnik->milosz())
		_komunikaty->push( przedstaw() + " zadal Ci " + to_string(obraz1) + " obrazen." );
	if(milosz())
 		_komunikaty->push( "Zadales " + przeciwnik->przedstaw() + " " + to_string(obraz1) + " obrazen." );
	
	if(milosz())
		_komunikaty->push( przeciwnik->przedstaw() + " zadal Ci " + to_string(obraz2) + " obrazen." );
	if(przeciwnik->milosz())
 		_komunikaty->push( "Zadales " + przedstaw() + " " + to_string(obraz2) + " obrazen." );
	
	przeciwnik->oberwij(obraz1);
	oberwij(obraz2);
	
	if(! wejdz(docelowe))
		_pktyRuchu -= przeciwnik->pole()->ruch();
	return true;
}

bool Stworzenie::wejdz(Pole * docelowe)
{
	if(! (docelowe->puste() && docelowe->dostepne()) )
		return false;
	if(docelowe->ruch() > _pktyRuchu)
		return false;
	_pktyRuchu -= docelowe->ruch();
	_pktyZdrowia -= docelowe->obrazenia();
	postaw(docelowe);
	return true;
}

void Stworzenie::rozmawiaj(Stworzenie *)
{
}

bool Stworzenie::dajPrezent()
{
	return false;
}

bool Stworzenie::wezPrezent()
{
	return false;
}

bool Stworzenie::wezZbroje(float)
{
	return false;
}

bool Stworzenie::wezBron(float)
{
	return false;
}

void Stworzenie::ulecz(int lecz)
{
	_pktyZdrowia += lecz;
}

void Stworzenie::ulecz()
{
	_pktyZdrowia = _maxZdrowia;
}

void Stworzenie::tura()
{
	_pktyRuchu = _maxRuchu;
}

int Stworzenie::losujRuchy()
{
	int res1 = 0, res2 = 0, res3 = 0;
	int n = rand();
// 	n = n - (n >> 2) << 2;
	n = n % 4;
	res1 = n;
	do
	{
		n = rand();
// 		n = n - (n >> 2) << 2;
		n = n % 4;
	} while(n == res1);
	res2 = n;
	do
	{
		n = rand();
// 		n = n - (n >> 2) << 2;
		n = n % 4;
	} while(n == res1 || n == res2);
	res3 = n;
	n = 0;
	while(n == res1 || n == res2 || n == res3) ++n;
	return (res1 << 6) + (res2 << 4) + (res3 << 2) + n;
}
