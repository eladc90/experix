#include "stratagy.h"
#include "player.h"
#include "table.h"
#include "hand.h"
#include "ui.h"
#include <stdio.h>
#include <string.h> /* strncat */


#define NUM_OF_PLAYERS 4
#define NUM_OF_SUITS 4
#define NUM_OF_CARDS 13
#define CARDS_IN_SUIT 13
#define HEARTS 1
#define MAX_SIZE_OF_CHAR 500
#define RANK(num)\
        (num)%(CARDS_IN_SUIT)
        
#define SUIT(num)\
        (num)/(CARDS_IN_SUIT)




static int GetBiger(Table *_table, int *_suit, int *_ishearts);

static int FirstPlayer(Hand *_hand, int *_cardInd);


static int StraHeart(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex);

static int HumanStr(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex);

static int StraPutCard(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex);




static int HumanStr(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex)
{
    int suitSize;
    int index = 0;
    int cardSelect;
    UiPrintTable(_table);
    printf("\n");
    UiPrintOptions(_hand);
    printf("\n");
    UiPrintHand(_hand);
    if (scanf("%d", &cardSelect) != 1)
    {
        cardSelect = -1;
        return cardSelect;
    }
    if (cardSelect > 12 || cardSelect < 0)
    {
        cardSelect = -1;
        return cardSelect;
    }
    for (index = 0; index < NUM_OF_SUITS; index++)
    {
        suitSize = HandOrigiSize(_hand, index);
        if (cardSelect <= suitSize - 1)
        {
            *_cardIndex = cardSelect;
            cardSelect = HandGetCard(_hand, index, cardSelect);
            return cardSelect;
        }
        else
        {
            cardSelect = cardSelect - suitSize;
        }
        
    }
    return cardSelect;
}



static int StraPutCard(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex)
{
    int index = 0;
    int secIndex = 0;
    int returnCard = -1;
    for (index = 0; index < NUM_OF_SUITS; index++)
    {
        if (HandSuitSize(_hand, index) > 0)
        {
            for (;secIndex < HandVecSize(_hand, index); secIndex++)
            {
                if (HandGetCard(_hand, index, secIndex) > -1)
                {
                    returnCard = HandGetCard(_hand, index, secIndex);
                    *_cardIndex = secIndex;
                    return returnCard;
                }
            }
        }
    }
    return returnCard;
}

static int StraHeart(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex)
{
    int card = 0;
    int index;
    for (index = 0; index < HandVecSize(_hand, 1); index++)
    {
        card = HandGetCard(_hand, 1, index);
        if (card == -1)
        {
            continue;
        }
        else
        {
            *_cardIndex = index;
            return card;
        }
        
    }
    return card;
}

static int FirstPlayer(Hand *_hand, int *_cardInd)
{
    int index = 0;
    int secIndex = 0;
    int returnCard;
    for (index = NUM_OF_SUITS - 1; index >= 0; index--)
    {
        if (HandSuitSize(_hand, index) > 0)
        {
            for (; secIndex < HandVecSize(_hand, index); secIndex++)
            {
                returnCard = HandGetCard(_hand, index, secIndex);
                if (returnCard == -1)
                {
                    continue;
                }
                else
                {
                    *_cardInd = secIndex;
                    return returnCard;
                }   
            }  
        }
    }
    return -1;
}

static int GetBiger(Table *_table, int *_suit, int *_ishearts)
{
    int bigNum;
    int index = 1;
    int isHearts = 0;
    bigNum = RANK(TableGetCard(_table, 0));
    *_suit = SUIT(TableGetCard(_table, 0));
    for (; index < NUM_OF_PLAYERS; index++)
    {
        if (RANK(TableGetCard(_table, index)) > bigNum)
        {
            bigNum = RANK(TableGetCard(_table, index));
        }
        if (SUIT(TableGetCard(_table, index)) == HEARTS)
        {
            isHearts = 1;
        }
    }
    *_ishearts = isHearts;
    return bigNum;
} 



int Strategy(Hand *_hand, Table *_table, int *_cardIndex, int _playerIndex, int _strategy)
{
    int card = -1;
    int bigCard;
    int returnCard = -1;
    int index = 0;
    int suit;
    int isheart;
    int suitSize;
    int cardInd;
    if (_strategy == 1)
    {
        while (card == -1)
        {
            card = HumanStr(_hand, _table, &cardInd, _playerIndex);
            *_cardIndex = cardInd;
            if (card == -1)
            {
                UiPrintNote();
            }
        }
        return card;
        
    }
    if (_playerIndex == 0)
    {
        returnCard = FirstPlayer(_hand, _cardIndex);
        return returnCard;
    }
    
    bigCard = GetBiger(_table, &suit, &isheart);
    suitSize = HandSuitSize(_hand, suit);
    if (suitSize > 0)
    {
        for (; index < HandVecSize(_hand, suit); index++)
        {
            card = HandGetCard(_hand, suit, index);
            if (card == -1)
            {
                continue;
            }
            if (RANK(card) < bigCard && RANK(card) > returnCard)
            {
                returnCard = card;
                *_cardIndex = index;
                return returnCard;
            }
        }
    }
    suitSize = HandSuitSize(_hand, 1);
    if (suitSize > 0)
    {
        card = StraHeart(_hand, _table, &cardInd, _playerIndex);
        *_cardIndex = cardInd;
        return card;
    }
    else
    {
        card = StraPutCard(_hand, _table, &cardInd, _playerIndex);
        *_cardIndex = cardInd;
        return card;
    }  
    return returnCard;
}


char *PrintOption(Hand *_hand)
{
    char *option;
	char temp[10];
    int index = 0;
    int suitNum;
    int secIndex = 0;
    int tempSuitNum = 0;
    option = (char *) malloc (sizeof (char) * MAX_SIZE_OF_CHAR);
    option[0] = '\0';

    strncat(option, "please press one of the options: ", 32);
    for (; index < NUM_OF_SUITS; index++)
    {
        suitNum = HandOrigiSize(_hand, index);
        for (secIndex = 0;secIndex < suitNum; secIndex++)
        {
            strncat(option, "[", 1);
            if (secIndex + tempSuitNum >= 10)
            {
                temp[0] = '1';
			    strncat(option, temp, 1);
                temp[0] = ((secIndex + tempSuitNum)%10 + '0');
			    strncat(option, temp, 1);
            }
            else
            {
                temp[0] = secIndex + tempSuitNum + '0';
                strncat(option, temp, 1);
            }
            strncat(option, "]", 1);
            strncat(option, " ", 1);
        }
        tempSuitNum = tempSuitNum + suitNum;
    }
    return option;
}






