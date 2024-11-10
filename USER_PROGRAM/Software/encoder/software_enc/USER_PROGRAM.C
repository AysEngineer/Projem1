#include "USER_PROGRAM.INC"
#include "BS83B08C.h"
#include "stdint.h"
#include "define.h"

#ifdef IR_ACTIVE
volatile uint8_t     IR_sayac = 0,
			         dur = 0,
			         sistem = 0,
			         ir_error = 0,
			         SEFER = 0,
			         bitsay = 0;
#endif

volatile uint8_t     kademe = 0,
			         button1PositiveDebounce = 0,
			         button2PositiveDebounce = 0,
			         button3PositiveDebounce = 0,
			         button4PositiveDebounce = 0,
			         allButtonsOffDebounce = 0,
					 timerAktif = 0,
			         ikiBirGecisiVar = 0,
			         blinkSay = 0,
			         lambaDurum = 0,
			         kisaFlagCalisti = 0,
			         uzunFlagCalisti = 0,
			         button1Flag = 0,
			         button2Flag = 0,
			         button3Flag = 0,
			         button4Flag = 0,
			         button2LongFlag = 0,
			         button3LongFlag = 0,
			         button4LongFlag = 0,
			         button1ReleaseActive = 0,
			         button2ReleaseActive = 0,
			         button3ReleaseActive = 0,
			         button4ReleaseActive = 0,
			         button1ReleaseFlag = 0,
			         button2ReleaseFlag = 0,
			         button3ReleaseFlag = 0,
			         button4ReleaseFlag = 0,
			         button1PressedFlag = 0,
			         button2PressedFlag = 0,
			         button3PressedFlag = 0,
			         button4PressedFlag = 0,
			         ms10say = 0,
			         sebekeFlag = 0,
			         motorTrigger = 0,
			         hzDurum = 0,
			         motorTriggerSayac = 0,
			         hzTersle = 0,
			         butonTaramaDurdur = 0,
			         butonTaramaBaslatSayac = 0,
			         timerMsSay = 0,
			         ikiBirGecisiSay = 0,
			         blinkSayac = 0,
			         button1BasiliCounter = 0,
			         button2BasiliCounter = 0,
			         button3BasiliCounter = 0,
			         button4BasiliCounter = 0,
			         hzHataSay = 0;
         
struct _davlumbaz
{
volatile uint8_t   timerDk;
volatile uint8_t   timerSnSay;
}davlumbaz;

void TimerInitialize(void);
#ifdef IR_ACTIVE
void IRSayacSifirla(void);
#endif
void TimerStart(void);

void USER_PROGRAM_INITIAL()
{
	PINB1OUT;
	PINB1PULLHIGH;
	PINB1INITHIGH;
	
	PINB3OUT;
	PINB3PULLHIGH;
	PINB3INITHIGH;
	
	PINB5OUT;
	PINB5PULLHIGH;
	PINB5INITHIGH;
	
	PINB7OUT;
	PINB7PULLHIGH;
	PINB7INITHIGH;
	
	PINA1OUT;
	PINA1PULLHIGH;
	PINA1INITHIGH;
	
	PINA3OUT;
	PINA3PULLHIGH;
	PINA3INITHIGH;
	
	PINA2OUT;
	PINA2PULLHIGH;
	PINA2INITHIGH;
	
	PINA7OUT;
	PINA7PULLHIGH;
	PINA7INITHIGH;
	
	PINA0IN;
	PINA0NOPULL;
	PINA0INITLOW;
	
	PINA4IN;
	
	_ptmal = TIMER_PERIOD & 0xff;
	_ptmah = TIMER_PERIOD >> 8;
	
	_ptm1 = 1; _ptm0 = 1;	//Select PTM timer/counter Mode	
	_ptck2 = 0; _ptck1 = 0; _ptck0 = 0;	//Select PTM Counter clock Fsys/4
	_ptcclr = 1;	//PTM Counter Clear condition selection PTM Comparator A match
	
	_mff = 0;	//Multi-function interrupt request flag
	_mfe = 1; 	//Multi-function interrupt enable
	
	_ptmaf = 0; //Ptm comparator A interrupt  flag clear
	_ptmae = 1;	//Ptm comparator A interrupt enable
	
	_emi = 1;	//Global interrupt enable
	_pton = 1;	//Timer start
	
	_ints1 = 1; _ints0 = 1;	//both edge trigger external interrupt 0
	//_pbc0 = 1; _pbpu0 = 1;		//set int0 input mode and enable pull-high
	_inte = 1; _intf = 1;
	
	_tb0 = 1;
	_tbon = 1;
	
	/*LVR - Low Voltage Reset
	01010101: 2.1V
	00110011: 2.55V
	10011001: 3.15V
	10101010: 3.8V*/
	//_lvrc = 0X99;	//3.15V
	//_lvrc = 0X33;	//3.15V
	
	//GCC_DELAY(900);		//wait system stable
}

