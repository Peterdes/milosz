#ifndef PRYMITYWNE_H
#define PRYMITYWNE_H
#include "stworzenie.h"
#include "randengine.h"

class Prymitywne : public Stworzenie
{
public:
	Prymitywne(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Prymitywne(queue<string> *const komunikaty, RandEngine&);
	virtual ~Prymitywne();
	virtual bool ruszSie();
	bool inteligentny() const; //nie, głupi
	bool czlowiek() const; //nie
protected:
	virtual bool ruszSie(Kierunek) = 0;
};

class Agresywne : public Prymitywne
{
public:
	Agresywne(queue<string> *const komunikaty, RandEngine&);
	virtual ~Agresywne();
	const string& przedstaw() const;
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
};

class Wybredne : public Prymitywne
{
public:
	Wybredne(queue<string> *const komunikaty, RandEngine&);
	virtual ~Wybredne();
	const string& przedstaw() const;
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
};

class Tchorzliwe : public Prymitywne
{
public:
	Tchorzliwe(queue<string> *const komunikaty, RandEngine&);
	virtual ~Tchorzliwe();
	const string& przedstaw() const;
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
};

class Neutralne : public Prymitywne
{
public:
	Neutralne(queue<string> *const komunikaty, RandEngine&);
	virtual ~Neutralne();
	const string& przedstaw() const;
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
};

#endif
