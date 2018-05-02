/* actionChart.c 
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
#include <ctype.h>

#include "../headers/menu.h"
#include "../headers/constants.h"
#include "../headers/books.h"
#include "../headers/weapons.h"
#include "../headers/actionChart.h"
#include "../headers/disciplines.h"

void actionChart(WINDOW *actionChartWindow) {

    srand(time(NULL));

    int         goOn = 1;
    int 		choice = 20;
    int         wgetChoice = 0;
    int         i = 0;
    int         highlight = 0;
    int         book = T1;
    int         randomNumberTable = 0;
    int         weaponSkill = rand() % 7 + 1;

    // Booleans
    int         noWeapon = 0;
    int         hasWeaponSkill = 0;

    WINDOW      *titleWindow = NULL;
    WINDOW      *kaiDisciplinesWindow = NULL;
    WINDOW      *countEndurantWindow = NULL;
    WINDOW      *combatSkillWindow = NULL;
    WINDOW      *backpackWindow = NULL;
    WINDOW      *goldWindow = NULL;
    WINDOW      *mealWindow = NULL;
    WINDOW      *weaponsWindow = NULL;
    WINDOW      *specialItemsWindow = NULL;

    WINDOW      *kaiDisciplineWindows[9] = {0};
    WINDOW      *backpackWindows[7] = {0};
    WINDOW      *weaponWindows[1] = {0};
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
        "Armes",
        "Objets sp\u00E9ciaux",
    };
    int numberChoices = sizeof(actionChartMenu) / sizeof(char *);

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
    }; 

    char *disciplinesKai[] = {
        "Camouflage",
        "La chasse",
        "Sixi\u00E8me sens",
        "Orientation",
        "Gu\u00E9rison",
        "Ma\u00EEtrise des armes :",
        "Bouclier psychique",
        "Puissance psychique",
        "Communication animale",
        "Ma\u00EEtrise psychique de la mati\u00E8re",
        "Aucune",
        "Bloqu\u00E9",
    };
    char weaponSkillType[256] = "Ma\u00EEtrise des armes : ";
    strcat (weaponSkillType, weapons[weaponSkill]);
    strcat (weaponSkillType, " +2PH");
    disciplinesKai[WEAPONSSKILL] = weaponSkillType;

    char *books[] = {
        "Tome 1 - Les ma\u00EEtre des t\u00E9n\u00E8bres",
        "Tome 2 - La travers\u00E9e infernale",
        "Tome 3 - Les grottes de Kalte",
        "Tome 4 - Le gouffer maudit",
        "Tome 5 - Le tyran du d\u00E9sert",
    };

    // Initialisation of the character
    Personnage player;
    player.endurance = 20 + rand() % 10 ;
    player.currentEndurance = player.endurance;
    player.combatSkill = 10 + rand() %  10;
    player.currentCombatSkill = player.combatSkill;
    player.gold = rand() % 10;
    player.meal = 0;
    player.weapon1 = AXE;
    player.weapon2 = 0;
    for (i = 0 ; i < 5 ; i++) {
        player.disciplines[i] = NODISC;
    }
    for (i = 5 ; i < 10 ; i++) {
        player.disciplines[i] = NOTAVAILABLE;
    }

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
        int         ySizeEndurance = 1.75 * yBloc;
        int         xSizeCombatSkill = 3 * xBloc;
        int         ySizeCombatSkill = 1.75 * yBloc;
        int         xSizeBackpack = 3 * xBloc;
        int         ySizeBackpack = 8 * yBloc;
        int         xSizeGold = 3 * xBloc;
        int         ySizeGold = 1.75 * yBloc;
        int         xSizeMeal = 3 * xBloc;
        int         ySizeMeal = 1.75 * yBloc;
        int         xSizeWeapons = 3 * xBloc;
        int         ySizeWeapons = 2.5 * yBloc;
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
        int         xPositionWeapons = xBloc * 13;
        int         yPositionWeapons = yBloc * 8;
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
        float       xTitleWeapons = (xSizeWeapons / 2) - (strlen(actionChartMenu[WEAPONS]) / 2) + xPositionWeapons;
        float       yTitleWeapons = yPositionWeapons - 0.25;
        float       xTitleSpecialItems = (xSizeSpecialItems / 2) - (strlen(actionChartMenu[SPECITS]) / 2) + xPositionSpecialItems + 1;
        float       yTitleSpecialItems = yPositionSpecialItems - 0.25;

        int         xPositionRandomTable = xBloc * 13.5;
        int         yPositionRandomTable = yBloc * 10.5;	

        // Applies malus/bonus
        if (!noWeapon) {
	        if (player.weapon1 == NONE && player.weapon2 == NONE) {
	        	player.currentCombatSkill = player.currentCombatSkill - 4;
	        	noWeapon = 1;
	        }
    	}
    	if (noWeapon) {
    		if (!player.weapon1 == NONE || !player.weapon2 == NONE) {
    			player.currentCombatSkill = player.currentCombatSkill + 4;
    			noWeapon = 0;
    		}
    	}
        if (!hasWeaponSkill) {
            if (player.weapon1 == weaponSkill || player.weapon2 == weaponSkill) {
                player.currentCombatSkill = player.currentCombatSkill + 2;
                hasWeaponSkill = 1;
            }
        }
        if (hasWeaponSkill) {
            if (player.weapon1 != weaponSkill && player.weapon2 != weaponSkill) {
                player.currentCombatSkill = player.currentCombatSkill - 2;
                hasWeaponSkill = 0;
            }
        }
       
        // Display line buffering
        noecho();
        cbreak();
        clear();
        // Main windowweaponsWindow
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

        weaponsWindow = subwin(actionChartWindow, ySizeWeapons, xSizeWeapons, yPositionWeapons, xPositionWeapons);
        for (i = 0 ; i < 2 ; i ++) {
            weaponWindows[i] = subwin(weaponsWindow, yBloc, xSizeWeapons, yPositionWeapons + (yBloc * i), xPositionWeapons);
            box(weaponWindows[i], ACS_VLINE, ACS_HLINE);
        }
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleWeapons, xTitleWeapons, WEAPONS);

        specialItemsWindow = subwin(actionChartWindow, ySizeSpecialItems, xSizeSpecialItems, yPositionSpecialItems, xPositionSpecialItems);
        box(specialItemsWindow, ACS_VLINE, ACS_HLINE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleSpecialItems, xTitleSpecialItems, SPECITS);

        wattroff(actionChartWindow, A_BOLD);

        // Display player's attributes
        mvwprintw(countEndurantWindow, ySizeEndurance / 2, xSizeEndurance / 2, "%d", player.currentEndurance);
        mvwprintw(combatSkillWindow, ySizeCombatSkill / 2, xSizeCombatSkill / 2, "%d", player.currentCombatSkill);
        mvwprintw(goldWindow, ySizeGold / 2, xSizeGold / 2, "%d", player.gold);
        mvwprintw(mealWindow, ySizeMeal / 2, xSizeMeal / 2, "%d", player.meal);
        for (i = 0 ; i < 10 ; i++) {
            mvwprintw(kaiDisciplineWindows[i], ySizeDisciplines / 20, xSizeDisciplines / 8, disciplinesKai[player.disciplines[i]]);
        }
        mvwprintw(weaponWindows[0], ySizeWeapons / 4, xSizeWeapons / 8, weapons[player.weapon1]);
        mvwprintw(weaponWindows[1], ySizeWeapons / 4, xSizeWeapons / 8, weapons[player.weapon2]);

        // Display random number table
        mvwprintw(actionChartWindow, yPositionRandomTable, xPositionRandomTable, randomTable);
        wattron(actionChartWindow, A_BOLD);
        mvwprintw(actionChartWindow, yPositionRandomTable + 1, xPositionRandomTable + strlen(randomTable) / 2 - 1, "%d", randomNumberTable);
        wattroff(actionChartWindow, A_BOLD);

        // Display control list
        char statsUpandDown [] = "j/k : -/+ endurance\tl : réinitialiser l'endurance (conserve bonus/malus)\tu/i : -/+ habileté\to : réinitialiser l'habileté (conserve bonus/malus)";
        char options[] = "Options :\tq : quitter\t s : sauvegarder\t l : charger\t b : s\u00E9lectionner le livre\td : table de hasard\tf : combat";
        // The - 12 on ySize is for the 6 \t in options[]
        mvwprintw(actionChartWindow, yBloc * 13, (COLS / 2) - (strlen(statsUpandDown) / 2), statsUpandDown);
        mvwprintw(actionChartWindow, yBloc * 14, (COLS / 2) - (strlen(options) / 2) - 12, options);

        refresh();
        keypad(actionChartWindow, TRUE);
        wgetChoice = wgetch(actionChartWindow);
        switch (toupper(wgetChoice)) {
            // First, the navigation
            case KEY_UP:
                if (highlight == BACKPACK) {
                    highlight = PE;
                } else if (highlight == GOLD) {
                    highlight = CS;
                } else if (highlight == MEAL) {
                    highlight = GOLD;
                } else if (highlight == WEAPONS) {
                	highlight = MEAL;
                }
            break;

            case KEY_DOWN:
                if (highlight == PE) {
                    highlight = BACKPACK;
                } else if (highlight == CS) {
                    highlight = GOLD;
                } else if (highlight == GOLD) {
                    highlight = MEAL;
                } else if (highlight == MEAL) {
                	highlight = WEAPONS;
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
                } else if (highlight == WEAPONS) {
                	highlight = BACKPACK;
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
                    highlight = SPECITS;
                } else if (highlight == MEAL) {
                    highlight = SPECITS;
                } else if (highlight == WEAPONS) {
                	highlight = SPECITS;
                }
            break;
                
            //Then the options;
            case 'Q':
                goOn = 0;
            break;
            case 'B' : 
                book = bookChoice(actionChartWindow);
            break;
            case 'D' :
                randomNumberTable = rand() % 10;   
            break;
            case 'J' : 
            	player.currentEndurance--;
            break;
            case 'K' :
            	player.currentEndurance++;
            break;
            case 'L' : 
            	player.currentEndurance = player.endurance; 
            case 'U' : 
            	player.currentCombatSkill--;
            break;
            case 'I' : 
            	player.currentCombatSkill++;
            break;
            case 'O' : 
            	player.currentCombatSkill = player.combatSkill;
                hasWeaponSkill = 0;
                noWeapon = 0;
            break;
            case 10:
            	choice = highlight;
        }

        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleDisciplines, xTitleDisciplines, DISC);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleEndurance, xTitleEndurance, PE);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleCombatSkill, xTitleCombatSkill, CS);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleBackpack, xTitleBackpack, BACKPACK);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleGold, xTitleGold, GOLD);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleMeal, xTitleMeal, MEAL);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleWeapons, xTitleWeapons, WEAPONS);
        display_menu_actionChart(actionChartWindow, highlight, actionChartMenu, yTitleSpecialItems, xTitleSpecialItems, SPECITS);
        refresh();

        switch (choice) {
        	case WEAPONS:
        		weaponNumberChoice(actionChartWindow, &player.weapon1, &player.weapon2);
        		choice = -1;
        	break;
            case DISC:
                disciplineNumberChoice(actionChartWindow, player.disciplines, book);
                choice = -1;
            break;
        }
    }
    refresh();
    delwin(titleWindow);
    delwin(actionChartWindow);
}