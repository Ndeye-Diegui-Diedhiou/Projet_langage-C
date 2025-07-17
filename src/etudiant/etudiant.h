#ifndef ETUDIANT_H
#define ETUDIANT_H

typedef struct {
    int numero;
    char nom[50];
    char prenom[50];
    char email[100];
    char dateNaissance[20]; 
    int code; // ID de la classe à laquelle l'étudiant appartient
} Etudiant;

void ajouterEtudiant();
void afficherEtudiant();
void modifierEtudiant();
void supprimerEtudiant();
void rechercherEtudiant();

#endif