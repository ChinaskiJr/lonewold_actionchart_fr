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
#include "../headers/menu.h"

int main(int argc, char *argv[]) {

    //set UTF-8 THEN initiate ncurses
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    
    int             highlight = 1;
    int             choice = 0;
    int             wgetChoice = 0;
    int             goOn = 1;
    int             xBloc = COLS / 24;
    int             yBloc = LINES / 12;

    WINDOW          *titleWindow = NULL;
    WINDOW          *menuWindow = NULL;
    WINDOW          *actionChartWindow = NULL;

    WINDOW          *logoWindow = NULL;
    char            title[] = "Feuille d'aventure Loup Solitaire";
    char            credits[] = "Cr\u00E9\u00E9 par ChinaskiJr - Licence CC - v0.03";
    
    char *logo[] = {
         " _                        ____        _ _ _        _          ",
         "| |    ___  _   _ _ __   / ___|  ___ | (_) |_ __ _(_)_ __ ___ ",
         "| |   / _ \\| | | | '_ \\  \\___ \\ / _ \\| | | __/ _` | | '__/ _ \\",
         "| |__| (_) | |_| | |_) |  ___) | (_) | | | || (_| | | | |  __/",
         "|_____\\___/ \\__,_| .__/  |____/ \\___/|_|_|\\__\\__,_|_|_|  \\___|",
         "                 |_|                                          ",
    };
    int sizeLogoArray = sizeof(logo) / sizeof(char *);
    int xLogo = (COLS / 2) - (strlen(logo[0]) / 2);
    int yLogo = 7;

    char *choices[] = {
        "1 - Commencer une nouvelle feuille d'aventure",
        "2 - Charger une feuille d'aventure",
        "3 - Quitter le programme",
    };
    int numberChoices = sizeof(choices) / sizeof(char *);
    int xChoices = COLS / 2 - strlen(choices[0]) / 2;
    int yChoices = 20;
    

    // Always loop for dynamic size
    while(goOn) {
        // Actualize the COLS or LINES depedences variables 
        xBloc = COLS / 20;
        yBloc = LINES / 5;
        xLogo = (COLS / 2) - (strlen(logo[0]) / 2);
        xChoices = COLS / 2 - strlen(choices[0]) / 2;

        // Display line buffering
        noecho();
        cbreak();
        clear();

        // Set the windows
        titleWindow = subwin(stdscr, yBloc, COLS, 0, 0);
        box(titleWindow, ACS_VLINE, ACS_HLINE);
        menuWindow = subwin(stdscr, yBloc * 4, COLS, LINES / 5, 0);
        box(menuWindow, ACS_VLINE, ACS_HLINE);

        // Display the texts (no logo & no menu)
        wattron(titleWindow, A_BOLD);
        mvwprintw(titleWindow, xBloc / 2, COLS / 2 - strlen(title) / 2, title);
        wattroff(titleWindow, A_BOLD);
        wattron(menuWindow, A_DIM);
        mvwprintw(menuWindow, 3.8 * yBloc, COLS / 2 - strlen(credits) / 2, credits);
        wattroff(menuWindow, A_DIM);

        // display arrays
        refresh();
        display_logo(menuWindow, logo, xLogo, yLogo, sizeLogoArray);
        display_vertical_menu(menuWindow, highlight, choices, xChoices, yChoices, numberChoices);

        // Highlight selector for choices[]
        keypad(menuWindow, TRUE);
        wgetChoice = wgetch(menuWindow);
        switch(wgetChoice) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = numberChoices;
                else
                    highlight--;
            break;
            case KEY_DOWN:
                if(highlight == numberChoices)
                    highlight = 1;
                else
                    highlight++;
            break;
            case 10:
                choice = highlight;
            break;
        }
        display_vertical_menu(menuWindow, highlight, choices, xChoices, yChoices, numberChoices);
        refresh();

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

