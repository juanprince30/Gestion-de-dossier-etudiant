#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1000
#ifndef DOSSIER_H
#define DOSSIER_H

typedef struct 
{
	int ID;
    char nom[500];
    char prenom[500];
    char date_de_naissance[500];
} etudiant;

int supprimer_saut(char *chaine, int longueur)
{
	char *positionEntree = NULL;
	if (fgets(chaine, longueur, stdin) != NULL) // Pas d'erreur desaisie ?
	{
		positionEntree = strchr(chaine, '\n'); // On recherchel'"Entrée"
		if (positionEntree != NULL) // Si on a trouvé le retour àla ligne
		{
			*positionEntree = '\0'; // On remplace ce caractère par\0
		}
		return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
	}
	else
	{
		return 0; // On renvoie 0 s'il y a eu une erreur
	}
}

int identifiant()
{
	int compteur;
	
	FILE *fichier;
    char ligne[MAX_LINE_LENGTH];

    fichier = fopen("Dossier_etudiant.txt", "r");
	
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    
    compteur=1;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        compteur++;
    }
    fclose(fichier);
	
	return compteur;
}

int ajouter_dossier()
{
	etudiant ajout;
	
	ajout.ID=identifiant();
	printf("\t Veuillez entrer le Nom de L'etudiant :\t");
	fgets(ajout.nom, 500, stdin);
	supprimer_saut(ajout.nom,500);
	printf("\t Veuillez entrer le prenom de l'etudiant :\t");
	supprimer_saut(ajout.prenom,500);
	printf("\t Veuillez entrer la date de naissance de l'etudiant :(JJ/MM/AAAA)\t");
	supprimer_saut(ajout.date_de_naissance,500);
	
	FILE *fichier;
	fichier= fopen("Dossier_etudiant.txt","a");
	
	if (fichier == NULL) 
	{
       	fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
       	return 1;
   	}
   	
   	fprintf(fichier, "ID: %d\t  NOM: %s\t  PRENOM: %s\t Date DE NAISSANCE: %s\t ",ajout.ID, ajout.nom, ajout.prenom, ajout.date_de_naissance);
    fprintf(fichier, "\n");
    
    fclose(fichier);
    
    printf("\t L'enregistrement du dossier de l'etudiant a ete effectue avec succes.\n");
   	return 0;
	
}

int nombre_ligne()
{
	
	int compteur ;
    
	FILE *fichier;
    char ligne[MAX_LINE_LENGTH];

    fichier = fopen("Dossier_etudiant.txt", "r");
    
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    
    compteur=0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        compteur++;
    }
    fclose(fichier);
	
	return compteur;
}

int modifier_dossier()
{
	int ligne_total, ligne_modifier, numeroligne;
	char ligne[MAX_LINE_LENGTH];
	ligne_total =nombre_ligne();
	
	printf("Quel est l'identifiant de l'etudiant que vous voulez modifier: ");
	scanf("%d",&ligne_modifier);
	while(ligne_modifier<0 || ligne_modifier> ligne_total)
	{
		printf("Veuillez vous assurer de rentrer un identifiant d'etudiant Valide !!!\n");
		printf("Quel est l'identifiant de l'etudiant que vous voulez modifier: ");
		scanf("%d",&ligne_modifier);
	}
	
	FILE *fichier, *fichiersortie;
	
	fichier = fopen("Dossier_etudiant.txt", "r");
    fichiersortie= fopen("temp.txt", "w");
    
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    if (fichiersortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    
    numeroligne=0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        numeroligne++;
        if (numeroligne != ligne_modifier) {
            fputs(ligne, fichiersortie);
        }
        else
        {
        	etudiant modif;
	
			modif.ID=ligne_modifier;
			printf("\t Veuillez entrer le Nom de L'etudiant :\t");
			fgets(modif.nom, 500, stdin);
			supprimer_saut(modif.nom,500);
			printf("\t Veuillez entrer le prenom de l'etudiant :\t");
			supprimer_saut(modif.prenom,500);
			printf("\t Veuillez entrer la date de naissance de l'etudiant :(JJ/MM/AAAA)\t");
			supprimer_saut(modif.date_de_naissance,500);
			
			fprintf(fichiersortie, "ID: %d\t  NOM: %s\t  PRENOM: %s\t Date DE NAISSANCE: %s\t ",modif.ID,modif.nom, modif.prenom, modif.date_de_naissance);
    		fprintf(fichiersortie, "\n");
    	}
	}
	
	fclose(fichier);
    fclose(fichiersortie);
    
    remove("Dossier_etudiant.txt");
    rename("temp.txt", "Dossier_etudiant.txt");
    
    
    printf("\t La Modification du dossier de l'etudiant a ete effectue avec succes.\n");
   	return 0;
	
}

