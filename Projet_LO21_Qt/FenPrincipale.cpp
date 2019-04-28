#include <QtWidgets>
#include <autocell.h>
//#include "widgetautomate2d.h"
#include "FenPrincipale.h"

FenetrePrincipale::FenetrePrincipale()
{
//    widget = new QWidget;

                  // fenetreAutomate = new AutoCell();
                 // setCentralWidget(fenetreAutomate);

//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->setMargin(5);
//    layout->addWidget(fenetreAutomate);

//    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle(tr("Application AutoCell"));
    setMinimumSize(160, 160);
    resize(800, 800);
}

FenetrePrincipale::~FenetrePrincipale(){

}


void FenetrePrincipale::nouveau()
{
    QString message = tr("Nouveau");
    statusBar()->showMessage(message);
}

void FenetrePrincipale::ouvrir()
{
    QString message = tr("Ouvrir");
    statusBar()->showMessage(message);
}

void FenetrePrincipale::sauvegarder()
{
    QString message = tr("Sauver");
    statusBar()->showMessage(message);
}

void FenetrePrincipale::mode1D()
{
    fenetreAutomate = new AutoCell();
    setCentralWidget(fenetreAutomate);

    QString message = tr("automate 1d");
    statusBar()->showMessage(message);
}

/*void FenetrePrincipale::mode2D()
{
    fenetreAutomate = new WidgetAutomate2D();
    setCentralWidget(fenetreAutomate);

    QString message = tr("automate 2d");
    statusBar()->showMessage(message);
}*/

/*void FenetrePrincipale::mode2Dcouleur()
{
    fenetreAutomate = new WidgetAutomate2D();
    setCentralWidget(fenetreAutomate);

    QString message = tr("automate 2d couleur");
    statusBar()->showMessage(message);
}*/

void FenetrePrincipale::createActions()
{
    nouveauAct = new QAction(tr("&Nouveau"), this);
    nouveauAct->setShortcuts(QKeySequence::New);
    nouveauAct->setStatusTip(tr("Créer un nouvel automate"));
    connect(nouveauAct, &QAction::triggered, this, &FenetrePrincipale::nouveau);

    ouvrirAct = new QAction(tr("&Ouvrir..."), this);
    ouvrirAct->setShortcuts(QKeySequence::Open);
    ouvrirAct->setStatusTip(tr("Ouvrir un automate existant"));
    connect(ouvrirAct, &QAction::triggered, this, &FenetrePrincipale::ouvrir);

    sauvegarderAct = new QAction(tr("&Sauvegarder"), this);
    sauvegarderAct->setShortcuts(QKeySequence::Save);
    sauvegarderAct->setStatusTip(tr("Enregistrer l'automate"));
    connect(sauvegarderAct, &QAction::triggered, this, &FenetrePrincipale::sauvegarder);


    mode1DAct = new QAction(tr("&Automate 1D"), this);
    mode1DAct->setCheckable(true);

    connect(mode1DAct, &QAction::triggered, this, &FenetrePrincipale::mode1D);

    /*mode2DAct = new QAction(tr("&Automate 2D"), this);
    mode2DAct->setCheckable(true);
    connect(mode2DAct, &QAction::triggered, this, &FenetrePrincipale::mode2D);

    mode2DcouleurAct = new QAction(tr("&Automate 2D couleur"), this);
    mode2DcouleurAct->setCheckable(true);
    connect(mode2DcouleurAct, &QAction::triggered, this, &FenetrePrincipale::mode2Dcouleur);*/

    modeGroup = new QActionGroup(this);
    modeGroup->addAction(mode1DAct);
    //modeGroup->addAction(mode2DAct);
   // modeGroup->addAction(mode2DcouleurAct);
    mode1DAct->setChecked(true);
}

void FenetrePrincipale::createMenus()
{
    menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(nouveauAct);
    menuFichier->addAction(ouvrirAct);
    menuFichier->addAction(sauvegarderAct);
    //TODO : ajouter quitter
//    menuFichier->addSeparator();
//    menuFichier->addAction(exitAct);

    // TODO : menu options
    menuOptions = menuBar()->addMenu(tr("&Options"));

    menuMode = menuBar()->addMenu(tr("&Automate"));

    menuMode->addAction(mode1DAct);
   // menuMode->addAction(mode2DAct);
   // menuMode->addAction(mode2DcouleurAct);

}
