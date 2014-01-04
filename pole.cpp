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

bool PoleNiedostepne::postaw(Stworzenie *)
{
	return false;
}


Skaly::Skaly(int w) : PoleNiedostepne(w) {}

Skaly::~Skaly() {};

const string Skaly::wyglad("Skaly");

const string& Skaly::przedstaw() const
{
    return wyglad;
}

Jaskinie::Jaskinie(int w,Stworzenie * stw) : Pagorki(w, stw) {}

Jaskinie::~Jaskinie() {};

const string Jaskinie::wyglad("Jaskinie");

const string& Jaskinie::przedstaw() const
{
    return wyglad;
}

Trawy::Trawy(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Trawy::~Trawy() {};

const string Trawy::wyglad("Trawy");

const string& Trawy::przedstaw() const
{
    return wyglad;
}

int Trawy::ruch() const
{
    return 30;
}

Drogi::Drogi(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Drogi::~Drogi() {};

const string Drogi::wyglad("Drogi");

const string& Drogi::przedstaw() const
{
    return wyglad;
}

int Drogi::ruch() const
{
    return 20;
}

Pagorki::Pagorki(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Pagorki::~Pagorki() {};

const string Pagorki::wyglad("Pagorki");

const string& Pagorki::przedstaw() const
{
    return wyglad;
}

int Pagorki::ruch() const
{
    return 50;
}

Rzeki::Rzeki(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Rzeki::~Rzeki() {};

const string Rzeki::wyglad("Rzeki");

const string& Rzeki::przedstaw() const
{
    return wyglad;
}

int Rzeki::obrazenia() const
{
    return 5;
}

int Rzeki::ruch() const
{
    return 100;
}

Bagna::Bagna(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Bagna::~Bagna() {};

const string Bagna::wyglad("Bagna");

const string& Bagna::przedstaw() const
{
    return wyglad;
}

int Bagna::ruch() const
{
    return 70;
}

MartweBagna::MartweBagna(int w,Stworzenie * stw) : Bagna(w, stw) {}

MartweBagna::~MartweBagna() {};

int MartweBagna::obrazenia() const
{
    return 1000000;
}

ZwykleBagna::ZwykleBagna(int w,Stworzenie * stw) : Bagna(w, stw) {}

ZwykleBagna::~ZwykleBagna() {};

