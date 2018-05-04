/* disciplines.h
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : contains disciplines.c headers
 *
 */

#ifndef DEF_DISCIPLINES
#define DEF_DISCIPLINES

int disciplineNumberChoice(
	WINDOW* disciplineNumberChoiceWindow, 
	int *disciplines,
    int *hasDisciplines,
    int book
	);

int choseKaiDisciplines(WINDOW* choseDisciplinesWindow, int *hasDisciplines);

#endif