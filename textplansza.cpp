#include "textplansza.h"
#include "gra.h"
#include <map>
#include <string>
#include <tuple>
#include <QColor>

using std::tuple;
using std::make_tuple;
using std::get;

TextPlansza::TextPlansza(QWidget *parent) :
	QTextBrowser(parent)
{
	setFontFamily("monospace");
	setLineWrapMode(QTextEdit::NoWrap);
	zoomIn(13);
}

tuple<char, QColor> pokaz(const Pole& pole)
{

	static const std::map<string,tuple<char, QColor>> wyglad = {
		{ Trawy::wyglad, make_tuple('.', Qt::green) },
		{ Skaly::wyglad, make_tuple('#', Qt::darkGray) },
		{ Pagorki::wyglad, make_tuple('^', Qt::red) },
		{ Bagna::wyglad, make_tuple('&', Qt::darkCyan) },
		{ Drogi::wyglad, make_tuple('=', Qt::yellow) },
		{ Rzeki::wyglad, make_tuple('~', Qt::blue) },
		{ Jaskinie::wyglad, make_tuple('*', Qt::gray) },
		{ Skarb::wyglad, make_tuple('$', Qt::gray) }
	};


	if(pole.puste())
	{
		return wyglad.find(pole.przedstaw())->second;
	}
	else
	{
		char sign = pole.stworzenie()->przedstaw()[0];
		QColor bgColor = get<1>(wyglad.find(pole.przedstaw())->second);
		return make_tuple(sign, bgColor);
	}
}


void TextPlansza::pokazPlansze(Gra const * gra)
{
	int w = 0;
	const Pole * cel;
	clear();
	for(int i = 0; i < gra->yRozmiar(); ++i)
	{
		for(int j = 0; j < gra->xRozmiar(); ++j)
		{
			cel = gra->pole(w);
			tuple<char, QColor> wyg = pokaz(*cel);
			setTextBackgroundColor(get<1>(wyg));
			insertPlainText(QString(get<0>(wyg)));
			++w;
		}
		insertPlainText("\n");
	}
}
