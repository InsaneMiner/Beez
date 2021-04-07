#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <libs/string.h>
#include <kernel/system.h>
#include <kernel/console.h>

enum KYBRD_ENCODER_IO {
 
	KYBRD_ENC_INPUT_BUF	=	0x60,
	KYBRD_ENC_CMD_REG	=	0x60,
	KYBRD_ENC_CMD_SET_LED = 0xED
};
 
enum KYBRD_CTRL_IO {
 
	KYBRD_CTRL_STATS_REG	=	0x64,
	KYBRD_CTRL_CMD_REG	=	0x64
};

enum KYBRD_CTRL_STATS_MASK {
 
	KYBRD_CTRL_STATS_MASK_OUT_BUF	=	1,		//00000001
	KYBRD_CTRL_STATS_MASK_IN_BUF	=	2,		//00000010
	KYBRD_CTRL_STATS_MASK_SYSTEM	=	4,		//00000100
	KYBRD_CTRL_STATS_MASK_CMD_DATA	=	8,		//00001000
	KYBRD_CTRL_STATS_MASK_LOCKED	=	0x10,		//00010000
	KYBRD_CTRL_STATS_MASK_AUX_BUF	=	0x20,		//00100000
	KYBRD_CTRL_STATS_MASK_TIMEOUT	=	0x40,		//01000000
	KYBRD_CTRL_STATS_MASK_PARITY	=	0x80		//10000000
};

//! read keyboard encoder buffer
uint8_t kybrd_enc_read_buf () {
 
	return inportb (KYBRD_ENC_INPUT_BUF);
}


//! read status from keyboard controller
uint8_t kybrd_ctrl_read_status () {
 
	return inportb (KYBRD_CTRL_STATS_REG);
}
//! send command byte to keyboard controller
void kybrd_ctrl_send_cmd (uint8_t cmd) {
 
	//! wait for kkybrd controller input buffer to be clear
	while (1)
		if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
 
	outportb (KYBRD_CTRL_CMD_REG, cmd);
}


//! send command byte to keyboard encoder
void kybrd_enc_send_cmd (uint8_t cmd) {
 
	//! wait for kkybrd controller input buffer to be clear
	while (1)
		if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
			break;
 
	//! send command byte to kybrd encoder
	outportb (KYBRD_ENC_CMD_REG, cmd);
}
//! sets leds
void kkybrd_set_leds (bool num, bool caps, bool scroll) {
 
	uint8_t data = 0;
 
	//! set or clear the bit
	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (num | 2) : (num & 2);
	data = (caps) ? (num | 4) : (num & 4);
 
	//! send the command -- update keyboard Light Emetting Diods (LEDs)
	kybrd_enc_send_cmd (KYBRD_ENC_CMD_SET_LED);
	kybrd_enc_send_cmd (data);
}




