#include "textplansza.h"
#include "gra.h"
#include <map>
#include <string>

TextPlansza::TextPlansza(QWidget *parent) :
    QTextBrowser(parent)
{
    setFontFamily("monospace");
    setLineWrapMode(QTextEdit::NoWrap);
}

char pokaz(const Pole& pole)
{
    static map<string,char> pola = {
        { "Trawy", '.' },
        { "Skaly", '#' },
        { "Pagorki", '^' },
        { "Bagna", '&' },
        { "Drogi", '=' },
        { "Rzeki", '~' },
        { "Jaskinie", '*' }
    };

    if(pole.puste())
    {
        if(pole.widacSkarb()) return '$';
        return pola[pole.przedstaw()];
    }
    else return pole.stworzenie()->przedstaw()[0];
}


void TextPlansza::pokazPlansze(Gra const * gra)
{
    int w = 0;
    const Pole * cel;
    QString plansza;
    for(int i = 0; i < gra->yRozmiar(); ++i)
    {
        for(int j = 0; j < gra->xRozmiar(); ++j)
        {
            cel = gra->pole(w);
            plansza.append(pokaz(*cel));
            ++w;
        }
        plansza.append("\n");
    }
    setText(plansza);
}
