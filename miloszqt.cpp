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
#include <QFileDialog>
#include <fstream>
#include <QApplication>
#include <vector>
#include <tuple>
#include "textplansza.h"

miloszqt::miloszqt(QWidget *parent) :
	QMainWindow(parent)
{
	_gra = nullptr;

	/*
	 *
	 * Akcje
	 *
	 */
	QAction *goraAct = new QAction(QString("&Up"), this);
	connect(goraAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::GORA); } );
	goraAct->setShortcuts({Qt::Key_U, Qt::Key_Up});

	QAction *dolAct = new QAction("&Down", this);
	connect(dolAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::DOL); } );
	dolAct->setShortcuts({Qt::Key_D, Qt::Key_Down});

	QAction *lewoAct = new QAction("&Left", this);
	connect(lewoAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::LEWO); } );
	lewoAct->setShortcuts({Qt::Key_L, Qt::Key_Left});

	QAction *prawoAct = new QAction("&Right", this);
	connect(prawoAct, &QAction::triggered,
			[this](bool)
	{ this->idz(Kierunek::PRAWO); } );
	prawoAct->setShortcuts({Qt::Key_R, Qt::Key_Right});

	QAction *turaAct = new QAction("&New turn", this);
	connect(turaAct, &QAction::triggered, this, &miloszqt::tura);
	turaAct->setShortcuts({Qt::Key_X, Qt::Key_Space});

	QAction *nowaAct = new QAction("&New game", this);
	connect(nowaAct, &QAction::triggered, this, &miloszqt::zaladuj);
	nowaAct->setShortcuts({Qt::Key_N});

	QAction *otworzAct = new QAction("&Open a map", this);
	connect(otworzAct, &QAction::triggered, this, &miloszqt::otworzPlik);
	otworzAct->setShortcuts({Qt::Key_O});

	QAction *zakonczAct = new QAction("&Quit", this);
	connect(zakonczAct, &QAction::triggered, qApp, &QApplication::quit);
	zakonczAct->setShortcuts({Qt::Key_Q});

	/*
	 *
	 * Pasek menu
	 *
	 */
	QMenu *plikMenu = menuBar()->addMenu("&File");
	plikMenu->addAction(nowaAct);
	plikMenu->addAction(otworzAct);
	plikMenu->addSeparator();
	plikMenu->addAction(zakonczAct);

	QMenu *polecenieMenu = menuBar()->addMenu("&Command");
	polecenieMenu->addAction(turaAct);
	polecenieMenu->addSeparator();
	polecenieMenu->addAction(goraAct);
	polecenieMenu->addAction(dolAct);
	polecenieMenu->addAction(lewoAct);
	polecenieMenu->addAction(prawoAct);

	/***
	 *
	 * Lewa strona widoku
	 *
	 ***/

	/*
	 * Mapa
	 */
	TextPlansza *mapa = new TextPlansza(this);
	connect(this, &miloszqt::planszaChanged, mapa, &TextPlansza::pokazPlansze);

	/*
	 * Komunikaty pod mapą
	 */
	QListWidget *komunikaty = new QListWidget(this);
	komunikaty->setMaximumHeight(100);
	connect(this, &miloszqt::dodanyKomunikat,
			[komunikaty](const QString& kom)
	{ komunikaty->addItem(kom); komunikaty->scrollToBottom(); } );

	QVBoxLayout *lewa = new QVBoxLayout();
	lewa->addWidget(mapa);
	lewa->addWidget(komunikaty);

	/***
	 *
	 * Prawa strona widoku
	 *
	 ***/

	/*
	 * Przybliżanie i oddalanie
	 */
	QPushButton *przyblizButton = new QPushButton("ZoomIn", this);
	connect(przyblizButton, &QPushButton::clicked, mapa, &TextPlansza::przybliz);

	QPushButton *oddalButton = new QPushButton("ZoomOut", this);
	connect(oddalButton, &QPushButton::clicked, mapa, &TextPlansza::oddal);

	/*
	 * Statystyki gry
	 */
	std::vector<std::tuple<QLabel*,QLabel*>> stats;

	QLabel *zycieLabel = new QLabel("HP:", this);
	QLabel *zycie = new QLabel("0/0", this);
	connect(this, &miloszqt::zycieChanged,
			[zycie](int zyc,int max)
	{ zycie->setText(QString::number(zyc) + "/" + QString::number(max)); } );
	stats.push_back(std::make_tuple(zycieLabel,zycie));

	QLabel *ruchLabel = new QLabel("Move:", this);
	QLabel *ruch = new QLabel("0/0", this);
	connect(this, &miloszqt::ruchChanged,
			[ruch](int r,int max)
	{ ruch->setText(QString::number(r) + "/" + QString::number(max)); } );
	stats.push_back(std::make_tuple(ruchLabel,ruch));

	QLabel *silaLabel = new QLabel("Strength:", this);
	QLabel *sila = new QLabel("0", this);
	connect(this, &miloszqt::silaChanged,
			[sila](int s)
	{ sila->setText(QString::number(s)); } );
	stats.push_back(std::make_tuple(silaLabel,sila));

	QLabel *zbrojaLabel = new QLabel("Armor:", this);
	QLabel *zbroja = new QLabel("0.00", this);
	connect(this, &miloszqt::zbrojaChanged,
			[zbroja](float z)
	{ zbroja->setText(QString::number(z, 'g', 2)); });
	stats.push_back(std::make_tuple(zbrojaLabel,zbroja));

	QLabel *bronLabel = new QLabel("Weapon:", this);
	QLabel *bron = new QLabel("0.00", this);
	connect(this, &miloszqt::bronChanged,
			[bron](float z)
	{ bron->setText(QString::number(z, 'g', 2)); });
	stats.push_back(std::make_tuple(bronLabel,bron));

	QLabel *prezentLabel = new QLabel("Present:", this);
	QLabel *prezent = new QLabel("nie", this);
	connect(this, &miloszqt::prezentChanged,
			[prezent](bool p)
	{ if(p) prezent->setText("yes");
		else prezent->setText("no"); });
	stats.push_back(std::make_tuple(prezentLabel,prezent));

	QGridLayout *statystyki = new QGridLayout();

	for(int i = 0; i < int(stats.size()); ++i)
	{
		statystyki->addWidget(std::get<0>(stats[i]),i,0);
		statystyki->addWidget(std::get<1>(stats[i]),i,1);
	}

	/*
	 * Sterowanie myszką
	 */
	QPushButton *goraButton = new QPushButton("U",this);
	connect(goraButton, &QPushButton::clicked, goraAct, &QAction::trigger);

	QPushButton *dolButton = new QPushButton("D",this);
	connect(dolButton, &QPushButton::clicked, dolAct, &QAction::trigger);

	QPushButton *lewoButton = new QPushButton("L",this);
	connect(lewoButton, &QPushButton::clicked, lewoAct, &QAction::trigger);

	QPushButton *prawoButton = new QPushButton("R",this);
	connect(prawoButton, &QPushButton::clicked, prawoAct, &QAction::trigger);

	QPushButton *turaButton = new QPushButton("X",this);
	connect(turaButton, &QPushButton::clicked, turaAct, &QAction::trigger);

	QGridLayout *sterowanie = new QGridLayout();
	sterowanie->addWidget(goraButton,0,1);
	sterowanie->addWidget(dolButton,2,1);
	sterowanie->addWidget(lewoButton,1,0);
	sterowanie->addWidget(prawoButton,1,2);
	sterowanie->addWidget(turaButton,1,1);

	QVBoxLayout *prawa = new QVBoxLayout();
	prawa->addWidget(przyblizButton);
	prawa->addWidget(oddalButton);
	prawa->addLayout(statystyki);
	prawa->addLayout(sterowanie);

	/***
	 *
	 * Cały widok
	 *
	 ***/
	QWidget *glownyWidget = new QWidget(this);

	QHBoxLayout *glownyLayout = new QHBoxLayout(glownyWidget);
	glownyLayout->addLayout(lewa);
	glownyLayout->addLayout(prawa);

	setCentralWidget(glownyWidget);

	powitaj();
}

