#include <stdio.h>
#include "player.h"
#include "table.h"
#include "hand.h"
#include "stratagy.h"
#include "trick.h"

void UiPrintHand(Hand *_hand)
{
    printf("this is the hand:                ");
    printf("%s", PrintHand(_hand));
}

void UiPrintTable(Table *_table)
{
    printf("this is the table:   \n\n\n\n");
    printf("%s", PrintTable(_table));
    printf("\n\n\n\n");
}

void UiPrintOptions(Hand *_hand)
{
    printf("%s", PrintOption(_hand));
}

void UiPrintScore(Player **_player)
{
    printf("%s", TrickPrintScore(_player));
    printf("\n\n\n\n");
}

void UiPrintNote()
{
    printf("invalid input, please try again\n");
}