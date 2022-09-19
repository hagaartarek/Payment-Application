#include "Card/card.h"
#include "Terminal/terminal.h"
#include "Server/server.h"

EN_cardError_t RET1,RET2,RET3;
ST_cardData_t cardData;
EN_terminalError_t RET4,RET5,RET6,RET7,RET8;
ST_terminalData_t termData;
EN_serverError_t RET9,RET10,RET11,RET12,RET13;
ST_transaction_t transData;


int main(void){
	
	RET1 = getCardHolderName(&cardData);
	if(RET1 == CARD_OK){
		printf("\nEntered Card Holder Name : %s\n",cardData.cardHolderName);
	}else if(RET1 == WRONG_NAME){
		printf("\nUnvalid Card Holder Name :(\n\n");
	}else{
		printf("\nNULL Pointer...\n");
	}
	
	RET2 = getCardExpiryDate(&cardData);
	if(RET2 == CARD_OK){
		printf("\nEntered Card Expiration Date : %s\n",cardData.cardExpirationDate);
	}else if(RET2 == WRONG_EXP_DATE){
		printf("\nUnvalid Card Expiration Date :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}
	
	RET3 = getCardPAN(&cardData);
	if(RET3 == CARD_OK){
		printf("\nEntered Card PAN : %s\n",cardData.primaryAccountNumber);
	}else if(RET3 == WRONG_PAN){
		printf("\nUnvalid Card PAN :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}
	
	RET4 = getTransactionDate(&termData);
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	if(RET4 == TERMINAL_OK){
		 printf("\nCurrent Date is %s\n",termData.transactionDate);
	}else{
		printf("\nUnvalid Transaction Date :(\n");
	}
	
	RET5 = isCardExpired(&cardData,&termData);
	if(RET5 == TERMINAL_OK){
		printf("\nCard is not Expired :)\n");
	}else if(RET5 == EXPIRED_CARD){
		printf("\nCard is Expired :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}
	
	/*RET6 = isValidCardPAN(&cardData);
	if(RET6 == TERMINAL_OK){
		printf("\nCard is Valid :)\n");
	}else if(RET6 == INVALID_CARD){
		printf("\nCard is Invalid :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}*/
	
	RET7 = getTransactionAmount(&termData);
	if(RET7 == TERMINAL_OK){
		printf("\nTransaction Amount = %.02f\n",termData.transAmount);
	}else if(RET7 == INVALID_AMOUNT){
		printf("\nUnvalid Transaction Amount :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}
	

	setMaxAmount(&termData);

	RET8 = isBelowMaxAmount(&termData);
	if(RET8 == TERMINAL_OK){
		printf("\nTransaction Amount is below Maximum Amount :)\n");
	}else if(RET8 == EXCEED_MAX_AMOUNT){
		printf("\nTransaction Amount is Exceed Maximum Amount :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}

	RET9 = isValidAccount(&cardData);
	if(RET9 == SERVER_OK){
		printf("\nAccount is Valid :)\n");
		
	}else if(RET9 == ACCOUNT_NOT_FOUND){
		printf("\nAccount is Invalid :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}
	
	RET10 = isBlockedAccount(&termData);
	if(RET10 == SERVER_OK){
		printf("\nAccount is not Blocked :)\n");
	}else if(RET10 ==  BLOCKED_ACCOUNT){
		printf("\nAccount is Blocked :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}

	RET11 = isAmountAvailable(&termData);
	if(RET11 == SERVER_OK){
		printf("\nAmount is Available :)\n");
	}else if(RET11 == LOW_BALANCE){
		printf("\nAmount is Not Available :(\n");
	}else{
		printf("\nNULL Pointer...\n");
	}

	transData.cardHolderData= cardData;
	transData.terminalData= termData;
	
	RET12 = recieveTransactionData(&transData);
	if(RET12 == APPROVED){
		printf("\nTransaction is Allowed :)\n");
	}else{
		printf("\nTransaction is not Allowed\n");
	}

	RET13 = saveTransaction(&transData);
	if(RET13 == SERVER_OK){
		printf("\nTransaction is Saved :)\n");
	}else{
		printf("\nTransaction can't be saved\n");
	}
	
	
	return 0;
}