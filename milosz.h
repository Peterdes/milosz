#ifndef MILOSZ_H
#define MILOSZ_H
#include "rozwiniete.h"

class Milosz : public Poszukiwacz
{
public:
	Milosz(std::mt19937& gen, queue<string> *const komunikaty);
	virtual ~Milosz();
	
	const string& przedstaw() const;
	bool ruszSie(); //nic nie rób
	bool ruszSie(Kierunek);
	bool dajPrezent(); //chętnie
	bool wezPrezent(); //chętnie
	bool prezent() const;
	bool milosz() const; //tak
private:
	static const string wyglad;
	bool _prezent;
};

#endif
