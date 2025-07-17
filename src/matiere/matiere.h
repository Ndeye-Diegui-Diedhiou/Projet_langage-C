#ifndef MATIERE_H
#define MATIERE_H

typedef struct {
    int reference;
    char libelle[50];
    short int coefficient;
} Matiere;

void ajouterMatiere();
void afficherMatieres();
void modifierMatiere();
void supprimerMatiere();
void rechercherMatiere();

#endif