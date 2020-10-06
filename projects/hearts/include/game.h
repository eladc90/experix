#ifndef __GAME_H__
#define __GAME_H__
#include "ADTErr.h"

typedef struct Game Game;



/* this function create a game for 4 players
input:
    none
output:
    return a pointer to Game
error:
    if allocation fail return NULL
*/
Game *GameCreate();

/* this function start the game 

input:

    a pointer to the Game 
output:
    return status
error:
    
*/
ADTErr GamePlay(Game *_game);

/* this function destroy the Game

input:
    a pointer to the Game 
output:
    return status
error:
*/

ADTErr GameDestroy();

#endif /*__GAME_H__ */
