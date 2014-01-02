#include "pole.h"

/*
 * Pole
 */

Pole::Pole(int w) : _w(w), _sasiad{nullptr}, _skarb(0) {}
Pole::~Pole() {}

int Pole::obrazenia() const
{
	return 0;
}

int Pole::wspolrzedne() const
{
	return _w;
}

Pole * Pole::obok(Kierunek k)
{
	return _sasiad[k];
}

Pole const * Pole::obok(Kierunek k) const
{
	return _sasiad[k];
}

bool Pole::pokazSkarb()
{
	if(_skarb)
	{
		_skarb = 2;
		return true;
	}
	else return false;
}

bool Pole::widacSkarb() const
{
	if(_skarb == 2)
		return true;
	else return false;
}

bool Pole::skarb() const
{
	return _skarb > 0;
}

void Pole::ustawSasiada(Kierunek kier, Pole * sasiad)
{
	_sasiad[kier] = sasiad;
}

void Pole::postawSkarb()
{
	_skarb = 1;
}

void Pole::zdejmijSkarb()
{
	_skarb = 0;
}

/*
 * Pole dostępne
 */

PoleDostepne::PoleDostepne(int w, Stworzenie * stw)
: Pole(w),_stworzenie(stw) {}

PoleDostepne::~PoleDostepne() {}

void PoleDostepne::czysc()
{
	_stworzenie = nullptr;
}

bool PoleDostepne::puste() const
{
	return _stworzenie == nullptr;
}

bool PoleDostepne::dostepne() const
{
	return true;
}

Stworzenie * PoleDostepne::stworzenie()
{
	return _stworzenie;
}

Stworzenie const * PoleDostepne::stworzenie() const
{
	return _stworzenie;
}

bool PoleDostepne::postaw(Stworzenie * stw)
{
	if(_stworzenie == nullptr)
	{
		_stworzenie = stw;
		return true;
	}
	else return false;
}

/*
 * Pole niedostępne
 */
PoleNiedostepne::PoleNiedostepne(int w)
: Pole(w) {}

PoleNiedostepne::~PoleNiedostepne() {}

void PoleNiedostepne::czysc()
{
}

bool PoleNiedostepne::puste() const
{
	return true;
}

bool PoleNiedostepne::dostepne() const
{
	return false;
}

Stworzenie * PoleNiedostepne::stworzenie()
{
	return nullptr;
}

Stworzenie const * PoleNiedostepne::stworzenie() const
{
	return nullptr;
}

int PoleNiedostepne::ruch() const
{
	return 0;
}

bool PoleNiedostepne::postaw(Stworzenie * stw)
{
	return false;
}
