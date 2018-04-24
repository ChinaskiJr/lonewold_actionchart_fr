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

#include "../headers/menu.h"
#include "../headers/constants.h"

void actionChart(WINDOW *actionChartWindow) {

    int         goOn = 1;
    int         wgetChoice = 0;
    int         i = 0;
    int         highlight = 1;

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

    char *actionChartMenu[] = {
        "Disciplines Ka\u00EF",
        "Points d'endurance",
        "Points d'Habilet\u00E9",
        "Sac \u00E0 Dos",
        "Pi\u00E8ces d'or",
        "Repas",
        "Objets sp\u00E9ciaux",
    };


    while (goOn) {

        refresh();

        // blocs places
        int         xBloc = COLS / 20;
        int         yBloc = LINES / 11;
        int         xSizeTitle = 6 * xBloc;
        int         ySizeTitle = yBloc / 2;
        int         xSizeDisciplines = 5 * xBloc;
        int         ySizeDisciplines = 10 * yBloc;
        int         xSizeEndurance = 2 * xBloc;
        int         ySizeEndurance = 1 * yBloc;
        int         xSizeCombatSkill = 2 * xBloc;
        int         ySizeCombatSkill = 1 * yBloc;
        int         xSizeBackpack = 3 * xBloc;
        int         ySizeBackpack = 8 * yBloc;
        int         xSizeGold = 2 * xBloc;
        int         ySizeGold = 1 * yBloc;
        int         xSizeMeal = 2 * xBloc;
        int         ySizeMeal = 1 * yBloc;
        int         xSizeSpecialItems = 4 * xBloc;
        int         ySizeSpecialItems = 10 * yBloc;

        //titles places
        int         xTitleDisciplines = xBloc * 3.75;
        int         yTitleDisciplines = yBloc * 1.75;
        int         xTitleEndurance = xBloc * 9.4;
        int         yTitleEndurance = yBloc * 1.75;
        int         xTitleCombatSkill = xBloc * 12.9;
        int         yTitleCombatSkill = yBloc * 1.75;
        int         xTitleBackpack = xBloc * 9.9;
        int         yTitleBackpack = yBloc * 3.75;
        int         xTitleGold = xBloc * 13.3;
        int         yTitleGold = yBloc * 3.75;
        int         xTitleMeal =xBloc * 13.7;
        int         yTitleMeal = yBloc * 5.75;
        int         xTitleSpecialItems = xBloc * 17;
        int         yTitleSpecialItems = yBloc * 1.75;

        // Display line buffering
        noecho();
        cbreak();
        clear();

        actionChartWindow = subwin(stdscr, LINES, COLS, 0, 0);
        box(actionChartWindow, ACS_VLINE, ACS_HLINE);

        // Title
        char title[] = "Feuille d'Aventure";
        titleWindow = subwin(actionChartWindow, ySizeTitle, xSizeTitle, yBloc * 0.75, COLS / 2 - (strlen(title) / 2));
        wattron(titleWindow, A_UNDERLINE);
        mvwprintw(titleWindow, 0, 0, title);
        wattroff(titleWindow, A_UNDERLINE);

        //Windows and sub-windows
        wattron(actionChartWindow, A_BOLD);
        kaiDisciplinesWindow = subwin(actionChartWindow, ySizeDisciplines, xSizeDisciplines, yBloc * 2, xBloc * 2);
        for (i = 0 ; i < 10 ; i++) {
            kaiDisciplineWindows[i] = subwin(kaiDisciplinesWindow, yBloc, xSizeDisciplines, yBloc * 2 + (yBloc * i), xBloc * 2);
            box(kaiDisciplineWindows[i], ACS_VLINE, ACS_HLINE);
        }
        // UNCOMMENT NEXT LINE FOR GRAPHIC DESIGN : BORDERS OF KAI DISCIPLINES
        //box(kaiDisciplinesWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleDisciplines, xTitleDisciplines, DISC);

        countEndurantWindow = subwin(actionChartWindow, ySizeEndurance, xSizeEndurance, yBloc * 2, xBloc * 9.5);
        box(countEndurantWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleEndurance, xTitleEndurance, PE);

        combatSkillWindow = subwin(actionChartWindow, ySizeCombatSkill, xSizeCombatSkill, yBloc * 2, xBloc * 13);
        box(combatSkillWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleCombatSkill, xTitleCombatSkill, CS);

        backpackWindow = subwin(actionChartWindow, ySizeBackpack, xSizeBackpack, yBloc * 4, xBloc * 9);
        for (i = 0 ; i < 8 ; i++) {
            backpackWindows[i] = subwin(backpackWindow, yBloc, xSizeBackpack, yBloc * 4 + (yBloc * i), xBloc * 9);
            box(backpackWindows[i], ACS_VLINE, ACS_HLINE);
        }
        // UNCOMMENT NEXT LINE FOR GRAPHIC DESIGN : BORDERS OF BACKPACK
        //box(backpackWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleBackpack, xTitleBackpack, BACKPACK);

        goldWindow = subwin(actionChartWindow, ySizeGold, xSizeGold, yBloc * 4, xBloc * 13);
        box(goldWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleGold, xTitleGold, GOLD);

        mealWindow = subwin(actionChartWindow, ySizeMeal, xSizeMeal, yBloc * 6, xBloc * 13);
        box(mealWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleMeal, xTitleMeal, MEAL);

        specialItemsWindow = subwin(actionChartWindow, ySizeSpecialItems, xSizeSpecialItems, yBloc * 2, xBloc * 16);
        box(specialItemsWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleSpecialItems, xTitleSpecialItems, SPECITS);

        wattroff(actionChartWindow, A_BOLD);

        mvwprintw(actionChartWindow, yBloc * 13, xBloc * 2, "Options :\t q : quitter\t s : sauvegarder\t l : charger\t b : s\u00E9lectionner le livre\td : table de hasard\tf : combat");

        refresh();
        keypad(actionChartWindow, TRUE);

        wgetChoice = wgetch(actionChartWindow);
        switch (wgetChoice) {
            case 113:
                goOn = 0;
            break;
        }
    }
    refresh();
    delwin(titleWindow);
    delwin(actionChartWindow);
}