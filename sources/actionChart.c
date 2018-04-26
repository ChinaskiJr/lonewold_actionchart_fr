/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : print the action chart
 *
 */

#include <stdlib.h>
#include <string.h>
#include <ncursesw/curses.h>
#include <wchar.h>
#include <time.h>


#include "../headers/menu.h"
#include "../headers/constants.h"
#include "../headers/books.h"

void actionChart(WINDOW *actionChartWindow) {

    srand(time(NULL));

    int         goOn = 1;
    int         wgetChoice = 0;
    int         i = 0;
    int         highlight = 0;
    int         book = 0;
    int         randomNumberTable = 0;

    WINDOW      *titleWindow = NULL;
    WINDOW      *kaiDisciplinesWindow = NULL;
    WINDOW      *countEndurantWindow = NULL;
    WINDOW      *combatSkillWindow = NULL;
    WINDOW      *backpackWindow = NULL;
    WINDOW      *goldWindow = NULL;
    WINDOW      *mealWindow = NULL;
    WINDOW      *specialItemsWindow = NULL;

    WINDOW      *kaiDisciplineWindows[9] = {0};
    WINDOW      *backpackWindows[7] = {0};
    WINDOW      *specialItemsWindows[1] = {0};

    WINDOW      *bookWindow = NULL;

    char title[] = "Feuille d'Aventure";
    char randomTable[] = "Table de hasard : ";

    char *actionChartMenu[] = {
        "Disciplines Ka\u00EF",
        "Points d'endurance",
        "Points d'Habilet\u00E9",
        "Sac \u00E0 Dos",
        "Couronnes",
        "Repas",
        "Objets sp\u00E9ciaux",
    };
    int numberChoices = sizeof(actionChartMenu) / sizeof(char *);

    char *books[] = {
        "Tome 1 - Les ma\u00EEtre des t\u00E9n\u00E8bres",
        "Tome 2 - La travers\u00E9e infernale",
        "Tome 3 - Les grottes de Kalte",
        "tome 4 - Le gouffre maudit",
        "tome 5 - Le tyran du d\u00E8sert",
    };

    while (goOn) {
        refresh();
        // define blocs
        int         xBloc = COLS / 24;
        int         yBloc = LINES / 12;

        // Windows size
        int         xSizeTitle = 12 * xBloc;
        int         ySizeTitle = yBloc / 2;
        int         xSizeDisciplines = 6 * xBloc;
        int         ySizeDisciplines = 10 * yBloc;
        int         xSizeEndurance = 3 * xBloc;
        int         ySizeEndurance = 1.5 * yBloc;
        int         xSizeCombatSkill = 3 * xBloc;
        int         ySizeCombatSkill = 1.5 * yBloc;
        int         xSizeBackpack = 3 * xBloc;
        int         ySizeBackpack = 8 * yBloc;
        int         xSizeGold = 3 * xBloc;
        int         ySizeGold = 1.5 * yBloc;
        int         xSizeMeal = 3 * xBloc;
        int         ySizeMeal = 1.5 * yBloc;
        int         xSizeSpecialItems = 8 * xBloc;
        int         ySizeSpecialItems = 10 * yBloc;

        // Windows position
        int         xPositionDisciplines = xBloc * 2;
        int         yPositionDisciplines = yBloc * 2;
        int         xPositionEndurance = xBloc * 9;
        int         yPositionEndurance = yBloc * 2;
        int         xPositionCombatSkill = xBloc * 13;
        int         yPositionCombatSkill = yBloc * 2;
        int         xPositionBackpack = xBloc * 9;
        int         yPositionBackpack = yBloc * 4;
        int         xPositionGold = xBloc * 13;
        int         yPositionGold = yBloc * 4;
        int         xPositionMeal = xBloc * 13;
        int         yPositionMeal = yBloc * 6;
        int         xPositionSpecialItems = xBloc * 17;
        int         yPositionSpecialItems = yBloc * 2;


        // Titles position (+1 because of strlen that count \u for 2)
        float       xTitleDisciplines = (xSizeDisciplines / 2) - (strlen(actionChartMenu[DISC]) / 2) + xPositionDisciplines + 1;
        float       yTitleDisciplines = yPositionDisciplines - 0.25;
        float       xTitleEndurance = (xSizeEndurance / 2) - (strlen(actionChartMenu[PE]) / 2) + xPositionEndurance;
        float       yTitleEndurance = yPositionEndurance - 0.25;
        float       xTitleCombatSkill = (xSizeCombatSkill / 2) - (strlen(actionChartMenu[CS]) / 2) + xPositionCombatSkill + 1;
        float       yTitleCombatSkill = yPositionCombatSkill - 0.25;
        float       xTitleBackpack = (xSizeBackpack / 2) - (strlen(actionChartMenu[BACKPACK]) / 2) + xPositionBackpack + 1;
        float       yTitleBackpack = yPositionBackpack - 0.25;
        float       xTitleGold = (xSizeGold / 2) - (strlen(actionChartMenu[GOLD]) / 2) + xPositionGold;
        float       yTitleGold = yPositionGold - 0.25;
        float       xTitleMeal = (xSizeMeal / 2) - (strlen(actionChartMenu[MEAL]) / 2) + xPositionMeal;
        float       yTitleMeal = yPositionMeal - 0.25;
        float       xTitleSpecialItems = (xSizeSpecialItems / 2) - (strlen(actionChartMenu[SPECITS]) / 2) + xPositionSpecialItems + 1;
        float       yTitleSpecialItems = yPositionSpecialItems - 0.25;

        int         xPositionRandomTable = xBloc * 13.5;
        int         yPositionRandomTable = yBloc * 8;

        // Display line buffering
        noecho();
        cbreak();
        clear();
        // Main window
        actionChartWindow = subwin(stdscr, LINES, COLS, 0, 0);
        box(actionChartWindow, ACS_VLINE, ACS_HLINE);
        // Title window
        titleWindow = subwin(actionChartWindow, ySizeTitle, xSizeTitle, yBloc * 0.75, COLS / 2 - (strlen(title) / 2));
        wattron(titleWindow, A_UNDERLINE);
        mvwprintw(titleWindow, 0, 0, title);
        wattroff(titleWindow, A_UNDERLINE);

        //TODO : book = 
        wattron(titleWindow, A_DIM);
        mvwprintw(titleWindow, 0, 7 * xBloc, books[book]);
        wattroff(titleWindow, A_DIM);

        //Display all other windows
        wattron(actionChartWindow, A_BOLD);
        kaiDisciplinesWindow = subwin(actionChartWindow, ySizeDisciplines, xSizeDisciplines, yPositionDisciplines, xPositionDisciplines);
        for (i = 0 ; i < 10 ; i++) {
            kaiDisciplineWindows[i] = subwin(kaiDisciplinesWindow, yBloc, xSizeDisciplines, yPositionDisciplines + (yBloc * i), xPositionDisciplines);
            box(kaiDisciplineWindows[i], ACS_VLINE, ACS_HLINE);
        }
        // UNCOMMENT NEXT LINE FOR GRAPHIC DESIGN : BORDERS OF KAI DISCIPLINES
        //box(kaiDisciplinesWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleDisciplines, xTitleDisciplines, DISC);

        countEndurantWindow = subwin(actionChartWindow, ySizeEndurance, xSizeEndurance, yPositionEndurance, xPositionEndurance);
        box(countEndurantWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleEndurance, xTitleEndurance, PE);

        combatSkillWindow = subwin(actionChartWindow, ySizeCombatSkill, xSizeCombatSkill, yPositionCombatSkill, xPositionCombatSkill);
        box(combatSkillWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleCombatSkill, xTitleCombatSkill, CS);

        backpackWindow = subwin(actionChartWindow, ySizeBackpack, xSizeBackpack, yPositionBackpack, xPositionBackpack);
        for (i = 0 ; i < 8 ; i++) {
            backpackWindows[i] = subwin(backpackWindow, yBloc, xSizeBackpack, yPositionBackpack + (yBloc * i), xPositionBackpack);
            box(backpackWindows[i], ACS_VLINE, ACS_HLINE);
        }
        // UNCOMMENT NEXT LINE FOR GRAPHIC DESIGN : BORDERS OF BACKPACK
        //box(backpackWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleBackpack, xTitleBackpack, BACKPACK);

        goldWindow = subwin(actionChartWindow, ySizeGold, xSizeGold, yPositionGold, xPositionGold);
        box(goldWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleGold, xTitleGold, GOLD);

        mealWindow = subwin(actionChartWindow, ySizeMeal, xSizeMeal, yPositionMeal, xPositionMeal);
        box(mealWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleMeal, xTitleMeal, MEAL);

        specialItemsWindow = subwin(actionChartWindow, ySizeSpecialItems, xSizeSpecialItems, yPositionSpecialItems, xPositionSpecialItems);
        box(specialItemsWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleSpecialItems, xTitleSpecialItems, SPECITS);

        wattroff(actionChartWindow, A_BOLD);

        // Display random number table
        mvwprintw(actionChartWindow, yPositionRandomTable, xPositionRandomTable, randomTable);
        mvwprintw(actionChartWindow, yPositionRandomTable + 1, xPositionRandomTable + strlen(randomTable) / 2 - 1, "%d", randomNumberTable);

        char options[] = "Options :\t q : quitter\t s : sauvegarder\t l : charger\t b : s\u00E9lectionner le livre\td : table de hasard\tf : combat";
        // The - 12 on ySize is for the 6 \t in options[]
        mvwprintw(actionChartWindow, yBloc * 13, (COLS / 2) - (strlen(options) / 2) - 12, options);

        refresh();
        keypad(actionChartWindow, TRUE);
        wgetChoice = wgetch(actionChartWindow);
        switch (wgetChoice) {
            // First, the navigation
            case KEY_UP:
                if (highlight == BACKPACK) {
                    highlight = PE;
                } else if (highlight == GOLD) {
                    highlight = CS;
                } else if (highlight == MEAL) {
                    highlight = GOLD;
                }
            break;

            case KEY_DOWN:
                if (highlight == PE) {
                    highlight = BACKPACK;
                } else if (highlight == CS) {
                    highlight = GOLD;
                } else if (highlight == GOLD) {
                    highlight = MEAL;
                }
            break;

            case KEY_LEFT:
                if (highlight == SPECITS) {
                    highlight = CS;
                } else if (highlight == CS) {
                    highlight = PE;
                } else if (highlight == PE) {
                    highlight = DISC;
                } else if (highlight == GOLD) {
                    highlight = BACKPACK;
                } else if (highlight == MEAL) {
                    highlight = BACKPACK;
                } else if (highlight == BACKPACK) {
                    highlight = DISC;
                }
            break;

            case KEY_RIGHT:
                if (highlight == DISC) {
                    highlight = PE;
                } else if (highlight == PE) {
                    highlight = CS;
                } else if (highlight == CS) {
                    highlight = SPECITS;
                } else if (highlight == BACKPACK) {
                    highlight = GOLD;
                } else if (highlight == GOLD) {
                    highlight == SPECITS;
                } else if (highlight == MEAL) {
                    highlight = SPECITS;
                }
            break;

            display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleDisciplines, xTitleDisciplines, DISC);

                
            //Then the options
            case 'q':
                goOn = 0;
            break;
            case 'Q':
                goOn = 0;
            break;
            case 'b' : 
                book = bookChoice(actionChartWindow);
            break;
            case 'B' : 
                book = bookChoice(actionChartWindow);
            break;
            case 'd' :
                randomNumberTable = rand() % 10;
            break;  
            case 'D' :
                randomNumberTable = rand() % 10;      
        }
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleEndurance, xTitleEndurance, PE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleCombatSkill, xTitleCombatSkill, CS);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleBackpack, xTitleBackpack, BACKPACK);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleGold, xTitleGold, GOLD);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleMeal, xTitleMeal, MEAL);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleSpecialItems, xTitleSpecialItems, SPECITS);
        refresh();
    }
    refresh();
    delwin(titleWindow);
    delwin(actionChartWindow);
}