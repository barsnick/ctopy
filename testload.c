/*
 * This is a test load for ctopy, the C to Python translator.
 * It is syntactically valid C, parts taken from the source for 
 * Super Star Trek and Galaxis.
 *
 * This boxed comment at the beginning should turn into a series of
 * Python comments with # at the left margin.  Both comment delimiters
 * should turn into # followed by a blank line.
 */

// Comments in C++ style beginning with // should turn into Python comments

// include of string.h should disappear
#include <string.h>
// include of stdlib.h should disappear
#include <stdlib.h>
// include of stdbool.h should disappear
#include <stdbool.h>
// include of stdlib.h should import sys
#include <stdio.h>
// include of stdlib.h should import math
#include <math.h>
// include of time.h should import time
#include <time.h>
// include of regex.h should import re
#include <regex.h>
// include of curses.h should import curses
#include <curses.h>

// extern declarations should just disappear
extern fubar(int);

// Simple macro definitions should turn into assignments
#define NDEVICES	14

// Macros that take arguments get translated to Python defines.
// If the expansion ends with a parenthesis, the macro is assumed to 
// return a value and turned into Python code that does likewise.
// 
#define square(i)		((i)*(i))
#define same(c1, c2)		((c1.x == c2.x) && (c1.y == c2.y))
#define distance(c1, c2)	sqrt(square(c1.x - c2.x) + square(c1.y - c2.y))
#define invalidate(w)		w.x = w.y = 0

/*************************************************************************
A different style of boxed comment. Should also turn into a series of
Python comments with # at the left margin.  Both comment delimiter lines
should turn into # followed by a blank line.
**************************************************************************/

// Test enumeration processing
typedef enum {
    IHR = 'R',
    IHK = 'K',
    IHC = 'C',
    IHS = 'S',
    IHSTAR = '*',
    IHP = 'P',
    IHW = '@',
    IHB = 'B',
    IHBLANK = ' ',
    IHDOT = '.',
    IHQUEST = '?',
    IHE = 'E',
    IHF = 'F',
    IHT = 'T',
    IHWEB = '#',
    IHMATER0 = '-',
    IHMATER1 = 'o',
    IHMATER2 = '0',
} feature;

typedef enum {
    FWON, FDEPLETE, FLIFESUP, FNRG, FBATTLE,
    FNEG3, FNOVA, FSNOVAED, FABANDN, FDILITHIUM,
    FMATERIALIZE, FPHASER, FLOST, FMINING, FDPLANET,
    FPNOVA, FSSC, FSTRACTOR, FDRAY, FTRIBBLE,
    FHOLE, FCREW
} FINTYPE ;

enum COLORS {
   DEFAULT,
   BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
   DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

// The static keyword goes away.  void as a formal list is ignored.

static int randdevice(void)
/* comment in this position should get indented to conform to Python usage */
{
    /*
     * This tests our ability to handle boxed comments with an indent.
     * The C initializer below will be translated into a tuple.
     */
    static int weights[NDEVICES] = {
	105,	/* DSRSENS: short range scanners	10.5% */
	105,	/* DLRSENS: long range scanners		10.5% */
	120,	/* DPHASER: phasers			12.0% */
	120,	/* DPHOTON: photon torpedoes		12.0% */
	25,	/* DLIFSUP: life support		 2.5% */
	65,	/* DWARPEN: warp drive			 6.5% */
	70,	/* DIMPULS: impulse engines		 6.5% */
	145,	/* DSHIELD: deflector shields		14.5% */
	30,	/* DRADIO:  subspace radio		 3.0% */
	45,	/* DSHUTTL: shuttle			 4.5% */
	15,	/* DCOMPTR: computer			 1.5% */
	20,	/* NAVCOMP: navigation system		 2.0% */
	75,	/* DTRANSP: transporter			 7.5% */
	20,	/* DSHCTRL: high-speed shield controller 2.0% */
	10,	/* DDRAY: death ray			 1.0% */
	30,	/* DDSP: deep-space probes		 3.0% */
    };
    // $ctopy class coord
    // Scalar type , one initializer just before semi, trailing comment
    int sum = 0, i, idx = Rand() * 1000.0;	/* weights must sum to 1000 */
    // All scalars -- this line should vanish
    int i, i2, j, ideltax, ideltay, ifindit, iwhichb;
    // Class instances variables require initialization
    coord iq, sc, ibq;
    // Arrays don't get initializers.  This could be handled better.
    int basetbl[BASEMAX+1];
    // Scalar, just one, should vanish
    bool avoid;

    // simple C for loops are translated
    for (i = 0; i < NDEVICES; i++) {
	sum += weights[i];
	if (idx < sum) {
	    fprintf(stdout, "Found device %i\n", i); 
	    return i;
    }
    return -1;	/* we should never get here, but this quiets GCC */
}

// Test the ability to declare a type is mapped into a class and pass
// back a reference to it.  Also test the hint parser.
// $ctopy class event

event *unschedule(int evtype)
/* remove an event from the schedule */
{
    // Test our ability to handle gettexted format strings
    printf(_("Unscheduling event %d\n"), evtype)
    game.future[evtype].date = FOREVER;
    // The & should be stripped
    return &game.future[evtype];
}

main(int argc, char *argv)
{
    intro();
    do {
	initgame();
	redisplay(TRUE);

	while (boatsfound < LIFEBOATS && !allmarked() && domove())
	    continue;

	redisplay(FALSE);	/* force found count to be updated */
	prompt("Want to play again [yn]? ");
    } while
	(confirm());
    outro();
    /*NOTREACHED*/
}
