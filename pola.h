#ifndef POLA_H
#define POLA_h
#include "pole.h"

class Skaly : public PoleNiedostepne
{
public:
	Skaly(int);
	virtual ~Skaly();
	const string& przedstaw() const;
private:
	static const string wyglad;
};

class Trawy : public PoleDostepne
{
public:
	Trawy(int,Stworzenie * = nullptr);
	virtual ~Trawy();
	const string& przedstaw() const;
	int ruch() const;
private:
	static const string wyglad;
};

class Drogi : public PoleDostepne
{
public:
	Drogi(int,Stworzenie * = nullptr);
	virtual ~Drogi();
	const string& przedstaw() const;
	int ruch() const;
private:
	static const string wyglad;
};

class Pagorki : public PoleDostepne
{
public:
	Pagorki(int,Stworzenie * = nullptr);
	virtual ~Pagorki();
	virtual const string& przedstaw() const;
	virtual int ruch() const;
private:
	static const string wyglad;
};

class Jaskinie : public Pagorki
{
public:
	Jaskinie(int,Stworzenie * = nullptr);
	virtual ~Jaskinie();
	const string& przedstaw() const;
private:
	static const string wyglad;
};

class Rzeki : public PoleDostepne
{
public:
	Rzeki(int,Stworzenie * = nullptr);
	virtual ~Rzeki();
	const string& przedstaw() const;
	int ruch() const;
	int obrazenia() const;
private:
	static const string wyglad;
};

class Bagna : public PoleDostepne
{
public:
	Bagna(int,Stworzenie * = nullptr);
	virtual ~Bagna();
	const string& przedstaw() const;
	int ruch() const;
private:
	static const string wyglad;
};

class MartweBagna : public Bagna
{
public:
	MartweBagna(int,Stworzenie * = nullptr);
	virtual ~MartweBagna();
	/*
	* Prymitywny chwyt: zwracam obrażenia przekraczające życie
	* dowolnej istniejącej jednostki
	*/
	int obrazenia() const;
};

class ZwykleBagna : public Bagna
{
public:
	ZwykleBagna(int,Stworzenie * = nullptr);
	virtual ~ZwykleBagna();
};

#endif