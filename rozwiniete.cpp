#include "rozwiniete.h"
#include "pole.h"

Rozwiniete::Rozwiniete(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie)
: Stworzenie(komunikaty, ruch, sila, maxZdrowie, zdrowie) {}

Rozwiniete::~Rozwiniete() {}

bool Rozwiniete::ruszSie()
{
	int k = 0;
	while(ruch() > 0 && k != 4 && pole() != nullptr)
	{
		int ruchy = losujRuchy();
		for(k = 0; k < 4 && ruch() > 0; ++k)
		{
			int kier = ruchy % 4;
			ruchy >>= 2;
			if(! pole()->obok(Kierunek(kier))->puste())
				if(ruszSie(Kierunek(kier)))
					break;
		}
	}
	return false;
}

bool Rozwiniete::inteligentny() const
{
	return true;
}

bool Rozwiniete::czlowiek() const
{
	return true;
}
