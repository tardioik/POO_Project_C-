//
//  simulateur.hpp
//  TD4_LO21
//
//  Created by Alexandre Touzeau on 22/03/2018.
//  Copyright © 2018 Alexandre Touzeau. All rights reserved.
//

#ifndef simulateur_hpp
#define simulateur_hpp

#include <stdio.h>
#include <string>
#include "automate2.h"


class Simulateur {

public:

    class Iterator {
    private:
        Simulateur &simulateur;
        unsigned int iteEtat;
    public:
        Iterator(Simulateur &simulateur) : simulateur(simulateur), iteEtat(0)
        {

        }
        bool isDone() const
        {
            return iteEtat == simulateur.rang;
        }

        void next()
        {
            iteEtat++;
        }
        Etat& current()
        {
            return *simulateur.etats[iteEtat];
        }
    };

    class const_iterator {


    private:
        const Simulateur& simulateur;
        int iteEtat;
    public:
        const_iterator(const Simulateur& simulateur, int iteEtat) : simulateur(simulateur), iteEtat(iteEtat) {}

        bool operator!=(const const_iterator& other) const{
            return iteEtat != other.iteEtat;
        }
        void operator++(){
            ++iteEtat;
        }
        const Etat& operator*() const{
            return *simulateur.etats[iteEtat];
        }
    };

    void setEtatDepart(const Etat& e) {depart = &e;} //permet de modifier cet attribut avec un état représenté par e
    Simulateur();

    Simulateur(const Automate& automate, unsigned int buffer = 2); //permet d’initialiser un objet Simulateur sur un automate référencé par a en utilisant un buffer de taille buf (2 par défaut) -> mais etat de dep précisé plus tard avec SetEtatDepart()

    Simulateur( const Automate& automate, const Etat& dep, unsigned int buffer = 2); //Permet, en même temps de fournir l’automate et la taille du buffer, de préciser l’état de départ.


    void run(unsigned int nbSteps); //permet d’avancer de nbSteps générations en une seule fois.
    void next(); //a la generation rang permet de générer l’état à la génération rang+1
    const Etat& dernier() const;
    unsigned int getRangDernier() const {return rang;} //permet de connaître le rang du dernier état généré.


    void reset(); //Permet de revenir à l'état de départ
    ~Simulateur();
    Iterator getIterator() {return Iterator (*this);}
    unsigned int getRang() {return rang;}

protected:
    unsigned int nbMaxEtats; //nb max d'etat que le simulateur peut sauvegarder
    unsigned int nbEtats;
    const Etat* depart; //pointe sur un éventuel état de départ (s’il a été donné)
    Etat** etats; //pointe sur un tableau d'Etat* alloué dynamiquement  et de dim nbMaxEtats
    const Automate& automate; //Reference un automate
    unsigned int rang = 0;
    void build(unsigned int c);
    Simulateur(const Simulateur&) = delete;
    Simulateur& operator=(const Simulateur&) = delete;

public:
    const_iterator begin() const
    {
        return const_iterator(*this, 0);
    }

    const_iterator end() const
    {
        return const_iterator(*this, rang);
    }

};

#endif /* simulateur_hpp */
