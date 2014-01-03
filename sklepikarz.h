#ifndef SKLEPIKARZ_H
#define SKLEPIKARZ_H
#include "rozwiniete.h"
#include <random>


class Sklepikarz : public Rozwiniete
{
public:
	Sklepikarz(float dostawy, std::mt19937& gen, queue<string> *const komunikaty,
	     int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Sklepikarz(float, queue<string> *const, std::mt19937&);
	Sklepikarz(std::mt19937& gen, queue<string> *const komunikaty,
	     int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	Sklepikarz(queue<string> *const, std::mt19937&);
	virtual ~Sklepikarz();
	
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
	float _dostawy;	//prawdopodobienstwo dostawy
	std::mt19937& _gen;
	static uniform_real_distribution<float> dist;\
	
	void init();
};

#endif
