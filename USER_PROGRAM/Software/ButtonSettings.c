#include "USER_PROGRAM.INC"
#include 	"defines.h"
#include 	"stdint.h"
#include 	"BS86D20CA.h"

volatile uint8_t keycounter = 0,
				 CookingAdjustment = 0,
				 EndAdjustment = 0,
				 AlarmAdjustment = 0,
				 keylock_adjustment = 0,
				 BrightnessAdjustment = 0,
				 WatchAdjustment = 0,
				 ToneAdjustment = 0,
				 BuzzerAdjust = 0;
				 
/*enum _menu
{
        MENU_MAIN                                               = 0x08,
		MENU_CLOCK                                              = 0x04,
        MENU_MINUSE                                      		= 0x02,
       	MENU_PULES												= 0x01,
        MENU_NONE                                               = 0x00,
        MENU_ALL                                                = 0xFF
};*/

volatile int vdcnt2 = 0;
uint8_t timerbuzzer, bzflsh,tmrb2,fbzupdw,digdsp = 0;
uint8_t keylock, pwron, fchldlock,cntoggle,counter20ms,timertoggle,ttstin = 0;
uint8_t hour,min,cooking_timehour,cooking_timemin,cooking_timesec,endcooking_timehour,endcooking_timemin;

unsigned char prvdat,presdb, button, vdcnt, butdat, prvbut = 0;
typedef union buzzer{
	uint8_t	buzzer_hour;
	uint8_t buzzer_min;
	uint8_t buzzer_sec;
	uint8_t buzzer20ms;
} __buzzer_times;				 

__buzzer_times bz;
				 
void AdjustmentClr (void){
	CookingAdjustment = 0;
	EndAdjustment = 0;
	AlarmAdjustment = 0;
	WatchAdjustment = 0;
	BrightnessAdjustment = 0;
	ToneAdjustment = 0;
	keylock_adjustment = 0;
}
void ToggleOn(void) {
    cntoggle = 0;
    timertoggle = Buf1;
}
void CookingTimesClr(void){
	cooking_timehour = 0;
	cooking_timemin = 0;
	endcooking_timehour = 0;
	endcooking_timemin = 0;
    cooking_timesec = 0;
}
void BuzzerTimesClr (void){
    bz.buzzer_hour = 0;
    bz.buzzer_min = 0;
    bz.buzzer_sec = 0;
    bz.buzzer20ms = 0;
//    fbzupdw = 1;
}

unsigned char CookingFunction(void){
    if (endcooking_timehour != 0)
		return 1;
	else if (endcooking_timemin > 1)
		return 1;
	else
		return 0;
}

    /* *********** END OF COOKING TIME LOAD ************	*/	
/*------------------------------------------------------------------------------------
This Subroutine is used to convert the end of cooking duration to end of cooking time
aubhr includes the expected end of cooking time -- wauhr includes the duration for the
cooking to be ready to serve from the time of day
--------------------------------------------------------------------------------------*/
void CookingTimeReady(void){
	uint8_t CookingReadyHour, CookingReadyMin = 0;

	CookingReadyHour = endcooking_timehour;
	CookingReadyMin = endcooking_timemin + min;
	if (CookingReadyMin >= 60)
	{
		CookingReadyMin = CookingReadyMin - 60;
		++CookingReadyHour;
	}
	CookingReadyHour = CookingReadyHour + hour;
	if (CookingReadyHour >= 24)
	{
		CookingReadyHour = CookingReadyHour - 24;
	}
}

/***********************************************
	TimerSettings Decrement && Increment
***********************************************/
uint8_t TimerDecreasing(unsigned char*mbuf, unsigned char *hrbuf)
{
	if (*mbuf != 0)
	{
		--*mbuf;
		CookingTimeReady();					// This subroutine loads the end of cooking time which will be displayed
	}
	else
	{
		if (*hrbuf != 0)
		{
			--*hrbuf;
			*mbuf = 59;	
    		CookingTimeReady();					// This subroutine loads the end of cooking time which will be displayed
		}
	}
	if (*mbuf == 0)
	{
		if (*hrbuf == 0)
            return 1;
	}
    return 0;
}
void TimerIncreasing(unsigned char *minbuf, unsigned char *hourbuf)
{
	if (*minbuf < 59)
    {
		++*minbuf;
    }
    else
	{
		if (*hourbuf < 23)
		{
            *minbuf = 0;
           ++*hourbuf;
		}
	}
}

