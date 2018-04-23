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

void actionChart(WINDOW *actionChartWindow) {

    int         goOn = 1;
    int         wgetChoice = 0;
    int         i;

    WINDOW      *titleWindow = NULL;
    WINDOW      *kaiDisciplinesWindow = NULL;
    WINDOW      *countEndurantWindow = NULL;
    WINDOW      *combatSkillWindow = NULL;
    WINDOW      *backpackWindow = NULL;
    WINDOW      *goldWindow = NULL;
    WINDOW      *mealWindow = NULL;
    WINDOW      *specialItemsWindow = NULL;

    WINDOW     *kaiDisciplineWindows[9] = {0};
    while (goOn) {

    int         xBloc = COLS / 20;
    int         yBloc = LINES / 11;
    int         xSizeTitle = 6 * xBloc;
    int         ySizeTitle = yBloc / 2;
    int         xSizeDisciplines = 5 * xBloc;
    int         ySizeDisciplines = 8 * yBloc;
    int         xSizeEndurance = 2 * xBloc;
    int         ySizeEndurance = 1 * yBloc;
    int         xSizeCombatSkill = 2 * xBloc;
    int         ySizeCombatSkill = 1 * yBloc;
    int         xSizeBackpack = 3 * xBloc;
    int         ySizeBackpack = 5 * yBloc;
    int         xSizeGold = 2 * xBloc;
    int         ySizeGold = 1 * yBloc;
    int         xSizeMeal = 2 * xBloc;
    int         ySizeMeal = 1 * yBloc;
    int         xSizeSpecialItems = 4 * xBloc;
    int         ySizeSpecialItems = 8 * yBloc;


        // Display line buffering
        noecho();
        cbreak();
        clear();

        refresh;

        actionChartWindow = subwin(stdscr, LINES, COLS, 0, 0);
        box(actionChartWindow, ACS_VLINE, ACS_HLINE);

        // Title
        char title[] = "Feuille d'Aventure";
        titleWindow = subwin(actionChartWindow, ySizeTitle, xSizeTitle, yBloc * 0.75, COLS / 2 - (strlen(title) / 2));
        wattron(titleWindow, A_UNDERLINE);
        mvwprintw(titleWindow, 0, 0, title);
        wattroff(titleWindow, A_UNDERLINE);



        // Kai Disciplines Window and sub-windows
        wattron(actionChartWindow, A_BOLD);
        kaiDisciplinesWindow = subwin(actionChartWindow, ySizeDisciplines, xSizeDisciplines, yBloc * 2, xBloc * 2);
        box(kaiDisciplinesWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 1.75, xBloc * 3.75, "Disciplines Ka\u00EF");

        countEndurantWindow = subwin(actionChartWindow, ySizeEndurance, xSizeEndurance, yBloc * 2, xBloc * 9.5);
        box(countEndurantWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 1.75, xBloc * 9.4, "Points d'endurance");

        combatSkillWindow = subwin(actionChartWindow, ySizeCombatSkill, xSizeCombatSkill, yBloc * 2, xBloc * 13);
        box(combatSkillWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 1.75, xBloc * 12.9, "Points d'Habileté");

        backpackWindow = subwin(actionChartWindow, ySizeBackpack, xSizeBackpack, yBloc * 4, xBloc * 9);
        box(backpackWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 3.75, xBloc * 9.9, "Sac \u00E0 Dos");

        goldWindow = subwin(actionChartWindow, ySizeGold, xSizeGold, yBloc * 4, xBloc * 13);
        box(goldWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 3.75, xBloc * 13.3, "Pi\u00E8ces d'or");

        mealWindow = subwin(actionChartWindow, ySizeMeal, xSizeMeal, yBloc * 6, xBloc * 13);
        box(mealWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 5.75, xBloc * 13.7, "Repas");

        specialItemsWindow = subwin(actionChartWindow, ySizeSpecialItems, xSizeSpecialItems, yBloc * 2, xBloc * 16);
        box(specialItemsWindow, ACS_VLINE, ACS_HLINE);
        mvwprintw(actionChartWindow, yBloc * 1.75, xBloc * 17, "Objets sp\u00E9ciaux");


        wattroff(actionChartWindow, A_BOLD);


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