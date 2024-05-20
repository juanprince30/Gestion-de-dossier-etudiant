#include <stdio.h>
#include <unistd.h>

#include "dossier.h"

#ifndef CHOIX_MENU_H
#define CHOIX_MENU_H

void menu_principal(void)
{
    printf("_______________________________________________________________________________________________\n");
    printf("|               BIENVENUE DANS LE SYSTEME DE GESTION DES DOSSIERS ETUDIANTS                   |\n");
    printf("_______________________________________________________________________________________________\n");
    printf("|                 Veuillez choisir l'action que vous voulez executer:                         |\n");
    printf("|                                                                                             |\n");
    printf("|                              1- AJOUTER UN DOSSIER D'ELEVE                                  |\n");
    printf("|                              2- MODIFIER UN DOSSIER D'ELEVE                                 |\n");
    printf("|                              3- SUPPRIMER UN DOSSIER D'ELEVE                                |\n");
    printf("|                              4- AFFICHER LES DOSSIERS D'ELEVE                               |\n");
    printf("|                              0- QUITER LE PROGRAMME                                         |\n");
    printf("|                                                                                             |\n");
    printf("_______________________________________________________________________________________________\n");

}

void clean(void)
{
	#ifdef _WIN32
        system("cls");
    #else
       	system("clear");
   	#endif
}

int choix_menu(void)
{
	int choix;
	printf("\n");
	printf(" \t Veuillez Entrer votre choix : \t");
	scanf("%d",&choix); 
	while (choix < 0 || choix > 5)
	{ 
		printf("\t ERREUR !!!! Veuillez choisir entre les chiffres propose!!! \n");
		printf("\n");
		printf(" \t Veuillez Entrer votre choix : \t");
		scanf("%d",&choix);	
	}
	
	return choix;
}

void redirection_vers_choix (int choix) 
{
	if(choix==1 )
	{
		printf("\n");
		ajouter_dossier();
	}
	else if(choix==2 )
	{
		printf("\n");
		modifier_dossier();
	}
	else if(choix==3 )
	{
		printf("\n");
		supprimer_dossier ();
	}
	else if(choix==4 )
	{
		printf("\n");
		afficher_les_infos ();
	}
	else
	{
		printf("\n");
		printf("\t FERMETURE DU PROGRAMME EN COURS...");
		sleep(5);
	}
}

#endif
