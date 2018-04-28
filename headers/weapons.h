/* main.c 
 * ------
 * By ChinaskiJr - April 2018
 * 
 * role : contains weapons.c's headers
 *
 */

#ifndef DEF_WEAPONS
#define DEF_WEAPONS

// chose between the two weapons
int weaponNumberChoice(WINDOW *numberWeaponChoiceWindow, int *weapon1, int *weapon2);
// chose your weapon
int weaponChoice(WINDOW *weaponsChoiceWindow, int weaponNumber);

#endif