#ifndef ROZWINIETE_H
#define ROZWINIETE_H
#include "stworzenie.h"
#include "randengine.h"

class Gra;

class Rozwiniete : public Stworzenie
{
public:
	Rozwiniete(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	virtual ~Rozwiniete();
	Rozwiniete(const Rozwiniete&) = delete;
	Rozwiniete& operator=(const Rozwiniete&) = delete;
	
	virtual bool ruszSie();
	bool inteligentny() const; //tak, jest
	bool czlowiek() const; //tak
private:
	virtual bool ruszSie(Kierunek) = 0;
};


class Sklepikarz : public Rozwiniete
{
public:
	Sklepikarz(queue<string> *const, RandEngine&);
	virtual ~Sklepikarz();
	Sklepikarz(const Sklepikarz&) = delete;
	Sklepikarz& operator=(const Sklepikarz&) = delete;

	const string& przedstaw() const;
	bool ruszSie();
	void rozmawiaj(Stworzenie *); //sprzedaj

protected:
	bool ruszSie(Kierunek);
	
private:
	static const string wyglad;
	bool _maZbroje;
	float _zbroja;
	bool _maBron;
	float _bron;
	bool _maPrezent;
	static const float _dostawy;	//prawdopodobieństwo dostawy w danej turze

	RandEngine& _gen;
	static std::uniform_real_distribution<float> dist;

	void init();
};

class Znachorka : public Rozwiniete
{
public:
	Znachorka(queue<string> *const, RandEngine&);
	virtual ~Znachorka();
	Znachorka(const Znachorka&) = delete;
	Znachorka& operator=(const Znachorka&) = delete;

	const string& przedstaw() const;
	bool ruszSie();
	void rozmawiaj(Stworzenie *); //spróbuj uleczyć
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
};


class Bard : public Rozwiniete
{
public:
	Bard(const Gra *, Pole *, queue<string> *const, RandEngine&);
	virtual ~Bard();
	Bard(const Bard&) = delete;
	Bard& operator=(const Bard&) = delete;

	const string& przedstaw() const;
	bool ruszSie();
	void rozmawiaj(Stworzenie *); //śpiewaj
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
	Pole * _skarb;
	const Gra * _gra;
};


class Poszukiwacz : public Rozwiniete
{
public:
	Poszukiwacz(float zbroja, float bron, queue<string> *const komunikaty,
		int ruch, int sila, int maxZdrowie, int zdrowie);
	Poszukiwacz(queue<string> *const komunikaty,
		int ruch, int sila, int maxZdrowie, int zdrowie, RandEngine& gen);
	Poszukiwacz(queue<string> *const, RandEngine&);
	virtual ~Poszukiwacz();
	Poszukiwacz(const Poszukiwacz&) = delete;
	Poszukiwacz& operator=(const Poszukiwacz&) = delete;

	virtual const string& przedstaw() const;
	virtual bool ruszSie();
	float zbroja() const;
	float bron() const;
	void rozmawiaj(Stworzenie *); //ignoruj
	bool wezZbroje(float);  //chętnie
	bool wezBron(float);  //jasne

protected:
	virtual bool ruszSie(Kierunek);

private:
	float _zbroja;
	float _bron;
	static const string wyglad;
};


#endif