miloszqt::~miloszqt()
{
	delete _gra;
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

void miloszqt::otworzPlik()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open a file"), QDir::currentPath());
	if(!fileName.isEmpty())
	{
		ustawZrodlo(fileName);
		zaladuj();
	}
}

void miloszqt::zaladuj()
{
	if(_gra != nullptr)
		delete _gra;

	std::fstream wejscie(_plik.toStdString());
	_gra = new Gra(wejscie);
	if(_gra->stan() == Stan::BLAD)
	{
		delete _gra;
		_gra = nullptr;
		dodanyKomunikat("Could not open " + _plik + ".");
	}
	else
	{
		powitaj();
	}
	odswiez();
}

void miloszqt::odswiez()
{
	if(_gra == nullptr)
		return;

	zycieChanged(_gra->milosz().zdrowie(), _gra->milosz().maxZdrowie());
	ruchChanged(_gra->milosz().ruch(), _gra->milosz().maxRuch());
	silaChanged(_gra->milosz().sila());
	zbrojaChanged(_gra->milosz().zbroja());
	bronChanged(_gra->milosz().bron());
	prezentChanged(_gra->milosz().prezent());
	planszaChanged(_gra);

	while(_gra->komunikat())
		dodanyKomunikat(QString::fromStdString(_gra->czytajKomunikat()));
}

void miloszqt::powitaj()
{
	dodanyKomunikat("Find the treasure before others! Bard (B), Seller (S) or Healer (Z) may help you. Watch out for monsters.");
	dodanyKomunikat("Begin with opening a map under the File menu.");
	dodanyKomunikat("Use arrows or UDLR to move, space or X to end turn, N to start a new game.");
}
