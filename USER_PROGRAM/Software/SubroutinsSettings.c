#include "defines.h"

 uint8_t sec = 0,tmrb1= 0;
 uint8_t buzzer_sec, buzzer_min, buzzer_hour,buzzer_flsh = 0;
/*=====================================================================
			******** UPDATE TIMER *******	
=====================================================================*/
void UpdateTime(unsigned char *mbuf,unsigned char *hrbuf)
{
	if (*mbuf != 0)
	{
		--*mbuf;
	}
	else
	{
		if (*hrbuf != 0)
		{
			--*hrbuf;
			*mbuf = 59;
		}
	}
}
/*=====================================================================
				*********** TIME UPDATE ************			
=====================================================================*/
void RTC_Settings(void){
	if (((cooking_timehour != 0) || (cooking_timemin != 0)) && ((endcooking_timehour == 0) && (endcooking_timemin == 0))){
		++cooking_timesec;
		if (cooking_timesec == 60) {					//orjinalde 60
			cooking_timesec = 0;
			UpdateTime(&cooking_timemin,&cooking_timehour);
			if ((cooking_timehour == 0) && (cooking_timemin == 0)){
				tmrb1 = 120;				//120 * 0.5sec = 1 min
				tmrb2 = 7;					//7 * 1min = 2ms
				auflsh = 1;
			}
		}
	}
	++sec;
	if (sec == 60){				//orjinalde 60
		sec = 0;
		++min;
		if (min >= 60) {				//orjinalde 60
			min =  0;
			++hour;
			if (hour >= 24)			//orjinalde 24
				hour =  0;
			if ((endcooking_timehour != 0) || (endcooking_timemin != 0))
			{
				UpdateTime(&endcooking_timemin,&endcooking_timehour);
			}
		}
	}
	/******************************************************
		BuzzerTime Setting
	******************************************************/
	++buzzer_sec;
	if (buzzer_sec == 60){			//orjinalde 60
		buzzer_sec = 0;
		if (buzzer_min != 0){
			--buzzer_min;
			if (buzzer_min == 0){
				if (buzzer_hour == 0){
					//fbzupdw = 0;
					tmrb1 = 120;				//120 * 0.5sec = 1 min
					tmrb2 = 7;					//7 * 1min = 2ms numune 5 dakika oldugu icin 5 dakika yapýldý barýs beye sorýuldu.
					buzzer_flsh = 1;
							//tglonld();
				}
			}
		}
		else {
			if (buzzer_hour != 0){
				--buzzer_hour;
				buzzer_min = 59;
			}
		}
	}
}
void hrmincon(void)
{
/*---------------------------------
Test Mode Display Timers Update
----------------------------------*/
   /* if (tmrtst != 0)	
    {
        --tmrtst;
    }
	
			
    ++cnttst20ms;
    if (cnttst20ms == cmp20msval)       // 50, 60 HZ gore sure
	{
        cnttst20ms = 0;
        if (ttstin != 0)
    		--ttstin;
	}*/
/*------------------
Toggle Timers Update
--------------------*/
	if (--timertoggle == 0)
	{	
		++cntoggle;
		if ((cntoggle & 0x01) == 1)	
		{
			timertoggle = Buf2;
			if ((cntoggle & 0x02) == 0)
			{
				timertoggle = Buf3;
                
			}
		}
		else
		{
			timertoggle = Buf1;
    		if ((cntoggle & 0x02) != 0)
            {
                if (digdsp)
                    --digdsp;
            }
		}
		
		if ((cntoggle & 0x01) == 0)
		{
			/*---------------------------------
			Decrease buzzer timers every  500ms
			----------------------------------*/
			if (tmrb2 != 0)
			{
				--tmrb1;
                timerbuzzer = 80;
				if (tmrb1 == 0)
				{
					tmrb1 = 120;
					-- tmrb2;
				}				
			}
		}
		if ((cntoggle & 0x03) == 3)
		{
			/*----------------------------------------
			Decrease adjusting mode timers every 500ms
			-----------------------------------------*/
			if (WatchAdjustment != 0){		// Saat Ayar Modu           
				--WatchAdjustment;
                if (WatchAdjustment == 0)
                    timerbuzzer = 16;
			}
            if (ToneAdjustment != 0){		// Buzzer Tonu Ayar Modu			
				--ToneAdjustment;
                if (ToneAdjustment == 0)
                    timerbuzzer = 16;
			}
            if (CookingAdjustment != 0){		// Piþirme Bitiþ Zamaný Ayar Modu			
				--CookingAdjustment;
                if (CookingAdjustment == 0)
                    timerbuzzer = 16;
			}
            if (EndAdjustment != 0){		// Piþirme Süresi Ayar Modu			
				--EndAdjustment;
                if (EndAdjustment == 0)
                    timerbuzzer = 16;
			}
            if (BrightnessAdjustment != 0){		// Piþirme Süresi Ayar Modu			
				--BrightnessAdjustment;
                if (BrightnessAdjustment == 0)		// bzadj 
                    timerbuzzer = 16;
			}
		}
	}
	if (ToneAdjustment == 0)		// MM adj süresi sonunda baslýyordu kaldýrdýk bunu
		fbzupdw  = 0;
}

/********************************************
            RELAY SETTINGS
*********************************************/
void RelaySettings(void)
{
    /*if ( tmrtst != 0 )
    {		
		RELAY_ON; 			    // oven shot off
        //if (r1stt == 0)
        //{
            //r1stt = 1; 
            //capondly = 10;
        //}     
    }*/
    if (pwron != 0 ){
	//	RelayON; 			    // oven shot off
        //if (r1stt == 0)
        //{
            //r1stt = 1; 
            //capondly = 10;
        //}
	}
	else if ((endcooking_timehour != 0) || (endcooking_timemin != 0))
	{
	//	RelayON; 			    // oven shot off		    
        //if (r1stt == 0)
        //{
            //r1stt = 1; 
            //capondly = 10;
        //}
	}
	else if (auflsh != 0)
	{
	//	RelayON; 			    // oven shot off
        //if (r1stt == 0)
        //{
            //r1stt = 1; 
            //capondly = 10;
        //}
	}
    else {
	//	RelayOFF;	// oven on
        //r1stt = 0;
        //capondly = 0;
        //capstt = 0;
        //// cap off yap
        //CAP_ON;
    }        
} 