#ifndef __UI_H__
#define __UI_H__

#include "player.h"
#include "table.h"
#include "hand.h"

void UiPrintHand(Hand *_hand);


void UiPrintTable(Table *_table);


void UiPrintOptions(Hand *_hand);

void UiPrintScore(Player **_player);

void UiPrintNote();











#endif /*_UI_H_*/