#ifndef GRA_H
#define GRA_H
#include <istream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include "randengine.h"

enum class Stan { TRWA, KONIEC, WYGRANA, PRZEGRANA, BLAD };

using std::vector;
using std::queue;
using std::string;

#include "pole.h"
#include "milosz.h"

class Gra
{
public:
	/*
	 * Konstruuje grę z planszy ze strumienia
	 */
	Gra(std::istream&);
	/*
	 * Destruktor
	 */
	~Gra();
	/*
	 * Kopiowania nie obsługujemy
	 */
	Gra(const Gra&) = delete;
	Gra& operator=(const Gra&) = delete;
	/*
	 * Zwraca stan gry.
	 */
	Stan stan() const;
	/*
	 * Wykonuje ruch Miłoszem.
	 */
	bool idz(Kierunek);
	/*
	 * Kończy ruch Miłosza w tej turze.
	 */
	void tura();
	/*
	 * Kończy grę.
	 * Nie da się już wykonać ruchu, wypisuję końcowe komunikaty.
	 */
	void zakoncz();
	/*
	 * Zwraca identyfikator pola o danych współrzędnych
	 */
    Pole const * pole(int w) const;
	/*
	 * Komunikaty wysyłam do interfejsu wrzucając je na kolejkę (do bufora).
	 * Komunikaty są trzymane w Miłoszu - chyba słabe rozwiązanie, ale na
	 * potrzeby tej specyfikacji wystarczy.
	 */
	bool komunikat() const; //czy oczekuje jakiś komunikat?
	string czytajKomunikat();
	/*
	 * Wskazuje na Miłosza
	 */
	Milosz const & milosz() const;
	/*
	 * Informują o rozmiarze
	 */
	std::pair<int, int> rozmiar() const;
	int xRozmiar() const;
	int yRozmiar() const;
	/*
	 * Liczą współrzędne
	 */
	std::pair<int, int> wspolrzedne(int) const;
	int x(int) const;
	int x(const Pole &) const;
	int x(const Stworzenie &) const;
	int y(int) const;
	int y(const Pole &) const;
	int y(const Stworzenie &) const;
	int wsp(int x,int y) const;
	/*
	 * Wskazują na stworzenia inne od Miłosza
	 */
	int liczbaStworzen() const;
	Stworzenie const * stworzenie(int n) const;
	
private:
	Stan _stanGry; //stan gry
	Pole* *_teren; //pola na planszy -> 1-wymiarowa tablica wskaźników na pola
	int _xSize, _ySize; //współrzędne
	vector<Stworzenie *> _stworzenia; //stworzenia w grze
	queue<string> _komunikaty; //kolejka z komunikatami
	RandEngine _gen;
	Pole * _skarb;
	
	Milosz _milosz; //nasz bohater
	/*
	 * Wykonuje ruchy wszystkimi stworzeniami innymi niż Miłosz
	 */
	void turaStworzen();
	/*
	 * Kończy turę i otwiera następną
	 */
	void nastepnaTura();
	/*
	 * Funkcja pomocnicza do poruszania się po planszy.
	 * Planszę reprezentuję jednowymiarową tablicą, więc
	 * chciałbym wiedzieć, co w tym wymiarze znaczy
	 * "pójść do góry" albo "pójść do dołu"
	 */
	int wKierunku(Kierunek);
};

#endif
