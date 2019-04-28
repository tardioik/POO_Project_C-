#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include"autocell.h"
#include <QMenu>







class FenetrePrincipale : public QMainWindow
{ Q_OBJECT

    private:

    AutoCell *fenetreAutomate;
    QAction* nouveauAct;
    QAction* ouvrirAct;
    QAction* sauvegarderAct;
    QAction* mode1DAct;
    QActionGroup* modeGroup;
    QMenu* menuFichier;
    QMenu* menuOptions;
    QMenu* menuMode;




    public:

   void nouveau();
   void ouvrir();
   void sauvegarder();
   void mode1D();
   void createActions();
   void createMenus();
   FenetrePrincipale();
   ~FenetrePrincipale();

};

#endif
