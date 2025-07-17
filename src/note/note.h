#ifndef NOTE_H
#define NOTE_H

typedef struct {
    int numero;
    int reference;
    float noteCC;
    float noteDS;
} Note;

// Ajout des notes
void ajouterNoteEtudiantMatiere();
void ajouterNotesToutesMatieres();
void ajouterNotesClasseMatiere();

// Affichage des notes
void afficherNotesEtudiantMatiere();
void afficherNotesEtudiantToutesMatieres();
void afficherNotesClasseMatiere();

// Modification et suppression
void modifierNote();
void supprimerNote();

#endif
