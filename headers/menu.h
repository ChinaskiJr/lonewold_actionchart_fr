/* menu.h
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : contains menu.c headers
 *
 */

#ifndef DEF_MENU
#define DEF_MENU

// Display a ASCII logo
void display_logo(WINDOW *window, char *logoToDisplay[], int x, int y, int size);

// Display classical vertical menus
void display_vertical_menu(WINDOW *menuWindow, int highlight, char *menuToDisplay[], int x, int y, int n_choices);

// Display the selection in actionChart
void display_menu_actionChart(WINDOW *actionChartWindow, int highlight, char *menu_actionChart[], int x, int y, int n_choices);

#endif