/***********************************************
	WatchSetting Decrement && Increment
***********************************************/
void WatchDecrement (void){
    if (vdcnt2 == 0)
        timerbuzzer = 16;
    WatchAdjustment = AdjustTIME;
    if (bzflsh && vdcnt2 == 0){
        bzflsh = 0;
        tmrb2 = 0;
        timerbuzzer = 16;
    }
    else {
        if (bzflsh && vdcnt2 != 0){
			bzflsh = 0;
			tmrb2 = 0;
			timerbuzzer = 20;
		}
		counter20ms = 0;
		sec = 0;
		if (min != 0)
			--min;
		else
		{
			min = 59;
			if (hour != 0)
				--hour;
			else
				hour = 23;
		}    
    }		
}
void WatchIncreasing(void)
{
    if (vdcnt2 == 0)
        timerbuzzer = 16;
    WatchAdjustment = AdjustTIME;
    if (bzflsh && vdcnt2  == 0){
        bzflsh = 0;
        tmrb2 = 0;
        timerbuzzer = 16;
    }
    else{
        if (bzflsh && vdcnt2 != 0 ){
			bzflsh = 0;
			tmrb2 = 0;
			timerbuzzer = 20;
		}
		counter20ms = 7;
		sec = 0;
		if (min < 59)
			++min;
		else
		{
            min = 0;
			if (hour < 23)
				++hour;
			else
				hour = 0;
		}    
    }
}
/***********************************************
*  BRIGHTNESS LEVEL CHANCE Decrement && Increment  
***********************************************/
void BrightnessDecrement(void)
{
    tmrb2 = 0;
    if (bzflsh)
    {
        bzflsh = 0;
        timerbuzzer = 16;
    }
   /* else if (vdcnt2 == 0 && fbtnent == 0)
    {
        
        if (brgslct >0 )
            --brgslct;
        fe2rec = 1;
//        tglonld();
        brgload();
        tmrbzr = 32;
    }*/
   
    BrightnessAdjustment = AdjustTIME;
   // fbtnent = 0;
}
void BrightnessIncrement(void)
{
    tmrb2 = 0;
    if (bzflsh)
    {
        bzflsh = 0;
        timerbuzzer = 16;
    }
    /*else if (vdcnt2 == 0 && fbtnent == 0)
    {
        fe2rec = 1;
        if (brgslct <2 )
            ++brgslct;
//        else
//            bzslct = 0;
//        tglonld();
//        bzronld();
        brgload();
        tmrbzr = 32;
    }*/
   
    BrightnessAdjustment = AdjustTIME;
    //fbtnent = 0;
}


/***********************************************
*   BUZZER TONE Decrement && Increment
***********************************************/
void BuzzerToneDecrement(void)
{
  /*  if (vdcnt2 == 0 && fbtnent == 0)
    {
        fe2rec = 1;
        if (bzslct >0 )
            --bzslct;

        tmrbzr = 16;
    }  */
    ToneAdjustment = AdjustTIME;
    //fbtnent = 0;
}
void BuzzerToneIncrement(void)
{
    /*if (vdcnt2 == 0 && fbtnent == 0)
    {
        fe2rec = 1;
        if (bzslct <2 )
            ++bzslct;
//        else
//            bzslct = 0;
//        tglonld();
//        bzronld();
        tmrbzr = 16;
    }*/
    ToneAdjustment = AdjustTIME;
    //fbtnent = 0;
}
void TimerEndInc(void)
{
	if (endcooking_timemin < 59)
	{
		++endcooking_timemin;
	}
	else
	{
		endcooking_timemin = 0;
		++endcooking_timehour;
	}
}
/************************************
	CookingTime Decrement && Increment
************************************/
void CookingTimeDecrement(void){   
	if (vdcnt2 == 0)
		timerbuzzer = 20;
	tmrb2  = 0;
	CookingAdjustment = AdjustTIME;
	if (bzflsh && vdcnt2 == 0){
		bzflsh = 0;
		timerbuzzer = 20;
	}
	else {
		if (bzflsh && vdcnt2 != 0)
		{
			bzflsh = 0;
			tmrb2 = 0;
			timerbuzzer = 20;
		}
		if ((digdsp != 0) || (cntoggle & 0x04) != 0)
		{
			if ((endcooking_timehour == 0) && (endcooking_timemin == 0))
			{
				if (TimerDecreasing(&cooking_timemin, &cooking_timehour))
					CookingTimesClr();
			}
			else
			{
				TimerEndInc();
				if (TimerDecreasing(&cooking_timemin, &cooking_timehour))
					CookingTimesClr();
			}
			cooking_timesec = 0;
			CookingTimeReady();
		}
		digdsp = 2;
	}
}

