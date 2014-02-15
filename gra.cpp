#include "gra.h"
#include "pole.h"
#include "stworzenia.h"
#include <cassert>

Gra::Gra(std::istream& input)
	: _stanGry(Stan::TRWA), _komunikaty(), _gen(), _milosz(_gen, &_komunikaty)
{
	int n=0, m=0;
	input >> n >> m;
	if( n < 1 || n > 1000 || m < 1 || m > 1000)
	{
		_stanGry = Stan::BLAD;
		_xSize = _ySize = 0;
		_teren = new Pole*[0];
		return;
	}
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
				dead = _gen(std::uniform_real_distribution<float>(0.0, 1.0));
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
				_skarb = _teren[w] = new Skarb(w);
				break;
			case '*':
				_teren[w] = new Jaskinie(w);
				break;
			default:
				_stanGry = Stan::BLAD;
				return;
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
	int rozmiarPlanszy = _xSize * _ySize;

	for(Kierunek k : { Kierunek::DOL, Kierunek::GORA, Kierunek::LEWO, Kierunek::PRAWO })
		for(w = 0; w < rozmiarPlanszy; ++w)
		{
			int z = w + wKierunku(k);
			if(z >= 0 && z < rozmiarPlanszy)
				_teren[w]->ustawSasiada(k, _teren[z]);
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
			_stanGry = Stan::BLAD;
			return;
		}
		if(stw != &_milosz)
			_stworzenia.push_back(stw);

		if(stw->pole() != nullptr)
		{
			_stanGry = Stan::BLAD;
			return;
		}
		if(! stw->postaw(pole))
		{
			_stanGry = Stan::BLAD;
			return;
		}
	}
}

Gra::~Gra()
{
	for(Stworzenie * i : _stworzenia)
		delete i;
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
	if(_stanGry != Stan::TRWA) return false;
	
	if(_milosz.pole()->obok(kier)->ruch() > _milosz.ruch())
		tura();
	
	bool res = _milosz.ruszSie(kier);
	if(_milosz.martwy())
	{
		_stanGry = Stan::PRZEGRANA;
		_komunikaty.push(string("Umarłeś!"));
		_komunikaty.push(string("Przegrana!"));
	}
	if(_milosz.pole()->skarb())
	{
		_stanGry = Stan::WYGRANA;
		_komunikaty.push(string("Tu jest skarb!"));
		_komunikaty.push(string("Wygrana!"));
	}
	return res;
}

void Gra::tura()
{
	if(_stanGry != Stan::TRWA) return;
	
	turaStworzen();
	nastepnaTura();
}

void Gra::zakoncz()
{
	_stanGry = Stan::KONIEC;
}

Pole const * Gra::pole(int w) const
{
	if(w < 0 || w >= _xSize * _ySize)
	{
		return nullptr;
	}
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

std::pair<int, int> Gra::rozmiar() const
{
	return std::pair<int,int>(_xSize, _ySize);
}

int Gra::xRozmiar() const
{
	return _xSize;
}

int Gra::yRozmiar() const
{
	return _ySize;
}

std::pair<int, int> Gra::wspolrzedne(int w) const
{
	return std::pair<int,int>(x(w), y(w));
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
	for(Stworzenie * i : _stworzenia)
	{
		if(i->ruszSie())
			_stanGry = Stan::PRZEGRANA;
	}
}

void Gra::nastepnaTura()
{
	for(Stworzenie * i : _stworzenia)
		i->tura();
	_milosz.tura();
}

int Gra::wKierunku(Kierunek kier)
{
	switch(kier)
	{
	case Kierunek::LEWO: return -1;
	case Kierunek::PRAWO: return 1;
	case Kierunek::GORA: return -_xSize;
	case Kierunek::DOL: return _xSize;
	default: return 0;
	}
}
