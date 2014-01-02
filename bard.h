#ifndef BARD_H
#define BARD_H
#include "rozwiniete.h"
#include <random>

class Gra;

class Bard : public Rozwiniete
{
public:
	Bard(const Gra * gra, Pole * skarb, queue<string> *const komunikaty,
	     int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Bard(const Gra *, Pole *, queue<string> *const, std::mt19937&);
	virtual ~Bard();
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

#endif
