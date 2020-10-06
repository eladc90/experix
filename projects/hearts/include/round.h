#ifndef __ROUND_H__
#define __ROUND_H__
#include "ADTErr.h"
#include "player.h"
/* this function create a round

input:
    none
output:
    return status
error:

*/
ADTErr roundCreate(Player **_playerArr, Table *_table);

/* this function start the round

input:
    a pointer to Game
output:
    return 0 if some of the player lose and 1 if not
error:
    ERR_NULL
*/

int RoundPlay();


/* 
this function destroy the round

input:
    a pointer to the players array 
output:
    return status
error:
*/

ADTErr roundDestroy(Player **_playerArr);




#endif /*__ROUND_H__ */