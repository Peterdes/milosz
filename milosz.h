#ifndef MILOSZ_H
#define MILOSZ_H
#include "rozwiniete.h"

class Milosz : public Poszukiwacz
{
public:
	Milosz(RandEngine& gen, queue<string> *const komunikaty);
	virtual ~Milosz();
	Milosz(const Milosz&) = delete;
	Milosz& operator=(const Milosz&) = delete;
	
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
