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
#include "etat.hpp"
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
    public:
   
    Automate(short unsigned int num); //Constructeur 1
    Automate(const std::string&  NumeroBitRegle);
    
    //virtual ~Automate();
    short unsigned int getNumero() const {return Numero;}
    std::string getNumeroBit() const {return NumeroBit;}
    void appliquerTransition(const Etat& dep, Etat& dest)const; //permet d’appliquer la règle d’évolution sur un état désigné par dep pour obtenir un état qui sera désigné par dest
    
    
    
    protected:
    short unsigned int Numero; //Numero de la regle d'évolution de l'automate (ici 30)
    std::string NumeroBit; //Regle d'évolution également mais en bit
    std::string NumToNumBit(short unsigned int num);
    short unsigned int NumBitToNum(const std::string& num);
    friend class AutomateManager;
    Automate(const Automate&) = delete;
    Automate& operator=(const Automate& ) = delete; 
    
};

std::ostream& operator<<(std::ostream& stream, const Automate& automate);


#endif /* automate_hpp */
