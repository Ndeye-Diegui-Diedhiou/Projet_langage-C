#include <stdio.h>
#include "matiere_classe.h"
#include "../utils/file_utils.h"
#include <wchar.h>

#define FICHIER_MATIERES_CLASSES "donnees/matieres_classes.csv"

void associerMatiereClasse() {
    int code;
    int reference;

    printf("Code de la classe : ");
    scanf("%d", code);

    printf("Référence de la matière : ");
    scanf("%d", &reference);

    FILE *f = fopen(FICHIER_MATIERES_CLASSES, "a");
    if (!f) {
        printf("Erreur d'ouverture du fichier !\n");
        return;
    }
    fprintf(f, "%d;%d\n", code, reference);
    fclose(f);

    printf("Matière %d associée à la classe %d.\n", reference, code);
}


void dissocierMatiereClasse() {
    int codeSaisi, referenceSaisie;

    printf("Code de la classe : ");
    scanf("%d", &codeSaisi);

    printf("Référence de la matière : ");
    scanf("%d", &referenceSaisie);

    FILE *f = fopen(FICHIER_MATIERES_CLASSES, "r");
    FILE *temp = fopen("temp_matieres_classes.csv", "w");
    if (!f || !temp) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    int codeLigne, referenceLigne;
    int trouve = 0;

    while (fscanf(f, "%d;%d\n", &codeLigne, &referenceLigne) == 2) {
        if (codeLigne == codeSaisi && referenceLigne == referenceSaisie) {
            trouve = 1;
            continue; // on saute cette ligne
        }
        fprintf(temp, "%d;%d\n", codeLigne, referenceLigne);
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp_matieres_classes.csv");
        printf("Association non trouvée.\n");
        return;
    }

    remove(FICHIER_MATIERES_CLASSES);
    rename("temp_matieres_classes.csv", FICHIER_MATIERES_CLASSES);
    printf("Association supprimée avec succès.\n");
}



// Afficher les matières d'une classe
void afficherMatieresClasse() {
    int code;
    printf("Veuillez saisir le Code de la classe : ");
    if (scanf("%d", &code) != 1) {
        printf("Entrée invalide.\n");
        return;
    }

    FILE *f = fopen(FICHIER_MATIERES_CLASSES, "r");
    if (!f) {
        printf("Fichier introuvable.\n");
        return;
    }

    int matiereCode;
    int reference;
    int trouve = 0;

    printf("Matières associées à la classe %d :\n", code);
    while (fscanf(f, "%d;%d\n", &matiereCode, &reference) == 2) {
        if (matiereCode == code) {
            printf("La référence de la matière : %d\n", reference);
            trouve = 1;
        }
    }

    fclose(f);
    
    if (!trouve) {
        printf("Cette classe n'est associée à aucune matière pour le moment.\n");
    }
}

// Afficher les classes d'une matière
void afficherClassesMatiere() {
    int reference;
    printf("Veuillez saisir la Référence de la matière : ");
    if (scanf("%d", &reference) != 1) {
        printf("Entrée invalide.\n");
        return;
    }

    FILE *f = fopen(FICHIER_MATIERES_CLASSES, "r");
    if (!f) {
        printf("Fichier introuvable.\n");
        return;
    }

    int code;
    int matiereReference;
    int trouve = 0;

    printf("Classes associées à la matière %d :\n", reference);
    while (fscanf(f, "%d;%d\n", &code, &matiereReference) == 2) {
        if (matiereReference == reference) {
            printf("Le code de la classe : %d\n", code);
            trouve = 1;
        }
    }

    fclose(f);
    
    if (!trouve) {
        printf("Cette matière n'est associée à aucune classe pour le moment.\n");
    }
}
