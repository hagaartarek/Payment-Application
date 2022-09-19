#include"server.h"


uint32_t i=0, s=0;

ST_accountsDB_t accountsarr[255]={
	{1000.0,RUNNING,"1234567895123456"},
	{2000.0,RUNNING,"1234567891234567"},
	{3000.0,BLOCKED,"1234567896123458"},
	{4000.0,RUNNING,"1234567897123459"},
	{5000.0,RUNNING,"1234567899123465"},
	{6000.0,BLOCKED,"1234567898123461"},
	{7000.0,RUNNING,"1234567891123462"},
	{8000.0,RUNNING,"1234567892123463"},
	{9000.0,BLOCKED,"1234567893123464"}
}; //Accounts Data base
ST_transaction_t transactionsarr[255]={0}; //Transactions Data base


/*Function to recieve transaction data*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData){
	
	EN_transState_t functionstate = APPROVED;
	if(transData == NULL){

		functionstate = INTERNAL_SERVER_ERROR;

	}else{

				accountsarr[i].balance = (accountsarr[i].balance) - (transData->terminalData.transAmount);
				printf("balance after transaction is %.02f\n",accountsarr[i].balance);

	}

	return functionstate;
}


/*Is Valid Account Function Implementation*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData){

	uint32_t x=0;
    EN_serverError_t functionstate = SERVER_OK;
    if(cardData == NULL){

        functionstate = SERVER_NULL_PTR;

    }else{

		for(i=0;i<255;i++){

			x=strcmp(cardData->primaryAccountNumber,accountsarr[i].primaryAccountNumber);
			if( x == 0){

				functionstate = SERVER_OK;
				break;

			}else{

				functionstate = ACCOUNT_NOT_FOUND;

			}
			
		}
	}

    return functionstate;
}


/*Is Blocked Account Function Implementation*/
EN_serverError_t isBlockedAccount(ST_terminalData_t *termData){
	
    EN_cardError_t functionstate = SERVER_OK;
    if(termData == NULL){

        functionstate = SERVER_NULL_PTR;

    }
    else{

        if(accountsarr[i].state == RUNNING){

            functionstate = SERVER_OK;

        }
        else{

            functionstate =  BLOCKED_ACCOUNT;

        }
        
    }

    return functionstate;
}


/*Is Amount Available Function Implementation*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData){
	
    EN_cardError_t functionstate = SERVER_OK;
    if(termData == NULL){

        functionstate = SERVER_NULL_PTR;

    }
    else{

        if(accountsarr[i].balance >= termData->transAmount){

            functionstate = SERVER_OK;

        }
        else{

            functionstate = LOW_BALANCE;
        }  
    }

    return functionstate;
}


/*Function to save transaction*/
EN_serverError_t saveTransaction(ST_transaction_t *transData){

	EN_cardError_t functionstate = SERVER_OK;
	transData->transactionSequenceNumber = s;
	if(transData == NULL){

     functionstate = SERVER_NULL_PTR;

 	}else{

		if(transData->transactionSequenceNumber<=255){
			transactionsarr[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
			transactionsarr[transData->transactionSequenceNumber].terminalData = transData->terminalData;
			transactionsarr[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;
			s++;
			listSavedTransactions();

		}else{

			functionstate = SAVING_FAILED;

		}
	}

	return functionstate;
}

/*function to print transactions*/
void listSavedTransactions(void){

	uint8_t j=0;
	for(j=0;j<s;j++){

		if(s != 0){

			printf("\n#######################\n");
			printf("\nTransaction Sequence Number : %d\n",s);
			printf("transaction Date : %s\n",transactionsarr[j].terminalData.transactionDate);
			printf("transaction Amount : %.02f\n",transactionsarr[j].terminalData.transAmount);
			printf("new balance = %.02f\n",accountsarr[i].balance);
			printf("Terminal Max Amount : %.02f\n",transactionsarr[j].terminalData.maxTransAmount);
			printf("card Holder Name : %s\n",transactionsarr[j].cardHolderData.cardHolderName);
			printf("primary Account Number : %s\n",transactionsarr[j].cardHolderData.primaryAccountNumber);
			printf("card Expiration Data : %s\n",transactionsarr[j].cardHolderData.cardExpirationDate);
			printf("\n#######################\n");

		}else{

			printf("No Transactions");

		}
	}
}