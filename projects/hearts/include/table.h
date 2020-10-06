#ifndef _TABLE_H_
#define _TABLE_H_
#include <stdlib.h>
#include "queue.h"
#include "ADTErr.h"



typedef struct Table Table;

typedef int Card;

/*create a table struct that hold the cards that the players will play
input:
    none
output:
    1.a pointer to a Table struct
error:
    1.if malloc failed return NULL
*/
Table *TableCreate();

/*get the players card nextPlayer is the first one to put the cards
input:
    1. int index of the player that start the trick
output:
    1.NA
*/
ADTErr TableAddCard(Table *_table, int _card, int index);


/* 
this function play the table - check the loser, the score and update the table

input:
    a pointer to the table and and index number of the first player

output:
    return status
error:
*/

ADTErr TablePlay(Table *_table, int _firstPlayer);

/* this function print the cards on the table 

input:
    a pointer to the table 
output:
    none
*/

char *PrintTable(Table *_table);

/*
this function get a table and return who lose in the table

input:
    a pointer to the table 
output:
    return the index of the loser
error:
*/

int TableGetLoser(Table *_table);

/*
this function check the score of the table 

input:
    a pointer to the table 
output:
    return the score on the table
error:
*/

int TableAddScore(Table *_table);

/* 
this function get a table and a index and return the card on the index in the table

input:
    a pointer to the table and a index number
output:
    return the card in the index place.
error:
*/

int TableGetCard(Table *_table, int _index);

/* 
this function get a card and insert the card to the table

input:
    a pointer to the table and a card to insert
output:
    none
*/

void TableAdd(Table *_table, int _card);    

/* 
this function zeroing the table score

input:
    a pointer to the table 
output:
    none
*/
void TableZeroScore(Table *_table);

/* this function zeroing the table

input:
    a pointer to the table

output:
    none
*/

void TableZero(Table *_table);




#endif /*_TABLE_H_*/
