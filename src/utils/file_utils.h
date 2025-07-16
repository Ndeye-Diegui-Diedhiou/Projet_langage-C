#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes pour les chemins de fichiers
#define DONNEES_DIR "donnees/"
#define ETUDIANTS_FILE DONNEES_DIR "etudiants.csv"
#define CLASSES_FILE DONNEES_DIR "classes.csv"
#define MATIERES_FILE DONNEES_DIR "matieres.csv"
#define MATIERES_CLASSES_FILE DONNEES_DIR "matieres_classes.csv"
#define NOTES_FILE DONNEES_DIR "notes.csv"

// Fonctions utilitaires pour les fichiers
FILE* ouvrir_fichier(const char* nom_fichier, const char* mode);
void fermer_fichier(FILE* fichier);
int fichier_existe(const char* nom_fichier);
void creer_fichier_vide(const char* nom_fichier);
int compter_lignes(FILE* fichier);

// Fonctions utilitaires pour les chaînes
void nettoyer_chaine(char* chaine);
char* trim(char* chaine);
int est_nombre(const char* chaine);
float convertir_float(const char* chaine);
int convertir_int(const char* chaine);

// Fonctions utilitaires pour l'affichage
void afficher_separateur();
void afficher_titre(const char* titre);
void afficher_erreur(const char* message);
void afficher_succes(const char* message);

#endif // FILE_UTILS_H 