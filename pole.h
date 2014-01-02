#ifndef POLE_H
#define POLE_H
#include <string>

class Stworzenie;

using namespace std;

enum Kierunek { LEWO, DOL, GORA, PRAWO };

class Pole
{
public:
	Pole(int); //konstruktor
	virtual ~Pole(); //destruktor
	/*
	 * Informuje o rodzaju pola
	 */
	virtual const string& przedstaw() const = 0;
	/*
	 * Usuwa stworzenie z pola -> przy dostepnym polu coś robi
	 */
	virtual void czysc() = 0;
	/*
	 * Czy nie ma na nim nikogo?
	 */
	virtual bool puste() const = 0;
	/*
	 * Czy da się po nim chodzić?
	 */
	virtual bool dostepne() const = 0;
	/*
	 * Ile obrażeń zabiera? Domyślnie 0!
	 */
	virtual int obrazenia() const;
	/*
	 * Ile punktów ruchu zabiera?
	 */
	virtual int ruch() const = 0;
	/*
	 * Zwraca wskaźnik na stworzenie na tym polu
	 */
	virtual Stworzenie * stworzenie() = 0;
	virtual Stworzenie const * stworzenie() const = 0;
	/*
	 * Wypisuje współrzędne
	 */
	int wspolrzedne() const;
	/*
	 * Wypisuje pole obok
	 */
	Pole * obok(Kierunek);
	Pole const * obok(Kierunek) const;
	/*
	 * Ustawia stworzenie na danym polu, jeśli się da
	 */
	virtual bool postaw(Stworzenie *) = 0;
	/*
	 * Pokazuje skarb
	 */
	bool pokazSkarb();
	/*
	 * Czy widac na nim skarb?
	 */
	bool widacSkarb() const;
	/*
	 * Czy jest na nim skarb?
	 */
	bool skarb() const;
	/*
	 * Ustaw sąsiada
	 */
	void ustawSasiada(Kierunek, Pole *);
	/*
	 * Ustaw skarb
	 */
	void postawSkarb();
	/*
	 * Zdejmij skarb
	 */
	void zdejmijSkarb();
private:
	Pole(const Pole&);
	Pole& operator=(Pole& inne); //nie chcemy

	int _w; //współrzędne
	Pole * _sasiad[4];
	int _skarb; //czy jest tu skarb? 1 - tak, 2 - tak, widać
};


class PoleDostepne : public Pole
{
public:
	PoleDostepne(int, Stworzenie * = nullptr);
	virtual ~PoleDostepne();
	void czysc();
	bool puste() const;
	bool dostepne() const;
	Stworzenie * stworzenie();
	Stworzenie const * stworzenie() const;
private:
	bool postaw(Stworzenie * stw);
	Stworzenie * _stworzenie;
};


class PoleNiedostepne : public Pole
{
public:
	PoleNiedostepne(int);
	virtual ~PoleNiedostepne();
	void czysc();
	bool puste() const;
	bool dostepne() const;
	Stworzenie * stworzenie();
	Stworzenie const * stworzenie() const;
	int ruch() const; //zwraca 0
private:
	bool postaw(Stworzenie * stw);
};


#endif
