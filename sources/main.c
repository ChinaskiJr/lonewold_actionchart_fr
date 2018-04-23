/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : deal the main menu
 *
 */

#include <stdlib.h>
#include <string.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <wchar.h>

#include "../headers/actionChart.h"

char         *choices[] = {
    "Commencer une nouvelle feuille d'aventure",
    "Charger une feuille d'aventure",
    "Quitter le programme",
};

void display_menu(WINDOW *menuWindow, int highlight);

int main(void) {

    int             n_choices = sizeof(choices) / sizeof (char *);
    int             highlight = 1;
    int             choice = 0;
    int             wgetChoice = 0;
    int             goOn = 1;

    WINDOW          *titleWindow = NULL;
    WINDOW          *menuWindow = NULL;
    WINDOW          *actionChartWindow = NULL;

    char            title[] = "Feuille d'aventure Loup Solitaire";
    char            credits[] = "Cr\u00E9\u00E9 par ChinaskiJr - Licence CC - v0.01";

    //set UTF-8 THEN initiate ncurses
    setlocale(LC_ALL, "");
    initscr();
    

    // always loop for dynamic size
    while(goOn) {
        // Display line buffering
        noecho();
        cbreak();
        clear();
        // Set the windows
        titleWindow = subwin(stdscr, LINES / 9, COLS, 0, 0);
        box(titleWindow, ACS_VLINE, ACS_HLINE);
        menuWindow = subwin(stdscr, LINES - (LINES / 9), COLS, LINES / 9, 0);
        box(menuWindow, ACS_VLINE, ACS_HLINE);
        // Display the wchar_t
        wattron(titleWindow, A_BOLD);
        mvwprintw(titleWindow, 1, COLS / 2 - strlen(title) / 2, title);
        wattroff(titleWindow, A_BOLD);
        wattron(menuWindow, A_DIM);
        mvwprintw(menuWindow, LINES - (LINES / 6), COLS / 2 - strlen(credits) / 2, credits);
        wattroff(menuWindow, A_DIM);
        refresh();
        // Display the menu
        display_menu(menuWindow, highlight);

        keypad(menuWindow, TRUE);

        // Highlight selector
        wgetChoice = wgetch(menuWindow);
        switch(wgetChoice) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    highlight--;
            break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else
                    highlight++;
            break;
            case 10:
                choice = highlight;
            break;
        }
        display_menu(menuWindow, highlight);

        // Lead the way
        if (choice == 3) {
            goOn = 0;
        }
            
        //else if (choice == 2)
            // GO TO load
        else if (choice == 1) 
            actionChart(actionChartWindow);
            choice = 0;
    }

    delwin(titleWindow);
    delwin(menuWindow);
    endwin();

    return 0;
}

void display_menu(WINDOW *menuWindow, int highlight)
{
    int x, y;    
    int i = 0;
    y = 2;
    int n_choices = sizeof(choices) / sizeof (char *);
    box(menuWindow, 0, 0);
    for(i = 0; i < n_choices; ++i) {
       x = COLS / 2 - strlen(choices[i]) / 2;
       if(highlight == i + 1) {
            wattron(menuWindow, A_REVERSE); 
            mvwprintw(menuWindow, y, x, "%s", choices[i]);
            wattroff(menuWindow, A_REVERSE);
        }
        else
            mvwprintw(menuWindow, y, x, "%s", choices[i]);
        y += 2;
    }
    wrefresh(menuWindow);
}