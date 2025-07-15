#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.h"
#include "etudiants.h"
#include "matieres.h"

#define FICHIER_NOTES "Notes.csv"
#define FICHIER_ETUDIANTS "Etudiants.csv"
#define FICHIER_MATIERES "Matieres.csv"

void ajouterNoteEtudiantMatiere() {
    Note note;
    printf("\n---- Ajouter une note à un étudiant pour une matière ----\n");
    printf("Numéro de l'étudiant : ");
    scanf("%d", &note.numero);
    printf("Référence de la matière : ");
    scanf("%d", &note.reference);
    printf("Note CC : ");
    scanf("%f", &note.noteCC);
    printf("Note DS : ");
    scanf("%f", &note.noteDS);

    FILE *f = fopen(FICHIER_NOTES, "a");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }

    fprintf(f, "%d;%d;%.2f;%.2f\n", note.numero, note.reference, note.noteCC, note.noteDS);
    fclose(f);

    printf("Note ajoutée avec succès.\n");
}

void ajouterNotesToutesMatieres(){
    Note note;
    Matiere matiere;
    Etudiant etudiant;
    printf("\n---- Ajouter des notes pour toutes les matières d'un étudiant ----\n");
    printf("Numéro de l'étudiant : ");
    scanf("%d", &note.numero);

    FILE *fEtudiants = fopen(FICHIER_ETUDIANTS, "r");
    if (fEtudiants == NULL) {
        printf("Erreur d'ouverture du fichier des étudiants.\n");
        return;
    }
    int etudiantTrouve = 0;
    while (fscanf(fEtudiants, "%d;%[^;];%[^;];%[^;];%[^;];%d\n", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, &etudiant.code) == 6) {
        if (etudiant.numero == note.numero) {
            etudiantTrouve = 1;
            break;
        }
    }
    fclose(fEtudiants);
    if (!etudiantTrouve) {
        printf("Étudiant non trouvé.\n");
        return;
    }
    FILE *fMatieres = fopen(FICHIER_MATIERES, "r");
    if (fMatieres == NULL) {
        printf("Erreur d'ouverture du fichier des matières.\n");
        return;
    }
    while (fscanf(fMatieres, "%d;%[^;];%hd\n", &matiere.reference, matiere.libelle, &matiere.coefficient) == 3) {
        printf("Référence de la matière : %d\n", matiere.reference);
        printf("Note CC : ");
        scanf("%.2f", &note.noteCC);
        printf("Note DS : ");
        scanf("%.2f", &note.noteDS);

        FILE *fNotes = fopen(FICHIER_NOTES, "a");
        if (fNotes == NULL) {
            printf("Erreur d'ouverture du fichier des notes.\n");
            fclose(fMatieres);
            return;
        }
        fprintf(fNotes, "%d;%d;%.2f;%.2f\n", note.numero, matiere.reference, note.noteCC, note.noteDS);
        fclose(fNotes);
    }
    fclose(fMatieres);
    printf("Notes ajoutées avec succès pour l'étudiant %d.\n", note.numero);

}


//ajouter les notes de toute une classe pour une matière
void ajouterNotesClasseMatiere() {
    int codeClasse, reference;
    Note note;
    printf("\n---- Ajouter des notes pour une classe et une matière ----\n");
    printf("Code de la classe : ");
    scanf("%d", &codeClasse);
    printf("Référence de la matière : ");
    scanf("%d", &reference);

    FILE *fEtudiants = fopen(FICHIER_ETUDIANTS, "r");
    if (fEtudiants == NULL) {
        printf("Erreur d'ouverture du fichier des étudiants.\n");
        return;
    }

    Etudiant etudiant;
    while (fscanf(fEtudiants, "%d;%[^;];%[^;];%[^;];%[^;];%d\n", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, &etudiant.code) == 6) {
        if (etudiant.code == codeClasse) {
            note.numero = etudiant.numero;
            note.reference = reference;
            printf("Note CC pour l'étudiant %s : ", etudiant.nom);
            scanf("%f", &note.noteCC);
            printf("Note DS pour l'étudiant %s : ", etudiant.nom);
            scanf("%f", &note.noteDS);

            FILE *fNotes = fopen(FICHIER_NOTES, "a");
            if (fNotes == NULL) {
                printf("Erreur d'ouverture du fichier des notes.\n");
                fclose(fEtudiants);
                return;
            }
            fprintf(fNotes, "%d;%d;%.2f;%.2f\n", note.numero, note.reference, note.noteCC, note.noteDS);
            fclose(fNotes);
        }
    }
    fclose(fEtudiants);
    printf("Notes ajoutées avec succès pour la classe %d et la matière %d.\n", codeClasse, reference);
}


void afficherNotesEtudiantMatiere() {
    int numero, reference;
    Note note;
    printf("\n---- Afficher les notes d'un étudiant pour une matière ----\n");
    printf("Numéro de l'étudiant : ");
    scanf("%d", &numero);
    printf("Référence de la matière : ");
    scanf("%d", &reference);
    
    FILE *f = fopen(FICHIER_NOTES, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes.\n");
        return;
    }
    int trouve = 0;
    while (fscanf(f, "%d;%d;%.2f;%.2f\n", &note.numero, &note.reference, &note.noteCC, &note.noteDS) == 4) {
        if (note.numero == numero && note.reference == reference) {
            printf("Note CC : %.2f, Note DS : %.2f\n", note.noteCC, note.noteDS);
            trouve = 1;
        }
    }
    fclose(f);
    if (!trouve) {
        printf("Aucune note trouvée pour l'étudiant %d et la matière %d.\n", numero, reference);
    }
}

