#ifndef AUTOCELL_H
#define AUTOCELL_H
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>
#include <string>
#include <QPushButton>
#include <QTableView>
#include <QTableWidget>

class AutoCell : public QWidget{

Q_OBJECT

QSpinBox* num; // numéro
QLineEdit* numeroBit[8]; // un QLineEdit par bit QLabel* numl;
QLabel* numl;
QLabel* numeroBitl[8];
QVBoxLayout* numc;
QVBoxLayout* bitc[8];
QHBoxLayout* numeroc;
QIntValidator* zeroOneValidator;
QPushButton* simulation;
QTableWidget* depart;
QVBoxLayout* couche;
QTableView* grille;
QTableWidget* etats;
unsigned int nbEtats;


unsigned int dimension = 25;

public:
explicit AutoCell(QWidget* parent = nullptr, unsigned int nbEtats = 2);
short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);


private slots:
void simuler();
void synchronizeNumToNumBit(int i);
void synchronizeNumToNumBit3(int i);
void synchronizeNumBitToNum(const QString& s);
void synchronizeNumBitToNum3(const QString& s);
void cellActivation(const QModelIndex& index);

unsigned int getNbEtats() {return nbEtats;}
};



#endif // AUTOCELL_H
