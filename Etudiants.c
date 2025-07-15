#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "etudiants.h"

#define FICHIER_ETUDIANTS "Etudiants.csv"


void ajouterEtudiant() {
    Etudiant etudiant;

    printf("\n=== Ajouter un étudiant ===\n");
    printf("le numero : ");
    scanf("%d", &etudiant.numero);
    printf("Nom : ");
    scanf("%s", etudiant.nom);
    printf("Prénom : ");
    scanf(" %[^\n]", etudiant.prenom);
    printf("Date de naissance (JJ/MM/AAAA) : ");
    scanf("%s", etudiant.dateNaissance);
    printf("Email : ");
    scanf("%s", etudiant.email);
    printf("le code de la Classe : ");
    scanf("%d", &etudiant.code);

    FILE *f = fopen(FICHIER_ETUDIANTS, "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%d;%s;%s;%s;%s;%d\n", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, etudiant.code);
    fclose(f);

    printf(" Étudiant ajouté avec succès :)\n");
}


void afficherEtudiant() {
    Etudiant etudiant;

    FILE *f = fopen(FICHIER_ETUDIANTS, "r");
    if (f == NULL) {
        printf("Fichier introuvable ou vide.\n");
        return;
    }

    printf("\n=== Liste des étudiants ===\n");
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%d", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, &etudiant.code) == 6) {
        printf("Numero: %d | Nom: %s | Prénom: %s | Email: %s | Date naissance: %s | Classe: %d\n",
               etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, etudiant.code);
    }

    fclose(f);
}




void modifierEtudiant() {
    int numero_recherche;
    Etudiant etudiant;

    printf("\n=== Modifier un étudiant ===\n");
    printf("le numero de l'étudiant à modifier : ");
    scanf("%d", &numero_recherche);

    FILE *f = fopen(FICHIER_ETUDIANTS, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    FILE *temp = fopen("temp_etudiants.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%d\n", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, etudiant.code) ==6) {
        if (etudiant.numero == numero_recherche) {
            printf("Nouveau nom : ");
            scanf("%s", etudiant.nom);
            printf("Nouveau prénom : ");
            scanf("%s", etudiant.prenom);
            printf("Nouvel email : ");
            scanf("%s", etudiant.email);
            printf("Nouvelle date de naissance (JJ/MM/AAAA) : ");
            scanf("%s", etudiant.dateNaissance);
            printf("Nouveau code classe : ");
            scanf("%s", etudiant.code);
            trouve = 1;
        }
        fprintf(temp, "%d;%s;%s;%s;%s;%d\n", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.dateNaissance, etudiant.code);
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_etudiants.txt");
        printf("Étudiant avec le numero %d non trouvé.\n", numero_recherche);
        return;
    }

    remove(FICHIER_ETUDIANTS);
    rename("temp_etudiants.txt", FICHIER_ETUDIANTS);

    printf(">> Étudiant modifié avec succès.\n");
}

void supprimerEtudiant() {
    int numero_recherche;
    Etudiant etudiant;

    printf("\n=== Supprimer un étudiant ===\n");
    printf("le numero de l'étudiant à supprimer : ");
    scanf("%d", &numero_recherche);

    FILE *f = fopen(FICHIER_ETUDIANTS, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    FILE *temp = fopen("temp_etudiants.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%d\n", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, etudiant.code) == 6) {
        if (etudiant.numero != numero_recherche) {
            fprintf(temp, "%d;%s;%s;%s;%s;%d\n", etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, etudiant.code);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_etudiants.txt");
        printf("Étudiant avec le numero %d non trouvé.\n", numero_recherche);
        return;
    }

    remove(FICHIER_ETUDIANTS);
    rename("temp_etudiants.txt", FICHIER_ETUDIANTS);

    printf(">> Étudiant supprimé avec succès.\n");
}

void rechercherEtudiant() {
    int numero_recherche;
    Etudiant etudiant;

    printf("\n=== Rechercher un étudiant ===\n");
    printf("Le numero de l'étudiant à rechercher : ");
    scanf("%d", &numero_recherche);

    FILE *f = fopen(FICHIER_ETUDIANTS, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%d\n", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, etudiant.code) == 6) {
        if (etudiant.numero == numero_recherche) {
            printf("\n>> Étudiant trouvé :\n");
            printf("Le numero            : %d\n", etudiant.numero);
            printf("Nom           : %s\n", etudiant.nom);
            printf("Prénom        : %s\n", etudiant.prenom);
            printf("Email         : %s\n", etudiant.email); 
            printf("Date naissance: %s\n", etudiant.dateNaissance);
            printf("Classe        : %s\n", etudiant.code);
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (!trouve) {
        printf("Aucun étudiant avec le numero %d trouvé.\n", numero_recherche);
    }
}
