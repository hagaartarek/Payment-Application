/*****************************************************************************/  
/**                  File Name : app.c                                      **/                              
/**                  File Info : Payment Application                        **/
/**                  Author    : Hagar Tarek El-Hassanien                   **/
/**                  Date      : 19.09.2022                                 **/
/**                  Version   : V1.0                                       **/
/*****************************************************************************/

#include"app.h"

/*****************************************************************************/
/************************ Global Declaration Section *************************/
/*****************************************************************************/

ST_cardData_t Carddata;
ST_terminalData_t Termdata;
EN_terminalError_t RET1,RET2;;
EN_serverError_t RET3,RET4,RET5,RET6;
ST_transaction_t transData;


/*****************************************************************************/
/******************************* Main Section ********************************/
/*****************************************************************************/	
int main(){

	appStart();
	
	return 0;
}


void appStart(void){
	
	printf("**********************************************************\n\n");
	printf("***********!! WELCOME TO PAYMENT APPLICATION !!***********\n\n");
	printf("**********************************************************\n\n");

	getCardHolderName(&Carddata);
	getCardExpiryDate(&Carddata);
	getCardPAN(&Carddata);        
	getTransactionDate(&Termdata);
	RET1=isCardExpired(&Carddata,&Termdata);
	if(RET1 == TERMINAL_OK){
		getTransactionAmount(&Termdata);
		setMaxAmount(&Termdata);
		RET2=isBelowMaxAmount(&Termdata);
		if(RET2 == TERMINAL_OK){
			RET3 = isValidAccount(&Carddata);
			if(RET3 == SERVER_OK){
				RET6=isBlockedAccount(&Termdata);
				if(RET6 == SERVER_OK){
					RET4=isAmountAvailable(&Termdata);
					if(RET4 == SERVER_OK){
						transData.cardHolderData= Carddata;
						transData.terminalData= Termdata;		
						recieveTransactionData(&transData);
						RET5 = saveTransaction(&transData);
						if(RET5 == SERVER_OK){
							printf("\nThanks :)\n\n");
							appStart();
						}else{
							printf("\nTransaction can't be saved :(");
							exit(0);
						}
						
					}else{
						printf("\nAmount is Not Available :(");
						exit(0);
					}
				}else{
					printf("\nAccount is Blocked :(");
					exit(0);
				}
			}else{
				printf("\nAccount is Invalid :(");
				exit(0);
			}
		}else{
			printf("\nTransaction Amount is Exceed Maximum Amount :(");
			exit(0);
		}
	}else{
		printf("\nCard is Expired :(");
		exit(0);
	}
		
}