void CookingTimeIncreasing(void) {
    if (vdcnt2 == 0)
		timerbuzzer = 20;
	tmrb2  = 0;
	CookingAdjustment = AdjustTIME;
	if (bzflsh && vdcnt2 == 0)
	{
		bzflsh = 0;
		timerbuzzer = 20;
	}
	else
	{
		if (bzflsh && vdcnt2 != 0)
		{
			bzflsh = 0;
			timerbuzzer = 20;
		}
		if (digdsp != 0 || (cntoggle & 0x04) != 0)
		{
			if ((endcooking_timehour == 0) && (endcooking_timemin == 0))
			{
				//auflsh = 0;
				TimerIncreasing(&cooking_timemin, &cooking_timehour);
			}
			else
			{
				if (CookingFunction() != 0)
				{
					if (!((cooking_timehour == 23) && (cooking_timemin == 59)))
					{
						TimerDecreasing(&endcooking_timemin, &endcooking_timehour);
						TimerIncreasing(&cooking_timemin, &cooking_timehour);
					}					
				}
			}
			cooking_timesec = 0;
			CookingTimeReady();
		}
		digdsp = 2;
	}
}
/************************************
	EndCookingTime Decrement && Increment
************************************/
void EndTimeDecrement(void){

}
void EndTimeIncrement(void){

}


/************************************
	Alarm Decrement && Increment
************************************/

void AlarmIncrement(void)
{
	if (vdcnt2 == 0)
        timerbuzzer = 16;
    BuzzerAdjust = 0;
    AlarmAdjustment = AdjustTIME;
    if (bzflsh){
        bzflsh = 0;
        tmrb2 = 0;
        timerbuzzer = 16;
    } 
    else {
        if (tmrb2){
            tmrb2  = 0;
            timerbuzzer = 16;
        }
        else if (fbzupdw || ((bz.buzzer_min == 0 ) && (bz.buzzer_hour != 1))){
        	TimerIncreasing(&bz.buzzer_min, &bz.buzzer_hour);
          	if (bz.buzzer_hour != 0){
            	if ((bz.buzzer_hour != 1) || ( bz.buzzer_hour == 1 && bz.buzzer_min != 0)) {        // 59:xx ten artýrma yapýnca 01:01 oluyordu onu önledik.
                	TimerIncreasing(&bz.buzzer_min, &bz.buzzer_hour);
                }
            }
            fbzupdw = 1;
            bz.buzzer20ms = 0;
            bz.buzzer_sec = 0;
        }
    }
}
void AlarmDecrement(void){
	if (vdcnt2 == 0)
        timerbuzzer = 16;
    AdjustmentClr();
    BuzzerAdjust = 0;
    AlarmAdjustment = AdjustTIME;
    if (bzflsh)
    {
        bzflsh = 0;
        tmrb2 = 0;
        timerbuzzer = 16;
    }
    else
    {
        if (tmrb2)
        {
            tmrb2  = 0;
            timerbuzzer = 16;
        }
        else
        {
    		if (bz.buzzer_min != 0)
    			--bz.buzzer_min;
    		else
    		{
    			if (bz.buzzer_hour != 0)
    			{
    				--bz.buzzer_hour;
    				bz.buzzer_min = 59;
    			}
    		}
            fbzupdw = 1;
            bz.buzzer20ms = 0;
            bz.buzzer_sec = 0;
        }
    }
}
/***********************************************
 CHILDLOCK OFF MODE CHANCE   
***********************************************/
void childlock_on_off (void)
{
    if(keylock == 1 ){
        timerbuzzer = 16;
	    keylock = 0;
	    //fe2rec = 1;
	    keylock_adjustment = AdjustTIME;
    }
	else{
        timerbuzzer = 16;
   		keylock = 1;
   // fe2rec = 1;
    	keylock_adjustment = AdjustTIME;
	}
}    
/**********************************************
   decrement button pressed
***********************************************/
void DecrementButtonPressed(void)
{
    if ((WatchAdjustment || pwron ==1) && keylock_adjustment == 0){
        pwron = 0;
        WatchDecrement();
    }
    else if(AlarmAdjustment){
        AlarmDecrement();
    }
    else if(CookingAdjustment){
        CookingTimeDecrement();
    }
    else if(EndAdjustment){
        EndTimeDecrement();
    }
    else if (keylock_adjustment && (keylock == 1)){
        childlock_on_off();
    }  
    else if (ToneAdjustment){         
        BuzzerToneDecrement();
    }
    else if (BrightnessAdjustment){
    	BrightnessDecrement();
    }
}
/***********************************************
*   increment button pressed
***********************************************/
void IncrementButtonPressed(void)
{
    if ((WatchAdjustment || pwron ==1) && keylock_adjustment == 0){
        pwron = 0;
        WatchIncreasing();
    }
    else if(AlarmAdjustment){
        AlarmIncrement();
    }
    else if(CookingAdjustment){
        CookingTimeIncreasing();
    }
    else if(EndAdjustment){
        EndTimeIncrement();
    }
    else if (keylock_adjustment && (keylock == 0)){
       childlock_on_off();
    }  
    else if (ToneAdjustment){         
       BuzzerToneIncrement();
     }
    else if (BrightnessAdjustment){
       BrightnessIncrement();
    }   
}

