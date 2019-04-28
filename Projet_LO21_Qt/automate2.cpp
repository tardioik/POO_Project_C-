//
//  automate.cpp
//  TD4_LO21
//
//  Created by Alexandre Touzeau on 22/03/2018.
//  Copyright © 2018 Alexandre Touzeau. All rights reserved.
//

#include "automate.hpp"
#include "etat.hpp"
#include "simulateur.hpp"
#include "AutomateManager.hpp"
#include "automate2.h"

#include <cstring>
#include <cstddef>
#include <string>



Etat::Etat() : dimension(0), valeur(NULL)
{

}

Etat::Etat(unsigned int dim) : dimension(dim)
{
    if(dim == 0)
    {
        valeur = NULL;
    }
    else
    {
        valeur = new bool[dim]; //On alloue un tableau de bool dynamiquement de dimension dim
        for(unsigned int ite = 0; ite < dim; ite++)
        {
            valeur[ite] = false; //On l'initialise à false (0) partout
        }
    }
}

Etat::~Etat()
{
    if(valeur)
    {
        delete[] valeur;
    }
}

Etat::Etat(const Etat& other) //Constructeur de copie qui prend en argument une ref sur un objet Etat
{
    dimension = other.dimension;
    if(dimension == 0)
    {
        valeur = NULL;
    }
    else
    {
        valeur = new bool[dimension];
        memcpy(valeur, other.valeur, dimension * sizeof(bool)); //Copie dimension*sizeof(bool) octets de other.valeur vers valeur
    }
}

Etat& Etat::operator=(const Etat& other) //valeur et dimension proviennent de la gauche et other.valeur et other.simension de la droite du "="
{
    dimension = other.dimension;
    if(dimension == 0)
    {
        valeur = NULL;
    }
    else
    {
        if(valeur)
            delete[] valeur; //Si on possède déjà une valeur alors on la supprime
        valeur = new bool[dimension]; //On alloue dynamiquement
        memcpy(valeur, other.valeur, dimension * sizeof(bool)); //On copie l'état de droite à gauche
    }
    return *this; //Enfin on retourne la valeur de l'objet pointé par this (donc ce qu'il y a à gauche)
}

void Etat::setCellule(unsigned int ite, bool val)
{
    if(ite >= dimension) //si on veut affecter une cellule en dehors de la dim alors on throw une erreur
        throw AutomateException("Cellule out of bound");
    valeur[ite] = val;
}


std::ostream& operator<<(std::ostream& stream, const Etat& etat)
{
    for(unsigned int ite = 0; ite < etat.getDimension(); ite++)
    {
        stream << (etat.getCellule(ite) == 1 ? "X" : (etat.getCellule(ite) == 2 ? "_" : " "));
    }
    return stream;
}



Automate::Automate(short unsigned int numRegle) : Numero(numRegle), NumeroBit(NumToNumBit(numRegle))
{

}


Automate::Automate(const std::string& NumeroBitRegle) : NumeroBit(NumeroBitRegle), Numero(NumBitToNum(NumeroBitRegle))
{

}

unsigned long long Automate::NumBaseToNum(const std::string& num, unsigned short int nEtats)
{
    if (nEtats == 2)
        return NumBitToNum(num);
    else
        return NumB3ToNum(num);
}

unsigned long long Automate::NumBitToNum(const std::string& num)
{
    if (num.size() != 8) throw AutomateException("Numero d'automate indefini");
    int puissance = 1;short unsigned int numero = 0;
    for (int i = 7; i >= 0; i--) {
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 2;
    }
    return numero;
}

unsigned long long Automate::NumB3ToNum(const std::string& num)
{
    if (num.size() != 27) throw AutomateException("Numero d'automate indef");
    int puissance = 1;short unsigned int numero = 0;
    for (int i = 26; i >= 0; i--) {
        if (num[i] == '2') numero += 2*puissance;
        if (num[i] == '1') numero += puissance;
        else if (num[i] != '0') throw AutomateException("Numero d'automate indefini");
        puissance *= 3;
    }
    return numero;
}

std::string Automate::NumToNumBase(unsigned long long num, short unsigned int nEtats)
{
    if (nEtats == 2)
        return NumToNumBit(num);
    else
        return NumToNumB3(num);
}


std::string Automate::NumToNumBit(unsigned long long num)
{
    std::string numeroBit;
    if (num > 256) throw AutomateException("Numero d'automate indefini");
    unsigned short int p = 128;
    int i = 7;
    while (i >= 0) {
        if (num >= p) { numeroBit.push_back('1'); num -= p; }
        else { numeroBit.push_back('0'); }
        i--;
        p = p / 2;
    }
    return numeroBit;
}