void USER_PROGRAM()
{
	if(SCAN_CYCLEF && butonTaramaDurdur == 0)
	{
		GET_KEY_BITMAP();
		
		if(DATA_BUF[0]&0x01)	//BUTON4 BASILI ÝKEN
		{
			if(button4BasiliCounter < (BUTTON4LONGPRESSTIME+1)) button4BasiliCounter++;

            if(button4PositiveDebounce < (BUTTONPOSITIVEDEBOUNCE+1)) button4PositiveDebounce++;
            if(button4PositiveDebounce == BUTTONPOSITIVEDEBOUNCE)
            {
                button4Flag = 1;
                button4ReleaseActive = 1;
                button4PressedFlag = 1;
            }
            if(button4BasiliCounter == BUTTON4LONGPRESSTIME)
            {
                button4LongFlag = 1;
            }
		}
		else
		{
			button4Flag = 0;
            button4LongFlag = 0;
            button4BasiliCounter = 0;
            button4PositiveDebounce = 0;

            if(button4ReleaseActive == 1)
            {
                button4ReleaseActive = 0;
                button4ReleaseFlag = 1;
                button4PressedFlag = 0;
            }
		}
		
		if(DATA_BUF[0]&0x04)	//BUTON3 BASILI ÝKEN
		{
			if(button3BasiliCounter < (BUTTON3LONGPRESSTIME+1)) button3BasiliCounter++;

            if(button3PositiveDebounce < (BUTTONPOSITIVEDEBOUNCE+1)) button3PositiveDebounce++;
            if(button3PositiveDebounce == BUTTONPOSITIVEDEBOUNCE)
            {
                button3Flag = 1;
                button3ReleaseActive = 1;
                button3PressedFlag = 1;
            }
            if(button3BasiliCounter == BUTTON3LONGPRESSTIME)
            {
                button3LongFlag = 1;
            }
		}
		else
		{
			button3Flag = 0;
            button3LongFlag = 0;
            button3BasiliCounter = 0;
            button3PositiveDebounce = 0;

            if(button3ReleaseActive == 1)
            {
                button3ReleaseActive = 0;
                button3ReleaseFlag = 1;
                button3PressedFlag = 0;
            }
		}
		
		if(DATA_BUF[0]&0x10)	//BUTON2 BASILI ÝKEN
		{
			if(button2BasiliCounter < (BUTTON2LONGPRESSTIME+1)) 
			button2BasiliCounter++;

            if(button2PositiveDebounce < (BUTTONPOSITIVEDEBOUNCE+1)) button2PositiveDebounce++;
            if(button2PositiveDebounce == BUTTONPOSITIVEDEBOUNCE)
            {
                button2Flag = 1;
                button2ReleaseActive = 1;
                button2PressedFlag = 1;
            }
            if(button2BasiliCounter == BUTTON2LONGPRESSTIME)
            {
                button2LongFlag = 1;
            }
		}
		else
		{
			button2Flag = 0;
            button2LongFlag = 0;
            button2BasiliCounter = 0;
            button2PositiveDebounce = 0;

            if(button2ReleaseActive == 1)
            {
                button2ReleaseActive = 0;
                button2ReleaseFlag = 1;
                button2PressedFlag = 0;
            }
		}
		
		if(DATA_BUF[0]&0x40)	//BUTON1 BASILI ÝKEN
		{
			if(button1PositiveDebounce < (BUTTONPOSITIVEDEBOUNCE+1)) button1PositiveDebounce++;
            if(button1PositiveDebounce == BUTTONPOSITIVEDEBOUNCE)
            {
                button1Flag = 1;
                button1ReleaseActive = 1;
                button1PressedFlag = 1;
            }
		}
		else
		{
			button1Flag = 0;
            button1BasiliCounter = 0;
            button1PositiveDebounce = 0;

            if(button1ReleaseActive == 1)
            {
                button1ReleaseActive = 0;
                button1PressedFlag = 0;
            }
		}
		
		if(DATA_BUF[0] == 0x00)	//HÝÇBÝR BUTON BASILI DEÐÝL
		{
			/*if(allButtonsOffDebounce < (BUTTONPOSITIVEDEBOUNCE+1)) */allButtonsOffDebounce++;
            if(allButtonsOffDebounce == BUTTONPOSITIVEDEBOUNCE)
            {
                kisaFlagCalisti = 0;
                uzunFlagCalisti = 0;
            }
		}
		else
		{
			allButtonsOffDebounce = 0;	
		}
		
		if(button1Flag == 1)
	    {
	        button1Flag = 0;
	        lambaDurum = lambaDurum ^ 1;
	    }
	    
	    if(button2Flag == 1)
	    {
	        button2Flag = 0;
	        if(kademe != 3)
	        {
		        kademe = 3;
		        TimerInitialize();
		        kisaFlagCalisti = 1;
	        }
	        
	    }
	    else if(button2LongFlag == 1 && kisaFlagCalisti == 0)
	    {
	        button2LongFlag = 0;
	        TimerStart();
	        uzunFlagCalisti = 1;
	    }
	    else if(button2ReleaseFlag == 1)
	    {
	        button2ReleaseFlag = 0;
	        if(uzunFlagCalisti == 0 && kisaFlagCalisti == 0)
	        {
	            if(kademe == 3)
	            {
	                TimerInitialize();
	                kademe = 0;
	            }
	        }
	    }
	    
	    if(button3Flag == 1)
	    {
	        button3Flag = 0;
	        if(kademe != 2)
	        {
		        kademe = 2;
		        TimerInitialize();
		        kisaFlagCalisti = 1;
	        }
	    }
	    else if(button3LongFlag == 1 && kisaFlagCalisti == 0)
	    {
	        button3LongFlag = 0;
	        TimerStart();
	        uzunFlagCalisti = 1;
	    }
	    else if(button3ReleaseFlag == 1)
	    {
	        button3ReleaseFlag = 0;
	        if(uzunFlagCalisti == 0 && kisaFlagCalisti == 0)
	        {
	            if(kademe == 2)
	            {
	                TimerInitialize();
	                kademe = 0;
	            }
	        }
	    }
	    
	    if(button4Flag == 1)
	    {
	        button4Flag = 0;
	        if(kademe == 0)
	        {
	            kademe = 1;
	            ikiBirGecisiVar = 1;
	            ikiBirGecisiSay = 0;
	            kisaFlagCalisti = 1;
	        }
	        else if(kademe == 2 || kademe == 3)
	        {
	            kademe = 1;
	            TimerInitialize();
	            kisaFlagCalisti = 1;
	        }
	    }
	    else if(button4LongFlag == 1 && kisaFlagCalisti == 0)
	    {
	        button4LongFlag = 0;
	        TimerStart();
	        uzunFlagCalisti = 1;
	    }
	    else if(button4ReleaseFlag == 1)
	    {
	        button4ReleaseFlag = 0;
	        if(uzunFlagCalisti == 0 && kisaFlagCalisti == 0)
	        {
	            if(kademe == 1)
	            {
	                TimerInitialize();
	                kademe = 0;
	            }
	        }
	    }
	}
}

