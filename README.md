# Smartcard-Reader-MFC
--MFC application - READER ACS-ACR38X SMART CARD--

This software is a MFC sample to transmit commands to the smartcard reader.
It use the PC/SC driver for the communication (the winscard library in the system) and not the ct-api suggested by ACS that is deprecated.
The project is builded with Visual Studio 17  ( Windows vc70 32bit), and tested with the ACS-ACR38X with a card SLE5542


**FOR USERs(USAGE):**
  Probabily you will need to install the Driver for your specific reader. Also i setted my driver configuration in windows device mgmt as it follow<br />

  ![Alt text](https://github.com/johnMinelli/Smartcard-Reader-MFC/images/devices.png?raw=true "device settings")

  Note that the sle5542 and sle4442 are comaptible (see spec for details)
  Unfortunately my reader's driver supported only up to the 5532 so i selected the one compatible with my card's chip.

  **COMMANDS TO TRANSMIT FOR ACR38X<br />**
  \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_CLA\_\_\_INS\_\_\_P1\_\_\_\_P2\_\_\_\_\_Addr\_\_\_Le<br />
  GETDATA:\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_0xFF,_ 0xCA,_ 0x00,_ 0x00,_ 0x00\_\_\_\_\_\_\_\_\_\_\_\_ ----> FFCA000000<br />
  SELECT_CARD_TYPE:\_\_\_\_0xFF,_ 0xA4,_ 0x00,_ 0x00,_ 0x01,_ 0x06_\_\_\_\_ ----> FFA400000106<br />
  READ:\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_0xFF,_ 0xB0,_ 0x00,\_\_\_\_\_\_\_\_\_0x20,_ 0xC0\_\_\_\_\_ ----> FFFFB00020C0<br />

  More commands in the documentation file of the reader provided by ACS

**FOR DEVELOPERs:**
  In the doc folder you can find:
  -Documentation about the chip of the card used by me for testing
  -ACS manuals with more commands and specifications (relative to the ACR38 and ACR39 readers)

  If you want to import the project in your solution be sure to enable the precompiled header option<br />
  ![Alt text](https://github.com/johnMinelli/Smartcard-Reader-MFC/images/vscpp.png?raw=true "visual studio setting 1")

  and to !!!!IMPORTANT!!!! import the library for the linker: odbc32.lib;odbccp32.lib;winscard.lib;%(AdditionalDependencies)<br />
  ![Alt text](https://github.com/johnMinelli/Smartcard-Reader-MFC/images/vslinker.png?raw=true "visual studio setting 2")
