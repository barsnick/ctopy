import math
#
# This is a test load for ctopy, the C to Python translator.
# It is syntactically valid C, parts taken from the source for 
# Super Star Trek and Galaxis.
# 
# This boxed comment at the beginning should turn into a series of
# Python comments with # at the left margin.  Both comment delimiters
# should turn into # followed by a blank line.
# 

# Comments in C++ style beginning with // should turn into Python comments

# include of string.h should disappear
# include of stdlib.h should disappear
# include of stdbool.h should disappear
# include of stdlib.h should import sys
import sys
# include of stdlib.h should import math
import math
# include of time.h should import time
import time
# include of regex.h should import re
import re
# include of curses.h should import curses
import curses

# extern declarations should just disappear

# Simple macro definitions should turn into assignments
NDEVICES	= 14

# Macros that take arguments get translated to Python defines.
# If the expansion ends with a parenthesis, the macro is assumed to 
# return a value and turned into Python code that does likewise.
# 
def square(i):	return ((i)*(i))
def same(c1, c2):	return ((c1.x == c2.x) and (c1.y == c2.y))
def distance(c1, c2):	return math.sqrt(square(c1.x - c2.x) + square(c1.y - c2.y))
def invalidate(w):	w.x = w.y = 0

#
# A different style of boxed comment. Should also turn into a series of
# Python comments with # at the left margin.  Both comment delimiter lines
# should turn into # followed by a blank line.
# 

# Test enumeration processing
# From enumerated type 'feature'
IHR = 'R'
IHK = 'K'
IHC = 'C'
IHS = 'S'
IHSTAR = '*'
IHP = 'P'
IHW = '@'
IHB = 'B'
IHBLANK = ' '
IHDOT = '.'
IHQUEST = '?'
IHE = 'E'
IHF = 'F'
IHT = 'T'
IHWEB = '#'
IHMATER0 = '-'
IHMATER1 = 'o'
IHMATER2 = '0'


# From enumerated type 'FINTYPE'
FWON = 0
FDEPLETE = 1
FLIFESUP = 2
FNRG = 3
FBATTLE = 4
FNEG3 = 5
FNOVA = 6
FSNOVAED = 7
FABANDN = 8
FDILITHIUM = 9
FMATERIALIZE = 10
FPHASER = 11
FLOST = 12
FMINING = 13
FDPLANET = 14
FPNOVA = 15
FSSC = 16
FSTRACTOR = 17
FDRAY = 18
FTRIBBLE = 19
FHOLE = 20
FCREW = 21



# The static keyword goes away.  void as a formal list is ignored.

def randdevice():
    # comment in this position should get indented to conform to Python usage 
    #
    # This tests our ability to handle boxed comments with an indent.
    # The C initializer below will be translated into a tuple.
    # 
    weights = (
	105,	# DSRSENS: short range scanners	10.5% 
	105,	# DLRSENS: long range scanners		10.5% 
	120,	# DPHASER: phasers			12.0% 
	120,	# DPHOTON: photon torpedoes		12.0% 
	25,	# DLIFSUP: life support		 2.5% 
	65,	# DWARPEN: warp drive			 6.5% 
	70,	# DIMPULS: impulse engines		 6.5% 
	145,	# DSHIELD: deflector shields		14.5% 
	30,	# DRADIO:  subspace radio		 3.0% 
	45,	# DSHUTTL: shuttle			 4.5% 
	15,	# DCOMPTR: computer			 1.5% 
	20,	# NAVCOMP: navigation system		 2.0% 
	75,	# DTRANSP: transporter			 7.5% 
	20,	# DSHCTRL: high-speed shield controller 2.0% 
	10,	# DDRAY: death ray			 1.0% 
	30,	# DDSP: deep-space probes		 3.0% 
    )
    # $ctopy class coord
    # Scalar type , one initializer just before semi, trailing comment
    sum = 0; idx = Rand() * 1000.0	# weights must sum to 1000 
    # All scalars -- this line should vanish
    # Class instances variables require initialization
    iq = coord(); sc = coord() ibq = coord()
    # Arrays don't get initializers.  This could be handled better.
    # Scalar, just one, should vanish

    # simple C for loops are translated
    for i in range(NDEVICES):
	sum += weights[i]
	if idx < sum:
	    fprintf(stdout, "Found device %i\n" % (i)) 
	    return i
    return -1	# we should never get here, but this quiets GCC 

# Test the ability to declare a type is mapped into a class and pass
# back a reference to it.  Also test the hint parser.
# $ctopy class event

def unschedule(evtype):
    # remove an event from the schedule 
    # Test our ability to handle gettexted format strings
    printf(_("Unscheduling event %d\n") % (evtype))
    game.future[evtype].date = FOREVER
    # The & should be stripped
    return game.future[evtype]

if __name__ == '__main__':
    intro()
    while True:
	initgame()
	redisplay(True)

	while boatsfound < LIFEBOATS and not allmarked() and domove():
	    continue

	redisplay(False)	# force found count to be updated 
	prompt("Want to play again [yn]? ")
    if not (confirm()): break	# DO-WHILE TERMINATOR -- INDENTATION IS PROBABLY WRONG
    outro()
    #NOTREACHED
