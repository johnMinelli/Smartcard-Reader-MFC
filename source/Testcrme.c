/* Calais Resource Manaer Interface Test Program  *****************************\
*                                                                              *
*                      - for 1 reader -                                        *
*                                                                              *
* Copyright (c) 1997 IBM Corporation                                           *
*                                                                              *
* Authors: Lutz Gemper, Erwin Feicht, Sep/1997                                 *              *
*                                                                              *
* This program tests the Calais Resource Manager Interface with good           *
* parameters. The readername is found via SCardListReaders.                    *                       *
* Test requires a T1 Chipcard with masterfile '3F00'                           *                                                                      *
*                                                                              *
* Following resource Manager Functions are tested with this testprogram with   *
* only good cases                                                              *
*                                                                              *
*              SCardEstablishContext                                           *
*              SCardReleaseContext                                             *
*              SCardListReaders                                                *
*              SCardState                                                      *
*              SCardGetStatusChange                                            *
*              SCardConnect                                                    *
*              SCardDisconnect                                                 *
*              SCardTransmit                                                   *
\******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "winscard.h"

// Local constants, types and function prototypes                                                   

#define NUMBER_OF_READERS     1
#define MINTIMEOUT 1

struct ICC_cmd {
   unsigned char * cmd;
   unsigned char cmd_len;
   };

void show_values(unsigned long,unsigned char*);
void error_print(long rc);



main()
{


SCARDCONTEXT ResHandle;
SCARDHANDLE  CardHandle;
DWORD ActiveProtocol, CardState, AtrLen, len;
long rc;
unsigned char i;

char Readername[64]={0, 0};
SCARD_READERSTATE reader[1];
SCARD_IO_REQUEST T1_request;
unsigned char Atr[33];
unsigned char Response[255];


/* MFC commands (DAD=0)  *****************************************************/

/* Select Master File '3F00'   This command is card specific!!!     */
BYTE SELECT_MF[]  = {0xA4, 0xA4, 0x00, 0x00, 0x02, 0x3F, 0x00};

// KJ File T1_TS1.REQ
BYTE Command1[]  = {0xB0, 0x20, 0x00, 0x00, 0x04, 0x31, 0x32, 0x33, 0x34};
BYTE Command2[]  = {0xB0, 0xA4, 0x04, 0x0C, 0x07, 0xD2, 0x76, 0x00, 0x00,
					0x03, 0x01, 0x01};
BYTE Command3[]  = {0xB0, 0x84, 0x00, 0x00, 0x08};


/*****************************************************************************/
/* Establish Context to Resource Manager #1                                  */
/*****************************************************************************/

  printf("Calais Resource Manager Test Program\n");

  printf("rc=SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&ResHandle)\n");

  rc=SCardEstablishContext(SCARD_SCOPE_USER,NULL,NULL,&ResHandle);

  error_print(rc);
  printf("ResHandle=%x\n",ResHandle);
  printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* List Readernames                                                          */
/*****************************************************************************/

  printf("rc=SCardListReaders(ResHandle, 0,response,&len)\n");

  len=sizeof(Response);
  memset(Response,0x00,sizeof(Response));
  rc=SCardListReaders(ResHandle,0,Response,&len);
  error_print(rc);
  strcpy(Readername, Response);

  printf("len= %d, Readers in System are= ",len);
  for (i=0;i<len ; i++) {
       printf("%c",Response[i]);
  } /* endfor */
  printf("\n");

  printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* GET_STATUS_CHANGE  -> look for card 1                                     */
/*****************************************************************************/

   printf("rc=SCardGetStatusChange(ResHandle,timeout=1,readerstructure[],NumOfRrdrs=1)\n");
   printf("\nPlease insert card ! \n");

   printf("readername %s \n",Readername);

   reader[0].dwCurrentState=SCARD_STATE_UNAWARE;
   reader[0].dwEventState=SCARD_STATE_UNAWARE;
   reader[0].szReader=Readername;

   while((reader[0].dwEventState & SCARD_STATE_PRESENT) != SCARD_STATE_PRESENT) {
      rc=SCardGetStatusChange(ResHandle, MINTIMEOUT, reader, 1);
          if (rc)
                  break;
   }

  error_print(rc);
   printf("State=%x\n,State=%x\n",reader[0].dwCurrentState,reader[0].dwEventState);
   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* SCardConnect Reader 1 with card                                           */
