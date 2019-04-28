//
//  automate.hpp
//  TD4_LO21
//
//  Created by Alexandre Touzeau on 22/03/2018.
//  Copyright © 2018 Alexandre Touzeau. All rights reserved.
//

#ifndef automate_hpp
#define automate_hpp

#include <stdio.h>
#include <string>
#include "etat2.h"
#include <iostream>

class AutomateException
{

    public:
    AutomateException(const std::string& message):info(message) {}
    std::string getInfo() const { return info; }
    private:
    std::string info;
};


class Automate
{
    private:
        unsigned long long numero;
        std::string numeroBase;
        unsigned short int nbEtats;
    public:
        Automate(unsigned long long num, unsigned short int nEtats);
        Automate(const std::string& num, unsigned short int nEtats);
        unsigned long long NumBaseToNum(const std::string& num, unsigned short int nEtats);
        unsigned long long NumBitToNum(const std::string& num);
        unsigned long long NumB3ToNum(const std::string& num);
        std::string NumToNumBase(unsigned long long num, short unsigned int nEtats);
        std::string NumToNumBit(unsigned long long num);
        std::string NumToNumB3(unsigned long long num);

        inline unsigned long long getNumero() const
        { return numero; }
        inline const std::string& getNumeroBase() const
        { return numeroBase; }
        inline unsigned short int getNbEtats() const
        { return nbEtats; }
        void appliquerTransition(const Etat& dep, Etat& dest) const;
};


std::ostream& operator<<(std::ostream& stream, const Automate& automate);


#endif /* automate_hpp */
