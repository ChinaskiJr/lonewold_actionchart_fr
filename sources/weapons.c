/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : deal the weapons of the player
 *
 */

#include <stdlib.h>
#include <ncursesw/curses.h>
#include <string.h>

#include "../headers/actionChart.h"
#include "../headers/constants.h"
#include "../headers/menu.h"
#include "../headers/weapons.h"

int weaponNumberChoice(WINDOW *numberWeaponChoiceWindow, int *weapon1, int *weapon2) {

	int 		xBloc = COLS / 24;
	int 		yBloc = LINES / 12;
	int 		wgetChoice = 0;
	int 		goOn = 1;
	int 		weaponNumberChoice = 0;
	int 		highlight = 1;

	char *weaponNumber[] = {
		"Arme 1",
		"Arme 2",
	};
	int sizeWeaponNumberArray = sizeof(weaponNumber) / sizeof(char *);
	int xWeaponNumberMenu = COLS / 4 - strlen(weaponNumber[0]) / 2;
	int yWeaponNumberMenu = LINES / 4 - sizeWeaponNumberArray;

	while (goOn) {
		numberWeaponChoiceWindow = newwin(LINES / 3, COLS / 3, LINES / 3, COLS / 3);
		box(numberWeaponChoiceWindow, ACS_VLINE, ACS_HLINE);

		xBloc = COLS / 24;
		yBloc = LINES / 12;
		xWeaponNumberMenu = COLS / 6 - strlen(weaponNumber[0]) / 2;
		yWeaponNumberMenu = LINES / 6 - sizeWeaponNumberArray;

 		display_vertical_menu(numberWeaponChoiceWindow, highlight, weaponNumber, xWeaponNumberMenu, yWeaponNumberMenu, sizeWeaponNumberArray);
		refresh();
		keypad(numberWeaponChoiceWindow, TRUE);
		wgetChoice = wgetch(numberWeaponChoiceWindow);

	    switch (wgetChoice) {
	    	case KEY_UP:
	    		if (highlight == 1)
	    			highlight = sizeWeaponNumberArray;
	    		else 
	    			highlight--;
	    	break;
	    	case KEY_DOWN:
	    		if (highlight == sizeWeaponNumberArray)
	    			highlight = 1;
	    		else
	    			highlight++;
	    	break;
	    	case 10:
	    		weaponNumberChoice = highlight;
	    		goOn = 0;
	    	break;
	    	case 'q':
	    		goOn = 0;
	    	break;
	    	case 'Q':
	    		goOn = 0;
	    	break;
	    }
 		display_vertical_menu(numberWeaponChoiceWindow, highlight, weaponNumber, xWeaponNumberMenu, yWeaponNumberMenu, sizeWeaponNumberArray);
	    refresh();
	}
	// 0 for weapon 1 ; 1 for weapon 2
	if (weaponNumberChoice == 1) {
		*weapon1 = weaponChoice(numberWeaponChoiceWindow, weaponNumberChoice);

	} else if (weaponNumberChoice == 2) {
		*weapon2 = weaponChoice(numberWeaponChoiceWindow, weaponNumberChoice);
	}
	delwin(numberWeaponChoiceWindow);
	return 0;
}

int weaponChoice(WINDOW *weaponsChoiceWindow, int weaponNumber) {
	
	int 		xBloc = COLS / 24;
	int 		yBloc = LINES / 12;
	int 		wgetChoice = 0;
	int 		goOn = 1;
	int			weapon = 0;
	int 		highlight = 1;

	char *weapons[] = {
		"Aucune",
    	"Dague",
    	"Lance",
    	"\u00C9p\u00E9e courte",
    	"Marteau de guerre",
    	"Hache",
    	"\u00C9p\u00E9e",
    	"B\u00E2ton",
    	"Glaive",
    	"Autre",
	};
	int sizeWeaponsArray = sizeof(weapons) / sizeof(char *);
	int xWeaponsMenu = COLS / 4 - strlen(weapons[0]) / 2;
	int yWeaponsMenu = LINES / 4 - sizeWeaponsArray;

	char choseWeapon[] = "S\u00E9lectionner votre arme :";

	while (goOn) {
		weaponsChoiceWindow = newwin(LINES * 0.6, COLS / 3, LINES / 6, COLS / 3);
		box(weaponsChoiceWindow, ACS_VLINE, ACS_HLINE);

		// Actualize the COLS or LINES dependences variables
		xBloc = COLS / 24;
		yBloc = LINES / 12;
		xWeaponsMenu = COLS / 6 - strlen(weapons[3]) / 2;
		yWeaponsMenu = LINES * 0.35 - sizeWeaponsArray;
		
		//display the menu 
		wattron(weaponsChoiceWindow, A_BOLD);
		mvwprintw(weaponsChoiceWindow, yBloc, COLS / 6 - strlen(choseWeapon) / 2, choseWeapon);
		wattroff(weaponsChoiceWindow, A_BOLD);
		
		display_vertical_menu(weaponsChoiceWindow, highlight, weapons, xWeaponsMenu, yWeaponsMenu, sizeWeaponsArray);
		refresh();
		keypad(weaponsChoiceWindow, TRUE);
		wgetChoice = wgetch(weaponsChoiceWindow);

	    switch (wgetChoice) {
	    	case KEY_UP:
	    		if (highlight == 1)
	    			highlight = sizeWeaponsArray;
	    		else 
	    			highlight--;
	    	break;
	    	case KEY_DOWN:
	    		if (highlight == sizeWeaponsArray)
	    			highlight = 1;
	    		else
	    			highlight++;
	    	break;
	    	case 10:
	    		weapon = highlight - 1;
	    		goOn = 0;
	    	break;
	    	case 'q':
	    		goOn = 0;
	    	break;
	    	case 'Q':
	    		goOn = 0;
	    	break;
	    }
		display_vertical_menu(weaponsChoiceWindow, highlight, weapons, xWeaponsMenu, yWeaponsMenu, sizeWeaponsArray);
	    refresh();
	}
	delwin(weaponsChoiceWindow);
	return weapon;
}