int mettre_a_jour()
{
	int ligne_total, ligne_supprimer, numeroligne, nl;
	char ligne[MAX_LINE_LENGTH];
	char ligne_cut[MAX_LINE_LENGTH-7];
	ligne_total =nombre_ligne();
	
	FILE *fichier, *fichiersortie;
	
	fichier = fopen("Dossier_etudiant.txt", "r");
    fichiersortie= fopen("temp.txt", "w");
    
    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    if (fichiersortie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
	
	
	int i,j,g;
    char l[MAX_LINE_LENGTH];
    g= 1;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
    	for (i = 7, j = 0; i < MAX_LINE_LENGTH; i++, j++) 
		{
        	ligne_cut[j] = ligne[i];
    	}
    	fprintf(fichiersortie, "ID: %d\t  ", g);
		fputs(ligne_cut, fichiersortie);
		g++;
    }
    
    fclose(fichier);
    fclose(fichiersortie);
    
    remove("Dossier_etudiant.txt");
    rename("temp.txt", "Dossier_etudiant.txt");	
	
	return 0;
}

int supprimer_dossier()
{
    int ligne_total, ligne_supprimer, numeroligne;
    char ligne[MAX_LINE_LENGTH];
    ligne_total = nombre_ligne();

    printf("Quel est l'identifiant de l'etudiant que vous voulez supprimer: ");
    scanf("%d", &ligne_supprimer);
    while (ligne_supprimer < 1 || ligne_supprimer > ligne_total)
    {
        printf("Veuillez vous assurer de rentrer un identifiant valide !!!\n");
        printf("Quel est l'identifiant de l'etudiant que vous voulez supprimer: ");
        scanf("%d", &ligne_supprimer);
    }

    FILE *fichier, *fichiersortie;

    fichier = fopen("Dossier_etudiant.txt", "r");
    if (fichier == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    fichiersortie = fopen("temp.txt", "w");
    if (fichiersortie == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier temporaire.\n");
        fclose(fichier);
        return 1;
    }

    numeroligne = 0;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        numeroligne++;
        if (numeroligne != ligne_supprimer)
        {
            fputs(ligne, fichiersortie);
        }
    }

    fclose(fichier);
    fclose(fichiersortie);

    // Supprimer l'ancien fichier et renommer le fichier temporaire
    if (remove("Dossier_etudiant.txt") != 0)
    {
        fprintf(stderr, "Erreur lors de la suppression du fichier original.\n");
        return 1;
    }
    if (rename("temp.txt", "Dossier_etudiant.txt") != 0)
    {
        fprintf(stderr, "Erreur lors du renommage du fichier temporaire.\n");
        return 1;
    }
    
    mettre_a_jour();

    printf("Le dossier de l'etudiant a ete supprime avec succes!!\n");
    return 0;
}


int afficher_les_infos()
{
    
	FILE *fichier;
    char ligne[MAX_LINE_LENGTH];

    fichier = fopen("Dossier_etudiant.txt", "r");

    if (fichier == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
	
	printf("Listes des ETUDIANTS: \n");
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

   	fclose(fichier);

   	return 0;
}

#endif
