#ifndef TEXTPLANSZA_H
#define TEXTPLANSZA_H

#include <QTextBrowser>

class Gra;

class TextPlansza : public QTextBrowser
{
    Q_OBJECT
public:
    explicit TextPlansza(QWidget *parent = 0);

signals:

public slots:
    void pokazPlansze(Gra const * gra);

};

#endif // TEXTPLANSZA_H
