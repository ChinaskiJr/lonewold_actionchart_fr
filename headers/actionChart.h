/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : contains headers of actionchart.c
 *
 */

#ifndef DEF_ACTIONCHART
#define DEF_ACTIONCHART

typedef struct Personnage Personnage;
struct Personnage {
    int endurance;
    int combatSkill;
    int gold;
    int meal;

    char disciplines[10];
    char backpack[200];
    char specialItems[200];
};

typedef struct Backpack BackpackItem;
struct BackpackItem {
    int endurModBackpack;
    int combSkillModBackpack;
};

typedef struct SpecialItem SpecialItem;
struct SpecialItem {
    int endurModSpecIt;
    int CombSkillModSpecIt;
};
void actionChart(WINDOW *actionChartWindow);

#endif