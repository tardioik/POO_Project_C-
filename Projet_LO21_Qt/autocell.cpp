#include <QApplication>
#include "autocell.h"
#include <iostream>
#include <string>
#include <QHeaderView>
#include "etat2.h"
#include "simulateur2.h"
#include "automate2.h"
#include "automatemanager2.h"


AutoCell::AutoCell(QWidget* parent, unsigned int n) : QWidget(parent), nbEtats(n) {

    num = new QSpinBox(this);
    if (nbEtats == 2){
    num->setRange(0, 255);
    }
    else{
      num->setRange(0, 12000); //A revérifier pour le nombre max
    }
    num->setValue(0);
    numl = new QLabel("Numero", this);
    numc = new QVBoxLayout;
    numc->addWidget(numl);
    numc->addWidget(num);

    numeroc = new QHBoxLayout;
    numeroc->addLayout(numc);

    zeroOneValidator = new QIntValidator(this);
if (nbEtats == 3){
    zeroOneValidator->setRange(0,2);
            }
else {zeroOneValidator->setRange(0,1);}

if(nbEtats == 2){
    for(unsigned int i =0; i<8; i++) {
        numeroBit[i] = new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);

        numeroBitl[i] = new QLabel(this);

        bitc[i] = new QVBoxLayout;
        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);
        numeroc->addLayout(bitc[i]);

    }

    numeroBitl[0]->setText("111");
    numeroBitl[1]->setText("110");
    numeroBitl[2]->setText("101");
    numeroBitl[3]->setText("100");
    numeroBitl[4]->setText("011");
    numeroBitl[5]->setText("010");
    numeroBitl[6]->setText("001");
    numeroBitl[7]->setText("000");
}
else {
    for(unsigned int i =0; i<27 ;i++){
        numeroBit[i] = new QLineEdit(this);
        numeroBit[i]->setFixedWidth(20);
        numeroBit[i]->setMaxLength(1);
        numeroBit[i]->setText("0");
        numeroBit[i]->setValidator(zeroOneValidator);

        numeroBitl[i] = new QLabel(this);

        bitc[i] = new QVBoxLayout;
        bitc[i]->addWidget(numeroBitl[i]);
        bitc[i]->addWidget(numeroBit[i]);
        numeroc->addLayout(bitc[i]);

    }

    numeroBitl[0]->setText("111"); //Revoir les bon chiffres à mettre
    numeroBitl[1]->setText("110");
    numeroBitl[2]->setText("101");
    numeroBitl[3]->setText("100");
    numeroBitl[4]->setText("011");
    numeroBitl[5]->setText("010");
    numeroBitl[6]->setText("001");
    numeroBitl[8]->setText("000");
    numeroBitl[9]->setText("000");
    numeroBitl[10]->setText("000");
    numeroBitl[11]->setText("000");
    numeroBitl[12]->setText("000");
    numeroBitl[13]->setText("000");
    numeroBitl[14]->setText("000");
    numeroBitl[15]->setText("000");
    numeroBitl[16]->setText("000");
    numeroBitl[17]->setText("000");
    numeroBitl[18]->setText("000");
    numeroBitl[19]->setText("000");
    numeroBitl[20]->setText("000");
    numeroBitl[21]->setText("000");
    numeroBitl[22]->setText("000");
    numeroBitl[23]->setText("000");
    numeroBitl[24]->setText("000");
    numeroBitl[25]->setText("000");
    numeroBitl[26]->setText("000");

    }


    dimension = 25;

    depart = new QTableWidget(1, dimension, this);
    int taille = 20;
    depart->setFixedSize(dimension * taille, taille);
    depart->horizontalHeader()->setVisible(false);
    depart->verticalHeader()->setVisible(false);
    depart->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    depart->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    depart->setFixedHeight(taille);

    for (unsigned int i =0; i<dimension; i++) {
        depart->setColumnWidth(i, taille);
        depart->setItem(0, i, new QTableWidgetItem(""));
        depart->item(0, i)->setBackgroundColor("white");
        depart->item(0, i)->setTextColor("white");
    }

    simulation = new QPushButton("Simulation", this);

    etats = new QTableWidget(dimension, dimension, this);
    etats->setFixedSize(dimension * taille, dimension* taille);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (unsigned int i=0; i<dimension; i++) {
        etats->setColumnWidth(i, taille);
        etats->setRowHeight(i, taille);
        for (unsigned int j=0; j<dimension; j++) {
            etats->setItem(i, j, new QTableWidgetItem(""));
            etats->item(0, i)->setBackgroundColor("white");
            etats->item(0, i)->setTextColor("white");
        }
    }

    couche = new QVBoxLayout;
    couche->addLayout(numeroc);
    couche->addWidget(depart);
    couche->addWidget(simulation);
    couche->addWidget(etats);


    setLayout(couche);
    connect(depart, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(cellActivation(const QModelIndex&)));

    connect(simulation, SIGNAL(clicked()), this, SLOT(simuler()));

    if (nbEtats == 2){
    connect(num, SIGNAL(valueChanged(int)), this, SLOT(synchronizeNumToNumBit(int)));
    for (unsigned int i=0; i<8; i++) {
        connect(numeroBit[i], SIGNAL(textChanged(QString)), this, SLOT(synchronizeNumBitToNum(const QString&)));
        }
     }

 }

