#include <stdio.h>
#include <unistd.h>
#include "choix_menu.h"

int main()
{
	int chx;
	do
	{
		menu_principal();
		chx=choix_menu();
		clean();
		redirection_vers_choix(chx);
	}while (chx!=0);
	
	
	return 0;
}
