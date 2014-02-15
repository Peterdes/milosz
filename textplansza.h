#ifndef TEXTPLANSZA_H
#define TEXTPLANSZA_H

#include <QTextBrowser>

class Gra;

class TextPlansza : public QTextBrowser
{
	Q_OBJECT
public:
	explicit TextPlansza(QWidget *parent = 0);
	virtual ~TextPlansza();
	TextPlansza(const TextPlansza&) = delete;
	TextPlansza& operator=(const TextPlansza&) = delete;

signals:

public slots:
	void pokazPlansze(Gra const * gra);
	void przybliz();
	void oddal();

private:
	int _zoom;

};

#endif // TEXTPLANSZA_H
