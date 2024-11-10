#include 	"defines.h"
#include 	"stdint.h"
#include 	"BS86D20CA.h"

uint16_t display_buffer[4] = {0,0,0,0};
volatile uint8_t adjkey = 0, auflsh = 0;
/*uint8_t digitcounter = 0;*/
							//    0        1       2		3		4		5		6		7		8	  9	     n		F		d	  u		 r      E
uint16_t   segment_table[16] = {0x003F, 0x0006, 0x001B, 0x004F, 0x0066, 0x006D, 0x0079, 0x0007, 0x007F, 0x006F,0x0054,0x0071,0x005E,0x001C,0x0050,0x0079};

/*typedef struct TIMEVAL{
	uint8_t hour,min,cooking_timehour,cooking_timemin,endcooking_timehour,endcooking_timemin;
}TIME;

TIME _timevalue;*/

//typedef struct {
//    uint8_t  CookingAdjustment, EndAdjustment, AlarmAdjustment;   // working time of rezistance
//}ICON;
//ICON _icons;


typedef struct TIMEVAL TIME;
void CookingTimeFlashing(void);
/*============================================================================
//                 *********** Clear Display Buffer ************          
==============================================================================*/
void __cleardspbuf(void)
{
   unsigned char temp = 4;     //
   
   while (temp > 0)            //
   {   -- temp;                    // clear display_buffer                 //
       display_buffer[temp] = 0;       //
   }
}
unsigned char __bcd_to_converter(unsigned char bcdvalue)
{
    unsigned char degisken = 0;
    while (bcdvalue >= 10)
    {
        bcdvalue = bcdvalue - 10;
        degisken = degisken + 16;
    }
    bcdvalue = bcdvalue | degisken;
    return bcdvalue;
}
///*=====================================================================
//            *********** LOAD DIGIT DATA TO display_buffer ************          
//=====================================================================*/
///*  1. digit    2. digit    3. digit    4. digit    --------
//       ---- HOUR ----         ---- MINUTE ----
//=====================================================================*/
void __digit_loading(unsigned char digitdata, unsigned char dspbup)
{
    unsigned char value = 0;
    unsigned char bcddigitdata = 0;
    
    bcddigitdata = __bcd_to_converter(digitdata);
    value = bcddigitdata & 0xF0;
    value = value >> 4;
    /*if (dspbup == 0)
    {
        if (value != 0)
        {
            display_buffer[dspbup] |= segment_table[value];     //dig1
        }
        value = bcddigitdata & 0x0F;
        display_buffer[dspbup + 1] |= segment_table[value];     //dig2
   }
   else
   {
        display_buffer[dspbup] |= segment_table[value];         //dig3
        value = bcddigitdata & 0x0F;
        display_buffer[dspbup + 1] |= segment_table[value];     //dig4
   }*/
}	
void CookingTimeFlashing(void)
{
	if (auflsh == 1)
	{
		if ((cntoggle & 0x03) != 0x03)
		{
			display_buffer[0] |= IconEndStartAlarmProbe;
		}
	}
	else if (CookingAdjustment != 0)
	{
		if ((cntoggle & 0x03) != 0x03)
		{
			display_buffer[0] |= IconEndStartAlarmProbe;
		}
	}
	else if (EndAdjustment != 0)
	{
		if ((cntoggle & 0x03) != 0x03)
		{
			display_buffer[0] |= IconEndStartAlarmProbe;
		}
	}
	else if (cooking_timehour != 0 || cooking_timemin != 0)
	{
		display_buffer[0] |= IconEndStartAlarmProbe;
		if (endcooking_timehour != 0 || endcooking_timemin != 0)
			display_buffer[0] |= IconEndStartAlarmProbe;
	}
}
void __watchDsp(void)
{
	if ((cntoggle & 0x03) != 0x03)
	{
		display_buffer[0] |= IconAMPMDOT;
	}
	__digit_loading(hour, 1);
	__digit_loading(min, 3);	
}
void __keyLockDsp(void)
{
 /*   iccooktimecon();
    ickeylockcon();
    bzikcon();
    icxpancon();
    icpancon();
    auikcon();
    icendtimecon();
    ickeylockcon();*/
    if (keylock){
        display_buffer[2] |= segment_table[0];		// "o"
		display_buffer[3] |= segment_table[10];		// "n"
    }
    else{
    	display_buffer[1] |= segment_table[0];		// "o"
    	display_buffer[2] |= segment_table[11];		// "F"
    	display_buffer[3] |= segment_table[11];		// "F"
    }
}

