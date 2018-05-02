/* disciplines.c
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : display and deal disciplines interactions with other values
 *
 */

#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../headers/menu.h"
#include "../headers/disciplines.h"
#include "../headers/actionChart.h"
#include "../headers/constants.h"

int disciplineNumberChoice(WINDOW *disciplineNumberChoiceWindow, int *disciplines, int book) {
	
	int 		xBloc = 0;
	int 		yBloc = 0;
	int 		wgetChoice = 0;
	int 		goOn = 1;
	int 		disciplineNumberChoice = 0;
	int 		highlight = 1;
	int 		xDisciplineNumberMenu = 0;
	int 		yDisciplineNumberMenu = 0;

	char *disciplineNumber[] = {
		"Discipline 1",
		"Discipline 2",
		"Discipline 3",
		"Discipline 4",
		"Discipline 5",
		"Discipline 6",
		"Discipline 7",
		"Discipline 8",
		"Discipline 9",
		"Discipline 10",
	};
	int sizeDisciplineNumberArray = sizeof(disciplineNumber) / sizeof(char *);

	while (goOn) {
		disciplineNumberChoiceWindow = newwin(LINES * 0.6, COLS * 0.5, LINES / 4, COLS / 4);
		box(disciplineNumberChoiceWindow, ACS_VLINE, ACS_HLINE);

		xBloc = COLS / 24;
		yBloc = COLS / 12;
		xDisciplineNumberMenu = COLS / 4 - strlen(disciplineNumber[0]) / 2;
		yDisciplineNumberMenu = LINES * 0.3 - sizeDisciplineNumberArray;

		display_vertical_menu(disciplineNumberChoiceWindow, highlight, disciplineNumber, xDisciplineNumberMenu, yDisciplineNumberMenu, sizeDisciplineNumberArray);
		refresh();
		keypad(disciplineNumberChoiceWindow, TRUE);
		wgetChoice = wgetch(disciplineNumberChoiceWindow);

	    switch (toupper(wgetChoice)) {
	    	case KEY_UP:
	    		if (highlight == 1)
	    			highlight = sizeDisciplineNumberArray;
	    		else 
	    			highlight--;
	    	break;
	    	case KEY_DOWN:
	    		if (highlight == sizeDisciplineNumberArray)
	    			highlight = 1;
	    		else
	    			highlight++;
	    	break;
	    	case 10:
	    		disciplineNumberChoice = highlight;
	    		goOn = 0;
	    	break;
	    	case 'Q':
	    		goOn = 0;
	    	break;
	    }
	   	display_vertical_menu(disciplineNumberChoiceWindow, highlight, disciplineNumber, xDisciplineNumberMenu, yDisciplineNumberMenu, sizeDisciplineNumberArray);
	   	refresh();
	   	switch(disciplineNumberChoice) {
	   		case 1 : 
	   			disciplines[0] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   		break;
	   		case 2 : 
	   			disciplines[1] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   		break;
	   		case 3 : 
	   			disciplines[2] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   		break;
	   		case 4 :
	   			disciplines[3] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   		break;
	   		case 5 :
	   			disciplines[4] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   		break;
		   	case 6 : 
	   			if (book >= T2) {
		   			disciplines[5] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   			} 
		   	break;
		   	case 7 : 
	   			if (book >= T3) {
		   			disciplines[6] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   			}
		   	break;
		   	case 8 : 
	   			if (book >= T4) {
		   			disciplines[7] = choseKaiDisciplines(disciplineNumberChoiceWindow);
	   			}
		   	break;
		   	case 9 : 
		   		if (book >= T5) {
		   			disciplines[8] = choseKaiDisciplines(disciplineNumberChoiceWindow);
		   		} 
		   	break;
		   	case 10 : 
	   			if (book > T5) {
		   			disciplines[9] = choseKaiDisciplines(disciplineNumberChoiceWindow);
		   		}
		   	break;
	   	}	
	}

	delwin(disciplineNumberChoiceWindow);
	return 0;
}

int choseKaiDisciplines(WINDOW* choseDisciplinesWindow) {

	srand(time(NULL));

	int 		xBloc = COLS / 24;
	int 		yBloc = LINES / 12;
	int 		wgetChoice = 0;
	int 		disciplineChoice = 0;
	int 		goOn = 1;
	int 		highlight = 1;

	
   	char *disciplinesKai[] = {
    	"Camouflage",
    	"La chasse",
    	"Sixi\u00E8me sens",
    	"Orientation",
    	"Gu\u00E9rison",
    	"Ma\u00EEtrise des armes",
    	"Bouclier psychique",
    	"Puissance psychique",
    	"Communication animale",
    	"Ma\u00EEtrise psychique de la mati\u00E8re",
    	"Aucune",
    };
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
    int sizeDisciplinesArray = sizeof(disciplinesKai) / sizeof(char *);
    int xDisciplinesMenu = COLS / 6 - strlen(disciplinesKai[9]) / 2;
    int yDisciplinesMenu = LINES * 0.35 - sizeDisciplinesArray;

    char choseDiscipline[] = "Choisissez une discipline :";

    while (goOn) {
    	choseDisciplinesWindow = newwin(LINES * 0.75, COLS / 3, LINES / 6, COLS / 3);
    	box(choseDisciplinesWindow, ACS_VLINE, ACS_HLINE);

		// Actualize the COLS or LINES dependences variables
    	xBloc = COLS / 24;
		yBloc = LINES / 12;
    	xDisciplinesMenu = COLS / 6 - strlen(disciplinesKai[9]) / 2, COLS / 24;
		yDisciplinesMenu = LINES * 0.35 - sizeDisciplinesArray;

		//display the menu
		wattron(choseDisciplinesWindow, A_BOLD);
		mvwprintw(choseDisciplinesWindow, yBloc, COLS / 6 - strlen(choseDiscipline) / 2, choseDiscipline);
		wattroff(choseDisciplinesWindow, A_BOLD);

		display_vertical_menu(choseDisciplinesWindow, highlight, disciplinesKai, xDisciplinesMenu, yDisciplinesMenu, sizeDisciplinesArray);
		refresh();
		keypad(choseDisciplinesWindow, TRUE);
		wgetChoice = wgetch(choseDisciplinesWindow);

	    switch (toupper(wgetChoice)) {
	    	case KEY_UP:
	    		if (highlight == 1)
	    			highlight = sizeDisciplinesArray;
	    		else 
	    			highlight--;
	    	break;
	    	case KEY_DOWN:
	    		if (highlight == sizeDisciplinesArray)
	    			highlight = 1;
	    		else
	    			highlight++;
	    	break;
	    	case 10:
	    		disciplineChoice = highlight - 1;
	    		goOn = 0;
	    	break;
	    	case 'Q':
	    		goOn = 0;
	    	break;
	    }
	    display_vertical_menu(choseDisciplinesWindow, highlight, disciplinesKai, xDisciplinesMenu, yDisciplinesMenu, sizeDisciplinesArray);
	    refresh();
    }
    delwin(choseDisciplinesWindow);
    return disciplineChoice;
}