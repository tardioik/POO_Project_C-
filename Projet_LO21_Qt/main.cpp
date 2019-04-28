
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include "autocell.h"
#include "FenPrincipale.h"


int main(int argc, char* argv[]) {
   QApplication app(argc, argv);

//FenetrePrincipale menu;
//menu.show();



   /* QWidget fenetre;
    //fenetre.setFixedSize(150, 110);


    QLabel numeroBitl("NuméroBit", &fenetre);
    numeroBitl.move(10,45);
    QLabel numl("Numéro", &fenetre);
    numl.move(10,10);

    QLineEdit num(&fenetre);
    num.setFixedWidth(25);
    num.move(70,10);
    QLineEdit numeroBit(&fenetre);
    numeroBit.setFixedWidth(60);
    numeroBit.move(80,45);


QPushButton bouton_ok("Ok", &fenetre);
//bouton_ok.setFixedWidth(60);
bouton_ok.move(10,80);
bouton_ok.show();

QPushButton bouton_q("Quitter", &fenetre);
bouton_q.move(70,80);
bouton_q.show(); //La méthode show permet d'afficher l'objet bouton

QObject::connect(&bouton_q, SIGNAL(clicked()), qApp, SLOT(quit())); //Attention il faut l'adresse de bouton

QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(&numl);
    layout->addWidget(&num);
    layout->addWidget(&numeroBitl);
    layout->addWidget(&numeroBit);
    layout->addWidget(&bouton_ok, 1, 0);
    layout->addWidget(&bouton_q, 1, 0);

fenetre.setLayout(layout);
    fenetre.show(); */
    return app.exec(); }