void afficherNotesEtudiantToutesMatieres() {
    int numero;
    Note note;
    printf("\n---- Afficher les notes d'un étudiant pour toutes les matières ----\n");
    printf("Numéro de l'étudiant : ");
    scanf("%d", &numero);

    FILE *f = fopen(FICHIER_NOTES, "r"); 
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes.\n");
        return;
    } 
    int trouve = 0;
    while (fscanf(f, "%d;%d;%.2f;%.2f\n", &note.numero, &note.reference, &note.noteCC, &note.noteDS) == 4) {
        if (note.numero == numero) {
            printf("Matière %d - Note CC : %.2f, Note DS : %.2f\n", note.reference, note.noteCC, note.noteDS);
            trouve = 1;
        }
    }
    fclose(f);
    if (!trouve) {
        printf("Aucune note trouvée pour l'étudiant %d.\n", numero);
    } 
}


void afficherNotesClasseMatiere() {
    int codeClasse, reference;
    Note note;
    printf("\n---- Afficher les notes d'une classe pour une matière ----\n");
    printf("Code de la classe : ");
    scanf("%d", &codeClasse);
    printf("Référence de la matière : ");
    scanf("%d", &reference);

    FILE *fEtudiants = fopen(FICHIER_ETUDIANTS, "r");
    if (fEtudiants == NULL) {
        printf("Erreur d'ouverture du fichier des étudiants.\n");
        return;
    }

    Etudiant etudiant;
    while (fscanf(fEtudiants, "%d;%[^;];%[^;];%[^;];%[^;];%d\n", &etudiant.numero, etudiant.nom, etudiant.prenom, etudiant.email, etudiant.dateNaissance, &etudiant.code) == 6) {
        if (etudiant.code == codeClasse) {
            FILE *fNotes = fopen(FICHIER_NOTES, "r");
            if (fNotes == NULL) {
                printf("Erreur d'ouverture du fichier des notes.\n");
                fclose(fEtudiants);
                return;
            }
            int trouve = 0;
            while (fscanf(fNotes, "%d;%d;%.2f;%.2f\n", &note.numero, &note.reference, &note.noteCC, &note.noteDS) == 4) {
                if (note.numero == etudiant.numero && note.reference == reference) {
                    printf("Étudiant %s - Note CC : %.2f, Note DS : %.2f\n", etudiant.nom, note.noteCC, note.noteDS);
                    trouve = 1;
                }
            }
            fclose(fNotes);
            if (!trouve) {
                printf("Aucune note trouvée pour l'étudiant %s dans la matière %d.\n", etudiant.nom, reference);
            }
        }
    }
    fclose(fEtudiants);
}
void modifierNote() {
    int numero, reference;
    Note note;
    int trouve = 0;

    printf("\n---- Modifier une note ----\n");
    printf("Numéro de l'étudiant : ");
    scanf("%d", &numero);
    printf("Référence de la matière : ");
    scanf("%d", &reference);

    FILE *f = fopen(FICHIER_NOTES, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes.\n");
        return;
    }

    FILE *temp = fopen("notes_temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur d'ouverture du fichier temporaire.\n");
        return;
    }

    while (fscanf(f, "%d;%d;%f;%f\n", &note.numero, &note.reference, &note.noteCC, &note.noteDS) == 4) {
        if (note.numero == numero && note.reference == reference) {
            printf("Nouvelle Note CC : ");
            scanf("%f", &note.noteCC);
            printf("Nouvelle Note DS : ");
            scanf("%f", &note.noteDS);
            trouve = 1;
        }
        fprintf(temp, "%d;%d;%.2f;%.2f\n", note.numero, note.reference, note.noteCC, note.noteDS);
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("notes_temp.txt");
        printf("Aucune note trouvée pour l'étudiant %d et la matière %d.\n", numero, reference);
        return;
    }

    remove(FICHIER_NOTES);                      // Supprimer l'ancien fichier
    rename("notes_temp.txt", FICHIER_NOTES);    // Renommer le nouveau
    printf("Note modifiée avec succès :)\n");
}



void supprimerNote() {
    int numero, reference;
    Note note;
    printf("\n---- Supprimer une note ----\n");
    printf("Numéro de l'étudiant : ");
    scanf("%d", &numero);
    printf("Référence de la matière : ");
    scanf("%d", &reference);

    FILE *f = fopen(FICHIER_NOTES, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes.\n");
        return;
    }

    FILE *temp = fopen("notes_temp.txt", "w");
    if (temp == NULL) {
        fclose(f);
        printf("Erreur de création du fichier temporaire.\n");
        return;
    }

    int trouve = 0;
    while (fscanf(f, "%d;%d;%.2f;%.2f\n", &note.numero, &note.reference, &note.noteCC, &note.noteDS) == 4) {
        if (note.numero != numero || note.reference != reference) {
            fprintf(temp, "%d;%d;%.2f;%.2f\n", note.numero, note.reference, note.noteCC, note.noteDS);
        } else {
            trouve = 1;
        }
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("notes_temp.txt");
        printf("Aucune note trouvée pour l'étudiant %d et la matière %d.\n", numero, reference);
        return;
    }

    remove(FICHIER_NOTES);
    rename("notes_temp.txt", FICHIER_NOTES);
    printf("Note supprimée avec succès :)\n");
}

