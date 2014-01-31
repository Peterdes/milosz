#include "miloszqt.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QShortcut>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QListWidget>
#include <QLabel>
#include <fstream>
#include "textplansza.h"

miloszqt::miloszqt(QWidget *parent) :
	QMainWindow(parent)
{
	_gra = nullptr;

	QAction *goraAct = new QAction(QString("&Góra"), this);
	connect(goraAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::GORA); } );
	goraAct->setShortcuts({Qt::Key_G, Qt::Key_Up});

	QAction *dolAct = new QAction("&Dół", this);
	connect(dolAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::DOL); } );
	dolAct->setShortcuts({Qt::Key_D, Qt::Key_Down});

	QAction *lewoAct = new QAction("&Lewo", this);
	connect(lewoAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::LEWO); } );
	lewoAct->setShortcuts({Qt::Key_L, Qt::Key_Left});

	QAction *prawoAct = new QAction("&Prawo", this);
	connect(prawoAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::PRAWO); } );
	prawoAct->setShortcuts({Qt::Key_P, Qt::Key_Right});

	QAction *turaAct = new QAction("&Nowa tura", this);
	connect(turaAct, &QAction::triggered, this, &miloszqt::tura);
	turaAct->setShortcuts({Qt::Key_X, Qt::Key_Space});

	QAction *nowaAct = new QAction("&Nowa gra", this);
	connect(nowaAct, &QAction::triggered, this, &miloszqt::zaladuj);
	nowaAct->setShortcuts({Qt::Key_N});

	QMenu *plikMenu = menuBar()->addMenu("&Plik");
	plikMenu->addAction(nowaAct);

	QMenu *polecenieMenu = menuBar()->addMenu("&Polecenie");
	polecenieMenu->addAction(turaAct);
	polecenieMenu->addSeparator();
	polecenieMenu->addAction(goraAct);
	polecenieMenu->addAction(dolAct);
	polecenieMenu->addAction(lewoAct);
	polecenieMenu->addAction(prawoAct);

	TextPlansza *mapa = new TextPlansza;
	connect(this, &miloszqt::planszaChanged, mapa, &TextPlansza::pokazPlansze);

	_komunikaty = new QListWidget;
	_komunikaty->setMaximumHeight(100);
	connect(this, &miloszqt::dodanyKomunikat,
			[this](const QString& kom)
	{ _komunikaty->addItem(kom); _komunikaty->scrollToBottom(); } );
    _komunikaty->addItem(QString("Naciśnij n, aby rozpocząć nową grę!"));

	QVBoxLayout *lewa = new QVBoxLayout;
	lewa->addWidget(mapa);
	lewa->addWidget(_komunikaty);

	QLabel *zycieLabel = new QLabel("Życie:");
	QLabel *zycie = new QLabel("0/0");
	connect(this, &miloszqt::zycieChanged,
			[zycie](int zyc,int max)
	{ zycie->setText(QString::number(zyc) + "/" + QString::number(max)); } );

	QLabel *ruchLabel = new QLabel("Ruch:");
	QLabel *ruch = new QLabel("0/0");
	connect(this, &miloszqt::ruchChanged,
			[ruch](int r,int max)
	{ ruch->setText(QString::number(r) + "/" + QString::number(max)); } );

	QLabel *zbrojaLabel = new QLabel("Zbroja:");
	QLabel *zbroja = new QLabel("0.00");
	connect(this, &miloszqt::zbrojaChanged,
			[zbroja](float z)
	{ zbroja->setText(QString::number(z, 'g', 2)); });

	QLabel *bronLabel = new QLabel("Broń:");
	QLabel *bron = new QLabel("0.00");
	connect(this, &miloszqt::bronChanged,
			[bron](float z)
	{ bron->setText(QString::number(z, 'g', 2)); });

	QLabel *prezentLabel = new QLabel("Prezent:");
	QLabel *prezent = new QLabel("nie");
	connect(this, &miloszqt::prezentChanged,
			[prezent](bool p)
	{ if(p) prezent->setText("tak");
		else prezent->setText("nie"); });

	QGridLayout *statystyki = new QGridLayout;
	statystyki->addWidget(zycieLabel,0,0);
	statystyki->addWidget(zycie,0,1);
	statystyki->addWidget(ruchLabel,1,0);
	statystyki->addWidget(ruch,1,1);
	statystyki->addWidget(zbrojaLabel,2,0);
	statystyki->addWidget(zbroja,2,1);
	statystyki->addWidget(bronLabel,3,0);
	statystyki->addWidget(bron,3,1);
	statystyki->addWidget(prezentLabel,4,0);
	statystyki->addWidget(prezent,4,1);

	QPushButton *goraButton = new QPushButton("g");
	connect(goraButton, &QPushButton::clicked, goraAct, &QAction::trigger);

	QPushButton *dolButton = new QPushButton("d");
	connect(dolButton, &QPushButton::clicked, dolAct, &QAction::trigger);

	QPushButton *lewoButton = new QPushButton("l");
	connect(lewoButton, &QPushButton::clicked, lewoAct, &QAction::trigger);

	QPushButton *prawoButton = new QPushButton("p");
	connect(prawoButton, &QPushButton::clicked, prawoAct, &QAction::trigger);

	QPushButton *turaButton = new QPushButton("x");
	connect(turaButton, &QPushButton::clicked, turaAct, &QAction::trigger);

	QGridLayout *sterowanie = new QGridLayout;
	sterowanie->addWidget(goraButton,0,1);
	sterowanie->addWidget(dolButton,2,1);
	sterowanie->addWidget(lewoButton,1,0);
	sterowanie->addWidget(prawoButton,1,2);
	sterowanie->addWidget(turaButton,1,1);

	QVBoxLayout *prawa = new QVBoxLayout;
	prawa->addLayout(statystyki);
	prawa->addLayout(sterowanie);

	QHBoxLayout *glownyLayout = new QHBoxLayout;
	glownyLayout->addLayout(lewa);
	glownyLayout->addLayout(prawa);

	QWidget *glownyWidget = new QWidget();
	glownyWidget->setLayout(glownyLayout);

	setCentralWidget(glownyWidget);

	zaladuj();
}

miloszqt::~miloszqt()
{
}

void miloszqt::idz(Kierunek kier)
{
	_gra->idz(kier);
	odswiez();
}

void miloszqt::tura()
{
	_gra->tura();
	odswiez();
}

void miloszqt::ustawZrodlo(const QString& plik)
{
	_plik = plik;
}

void miloszqt::zaladuj()
{
	if(_gra != nullptr)
		delete _gra;

	std::fstream wejscie(_plik.toStdString());
	_gra = new Gra(wejscie);
	powitaj();
	odswiez();
}

void miloszqt::odswiez()
{
	if(_gra == nullptr)
		return;

	zycieChanged(_gra->milosz().zdrowie(), _gra->milosz().maxZdrowie());
	ruchChanged(_gra->milosz().ruch(), _gra->milosz().maxRuch());
	zbrojaChanged(_gra->milosz().zbroja());
	bronChanged(_gra->milosz().bron());
	prezentChanged(_gra->milosz().prezent());
	planszaChanged(_gra);

	while(_gra->komunikat())
		dodanyKomunikat(QString::fromStdString(_gra->czytajKomunikat()));
}

void miloszqt::powitaj()
{
	_komunikaty->addItem("Sterowanie jak w specyfikacji, ale też strzałkami, spacja to nowa tura, n to nowa gra.");
}
