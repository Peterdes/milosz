#ifndef ZNACHORKA_H
#define ZNACHORKA_H
#include "rozwiniete.h"
#include <random>

class Znachorka : public Rozwiniete
{
public:
	Znachorka(queue<string> *const komunikaty,
	     int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Znachorka(queue<string> *const, std::mt19937&);
	virtual ~Znachorka();
	
	const string& przedstaw() const;
	bool ruszSie();
	void rozmawiaj(Stworzenie *); //spróbuj uleczyć
protected:
	bool ruszSie(Kierunek);
private:
	static const string wyglad;
};

#endif
