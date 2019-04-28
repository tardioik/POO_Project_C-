//
//  AutomateManager.hpp
//  TD4_LO21
//
//  Created by Alexandre Touzeau on 29/03/2018.
//  Copyright © 2018 Alexandre Touzeau. All rights reserved.
//

#ifndef AutomateManager_hpp
#define AutomateManager_hpp

#include <stdio.h>
#include <string>
#include <vector>

class AutomateManager
{
    //Singleton
    public :

    static AutomateManager &getInstance();

    private :
        static AutomateManager *instance; //Partagé avec tous les objets de la classe
    AutomateManager() {};
      //  ~AutomateManager();
        AutomateManager(const AutomateManager&) = delete; //pas d'implémentation pour l'opérateur de copie
        void operator=(const AutomateManager&) = delete; // pas d'implémentation pour l'opérateur de recopie (ou inverse avec celui du haut vérifiier)


    //Automatemanager
    private :
        std::vector<Automate*> automates;
         Automate* findAutomate(unsigned short int num);
         Automate* findAutomate(const std::string &numBit);

    public :
       // Automate getAutomateManager(short unsigned int Num) const {return 0; }
      //  Automate getAutomateManager(std::string NumBit) const  {return 0; }
    const Automate &getAutomate(unsigned short int num);
    const Automate &getAutomate( const std::string &numBit);


//Automate getAutomate(short unsigned int Numero) {return } ;

};
#endif /* AutomateManager_hpp */
