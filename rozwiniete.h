#ifndef ROZWINIETE_H
#define ROZWINIETE_H
#include "stworzenie.h"

class Rozwiniete : public Stworzenie
{
public:
	Rozwiniete(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	virtual ~Rozwiniete();
	
	virtual bool ruszSie();
	bool inteligentny() const; //tak, jest
	bool czlowiek() const; //tak
protected:
	virtual bool ruszSie(Kierunek) = 0;
};

#endif
