#include    "USER_PROGRAM.INC"
#include 	"BS86D20CA.h"
#include	"defines.h"
#include 	"stdint.h"

uint8_t freq2ms = 0, cnt2ms = 0, freq20ms = 0, synstt = 0;
uint16_t cnt1250us = 0;
/*uint8_t syncnt = 0, stblcnt = 5;*/
volatile uint8_t digitcounter;
volatile uint8_t buttonScanSt,buttonScan,hzTersle, hzHataSay = 0;
////==============================================
////**********************************************
////==============================================
//void __attribute((interrupt(0x04))) Interrupt_Extemal(void)
//{
//	//Insert your code here
//}

/*static uint8_t digitcounter = 0;*/
//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{
	_papu3 = 0;
    _pcc = 0b11000000;
	_pc = 0b00110100;
	_pbc = 0b00000000;
	_pb = 0b00000000;
	_pac = 0b00011010;
	_pa = 0b00000000;
	_papu1 = 0;
	_papu4 = 0;
	_pcpu6 = 0;
	_pcpu7 = 0;
	
	_ptm1al = TempCCRA & 0xff;
	_ptm1ah = TempCCRA >> 8;
	_pt1m1 = 1; _pt1m0 = 1;	//Select PTM timer/counter Mode	
	_pt1ck2 = 0; _pt1ck1 = 0; _pt1ck0 = 0;	//Select PTM Counter clock Fsys/4
	_pt1cclr = 1;	//PTM Counter Clear condition selection PTM Comparator A match
	
	_mff = 0;	//Multi-function interrupt request flag
	_mfe = 1; 	//Multi-function interrupt enable
	
    _ptm1af = 0;  //Ptm comparator A interrupt  flag clear
	_ptm1ae = 1; //Ptm comparator A interrupt enable
	
	_emi = 1;	//Global interrupt enable
	_pt1on = 1;	//Timer start
	
	//pwron = 1;
}
	
//==============================================
//**********************************************
//==============================================
void ScanDisplay(void){
	
	if (digitcounter < 4){
    	++digitcounter;
    	
	} else {
    	digitcounter = 0;
    }		
    	
    if(digitcounter == 0){
		DIG1_ON;			//DIG1_ON
		DIG2_OFF;
		DIG3_OFF;
		DIG4_OFF;
    }
	else if(digitcounter == 1){
		DIG2_ON;
		DIG1_OFF;
		DIG3_OFF;
		DIG4_OFF;
	}			//dig2
	else if(digitcounter == 2){
		DIG3_ON;		//dig3
		DIG2_OFF;
		DIG1_OFF;
		DIG4_OFF;
	}
	else{
		DIG4_ON;		//dig4
    	DIG2_OFF;
		DIG3_OFF;
		DIG1_OFF;
	}
}
void SyncRead(void)
{
	uint8_t syncnt = 0, stblcnt = 5;
	if (cnt2ms < 18)
		++cnt2ms;
//	__turnoff_digits();
//	_pa3 = 1;  			//syncron pin pullhigh before read
//	GCC_DELAY(5);
	/*while (stblcnt)
	{*/
		if ((_pa3) != 0) //2+2 cycle
		{
			if (synstt == 0) //1+2
			{
				if (++syncnt == 1)
				{
					synstt = 1;
					cnt2ms = 0;
					stblcnt = 0;			
				}
			}
			else
			{
				syncnt = 0;
				--stblcnt;
			}
		}
		else
		{
			if (synstt == 1) //1+2
			{
				if (++syncnt == 1) //1+1+1 __(2+2+1+2+1+1+1= 10cycle*0,25us*20=50us)
				{
					synstt = 0;
					freq20ms = 1;
					cnt2ms = 0;
					stblcnt = 0;
				}
			}
			else	//1+1
			{
				syncnt = 0;
				--stblcnt;
			}
		}
	//}
}
/*void SyncWait(void)
{
	unsigned char tmrwait = 0;
	tmrwait = 60;			// 60 * 10ms = 600ms
	do
	{
		GCC_CLRWDT();					//watchdog reset
		SyncRead();
		if(cnt2ms >= 18) 		// 18 * 2ms = 36 ms
		{
			cnt2ms = 0;			//sleep enter
			tmrwait = 60;		// sync dont read reload tmrwait 60 * 10 ms = 600ms
		}
		if (freq20ms == 1)
		{
			freq20ms = 0;
			//frqcon();
			--tmrwait ;
		}
	}
	while (tmrwait != 0) ;
}
void SleepControl(void)
{
	GCC_CLRWDT(); 				//watchdog reset asm("wdr");
	if(cnt2ms >= 18) 		// 18 * 2ms = 36 ms
	{
		//cnt2ms = 0;			//sleep enter
		RelayON; 			    // oven shot off
		__cleardspbuf();
		__turnoff_display();
		BuzzerON;
		if (fe2rec == 1)
		{
			fe2rec = 0;
			eeprmwrt_buf[0] = bzslct;
			flash_write();
		}
		SyncWait();
		freq20ms = 0;
	}
}*/
//==============================================
//**********************************************
//==============================================
void __attribute((interrupt(0x3C))) PTM(void)  //125us interrupt süresi 62.5
{
 	static unsigned int cnt125us = 0;
 	
  	if (++cnt125us == 16) 
  	{
  		  //for 2ms cnt125us == 16
  		cnt125us = 0;
   		freq2ms = 1;
   		freq20ms = 1;
   		ScanDisplay();	
   		__update_display();
	   	/*if(hzTersle != _pa3)
		{
			hzTersle = hzTersle^1;
			hzHataSay = 0;
	   		if(buttonScan == 1)
			{
				buttonScanSt++;
				if(buttonScanSt == 30)
				{
					//BS86D20CA_CTOUCH();
					//BS86D20CA_CTOUCH_INITIAL();
					buttonScan = 0;
					buttonScanSt = 0;
				}
			}
		}
		else {
			hzHataSay++;
			if(hzHataSay == 229)
			{
				buttonScan = 1;
				buttonScanSt = 0;
			}
	  	}*/
   }
   __Ptm_Clear();
}

void USER_PROGRAM()
{	
	pwron = 1;
	//SyncWait();	
//	while(1)
	//{	
		GCC_CLRWDT();  //asm ("wdr");		// Watchdog Reset
		if (freq2ms == 1) 
		{
			freq2ms = 0;
			/*if (tmrbzr)
				--tmrbzr;*/
			SyncRead();
  	 		ButtonSetting();
			//frqcon();
			//hrmincon();
			__digitDataUpdating();
			//relay_updt();
						
		//	SleepControl();			// Sleep Mode Control	
		}
	//}
}

void USER_PROGRAM_HALT_PREPARE()
{
	
}

void USER_PROGRAM_HALT_WAKEUP()
{	
}

void USER_PROGRAM_RETURN_MAIN()
{
	
}