void ButtonSetting(void) {
if(SCAN_CYCLEF) {
	GET_KEY_BITMAP();   //get key status with level
	butdat = DATA_BUF[2];
	if (butdat == prvdat)					//.0=sw1,.1=sw2,.2=sw3,.3=sw4,.4=sw5,.5=sw6
	{
		vdcnt++;
		if (button != butdat)			//Long button control; butdat
		{
			if (vdcnt == 6)			
			{
				vdcnt = 0;
				prvbut = button;
				button = butdat;
				presdb = (butdat ^ prvbut) & butdat;
				if (presdb != 0)
				{		
					//fbzton = 0;
                    tmrb2 = 0;
                    if(bzflsh)
                    {
                        bzflsh = 0;
                        timerbuzzer = 16 ;
                    }
					if(DATA_BUF[2] & 0x04){        //MenuButtonPressed
						if (presdb == 0x04){
							if (pwron == 0) {
								ToggleOn();
								AdjustmentClr();
								if (keylock_adjustment == 0) 
									keylock_adjustment = AdjustTIME; 
								else if ((keylock_adjustment != 0) && (cooking_timehour == 0) && (cooking_timemin == 0)){
									WatchAdjustment = AdjustTIME;
									if (WatchAdjustment != 0)
										WatchAdjustment = 0; 
								}							
								else if (BrightnessAdjustment == 0)
									BrightnessAdjustment = AdjustTIME;
								else if (ToneAdjustment == 0 && CookingAdjustment == 0 && EndAdjustment == 0) {
									timerbuzzer = 20;
									ToggleOn();
									AdjustmentClr();
									ToneAdjustment = AdjustTIME;
								}
							}
						}
					}
					else if(DATA_BUF[2] & 0x01){   //PlusButtonPressed
						if (presdb == 0x01 /*&& (fchldlock == 0 || keylock_adjustment != 0)*/) {
		                   if (ttstin != 0){
		                      if (keycounter == 1){
		                          ++keycounter;
		                      }
		                      else {
		                          keycounter = 0;
		                      }
		                      timerbuzzer = 16;
		                   }
	                        IncrementButtonPressed(); 
	                        timerbuzzer = 16;
						}
	                }
					else if(DATA_BUF[2] & 0x02){		//MinusButtonPressed
						if ((presdb == 0x02) /*&& (fchldlock == 0 || keylock_adjustment != 0)*/){						
		                   if (ttstin != 0){
		                      if (keycounter == 4){
		                         ++keycounter;
		                      }
		                      else {
		                         keycounter = 0;
		                      }
		                      timerbuzzer = 16;   
		                   }
		                   DecrementButtonPressed(); 
		                   timerbuzzer = 16;
						}
					}
					else if(DATA_BUF[2] & 0x08) {
						if(presdb == 0x08) {
							if (pwron == 0){
								digdsp = 0;
								tmrb2 = 0;							
								if (auflsh == 0) { 
								 	if (bzflsh == 0) {
										if (ToneAdjustment != 0){
									        timerbuzzer = 20;
									        ToggleOn();
									        AdjustmentClr();
									        CookingAdjustment = AdjustTIME;
								        }
										else if (CookingAdjustment != 0) {
											timerbuzzer = 20;
											ToggleOn();
											AdjustmentClr();
											if ((cooking_timehour != 0) || (cooking_timemin != 0))
												EndAdjustment = AdjustTIME;
										}
										else if (WatchAdjustment != 0){
											timerbuzzer = 20;
											ToggleOn();
											AdjustmentClr();
										}
										else if (ToneAdjustment == 0 && CookingAdjustment == 0 && EndAdjustment == 0){
											timerbuzzer = 20;
											ToggleOn();
											AdjustmentClr();
											ToneAdjustment = AdjustTIME;
										}
								 	}	
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		vdcnt = 0;
		//vdcnt2 = 0;
		prvdat = butdat;
	}
	}
}   