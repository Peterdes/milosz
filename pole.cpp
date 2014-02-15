#include "pole.h"

/*
 * Liczba punktów ruchu potrzebna na przejście po różnych rodzajach terenu
 */

int Trawy::ruch() const
{
	return 30;
}

int Drogi::ruch() const
{
	return 20;
}

int Pagorki::ruch() const
{
	return 50;
}

int Rzeki::ruch() const
{
	return 100;
}

int Bagna::ruch() const
{
	return 70;
}

/*
 * Obrażenia zadawane przez różne rodzaje terenu
 */

int Rzeki::obrazenia() const
{
	return 5;
}

int MartweBagna::obrazenia() const
{
	return 1000000;  //zabójcze dla dowolnego stworzenia w grze
}

/*
 * Pole
 */

Pole::Pole(int w) : _w(w), _sasiad{nullptr} {}
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
	return _sasiad[int(k)];
}

Pole const * Pole::obok(Kierunek k) const
{
	return _sasiad[int(k)];
}

bool Pole::pokazSkarb()
{
	return false;
}

bool Pole::widacSkarb() const
{
	return false;
}

bool Pole::skarb() const
{
	return false;
}

void Pole::ustawSasiada(Kierunek kier, Pole * sasiad)
{
	_sasiad[int(kier)] = sasiad;
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

Skarb::Skarb(int w) : Jaskinie(w), widac(false) {}

Skarb::~Skarb() {};

const string Skarb::wyglad("Skarb");

const string& Skarb::przedstaw() const
{
	if(widac) return wyglad;
	else return Jaskinie::przedstaw();
}

bool Skarb::pokazSkarb()
{
	widac = true;
	return true;
}

bool Skarb::widacSkarb() const
{
	return widac;
}

bool Skarb::skarb() const
{
	return true;
}

Trawy::Trawy(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Trawy::~Trawy() {};

const string Trawy::wyglad("Trawy");

const string& Trawy::przedstaw() const
{
	return wyglad;
}

Drogi::Drogi(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Drogi::~Drogi() {};

const string Drogi::wyglad("Drogi");

const string& Drogi::przedstaw() const
{
	return wyglad;
}

Pagorki::Pagorki(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Pagorki::~Pagorki() {};

const string Pagorki::wyglad("Pagorki");

const string& Pagorki::przedstaw() const
{
	return wyglad;
}

Rzeki::Rzeki(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Rzeki::~Rzeki() {};

const string Rzeki::wyglad("Rzeki");

const string& Rzeki::przedstaw() const
{
	return wyglad;
}

Bagna::Bagna(int w,Stworzenie * stw) : PoleDostepne(w, stw) {}

Bagna::~Bagna() {};

const string Bagna::wyglad("Bagna");

const string& Bagna::przedstaw() const
{
	return wyglad;
}

MartweBagna::MartweBagna(int w,Stworzenie * stw) : Bagna(w, stw) {}

MartweBagna::~MartweBagna() {};

ZwykleBagna::ZwykleBagna(int w,Stworzenie * stw) : Bagna(w, stw) {}

ZwykleBagna::~ZwykleBagna() {};

