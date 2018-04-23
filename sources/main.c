/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : deal the first menuWindow of the program
 *
 * TODO : Fix the border issue on the lines who contains strings 
 *
 */

#include <stdlib.h>
#include <string.h>
#include <ncursesw/curses.h>
#include <locale.h>
#include <wchar.h>

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

    WINDOW          *titleWindow = NULL;
    WINDOW          *menuWindow = NULL;

    char            title[] = "Bienvenue sur la feuille d'aventure Loup Solitaire";
    char            credits[] = "Cr\u00E9\u00E9 par ChinaskiJr - Licence CC - v0.01";

    //set UTF-8 THEN initiate ncurses
    setlocale(LC_ALL, "");
    initscr();
    
    // Display line buffering
    noecho();
    cbreak();
    clear();


    // always loop for dynamic size
    while(1) {
        // Set the windows
        titleWindow = subwin(stdscr, LINES / 9, COLS, 0, 0);
        box(titleWindow, ACS_VLINE, ACS_HLINE);
        menuWindow = subwin(stdscr, LINES - (LINES / 9), COLS, LINES / 9, 0);
        box(menuWindow, ACS_VLINE, ACS_HLINE);
        // Display the wchar_t
        mvwprintw(titleWindow, 1, COLS / 2 - strlen(title) / 2, title);
        mvwprintw(menuWindow, (LINES / 12) * 11, COLS / 2 - strlen(credits) / 2, credits);
        refresh();
        // Display the menu
        display_menu(menuWindow, highlight);

        keypad(menuWindow, TRUE);

        // Highlight slector
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
                    // TO DO
        }
        display_menu(menuWindow, highlight);
        if (choice == 3)
            break;
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