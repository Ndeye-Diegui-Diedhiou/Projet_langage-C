#ifndef CLASSE_H
#define CLASSE_H

typedef struct {
    int code;
    char nom[50];
    enum niveau {
        Licence,
        Master
    } niveau;
} Classe;

void ajouterClasse();
void afficherClasses();
void modifierClasse();
void supprimerClasse();
void rechercherClasse();

#endif