string kb_input()
{
    char buff;
    string buffstr;
    memset(&buffstr,'\0', sizeof(buffstr));   
    uint8_t i = 0;
    uint8_t reading = 1;
    while(reading)
    {
        if(inportb(0x64) & 0x1)                 
        {
            switch(inportb(0x60))
            { 
      /*case 1:
                putch('(char)27);           Escape button
                buffstr[i] = (char)27;
                i++;
                break;*/
        case 2:
                putch('1');
                buffstr[i] = '1';
                i++;
                break;
        case 3:
                putch('2');
                buffstr[i] = '2';
                i++;
                break;
        case 4:
                putch('3');
                buffstr[i] = '3';
                i++;
                break;
        case 5:
                putch('4');
                buffstr[i] = '4';
                i++;
                break;
        case 6:
                putch('5');
                buffstr[i] = '5';
                i++;
                break;
        case 7:
                putch('6');
                buffstr[i] = '6';
                i++;
                break;
        case 8:
                putch('7');
                buffstr[i] = '7';
                i++;
                break;
        case 9:
                putch('8');
                buffstr[i] = '8';
                i++;
                break;
        case 10:
                putch('9');
                buffstr[i] = '9';
                i++;
                break;
        case 11:
                putch('0');
                buffstr[i] = '0';
                i++;
                break;
        case 12:
                putch('-');
                buffstr[i] = '-';
                i++;
                break;
        case 13:
                putch('=');
                buffstr[i] = '=';
                i++;
                break;
        case 14:
                putch('\b');
                i--;
                if(i<0)
                {
                	i = 0;
                }
                buffstr[i+1] = 0;
                buffstr[i] = 0;
                break;
       /* case 15:
                putch('\t');          Tab button
                buffstr[i] = '\t';
                i++;
                break;*/
        case 16:
                putch('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 17:
                putch('w');
                buffstr[i] = 'w';
                i++;
                break;
        case 18:
                putch('e');
                buffstr[i] = 'e';
                i++;
                break;
        case 19:
                putch('r');
                buffstr[i] = 'r';
                i++;
                break;
        case 20:
                putch('t');
                buffstr[i] = 't';
                i++;
                break;
        case 21:
                putch('y');
                buffstr[i] = 'y';
                i++;
                break;
        case 22:
                putch('u');
                buffstr[i] = 'u';
                i++;
                break;
        case 23:
                putch('i');
                buffstr[i] = 'i';
                i++;
                break;
        case 24:
                putch('o');
                buffstr[i] = 'o';
                i++;
                break;
        case 25:
                putch('p');
                buffstr[i] = 'p';
                i++;
                break;
        case 26:
                putch('[');
                buffstr[i] = '[';
                i++;
                break;
        case 27:
                putch(']');
                buffstr[i] = ']';
                i++;
                break;
        case 28:
               putch('\n');
               //buffstr[i] = '\n';
                  i++;
               reading = 0;
                break;
      /*  case 29:
                putch('q');           Left Control
                buffstr[i] = 'q';
                i++;
                break;*/
        case 30:
                putch('a');
                buffstr[i] = 'a';
                i++;
                break;
        case 31:
                putch('s');
                buffstr[i] = 's';
                i++;
                break;
        case 32:
                putch('d');
                buffstr[i] = 'd';
                i++;
                break;
        case 33:
                putch('f');
                buffstr[i] = 'f';
                i++;
                break;
        case 34:
                putch('g');
                buffstr[i] = 'g';
                i++;
                break;
        case 35:
                putch('h');
                buffstr[i] = 'h';
                i++;
                break;
        case 36:
                putch('j');
                buffstr[i] = 'j';
                i++;
                break;
        case 37:
                putch('k');
                buffstr[i] = 'k';
                i++;
                break;
        case 38:
                putch('l');
                buffstr[i] = 'l';
                i++;
                break;
        case 39:
                putch(';');
                buffstr[i] = ';';
                i++;
                break;
        case 40:
                putch((char)44);               //   Single quote (')
                buffstr[i] = (char)44;
                i++;
                break;
        case 41:
                putch((char)44);               // Back tick (`)
                buffstr[i] = (char)44;
                i++;
                break;
     /* case 42:                                 Left shift 
                putch('q');
                buffstr[i] = 'q';
                i++;
                break;
        case 43:                                 \ (< for somekeyboards)   
                putch((char)92);
                buffstr[i] = 'q';
                i++;
                break;*/
        case 44:
                putch('z');
                buffstr[i] = 'z';
                i++;
                break;
        case 45:
                putch('x');
                buffstr[i] = 'x';
                i++;
                break;
        case 46:
                putch('c');
                buffstr[i] = 'c';
                i++;
                break;
        case 47:
                putch('v');
                buffstr[i] = 'v';
                i++;
                break;                
        case 48:
                putch('b');
                buffstr[i] = 'b';
                i++;
                break;               
        case 49:
                putch('n');
                buffstr[i] = 'n';
                i++;
                break;                
        case 50:
                putch('m');
                buffstr[i] = 'm';
                i++;
                break;               
        case 51:
                putch(',');
                buffstr[i] = ',';
                i++;
                break;                
        case 52:
                putch('.');
                buffstr[i] = '.';
                i++;
                break;            
        case 53:
                putch('/');
                buffstr[i] = '/';
                i++;
                break;            
        case 54:
                putch('.');
                buffstr[i] = '.';
                i++;
                break;            
        case 55:
                putch('/');
                buffstr[i] = '/';
                i++;
                break;            
      /*case 56:
                putch(' ');           Right shift
                buffstr[i] = ' ';
                i++;
                break;*/           
        case 57:
                putch(' ');
                buffstr[i] = ' ';
                i++;
                break;
            }
        }
    }
    buffstr[i-1] = 0;                
    return buffstr;
}