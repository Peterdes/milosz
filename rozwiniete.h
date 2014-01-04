#ifndef ROZWINIETE_H
#define ROZWINIETE_H
#include "stworzenie.h"
#include <random>

class Gra;

class Rozwiniete : public Stworzenie
{
public:
	Rozwiniete(queue<string> *const komunikaty, int ruch, int sila, int maxZdrowie, int zdrowie = 0);
	virtual ~Rozwiniete();
	
	virtual bool ruszSie();
	bool inteligentny() const; //tak, jest
	bool czlowiek() const; //tak
protected:
	virtual bool ruszSie(Kierunek) = 0;
};


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
    static uniform_real_distribution<float> dist;

    void init();
};


class Znachorka : public Rozwiniete
{
public:
    Znachorka(queue<string> *const komunikaty,
         int ruch, int sila, int maxZdrowie, int zdrowie = 0);
    Znachorka(queue<string> *const, std::mt19937&);
    virtual ~Znachorka();

    const string& przedstaw() const;
    bool ruszSie();
    void rozmawiaj(Stworzenie *); //spróbuj uleczyć
protected:
    bool ruszSie(Kierunek);
private:
    static const string wyglad;
};


class Bard : public Rozwiniete
{
public:
    Bard(const Gra * gra, Pole * skarb, queue<string> *const komunikaty,
         int ruch, int sila, int maxZdrowie, int zdrowie = 0);
    Bard(const Gra *, Pole *, queue<string> *const, std::mt19937&);
    virtual ~Bard();
    const string& przedstaw() const;
    bool ruszSie();
    void rozmawiaj(Stworzenie *); //śpiewaj
protected:
    bool ruszSie(Kierunek);
private:
    static const string wyglad;
    Pole * _skarb;
    const Gra * _gra;
};


class Poszukiwacz : public Rozwiniete
{
public:
    Poszukiwacz(float zbroja, float bron, queue<string> *const komunikaty,
         int ruch, int sila, int maxZdrowie, int zdrowie = 0);
    Poszukiwacz(std::mt19937& gen, queue<string> *const komunikaty,
         int ruch, int sila, int maxZdrowie, int zdrowie = 0);
    Poszukiwacz(queue<string> *const, std::mt19937&);
    virtual ~Poszukiwacz();

    virtual const string& przedstaw() const;
    virtual bool ruszSie();
    float zbroja() const;
    float bron() const;
    void rozmawiaj(Stworzenie *); //ignoruj
    bool wezZbroje(float);  //chetnie
    bool wezBron(float);  //jasne

protected:
    virtual bool ruszSie(Kierunek);

private:
    float _zbroja;
    float _bron;
    static const string wyglad;
};


#endif
