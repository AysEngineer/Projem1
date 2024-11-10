#ifndef DEFINES_H_
#define DEFINES_H_
#include 	"stdint.h"

#define TempCCRA				250
#define AdjustTIME				5
#define Buf1					10
#define Buf2					25
#define Buf3					20	

void __cleardspbuf(void);

#define AllButtonPressed        0xFF;
#define MenuButtonPressed  		0x04			//_pa1 = 1
#define ProgramButtonPressed	0x08			//_pa4 = 1
#define MinusButtonPressed		0x02			//_pc6 = 1
#define PlusButtonPressed		0x01			//_pc7 = 1


/* Komutator */
#define comutator              		_pcc2 = 0
#define comutatorpullhigh           _pcpu2 = 0
#define comutatorinithigh           _pc2 = 1

/* Termostat*/
#define termostat              		_pcc3 = 0
#define termostatpullhigh           _pcpu3 = 0
#define termostatinithigh           _pc3 = 1



#define SEG_A_ON            		_pb4 = 1
#define SEG_B_ON					_pb5 = 1				
#define SEG_C_ON					_pb6 = 1				
#define SEG_D_ON					_pb7 = 1
#define SEG_E_ON					_pc0 = 1
#define SEG_F_ON					_pc1 = 1
#define SEG_G_ON					_pc2 = 1
#define IconAMPMDOT					_pc3 = 1        //SEG_8_ON
#define IconLockTimeSoundBrigh		_pa3 = 1		//SEG_9_ON	
#define IconEndStartAlarmProbe		_pa0 = 1		//SEG_10_ON
#define IconComutatorTermostat		_pa2 = 1		//SEG_11_ON

#define DIG1_ON				_pb0 = 0
#define DIG2_ON				_pb1 = 0
#define DIG3_ON				_pb3 = 0
#define DIG4_ON				_pb2 = 0

/*#define DIGITS_OFF			_pb = 0x0F */
#define DIG1_OFF				_pb0 = 1
#define DIG2_OFF				_pb1 = 1
#define DIG3_OFF				_pb3 = 1
#define DIG4_OFF				_pb2 = 1
#define SEG_A_OFF           _pb4 = 0
#define SEG_B_OFF			_pb5 = 0				
#define SEG_C_OFF			_pb6 = 0				
#define SEG_D_OFF			_pb7 = 0
#define SEG_E_OFF			_pc0 = 0
#define SEG_F_OFF			_pc1 = 0
#define SEG_G_OFF			_pc2 = 0
//#define SEG_8_OFF			_pc3 = 0
//#define SEG_9_OFF			_pa3 = 0
//#define SEG_10_OFF			_pa0 = 0
//#define SEG_11_OFF			_pa2 = 0


#define BuzzerON	                _pa7 = 1
#define BuzzerOFF 					_pa7 = 0

/*Relay Control*/
#define RelayON                     _pc4 = 1
#define RelayOFF					_pc4 = 0

#define RelayCapON                  _pc5 = 1
#define RelayCapOFF                 _pc5 = 0


#define __Ptm_Clear()					_ptm1af = 0


extern volatile uint8_t digitcounter;

extern volatile uint8_t adjkey, auflsh;
extern uint8_t hour,min,sec,cooking_timehour,cooking_timemin,cooking_timesec,cooking_timesec,endcooking_timehour,endcooking_timemin,buzzer_sec,buzzer_min,buzzer_hour;
extern uint8_t keylock, pwron, cntoggle,timertoggle, digdsp,timerbuzzer,tmrb1,tmrb2, buzzer_flsh, fbzupdw;
extern volatile int vdcnt2;
/*extern volatile uint8_t buttonScanSt,buttonScan;*/
extern 
volatile uint8_t keycounter,
				 CookingAdjustment,
				 EndAdjustment,
				 AlarmAdjustment,
				 keylock_adjustment,
				 BrightnessAdjustment,
				 WatchAdjustment,
				 ToneAdjustment,
				 BuzzerAdjust ;
void ScanDisplay(void);
void __cleardspbuf(void);
void __update_display(void);
void __turnoff_digits(void);
void __turnoff_display(void);
void ButtonSetting(void);
void KeyLockDsp(void);
void RelaySettings(void);

typedef struct TIMEVAL TIME;
typedef union buzzer __buzzer_times;

#endif  