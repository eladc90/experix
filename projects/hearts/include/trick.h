#ifndef __TRICK_H__
#define __TRICK_H__
#include "../include/table.h"
#include "../include/player.h"




/* this function start a round of tricks

input:
    a pointer to the game 
output:
    return 0 if game is over and 1 if not
error:

*/
int TrickPlay(Player **_playerArr, Table *_table);

/* this function check for the next player turn

input:
    a pointer to the game
output:
    return the next player number
error:

*/

int trickGetNextPlayer(Table *_table);

/* this function get the cards on the table a return the score value

input:
    a pointer to a table
output:
    return the score of the table 
error:

*/
void trickGetCards(Player **_playerArr, Table *_table, int _firstPlayer);

/* 
this function get the score on the table
input:
    a pointer to the table 

output:
    return the score number

error:

*/

int trickGetScore(Table *_table);


/* this function print the score of all the players

input:
    a pointer to the players array
output:
    return the string of the players score
*/

char *TrickPrintScore(Player **_playerArr);



#endif /*__TRICK_H__ */