/*****************************************************************************/


   printf("rc=SCardConnect(ResHandle,Readername=%s,SCARD_SHARE_EXCLUSIVE,SCARD_PROTOCOL_T1,&CardHandle,ActiveProtocol)\n",Readername);

   len=256;
   ActiveProtocol=0; /* just for checking result change */

   rc=SCardConnect(ResHandle,Readername,SCARD_SHARE_DIRECT,SCARD_PROTOCOL_T1,&CardHandle,&ActiveProtocol);

	error_print(rc);
   printf("CardHandle   =%x\n",CardHandle);   printf("ActiveProtocol=%x\n",ActiveProtocol);
   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* SCardState   (ATR + Readerstate)                                          */
/*****************************************************************************/

   printf("rc=SCardState(CardHandle,&CardState,&ActiveProtocol,ATR,&AtrLen);\n");

   AtrLen=256;
   ActiveProtocol=0; /* just for checking result change */
   CardState=0;
   rc=SCardState(CardHandle,&CardState,&ActiveProtocol,Atr,&AtrLen);
	error_print(rc);

   printf("CardState     =%x\n",CardState);
   printf("ActiveProtocol=%x\n",ActiveProtocol);
   printf("ATR= ");
   show_values(AtrLen,Atr);
   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* ScardTransmit                                                             */
/*****************************************************************************/

   memset(Response,0x00,sizeof(Response));

   printf("Request for Reader #1:\n");
   show_values(sizeof(Command1),Command1);

   T1_request.dwProtocol=SCARD_PROTOCOL_T1;
   T1_request.cbPciLength=8;
   len=sizeof(Response);

   printf("rc=SCardTransmit(CardHandle,&T1_request,Command1,sizeof(Command1),0,Response,&len)");
   rc=SCardTransmit(CardHandle,&T1_request,Command1,sizeof(Command1),0,Response,&len);

  error_print(rc);
   printf("Response Reader #1:\n");
   printf("returned len= %d\n",len);
   show_values(len,Response);
   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* ScardTransmit                                                             */
/*****************************************************************************/

   memset(Response,0x00,sizeof(Response));

   printf("Request for Reader #1:\n");
   show_values(sizeof(Command2),Command2);

   T1_request.dwProtocol=SCARD_PROTOCOL_T1;
   T1_request.cbPciLength=8;
   len=sizeof(Response);

   printf("rc=SCardTransmit(CardHandle,&T1_request,Command2,sizeof(Command2),0,Response,&len)");
   rc=SCardTransmit(CardHandle,&T1_request,Command2,sizeof(Command2),0,Response,&len);
  error_print(rc);

   printf("Response Reader #1:\n");
   printf("returned len= %d\n",len);
   show_values(len,Response);
   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* ScardTransmit                                                             */
/*****************************************************************************/

   memset(Response,0x00,sizeof(Response));

   printf("Request for Reader #1:\n");
   show_values(sizeof(Command3),Command3);

   T1_request.dwProtocol=SCARD_PROTOCOL_T1;
   T1_request.cbPciLength=8;
   len=sizeof(Response);

   printf("rc=SCardTransmit(CardHandle,&T1_request,Command3,sizeof(Command3),0,Response,&len)");
   rc=SCardTransmit(CardHandle,&T1_request,Command3,sizeof(Command3),0,Response,&len);
  error_print(rc);

   printf("Response Reader #1:\n");
   printf("returned len= %d\n",len);
   show_values(len,Response);
   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* ScardTransmit                                                             */
/*****************************************************************************/
/*	orginal
   memset(Response,0x00,sizeof(Response));

   printf("Request for Reader #1:\n");
   show_values(sizeof(SELECT_MF),SELECT_MF);

   T1_request.dwProtocol=SCARD_PROTOCOL_T1;
   T1_request.cbPciLength=8;
   len=sizeof(Response);

   printf("rc=SCardTransmit(CardHandle,&T1_request,SELECT_MF,sizeof(SELECT_MF),0,Response,&len)");
   rc=SCardTransmit(CardHandle,&T1_request,SELECT_MF,sizeof(SELECT_MF),0,Response,&len);

   printf("Response Reader #1:\n");
   printf("returned len= %d\n",len);
   show_values(len,Response);
   printf("rc=%x\n-------------------------------\n",rc);
*/
/*****************************************************************************/
/* Disconnect Card                                                           */
/*****************************************************************************/

   printf("rc=SCardDisconnect(CardHandle, SCARD_EJECT_CARD)\n");

   rc=SCardDisconnect(CardHandle, SCARD_EJECT_CARD);
	error_print(rc);

   printf("rc=%x\n-------------------------------\n",rc);

/*****************************************************************************/
/* Release Context #1                                                        */
/*****************************************************************************/
   printf("rc=SCardReleaseContext(ResHandle1)\n");

   rc=SCardReleaseContext(ResHandle);
	error_print(rc);

   printf("rc=%x\n-------------------------------\n",rc);

   return(0);
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
void show_values(unsigned long number ,unsigned char* values)
{
unsigned int i;

     for (i=0;i<number ; i++) {
          printf(" %02x",values[i]);
     } /* endfor */

       printf("\n");
}

