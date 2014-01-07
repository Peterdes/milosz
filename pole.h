#ifndef POLE_H
#define POLE_H
#include <string>

using std::string;

class Stworzenie;

enum class Kierunek : int { LEWO = 0, DOL = 1, GORA = 2, PRAWO = 3 };

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
	virtual bool pokazSkarb();
	/*
	 * Czy widac na nim skarb?
	 */
	virtual bool widacSkarb() const;
	/*
	 * Czy jest na nim skarb?
	 */
	virtual bool skarb() const;
	/*
	 * Ustaw sąsiada
	 */
	void ustawSasiada(Kierunek, Pole *);
private:
	Pole(const Pole&);
	Pole& operator=(Pole& inne); //nie chcemy

	int _w; //współrzędne
	Pole * _sasiad[4];
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


class Skaly : public PoleNiedostepne
{
public:
    Skaly(int);
    virtual ~Skaly();
	const string& przedstaw() const;
    static const string wyglad;
};

class Trawy : public PoleDostepne
{
public:
    Trawy(int,Stworzenie * = nullptr);
    virtual ~Trawy();
    const string& przedstaw() const;
	int ruch() const;
    static const string wyglad;
};

class Drogi : public PoleDostepne
{
public:
    Drogi(int,Stworzenie * = nullptr);
    virtual ~Drogi();
    const string& przedstaw() const;
	int ruch() const;
    static const string wyglad;
};

class Pagorki : public PoleDostepne
{
public:
    Pagorki(int,Stworzenie * = nullptr);
    virtual ~Pagorki();
    virtual const string& przedstaw() const;
	virtual int ruch() const;
    static const string wyglad;
};

class Jaskinie : public Pagorki
{
public:
    Jaskinie(int,Stworzenie * = nullptr);
    virtual ~Jaskinie();
	virtual const string& przedstaw() const;
    static const string wyglad;
};

class Skarb : public Jaskinie
{
public:
	Skarb(int);
	virtual ~Skarb();
	const string& przedstaw() const;
	bool pokazSkarb();
	bool skarb() const;
	bool widacSkarb() const;
	static const string wyglad;
private:
	bool widac;
};

class Rzeki : public PoleDostepne
{
public:
    Rzeki(int,Stworzenie * = nullptr);
    virtual ~Rzeki();
    const string& przedstaw() const;
    int ruch() const;
	int obrazenia() const;
    static const string wyglad;
};

class Bagna : public PoleDostepne
{
public:
    Bagna(int,Stworzenie * = nullptr);
    virtual ~Bagna();
    const string& przedstaw() const;
	int ruch() const;
    static const string wyglad;
};

class MartweBagna : public Bagna
{
public:
    MartweBagna(int,Stworzenie * = nullptr);
    virtual ~MartweBagna();
    /*
    * Prymitywny chwyt: zwracam obrażenia przekraczające życie
    * dowolnej istniejącej jednostki
    */
    int obrazenia() const;
};

class ZwykleBagna : public Bagna
{
public:
    ZwykleBagna(int,Stworzenie * = nullptr);
    virtual ~ZwykleBagna();
};


#endif
