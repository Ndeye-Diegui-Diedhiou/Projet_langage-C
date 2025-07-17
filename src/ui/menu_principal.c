#include <stdio.h>
#include "../etudiant/etudiant.h"
#include "../matiere/matiere.h"
#include "../classe/classe.h"
#include "../note/note.h"
#include "../matiere/matiere_classe.h"
#include "../utils/file_utils.h"
#include <wchar.h>

void menuPrincipal() {
    int choixPrincipal, choixSous;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Gestion des étudiants\n");
        printf("2. Gestion des matières\n");
        printf("3. Gestion des classes\n");
        printf("4. Gestion des notes\n");
        printf("5. Gestion des associations matières <=> classes\n");
        printf("6. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choixPrincipal);

        switch (choixPrincipal) {
            case 1:
                do {
                    printf("\n--- Menu Étudiants ---\n");
                    printf("1. Ajouter un étudiant\n");
                    printf("2. Afficher les étudiants\n");
                    printf("3. Modifier un étudiant\n");
                    printf("4. Supprimer un étudiant\n");
                    printf("5. Rechercher un étudiant\n");
                    printf("6. Retour\n");
                    printf("Choix : ");
                    scanf("%d", &choixSous);

                    switch (choixSous) {
                        case 1: ajouterEtudiant(); break;
                        case 2: afficherEtudiant(); break;
                        case 3: modifierEtudiant(); break;
                        case 4: supprimerEtudiant(); break;
                        case 5: rechercherEtudiant(); break;
                    }
                } while (choixSous != 6);
                break;

            case 2:
                do {
                    printf("\n--- Menu Matières ---\n");
                    printf("1. Ajouter une matière\n");
                    printf("2. Afficher les matières\n");
                    printf("3. Modifier une matière\n");
                    printf("4. Supprimer une matière\n");
                    printf("5. Rechercher une matière\n");
                    printf("6. Retour\n");
                    printf("Choix : ");
                    scanf("%d", &choixSous);

                    switch (choixSous) {
                        case 1: ajouterMatiere(); break;
                        case 2: afficherMatieres(); break;
                        case 3: modifierMatiere(); break;
                        case 4: supprimerMatiere(); break;
                        case 5: rechercherMatiere(); break;
                    }
                } while (choixSous != 6);
                break;

            case 3:
                do {
                    printf("\n--- Menu Classes ---\n");
                    printf("1. Ajouter une classe\n");
                    printf("2. Afficher les classes\n");
                    printf("3. Modifier une classe\n");
                    printf("4. Supprimer une classe\n");
                    printf("5. Rechercher une classe\n");
                    printf("6. Retour\n");
                    printf("Choix : ");
                    scanf("%d", &choixSous);

                    switch (choixSous) {
                        case 1: ajouterClasse(); break;
                        case 2: afficherClasses(); break;
                        case 3: modifierClasse(); break;
                        case 4: supprimerClasse(); break;
                        case 5: rechercherClasse(); break;
                    }
                } while (choixSous != 6);
                break;

            case 4:
                do
                {
                    printf("\n--- Menu Notes ---\n");
                    printf("1. Ajouter une note pour un étudiant dans une matière\n");
                    printf("2. Ajouter les notes d'un étudiant pour toutes les matières\n");
                    printf("3. Ajouter les notes de toute une classe pour une matiere\n");
                    printf("4. Afficher les notes d'un étudiant pour une matière\n");
                    printf("5. Afficher toutes les notes d'un etudiant pour toutes les matiers\n");
                    printf("6. Afficher les notes d'une classe pour une matière\n");
                    printf("7. Modifier une note\n");
                    printf("8. Supprimer une note\n");
                    printf("9. Retour\n");
                    printf("Choix : ");
                    scanf("%d", &choixSous);

                    switch (choixSous) {
                        case 1: ajouterNoteEtudiantMatiere(); break;    
                        case 2: ajouterNotesToutesMatieres(); break;
                        case 3: ajouterNotesClasseMatiere(); break;
                        case 4: afficherNotesEtudiantMatiere(); break;
                        case 5: afficherNotesEtudiantToutesMatieres(); break;
                        case 6: afficherNotesClasseMatiere(); break;
                        case 7: modifierNote(); break;
                        case 8: supprimerNote(); break;
                        case 9: break; 
                        default: printf(">> Choix invalide.\n");
                    }
                } while (choixSous != 9);
                break;
                

            case 5:
                do {
                    printf("\n--- Menu Associations Matières/Classes ---\n");
                    printf("1. Associer une matière à une classe\n");
                    printf("2. dissocier une matière d'une classe\n");
                    printf("3. Afficher les matières d'une classe\n");
                    printf("4. Afficher les classes d'une matière\n");
                    printf("5. Retour\n");
                    printf("Choix : ");
                    scanf("%d", &choixSous);
                    switch (choixSous) {
                        case 1: associerMatiereClasse(); break;
                        case 2: dissocierMatiereClasse(); break;
                        case 3: afficherMatieresClasse(); break;
                        case 4: afficherClassesMatiere(); break;
                        case 5: break; 
                        default: printf(">> Choix invalide.\n");
                    }
                } while (choixSous != 5);
                break;

            case 6:
                printf("Au revoir !\n");
                break;
            

            default:
                printf(">> Choix invalide.\n");
                    
        }

    } while (choixPrincipal != 6);
}
