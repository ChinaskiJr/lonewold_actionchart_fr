/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : choice's book and variables for each book
 *
 */

#include <stdlib.h>
#include <string.h>
#include <ncursesw/curses.h>

#include "../headers/actionChart.h"
#include "../headers/constants.h"
#include "../headers/menu.h"

int bookChoice(WINDOW *bookWindow) {

	int 		xBloc = COLS / 24;
	int			yBloc = LINES / 12;
	int			wgetChoice = 0;
	int 		goOn = 1;
	int 		book = 0;
	int 		highlight = 1;

    char *books[] = {
        "Tome 1 - Les ma\u00EEtre des t\u00E9n\u00E8bres",
        "Tome 2 - La travers\u00E9e infernale",
        "Tome 3 - Les grottes de Kalte",
        "tome 4 - Le gouffre maudit",
        "tome 5 - Le tyran du d\u00E9sert",
    };
    int sizeBooksArray = sizeof(books) / sizeof(char *);
	int xBooksMenu = COLS / 4 - strlen(books[0]) / 2;
	int yBooksMenu = LINES / 4 - sizeBooksArray;

    char choseBook[100] = "S\u00E8lectionnez votre livre : ";

    while (goOn) {
    	bookWindow = newwin(LINES / 2, COLS / 2, LINES / 4, COLS / 4);
    	box(bookWindow, ACS_VLINE, ACS_HLINE);

    	// Actualize the COLS or LINES dependences variables
    	xBloc = COLS / 24;
    	yBloc = LINES / 12;
    	xBooksMenu = COLS / 4 - strlen(books[0]) / 2;
    	yBooksMenu = LINES / 4 - sizeBooksArray;

	    // display the menu
	    wattron(bookWindow, A_BOLD);
	    mvwprintw(bookWindow, yBloc,COLS / 4 - strlen(choseBook) / 2, choseBook);
	    wattroff(bookWindow, A_BOLD);

		display_vertical_menu(bookWindow, highlight, books, xBooksMenu, yBooksMenu, sizeBooksArray);
	    refresh();
	    keypad(bookWindow, TRUE);
	    wgetChoice = wgetch(bookWindow);

	    switch (wgetChoice) {
	    	case KEY_UP:
	    		if (highlight == 1)
	    			highlight = sizeBooksArray;
	    		else 
	    			highlight--;
	    	break;
	    	case KEY_DOWN:
	    		if (highlight == sizeBooksArray)
	    			highlight = 1;
	    		else
	    			highlight++;
	    	break;
	    	case 10:
	    		book = highlight - 1;
	    		goOn = 0;
	    	break;
	    	case 'q':
	    		goOn = 0;
	    	break;
	    	case 'Q':
	    		goOn = 0;
	    	break;
	    }
		display_vertical_menu(bookWindow, highlight, books, xBooksMenu, yBooksMenu, sizeBooksArray);
	    refresh();
	}
	delwin(bookWindow);
    return book;
}