#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"
#include "../utils/file_utils.h"
#include <wchar.h>

#define FICHIER_MATIERES "donnees/matieres.csv"
void ajouterMatiere() {
    Matiere matiere;

    printf("\n=== Ajouter une matière ===\n");

    printf("Référence : ");
    scanf("%d", &matiere.reference);

    printf("Libellé : ");
    scanf(" %[^\n]", &matiere.libelle);  

    printf("Coefficient : ");
    scanf("%hd", &matiere.coefficient);

    FILE *f = fopen(FICHIER_MATIERES, "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%d;%s;%hd\n", matiere.reference, matiere.libelle, matiere.coefficient);
    fclose(f);

    printf(" Matière ajoutée avec succès :)\n");
}

void afficherMatieres() {
    Matiere matiere;
    FILE *f = fopen(FICHIER_MATIERES, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    printf("\n=== Liste des matières ===\n");

    while (fscanf(f, "%d;%[^;];%hd\n", &matiere.reference, matiere.libelle, &matiere.coefficient) == 3) {
        printf("Référence: %d, Libellé: %s, Coefficient: %hd\n", matiere.reference, matiere.libelle, matiere.coefficient);
    }

    fclose(f);
}

void modifierMatiere() {
    int reference;
    char nouveauLibelle[50];
    int nouveauCoefficient;

    printf("\n=== Modifier une matière ===\n");
    printf("Référence de la matière à modifier : ");
    scanf("%d", &reference);
    printf("Nouveau libellé : ");
    scanf(" %[^\n]", nouveauLibelle); // Pour accepter les espaces
    printf("Nouveau coefficient : ");
    scanf("%hd", &nouveauCoefficient);

    FILE *f = fopen(FICHIER_MATIERES, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    FILE *temp = fopen("temp_matiere.csv", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    Matiere matiere;
    int trouve = 0;

    while (fscanf(f, "%d;%[^;];%hd\n", &matiere.reference, matiere.libelle, &matiere.coefficient) == 3) {
        if (matiere.reference == reference) {
            // Modifier les valeurs
            strncpy(matiere.libelle, nouveauLibelle, sizeof(matiere.libelle) - 1);
            matiere.libelle[sizeof(matiere.libelle) - 1] = '\0';
            matiere.reference = reference; // Assure que la référence reste la même
            matiere.coefficient = nouveauCoefficient;
            trouve = 1;
        }
        fprintf(temp, "%d;%s;%hd\n", matiere.reference, matiere.libelle, matiere.coefficient);
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_matiere.csv");
        printf("Matière avec référence %d non trouvée.\n", reference);
        return;
    }

    remove(FICHIER_MATIERES);
    rename("temp_matiere.csv", FICHIER_MATIERES);

    printf(" Matière modifiée avec succès :)\n");
}


void supprimerMatiere() {
    int reference;

    printf("\n=== Supprimer une matière ===\n");
    printf("Référence de la matière à supprimer : ");
    scanf("%d", &reference);

    FILE *f = fopen(FICHIER_MATIERES, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    FILE *temp = fopen("temp_matiere.csv", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    Matiere matiere;
    int trouve = 0;

    while (fscanf(f, "%d;%[^;];%hd\n", &matiere.reference, matiere.libelle, &matiere.coefficient)  == 3) {
        if (matiere.reference != reference) {
            fprintf(temp, "%d;%s;%hd\n", matiere.reference, matiere.libelle, matiere.coefficient);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_matiere.csv");
        printf(" Matière avec référence %d non trouvée :)\n", reference);
        return;
    }

    remove(FICHIER_MATIERES);
    rename("temp_matiere.csv", FICHIER_MATIERES);

    printf("Matière supprimée avec succès :)\n");
}


void rechercherMatiere() {
    int reference;
    Matiere matiere;

    printf("\n=== Rechercher une matière ===\n");
    printf("Référence de la matière à rechercher : ");
    scanf("%d", &reference);

    FILE *f = fopen(FICHIER_MATIERES, "r");
    if (f == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%hd\n", &matiere.reference, matiere.libelle, &matiere.coefficient) == 3) {
        if (matiere.reference == reference) {
            printf("\n Matière trouvée :\n");
            printf("Référence : %d\n", matiere.reference);
            printf("Libellé   : %s\n", matiere.libelle);
            printf("Coefficient : %hd\n", matiere.coefficient);
            trouve = 1;
            break;
        }
    }

    fclose(f);

    if (!trouve) {
        printf("Aucune matière avec la référence %d.\n", reference);
    }
}
