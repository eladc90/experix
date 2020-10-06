#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Deck.h"
#include "table.h"
#include "HEARTErr.h"
#include "ADTErr.h"

typedef struct Player Player;

typedef int (*strategy)(Player *_player, const Table *_table);


/* this function create a player

input:
    char for the name
output:
    a pointer to the player created
error:
    return NULL if aloocation fail
*/
Player *PlayerCreate(char *_name, int _isHuman);

/* this function destroy the player

input:
    a pointer to the player
output:
    return ERR_OK if player destroy 
error:
    
*/
/* HEARTErr playerDestroy(Player *_player); */


int PlayerPlay(Player *_player, Table *_table,  int _strategy, int _index, int _playerIndex);


/* this function get the score of the player

input:
    a pointer to the player 

output:
    return the score of the player
error:

*/

int PlayerGetScore(const Player *_player);

/* this function add a card to the player hand

input:
    a pointer to the player
output:
    return ERR_OK
error:
    ERR_NULL
*/

ADTErr PlayerAdd(Player *_player, int *Card);

/* this function sort the player hand

input:
    a pointer to the player 
output:
    return status
*/
ADTErr PlayerSort(Player *_player);


/* this function check who the first player in the next trick

input:
    a pointer 
    */


int PlayerCheckFirst(Player *_player);


/* this function print the player hand

input:
    a pointer to the player
output:
    print the hand of the player
*/

void PrintPlayerHand(Player *_player);


/* this function add the score to the player and check
 
if the score is more than 100

input:
    a pointer to the player and a number of score
output:
    add the score and return 1 if the score of the player is more than 100 and 0 if not
error:
*/


int PlayerAddScore(Player *_player, int _score);


/* this function create a hand to the player */

void PlayerHandCreate(Player *_player);

/* this function destroy the hand of the player */

void PlayerDestroyHand(Player *_player);


/* this function set the number of card in every suit */

void PlayerSuitSize(Player *_player);

/* this function print the player's score */

void PrintPlayerScore(Player *_player);

char *PlayerGerName(Player *_player);

#endif /*__PLAYER_H__*/