/*****************************************************************************/
/* Print ErrorCode                                                           */
/*****************************************************************************/
void error_print(long rc)
{
	switch (rc) {
		case SCARD_E_CANCELLED:
							printf("The action was cancelled by an SCardCancel request.\n");
							break;

		case SCARD_E_CANT_DISPOSE:
							printf("The system could not dispose of the media in the requested manner.\n");
							break;
		case SCARD_E_CARD_UNSUPPORTED:
							printf("The smart card does not meet minimal requirements for support.\n");
							break;
		case SCARD_E_DUPLICATE_READER:
							printf("The reader driver didn't produce a unique reader name.\n");
							break;
		case SCARD_E_INSUFFICIENT_BUFFER:
							printf("The data buffer to receive returned data is too small for the returned data.\n");
							break;
		case SCARD_E_INVALID_ATR:
							printf("An ATR obtained from the registry is not a valid ATR string.\n");
							break;
		case SCARD_E_INVALID_HANDLE:
							printf("The supplied handle was invalid.\n");
							break;
		case SCARD_E_INVALID_PARAMETER:
							printf("One or more of the supplied parameters could not be properly interpreted.\n");
							break;
		case SCARD_E_INVALID_TARGET:
							printf("Registry startup information is missing or invalid.\n");
							break;
		case SCARD_E_INVALID_VALUE:
							printf("One or more of the supplied parameters’ values could not be properly interpreted.\n");
							break;
		case SCARD_E_NOT_READY:
							printf("The reader or card is not ready to accept commands.\n");
							break;
		case SCARD_E_NOT_TRANSACTED:
							printf("An attempt was made to end a non-existent transaction.\n");
							break;
		case SCARD_E_NO_MEMORY:
							printf("Not enough memory available to complete this command.\n");
							break;
		case SCARD_E_NO_SERVICE:
							printf("The Smart card resource manager is not running.\n");
							break;
		case SCARD_E_NO_SMARTCARD:
							printf("The operation requires a smart card but no smart card is currently in the device.\n");
							break;
		case SCARD_E_PCI_TOO_SMALL:
							printf("The PCI Receive buffer was too small.\n");
							break;
		case SCARD_E_PROTO_MISMATCH:
							printf("The requested protocols are incompatible with the protocol currently in use with the card.\n");
							break;
		case SCARD_E_READER_UNAVAILABLE:
							printf("The specified reader is not currently available for use.\n");
							break;
		case SCARD_E_READER_UNSUPPORTED:
							printf("The reader driver does not meet minimal requirements for support.\n");
							break;
		case SCARD_E_SERVICE_STOPPED:
							printf("The Smart card resource manager has shut down.\n");
							break;
		case SCARD_E_SHARING_VIOLATION:
							printf("The card cannot be accessed because of other connections outstanding.\n");
							break;
		case SCARD_E_SYSTEM_CANCELLED:
							printf("The action was cancelled by the system presumably to log off or shut down.");
							break;
		case SCARD_E_TIMEOUT:
							printf("The user-specified timeout value has expired.\n");
							break;
		case SCARD_E_UNKNOWN_CARD:
							printf("The specified card name is not recognized.\n");
							break;
		case SCARD_E_UNKNOWN_READER:
							printf("The specified reader name is not recognized.\n");
							break;
		case SCARD_F_COMM_ERROR:
							printf("An internal communications error has been detected.\n");
							break;
		case SCARD_F_INTERNAL_ERROR:
							printf("An internal consistency check failed.\n");
							break;
		case SCARD_F_UNKNOWN_ERROR:
							printf("An internal error has been detected but the source is unknown.\n");
							break;
		case SCARD_F_WAITED_TOO_LONG:
							printf("An internal consistency timer has expired.\n");
							break;
		case SCARD_S_SUCCESS:
							printf("No error was encountered.\n");
							break;
		case SCARD_W_REMOVED_CARD:
							printf("The card has been removed so that further communication is not possible.\n");
							break;
		case SCARD_W_RESET_CARD:
							printf("The card has been reset so any shared state information is invalid.\n");
							break;
		case SCARD_W_UNPOWERED_CARD:
							printf("Power has been removed from the card so that further communication is not possible.\n");
							break;
		case SCARD_W_UNRESPONSIVE_CARD:
							printf("The card is not responding to a reset.\n");
							break;
		case SCARD_W_UNSUPPORTED_CARD:
							printf("The reader cannot communicate with the card due to ATR configuration conflicts.\n");
							break;
		default:
			printf("rc = %x\n", rc);
			break;
	}
}
