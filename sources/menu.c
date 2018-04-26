/* menu.h
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : contains fonctions that display & deal with menus selection
 *
 */

/* Display a menu with highlight selection (put highlight argument on 0 if it doesn't needed)
 * center by default, y for height.
 */

#include <stdlib.h>
#include <string.h>
#include <ncursesw/curses.h>

void display_logo(WINDOW *window, char *logoToDisplay[], int x, int y, int size) {
    int i = 0;
    for (i = 0 ; i < size ; i++) {
        mvwprintw(window, y, x, "%s", logoToDisplay[i]);
        y++;
    }
    wrefresh(window);
}

void display_vertical_menu(WINDOW *menuWindow, int highlight, char *menuToDisplay[], int x, int y, int n_choices) {
    
    int i = 0;

    for(i = 0 ; i < n_choices ; i++) {
       if(highlight == i + 1) {
            wattron(menuWindow, A_REVERSE); 
            mvwprintw(menuWindow, y, x, "%s", menuToDisplay[i]);
            wattroff(menuWindow, A_REVERSE);
        } else
            mvwprintw(menuWindow, y, x, "%s", menuToDisplay[i]);
        y += 2;
    }
    wrefresh(menuWindow);
}

void display_menu_actionChart(WINDOW *actionChartWindow, int highlight, char *actionChartMenu[], int y, int x, int category) {

    wattron(actionChartWindow, A_BOLD);
    if (highlight == category) {
        wattron(actionChartWindow, A_REVERSE); 
        mvwprintw(actionChartWindow, y, x, "%s", actionChartMenu[category]);
        wattroff(actionChartWindow, A_REVERSE);
    } else {
        mvwprintw(actionChartWindow, y, x, "%s", actionChartMenu[category]);
    }
    wattroff(actionChartWindow, A_BOLD);
}

