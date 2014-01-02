#ifndef POSZUKIWACZ_H
#define POSZUKIWACZ_H
#include "rozwiniete.h"
#include <random>

class Poszukiwacz : public Rozwiniete
{
public:
	Poszukiwacz(float zbroja, float bron, queue<string> *const komunikaty,
	     int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Poszukiwacz(std::mt19937& gen, queue<string> *const komunikaty,
	     int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Poszukiwacz(queue<string> *const, std::mt19937&);
	virtual ~Poszukiwacz();
	
	virtual const string& przedstaw() const;
	virtual bool ruszSie();
	float zbroja() const;
	float bron() const;
	void rozmawiaj(Stworzenie *); //ignoruj
	bool wezZbroje(float);  //chetnie
	bool wezBron(float);  //jasne
	
protected:
	virtual bool ruszSie(Kierunek);
	
private:
	float _zbroja;
	float _bron;
	static const string wyglad;
};

#endif
