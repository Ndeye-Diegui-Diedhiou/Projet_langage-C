#include "file_utils.h"
#include <ctype.h>

// Fonctions utilitaires pour les fichiers
FILE* ouvrir_fichier(const char* nom_fichier, const char* mode) {
    FILE* fichier = fopen(nom_fichier, mode);
    if (fichier == NULL) {
        afficher_erreur("Impossible d'ouvrir le fichier");
        return NULL;
    }
    return fichier;
}

void fermer_fichier(FILE* fichier) {
    if (fichier != NULL) {
        fclose(fichier);
    }
}

int fichier_existe(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier != NULL) {
        fclose(fichier);
        return 1;
    }
    return 0;
}

void creer_fichier_vide(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier != NULL) {
        fclose(fichier);
        afficher_succes("Fichier créé avec succès");
    } else {
        afficher_erreur("Impossible de créer le fichier");
    }
}

int compter_lignes(FILE* fichier) {
    if (fichier == NULL) return 0;
    
    int lignes = 0;
    char caractere;
    
    rewind(fichier);
    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == '\n') {
            lignes++;
        }
    }
    
    return lignes;
}

// Fonctions utilitaires pour les chaînes
void nettoyer_chaine(char* chaine) {
    if (chaine == NULL) return;
    
    // Supprimer les caractères de fin de ligne
    chaine[strcspn(chaine, "\r\n")] = 0;
}

char* trim(char* chaine) {
    if (chaine == NULL) return NULL;
    
    // Supprimer les espaces au début
    while (isspace((unsigned char)*chaine)) chaine++;
    
    if (*chaine == 0) return chaine;
    
    // Supprimer les espaces à la fin
    char* fin = chaine + strlen(chaine) - 1;
    while (fin > chaine && isspace((unsigned char)*fin)) fin--;
    
    fin[1] = '\0';
    return chaine;
}

int est_nombre(const char* chaine) {
    if (chaine == NULL || *chaine == '\0') return 0;
    
    char* endptr;
    strtod(chaine, &endptr);
    return *endptr == '\0';
}

float convertir_float(const char* chaine) {
    if (chaine == NULL) return 0.0f;
    return (float)atof(chaine);
}

int convertir_int(const char* chaine) {
    if (chaine == NULL) return 0;
    return atoi(chaine);
}

// Fonctions utilitaires pour l'affichage
void afficher_separateur() {
    printf("========================================\n");
}

void afficher_titre(const char* titre) {
    afficher_separateur();
    printf("  %s\n", titre);
    afficher_separateur();
}

void afficher_erreur(const char* message) {
    printf("❌ ERREUR: %s\n", message);
}

void afficher_succes(const char* message) {
    printf("✅ %s\n", message);
} 