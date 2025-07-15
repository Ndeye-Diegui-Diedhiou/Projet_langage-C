#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <wchar.h>
#include "classes.h"

#define FICHIER_CLASSES "Classes.csv"

void ajouterClasse() {
    Classe classe;

    printf("\n=== Ajouter une classe ===\n");
    printf("Code : ");
    scanf("%d", &classe.code);
    printf("Nom : ");
    scanf("%s", classe.nom);
    printf("Niveau : ");
    scanf("%s", classe.niveau);

    FILE *f = fopen(FICHIER_CLASSES, "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%d;%s;%s\n", classe.code, classe.nom, classe.niveau);
    fclose(f);

    printf(" Classe ajoutée avec succès :)\n");
}


void afficherClasses() {
    Classe classe;
    FILE *f = fopen(FICHIER_CLASSES, "r");
    if (f == NULL) {
        printf("Fichier vide ou introuvable.\n");
        return;
    }

    printf("\n=== Liste des classes ===\n");
    while (fscanf(f, "%d;%[^;];%s\n", &classe.code, classe.nom, classe.niveau) == 3) {
        printf("Code: %d, Nom: %s, Niveau: %s\n", classe.code, classe.nom, classe.niveau);
    }

    fclose(f);
}


void modifierClasse() {
    int code_recherche;
    Classe classe;

    printf("\n=== Modifier une classe ===\n");
    printf("le code de la classe à modifier : ");
    scanf("%d", &code_recherche);

    FILE *f = fopen(FICHIER_CLASSES, "r");
    if (f == NULL) {
        printf("Classe introuvable.\n");
        return;
    }

    FILE *temp = fopen("temp_classes.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%s", &classe.code, classe.nom, classe.niveau) == 3) {
        if (classe.code == code_recherche) {
            printf("Nouveau code : ");
            scanf("%d", &classe.code);
            printf("Nouveau nom : ");
            scanf("%s", classe.nom);
            printf("Nouvel niveau : ");
            scanf("%s", classe.niveau);
           
            trouve = 1;
        }
        fprintf(temp, "%d;%s;%s\n", classe.code, classe.nom, classe.niveau);
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_classes.txt");
        printf("Classe avec le code %d non trouvé.\n", code_recherche);
        return;
    }

    remove(FICHIER_CLASSES);
    rename("temp_classes.txt", FICHIER_CLASSES);

    printf("Classe modifié avec succès :)\n");
}

void supprimerClasse() {
    int code_recherche;
    Classe classe;

    printf("\n=== Supprimer une classe ===\n");
    printf("le code de la classe à supprimer : ");
    scanf("%d", &code_recherche);

    FILE *f = fopen(FICHIER_CLASSES, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    FILE *temp = fopen("temp_classes.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%s\n", &classe.code, classe.nom, classe.niveau) == 3) {
        if (classe.code != code_recherche) {
            fprintf(temp, "%d;%s;%s\n", classe.code, classe.nom, classe.niveau);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_classes.txt");
        printf("Classe avec le code %d non trouvé.\n", code_recherche);
        return;
    }

    remove(FICHIER_CLASSES);
    rename("temp_classes.txt", FICHIER_CLASSES);

    printf("Classe supprimé avec succès :)\n");
}


void rechercherClasse() {
    int code_recherche;
    Classe classe;

    printf("\n=== Rechercher une classe ===\n");
    printf("Le code de la classe à rechercher : ");
    scanf("%d", &code_recherche);

    FILE *f = fopen(FICHIER_CLASSES, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%s\n", &classe.code, classe.nom, classe.niveau) == 3) {
        if (classe.code == code_recherche) {
            printf("\n Classe trouvé :\n");
            printf("Le code           : %d\n", classe.code);
            printf("Nom           : %s\n", classe.nom);
            printf("Niveau        : %s\n", classe.niveau);
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (!trouve) {
        printf("Aucunne classe avec le code %d n'est trouvée.\n", code_recherche);
    }
}
