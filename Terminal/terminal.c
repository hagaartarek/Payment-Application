#include"terminal.h"

uint8_t d,m,y;
f32 Amount;

/*Transaction Data function implementation*/
/*This function imports current date from PC*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){

	EN_terminalError_t functionstate = TERMINAL_OK;
    if(termData == NULL){
		
		functionstate = WRONG_DATE;
		
    }else{
		
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        termData->transactionDate[0] = (tm.tm_mday/10) + '0';
        termData->transactionDate[1] = (tm.tm_mday%10) + '0';
        termData->transactionDate[2] = '/';
        termData->transactionDate[3] = (tm.tm_mon + 1)/10 + '0';
        termData->transactionDate[4] = (tm.tm_mon + 1)%10 + '0';
        termData->transactionDate[5] = '/';
        termData->transactionDate[6] = (tm.tm_year + 1900)/1000 + '0';
        termData->transactionDate[7] = ((tm.tm_year + 1900)/100)%10 + '0';
        termData->transactionDate[8] = ((tm.tm_year + 1900)/10)%10 + '0';
        termData->transactionDate[9] = (tm.tm_year + 1900)%10 + '0';
        termData->transactionDate[10] = '\0';

    }
	
    return functionstate;
}


/*Function checks if card is expired or not*/
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData){
	
    EN_terminalError_t functionstate = TERMINAL_OK;
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if((cardData != NULL) && (termData != NULL)){ 

		if(((cardData->cardExpirationDate[3] > termData->transactionDate[8])) ||
			((cardData->cardExpirationDate[3] == termData->transactionDate[8])
			&& (cardData->cardExpirationDate[4] > termData->transactionDate[9]))
			|| ((cardData->cardExpirationDate[3] == termData->transactionDate[8]) && (cardData->cardExpirationDate[4] == termData->transactionDate[9])
			&& ((cardData->cardExpirationDate[0] > termData->transactionDate[3]) || ((cardData->cardExpirationDate[0] == termData->transactionDate[3]) 
			&& (cardData->cardExpirationDate[1] > termData->transactionDate[4])))) ){
			
			functionstate = TERMINAL_OK;
			
		}else{
		
        	
			functionstate = EXPIRED_CARD;
	
		}
	}else{
        
        functionstate = TERMINAL_NULL_PTR;
    
    }
		
    return functionstate;
}


/*IS VALID Card Primary Account Number function implementation*/
/*Function to check if PAN is Luhn number or not*/
/*EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	
	uint8_t i=0;
    uint8_t x=0,z=0,sum=0;
	EN_terminalError_t functionstate = TERMINAL_OK;
	
	if(cardData != NULL){    
		for(i=0;i<20;i+=2){
			x = cardData->primaryAccountNumber[i] *2;
			
			if(x > 9){
				z = x-9;
			}else{
				z = x;
			}
			sum+=z;
			
		}
		for(i=1;i<20;i+=2){
			sum+=cardData->primaryAccountNumber[i];
		}
		if((sum%10) == 0){
	
			functionstate = TERMINAL_OK;
	
		}else{
	
			functionstate = INVALID_CARD;
			
		}
    }else{
        
        functionstate = TERMINAL_NULL_PTR;
    
    }
        
        return functionstate;
}*/


/*Function to get Transaction Amount*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData){
	
    EN_terminalError_t functionstate = TERMINAL_OK;
    if(termData == NULL){

		functionstate = TERMINAL_NULL_PTR;
        
    }else{
		
		printf("\nPlease Enter Transaction Amount: ");
        scanf("%f",&Amount);
        fflush(stdin);

        if(Amount > 0){
			
            termData->transAmount = Amount;
			
        }else{
			
            functionstate = INVALID_AMOUNT;
        }
	}
	
    return functionstate;
}


/*Function to check if transAmount is below max amount or not*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData){
	
    EN_terminalError_t functionstate = TERMINAL_OK;
    if(termData != NULL){
		
        if((termData->transAmount) <= (termData->maxTransAmount)){
			
            functionstate = TERMINAL_OK;
			
        }else{
			
            functionstate = EXCEED_MAX_AMOUNT;
           
        }
    }else{
		
		functionstate = TERMINAL_NULL_PTR;
		
	}
	return functionstate ;
}



/*Function to set max amount*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData){
        
        EN_terminalError_t functionstate = TERMINAL_OK;
        if(termData != NULL){
			termData->maxTransAmount = 5000;
        }else{
            functionstate = TERMINAL_NULL_PTR;
        }
        
        return functionstate;
}
