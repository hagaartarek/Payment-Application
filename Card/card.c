#include"card.h"

uint8_t HolderName[25] , ExpirationDate[6] , primaryaccountnumber[20] , ret;


/*function to getCardHolderName*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

    EN_cardError_t functionstate = CARD_OK;
	printf("Please Enter Card Holder Name: ");
    gets(HolderName);
    if(cardData != NULL){

		ret = checkString(HolderName);
        if((strlen(HolderName)>=20) && (strlen(HolderName)<=24) && (ret == 1)){
			strcpy(cardData->cardHolderName,HolderName);

		}else{

			functionstate = WRONG_NAME;

		}
    }else{

        functionstate = CARD_NULL_PTR;

    }

    return functionstate;
}

/*function to check string*/
uint8_t checkString(uint8_t arr[]){

	uint8_t i=0,s=0;
	s=strlen(arr);
	for (i = 0; i<s ; i++){

		if (((arr[i] >= 'a') && (arr[i] <= 'z')) || ((arr[i] >= 'A') && (arr[i] <= 'Z'))|| (arr[i] == ' ')){
			
			continue;

		}
		else{ 

			return 0; 

		}
    }

    return 1;
}

/*function to getCardExpiryDate*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData){

    EN_cardError_t functionstate = CARD_OK;
	printf("\nPlease Enter Card Expiration Date \"MM/YY\": ");
	gets(ExpirationDate);
    if((cardData != NULL)){
		
			if((((ExpirationDate[0] == '0') && ((ExpirationDate[1] >= '0') && (ExpirationDate[1] <= '9')))
				|| ((ExpirationDate[0] == '1') && ((ExpirationDate[1] >= '0') && (ExpirationDate[1] <= '2')))) 
				&& (ExpirationDate[2] == '/')
				&&((ExpirationDate[3] >= '0') && (ExpirationDate[3] <= '9')) &&((ExpirationDate[4] >= '0') && (ExpirationDate[4] <= '9'))){
				
				strcpy(cardData->cardExpirationDate,ExpirationDate);
				
			}else{
				
				functionstate = WRONG_EXP_DATE; 
				
			}
    }else{
		
        functionstate = CARD_NULL_PTR;

    }

    return functionstate;
}


/*function to getCardPAN*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData){
	
	EN_cardError_t functionstate = CARD_OK;
	printf("\nPlease Enter card's Primary Account Number: ");
    gets(primaryaccountnumber);
    if(cardData != NULL){
		
			ret = checkNumbers(primaryaccountnumber);
			if((strlen(primaryaccountnumber) >= 16) && (strlen(primaryaccountnumber) <=19) && (ret == 1)){
	
				strcpy(cardData->primaryAccountNumber,primaryaccountnumber);
				
			}else{
				
				functionstate = WRONG_PAN;
			}

    }else{
		
       functionstate = CARD_NULL_PTR;
	   
    }

    return functionstate;
}


/*function to check numbers*/
uint8_t checkNumbers(uint8_t arr[]){

	uint8_t i=0, s=0;
	s=strlen(arr);
	for (i = 0; i<s ; i++){

		if ((arr[i] >= '1') && (arr[i] <= '9')){

			continue;

		}
		else{ 

			return 0; 

		}
    }
	
    return 1;
} 