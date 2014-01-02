#include "pola.h"

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