void __endCookingTimeDsp(void) {
	/*CookingTimeFlashing();
	display_buffer[0] |= IconAMPMDOT;
	if(_icons.EndAdjustment != 0) 
	{
		if ((cnttgl & 0x03) == 0x03)
		{
			display_buffer[0] &= IconAMPMDOT;
		}
	}
	__digit_loading(_timevalue.endcooking_timehour, 1);
	__digit_loading(_timevalue.endcooking_timemin, 3);	*/
}
void __cookingTimeDsp(void) {
    CookingTimeFlashing();
	if (digdsp != 0 || (cntoggle & 0x04) != 0)
    {
		display_buffer[0] |= IconAMPMDOT;		
    	__digit_loading(cooking_timehour, 1);
    	__digit_loading(cooking_timemin, 3);	
    }
    else
	{
		display_buffer[1] |= segment_table[12];		// "d"
		display_buffer[2] |= segment_table[13];		// "u"
		display_buffer[3] |= segment_table[14];		// "r"
	}

}

//void IconCookingTimeEnding(void)
//{
//    if ((_icons.EndAdjustment == 0) && (_timevalue.cooking_timemin || _timevalue.cooking_timehour) && ((_timevalue.endcooking_timehour != _timevalue.cooking_timehour) || (_timevalue.endcooking_timemin != _timevalue.cooking_timemin)))
//    {
//        display_buffer[1] |= IconEndStartAlarmProbe;
//    }
////    else if ((/*digdsp != 0 ||*/ (cnttgl & 0x04) != 0) && wauadj != 0)
//    else if (((cnttgl & 0x01) == 0 || (cnttgl & 0x02) == 0) && (_icons.EndAdjustment != 0))
//    {
//		display_buffer[1] |= IconEndStartAlarmProbe;		
//    }
//}
//    

void pondsp(void)
{
	if ((cntoggle & 0x03) != 0x03){
		display_buffer[0] |= IconAMPMDOT;      // Dot icon on the display
		__digit_loading(hour,1);				// dig12data in digit 1 and digit 2
		__digit_loading(min,3);				// dig34data in digit 3 and digit 4
	}
}

void __digitDataUpdating(void) {
	__cleardspbuf();
	if (pwron == 1) {  //This part updates the display screen at "Power ON" condition
     	pondsp();
    }
	else{
		if (adjkey){
			__keyLockDsp();			
		}
		else if (WatchAdjustment != 0)
			__watchDsp();
    	else if (CookingAdjustment != 0)
    		__cookingTimeDsp();
    	else {
            CookingTimeFlashing();
            display_buffer[0] |= IconAMPMDOT;		
			__digit_loading(hour, 1);
        	__digit_loading(min, 3);
        }
	}
}
void __turnoff_digits(void) {
	DIG1_OFF;
	DIG2_OFF;	
	DIG3_OFF;
	DIG4_OFF;
}
void __turnoff_display(void) {
    SEG_A_OFF;
    SEG_B_OFF;
    SEG_C_OFF;
    SEG_D_OFF;
    SEG_E_OFF;
    SEG_F_OFF;
    SEG_G_OFF;
   /* DIGITS_OFF;*/
}

void __update_display(void) {
	uint16_t segment_data = 0;
	
//	uint16_t display_buffer2[4] = {0x0006, 0x005B, 0x004F, 0x0066};

/*	if (adjkey){
		segment_data = display_buffer2[digitcounter];
	}*/

	segment_data = display_buffer[digitcounter];
	
	__turnoff_display();
	if ((segment_data & 0x0001) != 0)
		SEG_A_ON;
	else
		SEG_A_OFF;
	if ((segment_data & 0x0002) != 0)
		SEG_B_ON;
	else 
		SEG_B_OFF;
	if ((segment_data & 0x0004) != 0)
		SEG_C_ON;
	else
		SEG_C_OFF;
	if ((segment_data & 0x0008) != 0)
		SEG_D_ON;
	else
		SEG_D_OFF;
	if ((segment_data & 0x0010) != 0)
		SEG_E_ON;
	else
		SEG_E_OFF;
	if ((segment_data & 0x0020) != 0)
		SEG_F_ON;
	else
		SEG_F_OFF;
	if ((segment_data & 0x0040) != 0)
		SEG_G_ON;
	else
		SEG_G_OFF;
}


