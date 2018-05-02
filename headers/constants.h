/* constats.h
 * ------
 * By ChinaskiJr - April 2018
 * 
 * Role : define constants for the whole program
 *
 */

#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS
    // actionchart
    enum {DISC, PE, CS, BACKPACK, GOLD, MEAL, WEAPONS, SPECITS};
    // books
    enum {T1, T2, T3, T4, T5};
    // weapons
    enum {
    	NONE, 
    	DAGGER, 
    	SPEAR, 
    	SHORTSWORD, 
    	WARHAMMER, 
    	AXE, 
    	SWORD, 
    	QUARTERSTAFF, 
    	BROADSWORD};
    // disciplines
    enum {
    	CAMOUFLAGE, 
    	HUNTING, 
    	SIXTHSENSE, 
    	TRACKING, 
    	HEALING, 
    	WEAPONSSKILL, 
    	MINDSHIELD, 
    	MINDBLAST, 
    	ANIMALKINSHIP, 
    	MINDOVERMATTER,
        NODISC,
        NOTAVAILABLE,
    };
#endif