void __attribute((interrupt(0x04))) INT0_ISR(void)	//IR Interrupt
{
	#ifdef IR_ACTIVE
	if(!(IR)&&(dur == 0))
	{
		dur = 1;
		IR_sayac = 0;
	}
	else if((IR)&&(dur == 1))
	{
		if((IR_sayac < 95 && IR_sayac > 85)) dur = 2;
		else dur = 0;
		IR_sayac = 0;
	}
	else if(!(IR)&&(dur == 2))
	{
		if((IR_sayac < 50 && IR_sayac > 40)) dur = 3;
		else dur = 0;
		IR_sayac = 0;
	}
	
	if((IR)&&(dur == 3)) dur = 4;

	if(!(IR)&&(dur == 4))
	{
		if((1<IR_sayac)&&(IR_sayac <= 12))
		{
			ir_error = 0;
			sistem = sistem >> 1;
		}
		else if((12 < IR_sayac)&&(IR_sayac < 50))
		{
			ir_error = 0;	
			if(!(bitsay == 0x00)){sistem = sistem >> 1;}
			sistem = sistem + 128;
		}
		else 
        {
            sistem = 0;
            dur = 0;
        }
		bitsay++;
		if(bitsay == 8)
		{
		    if(sistem == 0x00 && SEFER == 0)
            {
                SEFER = 1;sistem = 0;dur = 3;bitsay = 0;
            }
			else if(sistem > 0 &&  SEFER == 1)
            {
                dur = 3;SEFER = 2;sistem = 0;bitsay = 0;
            }
            else if(sistem == 0x45 && SEFER == 2)   //ON-OFF
            {
                if(kademe == 0)
                {
                    kademe = 1;
                    ikiBirGecisiVar = 1;
                    ikiBirGecisiSay = 0;
                }
                else
                {
                    kademe = 0;
                }
                TimerInitialize();
                IRSayacSifirla();
            }
            else if(sistem == 0x09 && SEFER == 2)   //ARTI
            {
            	if(kademe == 1)
                {
                    kademe = 2;
                    ikiBirGecisiVar = 0;
                    ikiBirGecisiSay = 0;
                    TimerInitialize();
                }
                else if(kademe == 2)
                {
                    kademe = 3;
                    TimerInitialize();
                }
                
            	IRSayacSifirla();
            }
            else if(sistem == 0x07 && SEFER == 2)   //EKSÝ
            {
            	if(kademe == 3)
                {
                    kademe = 2;
                    TimerInitialize(); 
                }
                else if(kademe == 2)
                {
                    kademe = 1;
                    TimerInitialize();
                }
            	IRSayacSifirla();
            }
            else if(sistem == 0x19 && SEFER == 2) //TIMER
            {
            	if(timerAktif == 0)
            	{
            		TimerStart();
            	}
            	else
            	{
            		TimerInitialize();	
            	}
                
                IRSayacSifirla();
            }
			else if(sistem == 0x47 && SEFER == 2)   //LAMBA
            {
                lambaDurum = lambaDurum ^ 1;
    
                IRSayacSifirla();
            }
			else IRSayacSifirla();
		}
		else
        {
			dur  = 3;
        }
		IR_sayac = 0;
	}
	#endif
}

