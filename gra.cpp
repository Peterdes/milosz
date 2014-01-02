#include "gra.h"
#include "pola.h"
#include "stworzenia.h"
#include <cassert>

using namespace std;

Gra::Gra(istream& input)
: _stanGry(TRWA), _komunikaty(), _gen(), _milosz(_gen, &_komunikaty)
{
	int n, m;
	input >> n >> m;
	_ySize = n + 2;
	_xSize = m + 2;
	_teren = new Pole*[_ySize * _xSize];
	int w = 0;
	for(; w < _xSize; ++w)
		_teren[w] = new Skaly(w);
	for(int i = 0; i < n; ++i)
	{
		_teren[w] = new Skaly(w);
		++w;
		string wiersz;
		input >> wiersz;
		for(int j = 0; j < m; ++j)
		{
			float dead;
			switch(wiersz[j])
			{
				case '#':
					_teren[w] = new Skaly(w);
					break;
				case '^':
					_teren[w] = new Pagorki(w);
					break;
				case '&':
					dead = uniform_real_distribution<float>(0.0, 1.0)(_gen);
					if(dead < 0.05) _teren[w] = new MartweBagna(w);
					else _teren[w] = new ZwykleBagna(w);
					break;
				case '.':
					_teren[w] = new Trawy(w);
					break;
				case '=':
					_teren[w] = new Drogi(w);
					break;
				case '~':
					_teren[w] = new Rzeki(w);
					break;
				case '$':
					_skarb = _teren[w] = new Jaskinie(w);
					_teren[w]->postawSkarb();
					break;
				case '*':
					_teren[w] = new Jaskinie(w);
					break;
				default:
					assert(0 == 1);
			}
			++w;
		}
		_teren[w] = new Skaly(w);
		++w;
	}
	for(int j = 0; j < _xSize; ++j)
	{
		_teren[w] = new Skaly(w);
		++w;
	}
	for(int i = 0; i < _xSize - 1; ++i)
	{
		for(int j = 0; j < _ySize; ++j)
		{
			w = wsp(i, j);
			_teren[w]->ustawSasiada(PRAWO, _teren[w+1]);
		}
	}
	for(int i = 0; i < _xSize; ++i)
	{
		for(int j = 0; j < _ySize - 1; ++j)
		{
			w = wsp(i, j);
			_teren[w]->ustawSasiada(DOL, _teren[w+_xSize]);
		}
	}
	for(int i = 1; i < _xSize; ++i)
	{
		for(int j = 0; j < _ySize; ++j)
		{
			w = wsp(i, j);
			_teren[w]->ustawSasiada(LEWO, _teren[w-1]);
		}
	}
	for(int i = 0; i < _xSize; ++i)
	{
		for(int j = 1; j < _ySize; ++j)
		{
			w = wsp(i, j);
			_teren[w]->ustawSasiada(GORA, _teren[w-_xSize]);
		}
	}
	
	string nazw;
	int x, y;
	while(input >> nazw >> y >> x)
	{
		Pole * pole = _teren[wsp(x,y)];
		Stworzenie * stw;
		switch(nazw[0])
		{
			case 'M':
				stw = &_milosz;
				break;
			case 'S':
				stw = new Sklepikarz(&_komunikaty, _gen);
				break;
			case 'Z':
				stw = new Znachorka(&_komunikaty, _gen);
				break;
			case 'B':
				stw = new Bard(this, _skarb, &_komunikaty, _gen);
				break;
			case 'P':
				stw = new Poszukiwacz(&_komunikaty, _gen);
				break;
			case 'W':
				stw = new Wybredne(&_komunikaty, _gen);
				break;
			case 'A':
				stw = new Agresywne(&_komunikaty, _gen);
				break;
			case 'T':
				stw = new Tchorzliwe(&_komunikaty, _gen);
				break;
			case 'N':
				stw = new Neutralne(&_komunikaty, _gen);
				break;
			default:
				assert( 0 == 1 );
		}
		if(stw != &_milosz)
			_stworzenia.push_back(stw);
		assert( stw->postaw(pole) );
	}
}

Gra::~Gra()
{
	for(vector<Stworzenie*>::iterator i = _stworzenia.begin();
	    i != _stworzenia.end(); ++i)
		delete (*i);
	int size = _xSize * _ySize;
	for(int i = 0; i < size; ++i)
		delete _teren[i];
	delete [] _teren;
}

Stan Gra::stan() const
{
	return _stanGry;
}

bool Gra::idz(Kierunek kier)
{
	if(_stanGry > 0) return false;
	
	bool res = _milosz.ruszSie(kier);
	if(_milosz.pole()->skarb())
	{
		_stanGry = WYGRANA;
		_komunikaty.push(string("Tu jest skarb!"));
		_komunikaty.push(string("Wygrana!"));
	}
	return res;
}

void Gra::tura()
{
	if(_stanGry > 0) return;
	
	turaStworzen();
	nastepnaTura();
}

void Gra::zakoncz()
{
	_stanGry = KONIEC;
}

Pole const * Gra::pole(int w)
{
	return _teren[w];
}

bool Gra::komunikat() const
{
	return ! _komunikaty.empty();
}

string Gra::czytajKomunikat()
{
	string str = _komunikaty.front();
	_komunikaty.pop();
	return str;
}

Milosz const & Gra::milosz() const
{
	return _milosz;
}

pair<int, int> Gra::rozmiar() const
{
	return pair<int,int>(_xSize, _ySize);
}

int Gra::xRozmiar() const
{
	return _xSize;
}

int Gra::yRozmiar() const
{
	return _ySize;
}

pair<int, int> Gra::wspolrzedne(int w) const
{
	return pair<int,int>(x(w), y(w));
}

int Gra::x(int w) const
{
	return w % _xSize;
}

int Gra::y(int w) const
{
	return w / _xSize;
}

int Gra::x(const Pole & pole) const
{
	return x(pole.wspolrzedne());
}

int Gra::x(const Stworzenie & stw) const
{
	return x(stw.pole()->wspolrzedne());
}

int Gra::y(const Pole &  pole) const
{
	return y(pole.wspolrzedne());
}

int Gra::y(const Stworzenie & stw) const
{
	return y(stw.pole()->wspolrzedne());
}

int Gra::wsp(int x, int y) const
{
	return y * _xSize + x;
}

int Gra::liczbaStworzen() const
{
	return _stworzenia.size();
}

Stworzenie const * Gra::stworzenie(int n) const
{
	return _stworzenia[n];
}

void Gra::turaStworzen()
{
	for(vector<Stworzenie *>::iterator i = _stworzenia.begin(); i != _stworzenia.end(); ++i)
	{
		if((*i)->ruszSie())
			_stanGry = PRZEGRANA;
	}
}

void Gra::nastepnaTura()
{
	for(vector<Stworzenie *>::iterator i = _stworzenia.begin(); i != _stworzenia.end(); ++i)
		(*i)->tura();
	_milosz.tura();
}

int Gra::wKierunku(Kierunek kier)
{
	switch(kier)
	{
		case LEWO: return -1;
		case PRAWO: return 1;
		case GORA: return _xSize;
		case DOL: return _ySize;
		default: return 0;
	}
}