void AutoCell::synchronizeNumToNumBit(int i) {
    if (nbEtats == 2){
    Automate a(0,2);
    std::string numBit = a.NumToNumBit(i);
    for (int i=0; i<8; i++)
        numeroBit[i]->setText(QString(numBit[i]));
}
    if (nbEtats == 3){
        Automate a(0,3);
        std::string numBit = a.NumToNumB3(i);
        for (int i=0; i<27; i++)
            numeroBit[i]->setText(QString(numBit[i]));
    }

}



void AutoCell::synchronizeNumBitToNum(const QString& s){
    if (nbEtats == 2){
    std::string str;
    Automate a(0,2);
    for (unsigned int i=0; i<8; i++)
        str += numeroBit[i]->text().toStdString();

    int i = a.NumBitToNum(str);
    num->setValue(i);
    }
     if (nbEtats == 3){
         std::string str;
         Automate a(0,3);
         for (unsigned int i=0; i<27; i++)
             str += numeroBit[i]->text().toStdString();

         int i = a.NumBitToNum(str);
         num->setValue(i);
     }
}

void AutoCell::cellActivation(const QModelIndex& index) {
    if (depart->item(0, index.column())->text() == "") {
        depart->item(0, index.column())->setText("_");
        depart->item(0, index.column())->setBackgroundColor("black");
        depart->item(0, index.column())->setTextColor("black");
    } else {
        depart->item(0, index.column())->setBackgroundColor("white");
        depart->item(0, index.column())->setTextColor("white");
        depart->item(0, index.column())->setText("");
    }
}

void AutoCell::simuler() {
    Etat e(dimension);
    for (unsigned int i=0; i<dimension; i++) {
        if(depart->item(0, i)->text() != "")
            e.setCellule(i, true);

    }
    const Automate& automate = AutomateManager::getInstance().getAutomate(num->value());
    Simulateur s(automate, e);
    for (unsigned int i=0; i<dimension; i++) {
        s.next();
        const Etat& dernier = s.dernier();
        for (unsigned int j=0; j<dimension; j++) {
            if (dernier.getCellule(j)) {
                etats->item(i, j)->setText("_");
                etats->item(i, j)->setBackgroundColor("black");
                etats->item(i, j)->setTextColor("black");
            } else {
                etats->item(i, j)->setBackgroundColor("white");
                etats->item(i, j)->setTextColor("white");
                etats->item(i, j)->setText("");
            }
        }
    }
}