void __attribute((interrupt(0x0C))) PTM_ISR(void)	//100us Timer 
{
	#ifdef IR_ACTIVE
	IR_sayac++;
	#endif
	if(hzTersle != ZeroCrossingRead)
	{
		hzTersle = hzTersle^1;
		hzHataSay = 0;
		if(butonTaramaDurdur == 1)
		{
			butonTaramaBaslatSayac++;
			if(butonTaramaBaslatSayac == 50)
			{
				BS83B08C_CTOUCH_INITIAL();
				butonTaramaDurdur = 0;
				butonTaramaBaslatSayac = 0;
			}
		}
		
		/* LED DURUM */
		if(kademe == 0)
	    {
	        LED2LOW;
	        LED3LOW;
	        LED4LOW;
	    }
	    else if(timerAktif == 0)
	    {
	    	if(kademe == 1)
		    {
		        LED4HIGH;
		        LED3LOW;
		        LED2LOW;
		    }
		    else if(kademe == 2)
		    {
		        LED2LOW;
		        LED3HIGH;
		        LED4LOW;
		    }
		    else if(kademe == 3)
		    {
		        LED2HIGH;
		        LED3LOW;
		        LED4LOW;
		    }
	    }

	    if(lambaDurum == 1)
	    {
	        LED1HIGH;
	    }
	    else
	    {
	        LED1LOW;
	    }
	    
	    /***************/
		
		/* BLINK SAY */
		if(blinkSay == 1)
	    {
	        blinkSayac++;
	        if(blinkSayac < 50)
	        {
	            if(kademe >= 1) {LED2LOW; LED3LOW; LED4LOW;}
	        }
	        else if(blinkSayac >= 50 && blinkSayac < 100)
	        {
	            if(kademe == 1) {LED2LOW; LED3LOW; LED4HIGH;}
	            else if(kademe == 2) {LED2LOW; LED3HIGH; LED4LOW;}
	            else if(kademe == 3) {LED2HIGH; LED3LOW; LED4LOW;}
	        }
	        else
	        {
	            blinkSayac = 0;
	        }
	    }
    	/**************/
    	
    	if(timerAktif == 1)
	    {
	        timerMsSay++;
	        if(timerMsSay >= 100)
	        {
	            timerMsSay = 0;
	            davlumbaz.timerSnSay++;
	            if(davlumbaz.timerSnSay == 60)
	            {
	                davlumbaz.timerSnSay = 0;
	                davlumbaz.timerDk = davlumbaz.timerDk - 1;
	                if(davlumbaz.timerDk == 0)
	                {
	                    kademe = 0;
	                    TimerInitialize();
	                }
	            }
	        }
	    }
	   
	    if(ikiBirGecisiVar == 1)// motor birin devirde açýldýðý zaman 2. devir ilk 0.5 saniye açýlýr sonra 1. devire geri döner
	    {
	        ikiBirGecisiSay++;
	        if(ikiBirGecisiSay == 50)
	        {
	            ikiBirGecisiVar = 0;
	            ikiBirGecisiSay = 0;
	        }
	    }
	}
	else
	{
		hzHataSay++;
		if(hzHataSay == 229)
		{
			butonTaramaDurdur = 1;
			butonTaramaBaslatSayac = 0;
		}
	}
	
	if (ZeroCrossingRead && hzDurum == 0) {hzDurum = 1; ms10say = 101;}
	
	if (ms10say > 1) ms10say--; 
	else if (ms10say == 1) 
	{
		motorTrigger = 1;
		ms10say = 0;
		hzDurum = 0;
	}
	
	if(motorTrigger == 1)
	{
		if(motorTriggerSayac < 40)
		{
			motorTriggerSayac++;
		}
		
		if(motorTriggerSayac == 40)
		{
			if(kademe == 0)
		    {
		        KADEME1LOW;
		        KADEME2LOW;
		        KADEME3LOW;
		    }
		    else if(kademe == 1)
		    {
		        if(ikiBirGecisiVar == 1)
		        {
		            KADEME1LOW;
		            KADEME3LOW;
		            KADEME2HIGH;
		        }
		        else
		        {
		            KADEME2LOW;
		            KADEME3LOW;
		            KADEME1HIGH;
		        }
		    }
		    else if(kademe == 2)
		    {
		        KADEME1LOW;
		        KADEME3LOW;
		        KADEME2HIGH;
		    }
		    else if(kademe == 3)
		    {
		        KADEME1LOW;
		        KADEME2LOW;
		        KADEME3HIGH;
		    }
		    
		    if(lambaDurum == 1)
		    {
		        LAMBAROLEHIGH;
		    }
		    else
		    {
		        LAMBAROLELOW;
		    }
		    
		    motorTriggerSayac = 0;
		    motorTrigger = 0;
		}
	}
	
	PTM_CLEAR_FLAG();
}


void TimerInitialize(void)
{
	timerAktif = 0;
    blinkSay = 0;
    blinkSayac = 0;
}

void TimerStart(void)
{
	timerAktif = 1;
    blinkSay = 1;
    davlumbaz.timerDk = TIMERDK;
    davlumbaz.timerSnSay = 0;
}
#ifdef IR_ACTIVE
void IRSayacSifirla(void)
{
	dur = 0; SEFER = 0; sistem = 0; bitsay = 0;
}
#endif