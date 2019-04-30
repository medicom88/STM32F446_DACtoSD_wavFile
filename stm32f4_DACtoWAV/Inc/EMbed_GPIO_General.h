#ifndef __EMBED_GPIO_GENERAL_H__
#define __EMBED_GPIO_GENERAL_H__


#define LONGPRESS		2000	//2000ms
#define SHORTPRESS	50		//50ms

#define HIGH	1
#define LOW		0

#define GPIO_SW_PORT		GPIOE
#define GPIO_SW_BT1			GPIO_PIN_2
#define GPIO_SW_BT2			GPIO_PIN_3
#define GPIO_SW_BT3			GPIO_PIN_4
#define GPIO_SW_BT4			GPIO_PIN_5
#define GPIO_SW_BT5			GPIO_PIN_6

#define GPIO_LED_PORT		GPIOF
#define GPIO_LED_1			GPIO_PIN_6
#define GPIO_LED_2			GPIO_PIN_7
#define GPIO_LED_3			GPIO_PIN_8
#define GPIO_LED_4			GPIO_PIN_9
#define GPIO_LED_5			GPIO_PIN_10

#define GPIO_DLY				300

#define LCD_IMU_STATE_ON 		0
#define LCD_IMAGE_STATE_ON		1

#define SAMPLE_IMAGE	0
#define EMBED_IMAGE		1
#define STM_IMAGE		2
#define IMAGE_DONE		3

typedef struct
{
	unsigned int u_1ms;
	unsigned int u_10ms;
	unsigned int u_100ms;
	unsigned int u_1s;
}TICK_TypeDef;

extern TICK_TypeDef hsystick;


typedef struct
{
	unsigned int 	uiDelaycount;			//키 눌린 시간 카운트
	unsigned char	ucLongpress;			//키 길게 눌려짐
	unsigned char	ucLongpressflag;	//키 처음 길게 눌렸을때 
	unsigned char	ucPressed;				//키 첫음 눌림
	unsigned char	ucState;					//키 상태
	unsigned char	ucValue;					//키 값
	
}BUTTON_TypeDef;


extern BUTTON_TypeDef hButton;

void GPIO_BT_READ(BUTTON_TypeDef *hBT);
void BT_SHORT_Event(unsigned char bt_state);
void BT_LONG_Event_test();
void BT_TICK_FUNC(BUTTON_TypeDef *hBT);
void LED_test();

#endif /* __EMBED_GPIO_GENERAL_H__ */
