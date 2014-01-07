#ifndef MILOSZQT_H
#define MILOSZQT_H

#include <QMainWindow>
#include "gra.h"
#include <QListWidget>

class miloszqt : public QMainWindow
{
	Q_OBJECT

public:
	explicit miloszqt(QWidget *parent = 0);
	~miloszqt();

	void idz(Kierunek kier);
	void tura();

	void zaladuj();
	void ustawZrodlo(const QString&);

	void odswiez();

signals:
	void zycieChanged(int zycie,int max);
	void ruchChanged(int ruch,int max);
	void zbrojaChanged(float zbroja);
	void bronChanged(float bron);
	void prezentChanged(bool prezent);
	void planszaChanged(Gra const * g);
	void dodanyKomunikat(const QString &);

private:
	Gra * _gra;
	QString _plik;
	QListWidget *_komunikaty;
	void powitaj();
};

#endif // MILOSZQT_H
