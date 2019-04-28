//
//  etat.hpp
//  TD4_LO21
//
//  Created by Alexandre Touzeau on 22/03/2018.
//  Copyright © 2018 Alexandre Touzeau. All rights reserved.
//

#ifndef etat_hpp
#define etat_hpp

#include <stdio.h>
#include <string>

class Etat
{
public:
    inline unsigned int getDimension() const {return dimension;} //Permet de connaitre la dimension d'un etat
   
    bool getCellule(unsigned int i) const {return valeur[i];} //Permet de connaitre l'état de la cellule i entre 0 et dimension-1
    Etat();
    ~Etat();
    Etat(const Etat& other);
    Etat(unsigned int dimension); //Constructeur qui permet d’initialiser un objet Etat dont la dimension est précisée
    void setCellule(unsigned int i, bool val); //modifie la cellule i avec la valeur val
    Etat& operator=(const Etat& other);
    
    
    
protected:
    unsigned int dimension; //nb de cellule impliquée(s) dans la grille
    bool* valeur; //Pointe sur un tableau alloué dynamiquement de taille dimension
};

std::ostream& operator<<(std::ostream& stream, Etat const& e); // Pour afficher un etat ?

#endif /* etat_hpp */
