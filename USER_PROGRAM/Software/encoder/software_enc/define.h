#define PIN_DIR_OUT 				0
#define PIN_DIR_IN					1
	
#define PIN_PULL_HIGH_ENABLE		1
#define PIN_PULL_HIGH_DISABLE		0

#define PIN_INITIAL_LEVEL_HIGH		1
#define PIN_INITIAL_LEVEL_LOW		0

/*M1*/
#define PINA1OUT					_pac1 = 0
#define PINA1PULLHIGH				_papu1 = 0
#define PINA1INITHIGH				_pa1 = 1

/*M2*/
#define PINA3OUT					_pac3 = 0
#define PINA3PULLHIGH				_papu3 = 0
#define PINA3INITHIGH				_pa3 = 1

/*M3*/
#define PINA2OUT					_pac2 = 0
#define PINA2PULLHIGH				_papu2 = 0
#define PINA2INITHIGH				_pa2 = 1

/*LAMP*/
#define PINA7OUT					_pac7 = 0
#define PINA7PULLHIGH				_papu7 = 0
#define PINA7INITHIGH				_pa7 = 1

/*RELAY CONTROL*/
#define PINA0IN				    	_pac0 = 1
#define PINA0NOPULL 				_papu0 = 0
#define PINA0INITLOW				_pa0 = 0

/*LED4*/
#define PINB1OUT					_pbc1 = 0
#define PINB1PULLHIGH				_pbpu1 = 0
#define PINB1INITHIGH				_pb1 = 1

/*LED3*/
#define PINB3OUT					_pbc3 = 0
#define PINB3PULLHIGH				_pbpu3 = 0
#define PINB3INITHIGH				_pb3 = 1

/*LED2*/
#define PINB5OUT					_pbc5 = 0
#define PINB5PULLHIGH				_pbpu5 = 0
#define PINB5INITHIGH				_pb5 = 1

/*LED1*/
#define PINB7OUT					_pbc7 = 0
#define PINB7PULLHIGH				_pbpu7 = 0
#define PINB7INITHIGH				_pb7 = 1

/*IR PIN*/
#define PINA4IN 					_pac4 = 1

#define IR     					    _pa4

#define LED1HIGH					_pb7 = 0
#define LED1LOW 					_pb7 = 1

#define LED2HIGH					_pb5 = 0
#define LED2LOW 					_pb5 = 1

#define LED3HIGH					_pb3 = 0
#define LED3LOW 					_pb3 = 1

#define LED4HIGH					_pb1 = 0
#define LED4LOW 					_pb1 = 1

/* SIRALAMA L-1-2-3 */
#define LAMBAROLEHIGH				_pa1 = 0
#define LAMBAROLELOW 				_pa1 = 1

#define KADEME1HIGH					_pa3 = 0
#define KADEME1LOW 					_pa3 = 1

#define KADEME2HIGH					_pa2 = 0
#define KADEME2LOW 					_pa2 = 1

#define KADEME3HIGH					_pa7 = 0
#define KADEME3LOW 					_pa7 = 1

/* EÐER 1-2-3-L SIRALAMASI GEREKÝRSE */
/*#define KADEME1HIGH				_pa1 = 0
#define KADEME1LOW 					_pa1 = 1

#define KADEME2HIGH					_pa3 = 0
#define KADEME2LOW 					_pa3 = 1

#define KADEME3HIGH					_pa2 = 0
#define KADEME3LOW 					_pa2 = 1

#define LAMBAROLEHIGH				_pa7 = 0
#define LAMBAROLELOW 				_pa7 = 1*/

#define ZeroCrossingRead			_pa0

#define PTM_CLEAR_FLAG()			_ptmaf = 0

#define TIMER_PERIOD				200

#define BUTTON1LONGPRESSTIME		100
#define BUTTON2LONGPRESSTIME		100
#define BUTTON3LONGPRESSTIME		100
#define BUTTON4LONGPRESSTIME		100

#define BUTTONPOSITIVEDEBOUNCE		2

#define TIMERDK						5

//#define IR_ACTIVE