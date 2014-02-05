#ifndef STWORZENIE_H
#define STWORZENIE_H
#include <queue>
#include <string>
#include "randengine.h"
#include <array>
#include "pole.h"

using std::queue;
using std::string;

class Stworzenie
{
public:
	Stworzenie(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	virtual ~Stworzenie();
	/*
	 * Poniższe mówią same za siebie
	 */
	int maxRuch() const;
	int ruch() const;
	int maxZdrowie() const;
	int zdrowie() const;
	int sila() const;
	bool martwy() const;
	virtual float zbroja() const; //domyślnie 0
	virtual float bron() const; //domyślnie 0
	/*
	 * Czy jestem inteligentny?
	 */
	virtual bool inteligentny() const = 0;
	/*
	 * Czy jestem człowiekiem?
	 */
	virtual bool czlowiek() const = 0;
	/*
	 * Czy jestem Miłoszem?
	 */
	virtual bool milosz() const;
	/*
	* Podobnie jak przy polach
	*/
	virtual const string& przedstaw() const = 0;
	/*
	* Położenie
	*/
	Pole * pole();
	Pole const * pole() const;
	int wspolrzedne() const;
	
	/*
	 * Wykonaj ruch na swój sposób - gdzie sobie chcesz
	 */
	virtual bool ruszSie() = 0;
	
	/*
	 * Spróbuj przyjąć prezent; domyślnie nie biorę
	 */
	virtual bool wezPrezent();
	/*
	 * Spróbuj przyjąć zbroję
	 */
	virtual bool wezZbroje(float);
	/*
	 * Spróbuj przyjąć broń
	 */
	virtual bool wezBron(float);
	/*
	 * Spróbuj oddać prezent
	 */
	virtual bool dajPrezent();
	/*
	 * Ulecz
	 */
	void ulecz(int);
	void ulecz();
	/*
	 * Rozmawiaj ze stworzeniem. Tu wkładamy m.in. mechanikę sklepikarza,
	 * znachorki, barda etc.; domyślnie nic nie robię
	 */
	virtual void rozmawiaj(Stworzenie *);
	/*
	 * Zakończ turę
	 */
	virtual void tura();
	/*
	 * Postaw na danym polu
	 */
	bool postaw(Pole *);
protected:
	/*
	 * Poniższe same się wyjaśniają
	 */
	int _pktyRuchu;
	const int _maxRuchu;
	int _pktyZdrowia;
	const int _maxZdrowia;
	
	const int _sila;
	
	/*
	 * Wykonaj ruch w danym kierunku
	 */
	virtual bool ruszSie(Kierunek) = 0;
	/*
	 * Walcz ze stworzeniem!
	 */
	bool walcz(Stworzenie * przeciwnik);
	/*
	 * Wejdź na pole, jeśli się da
	 */
	bool wejdz(Pole * docelowe);
	/*
	 * Losuj kierunki ruchu
	 */
	static std::array<Kierunek,4> losujRuchy();
	
	queue<string> * const _komunikaty; //gdzie wyrzucamy komunikaty
	
private:
	Stworzenie(const Stworzenie&);
	Stworzenie& operator=(Stworzenie& inne); //nie chcemy
	
	Pole * _pole; //gdzie stoimy
	
	/*
	 * Przyjmujemy na klate
	 */
	void oberwij(int obraz);
	/*
	 * Uderz stworzenie! Tu będzie wzór na obrażenia.
	 */
	int obrazenia(Stworzenie * ofiara);
};

#endif
