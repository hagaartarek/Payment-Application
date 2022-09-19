#ifndef CARD_H
#define CARD_H   


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include<time.h>
#include "..\STD_TYPES.h"


typedef struct ST_cardData_t{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t {
    CARD_OK, 
	CARD_NULL_PTR,
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;


EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
uint8_t checkString(uint8_t arr[]);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);
uint8_t checkNumbers(uint8_t arr[]);


#endif