std::string Automate::NumToNumB3(unsigned long long num)
{
    std::string numeroB3;
    if (num > 7625597484987) throw AutomateException("Numero d'automate indefini");
    unsigned long long p = 2541865828329;
    int i = 26;
    while (i >= 0) {
        if (num >= 2 * p) { numeroB3.push_back('2'); num -= 2 * p; }
        else if (num >= p) { numeroB3.push_back('1'); num -= p; }
        else { numeroB3.push_back('0'); }
        i--;
        p = p / 3;
    }
    return numeroB3;
}

void Automate::appliquerTransition(const Etat& dep, Etat& dest) const
{
    dest = dep;
    for(unsigned int ite = 0; ite < dep.getDimension(); ite++)
    {
        unsigned short int conf = 0;
        if(ite > 0)
            conf += (dep.getCellule(ite - 1) ? 1 : 0) * 4;
        conf += (dep.getCellule(ite) ? 1 : 0) * 2;
        if (ite < dep.getDimension() - 1)
            conf += (dep.getCellule(ite + 1) ? 1 : 0);
        dest.setCellule(ite, NumeroBit[7 - conf]-'0');
    }
}




std::ostream& operator<<(std::ostream& stream, const Automate& automate)
{
    stream << automate.getNumero();
    stream << " : " << automate.getNumeroBit();
    return stream;
}

Simulateur::Simulateur(const Automate& automate, unsigned int buffer) : automate(automate), nbMaxEtats(buffer)
{
    etats = new Etat*[nbMaxEtats];
    for(unsigned int ite = 0; ite < nbMaxEtats; ite++)
        etats[ite] = NULL;
    reset();
}

Simulateur::Simulateur(const Automate& automate, const Etat& dep, unsigned int buffer) : automate(automate), nbMaxEtats(buffer), depart(&dep)
{
    etats = new Etat*[nbMaxEtats];
    for(unsigned int ite = 0; ite < nbMaxEtats; ite++)
        etats[ite] = NULL;
    etats[0] = new Etat(dep);
    reset();
}

void Simulateur::build(unsigned int iteEtat) { //Pour allouer dynamiquement les cases d'un tableau d'état?
    if(iteEtat >= nbMaxEtats)
        throw AutomateException("Erreur taille");
    if(etats[iteEtat] == NULL)
        etats[iteEtat] = new Etat();
}

void Simulateur::reset()
{
    if(depart == NULL)
        throw AutomateException("Etat depart non défini");
    build(0);
    *etats[0] = *depart;
    rang = 0;
}

void Simulateur::run(unsigned int nbSteps)
{
    for(unsigned int ite = 0; ite < nbSteps; ite++)
        next();
}

void Simulateur::next()
{
    if(depart == NULL)
        throw AutomateException("Etat depart non defini");
    rang = (rang +1) %nbMaxEtats; //Sécurité car sinon le rang va dépasser le nbMaxEtats

    build(rang % nbMaxEtats);
    automate.appliquerTransition(
                                 *etats[(rang - 1) % nbMaxEtats],
                                 *etats[(rang) % nbMaxEtats]);
}

const Etat& Simulateur::dernier() const
{
    return *etats[rang % nbMaxEtats];
}

Simulateur::~Simulateur()
{
    for(unsigned int ite = 0; ite < nbMaxEtats; ite++)
    {
        if(etats[ite] != NULL)
            delete etats[ite];
    }
    delete [] etats;
   // AutomateManager(const AutomateManager &) = default;
}

AutomateManager *AutomateManager::instance = NULL;



AutomateManager  &AutomateManager::getInstance()
{
    if(instance == NULL)
        instance = new AutomateManager();
    return *instance;
}

Automate *AutomateManager::findAutomate(unsigned short int num)
{
    for(Automate *automate : automates)
    {
        if(automate->getNumero() == num)
            return automate;
    }
    return NULL;
}

Automate *AutomateManager::findAutomate(const std::string &num)
{
    //    for(std::vector<Automate *>::iterator ite = automates.begin(); ite != automates.end(); ite++)
    //        *ite
    for(unsigned int ite = 0; ite < automates.size(); ite++)
    {
        if(automates[ite]->getNumeroBit() == num)
            return automates[ite];
    }
    return NULL;
}

const Automate &AutomateManager::getAutomate(unsigned short int num)
{
    Automate *automate = findAutomate(num);
    if(automate)
    {
        return *automate;
    }
    else
    {
        automate = new Automate(num);
        automates.push_back(automate);
        return *automate;
    }
}



const Automate &AutomateManager::getAutomate(const std::string &numBit)
{
    Automate *automate = findAutomate(numBit);
    if(automate)
    {
        return *automate;
    }
    else
    {
        automate = new Automate(numBit);
        automates.push_back(automate);
        return *automate;
    }
}



