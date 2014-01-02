#include "gra.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>

using namespace std;

map<string,char> pola = {
	{ "Trawy", '.' },
	{ "Skaly", '#' },
	{ "Pagorki", '^' },
	{ "Bagna", '&' },
	{ "Drogi", '=' },
	{ "Rzeki", '~' },
	{ "Jaskinie", '*' }
};

char pokaz(const Pole& pole)
{
	if(pole.puste())
	{
		if(pole.widacSkarb()) return '$';
		return pola[pole.przedstaw()];
	}
	else return pole.stworzenie()->przedstaw()[0];
}

void pokaz(Gra& gra)
{
	while(gra.komunikat())
		cout << gra.czytajKomunikat() << endl;
	int w = 0;
	const Pole * cel;
	for(int i = 0; i < gra.yRozmiar(); ++i)
	{
		for(int j = 0; j < gra.xRozmiar(); ++j)
		{
			cel = gra.pole(w);
			cout << pokaz(*cel);
			++w;
		}
		cout << endl;
	}
	cout << std::fixed << std::setprecision(2);
	cout << "HP: " << gra.milosz().zdrowie() << "/100  |  "
		<< "R: " << gra.milosz().ruch() << "/100 |  "
		<< "S: " << gra.milosz().sila() << "  |  "
		<< "Z: " << gra.milosz().zbroja() << "  |  "
		<< "B: " << gra.milosz().bron() << "  |  "
		<< "P: " << gra.milosz().prezent() << endl;
}

int main(int argc, char* *argv)
{
	string polecenie;
	while(true)
	{
		if(polecenie[0] == 'w')
		{
			cout << "Do zobaczenia!" << endl;
			break;
		}
		fstream wejscie;
		wejscie.open(argv[1]);
		if(wejscie.good())
		{
			cout << "Zaczynamy!" << endl;
			Gra gra(wejscie);
			pokaz(gra);
			
			while(gra.stan() == TRWA)
			{
				cin >> polecenie;
				switch(polecenie[0])
				{
					case 'l':
						gra.idz(LEWO);
						break;
					case 'p':
						gra.idz(PRAWO);
						break;
					case 'g':
						gra.idz(GORA);
						break;
					case 'd':
						gra.idz(DOL);
						break;
					case 'w':
						gra.zakoncz();
						break;
					case 'n':
					case 't':
						gra.tura();
						break;
				}
				pokaz(gra);
			}
			if(gra.stan() == KONIEC)
				cout << "Zakonczyles gre." << endl;
			else if(gra.stan() == WYGRANA)
				cout << "Gratulacje! Wygrana!" << endl << endl << endl;
			else if(gra.stan() == PRZEGRANA)
				cout << "Niestety, ktos Cie uprzedzil." << endl << endl << endl;
			else return 123;
		}
		else cout << "Nie udalo sie otworzyc pliku." << endl;
		wejscie.close();
	}
	
	return 0;
}
