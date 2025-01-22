#include "my_gui.h"
#include "lvgl.h"
#include "usart.h"

lv_obj_t *menu_obj1;
lv_obj_t *menu_obj2;
lv_obj_t *menu_obj3;
lv_obj_t *menu_obj4;

const lv_font_t *font;
lv_obj_t *imgbtn1;
lv_obj_t *imgbtn2;
lv_obj_t *led;

void menu_event_cb(lv_event_t *e)
{
		lv_event_code_t code = lv_event_get_code(e);
		if(code == LV_EVENT_CLICKED)
		LED_Disp();
		UART1_SendString((char*)"LED\r\n");
}
void event_cb(lv_event_t *e)
{
		lv_event_code_t code = lv_event_get_code(e);
		if(code == LV_EVENT_CLICKED)
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		lv_led_toggle(led);
		// 获取当前亮度
		uint8_t brightness = lv_led_get_brightness(led);

		// 判断 LED 是否开启（亮度大于 0）
		UART1_SendInt(brightness);
		if (brightness > 80) 
		{
				UART1_SendString((char*)"LED ON\r\n");
		} 
		else 
		{
				UART1_SendString((char*)"LED OFF\r\n");
		}
}
void Next_event_cb(lv_event_t *e)
{	
		lv_event_code_t code = lv_event_get_code(e);
		if(code == LV_EVENT_CLICKED)
		menu();
		UART1_SendString((char*)"menu\r\n");
}

void menu(void)
{
	lv_obj_clean(lv_scr_act());
	//声明图片
	LV_IMG_DECLARE(light1);
	LV_IMG_DECLARE(buzzer);
	
	//创建框架
	menu_obj1 = lv_obj_create(lv_scr_act());
	menu_obj2 = lv_obj_create(lv_scr_act());
	menu_obj3 = lv_obj_create(lv_scr_act());
	menu_obj4 = lv_obj_create(lv_scr_act());
	//obj1
	lv_obj_set_size(menu_obj1, 120, 150);
	lv_obj_set_align(menu_obj1, LV_ALIGN_TOP_LEFT);
	//创建图标摁键
	imgbtn1 = lv_imgbtn_create(menu_obj1);
	lv_obj_align_to(imgbtn1, menu_obj1, LV_ALIGN_CENTER, 25, 30);
	//设置图片
	lv_imgbtn_set_src(imgbtn1, LV_IMGBTN_STATE_RELEASED,&light1, NULL, NULL);
	lv_obj_set_size(imgbtn1, 120, 150);
	lv_obj_add_event_cb(imgbtn1, menu_event_cb, LV_EVENT_CLICKED, NULL);
	//obj2
	lv_obj_set_size(menu_obj2, 120, 150);
	lv_obj_set_align(menu_obj2, LV_ALIGN_TOP_RIGHT);
	//创建图标摁键
	imgbtn2 = lv_imgbtn_create(menu_obj2);
	lv_obj_align_to(imgbtn2, menu_obj1, LV_ALIGN_CENTER, 0, 0);
	//设置图片
	lv_imgbtn_set_src(imgbtn2, LV_IMGBTN_STATE_RELEASED,&buzzer, NULL, NULL);
	lv_obj_set_size(imgbtn2, 120, 150);
	
	//obj3
	lv_obj_set_size(menu_obj3, 120, 150);
	lv_obj_align_to(menu_obj3, menu_obj1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
	
	//obj4
	lv_obj_set_size(menu_obj4, 120, 150);
	lv_obj_align_to(menu_obj4, menu_obj2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

void LED_Disp(void)
{
		font = &lv_font_montserrat_14;
		
		lv_obj_clean(lv_scr_act());
		/* 创建LVGL对象 */
		lv_obj_t *btn = lv_btn_create(lv_scr_act());
		lv_obj_set_size(btn, 80, 50);
		lv_obj_center(btn);
		lv_obj_add_event_cb(btn, event_cb, LV_EVENT_CLICKED, NULL);
	
		lv_obj_t *menu_btn = lv_btn_create(lv_scr_act());
		lv_obj_set_size(menu_btn, 80, 50);
		lv_obj_align_to(menu_btn, btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
		lv_obj_add_event_cb(menu_btn, Next_event_cb, LV_EVENT_CLICKED, NULL);
	
		lv_obj_t *label_menu = lv_label_create(menu_btn);
		lv_obj_align(label_menu, LV_ALIGN_CENTER, 0, 0);
		lv_obj_set_style_text_font(label_menu, font, LV_STATE_DEFAULT);
		lv_label_set_text(label_menu, "RE");
		
	
	
		/* 创建LED部件 */
		led = lv_led_create(lv_scr_act());
		lv_obj_set_size(led, 50, 50);
	//	lv_obj_set_style_bg_color(led, lv_color_hex(0x359a35), LV_PART_MAIN);
		lv_led_set_color(led, lv_color_hex(0x359a35));
		lv_obj_align_to(led, btn, LV_ALIGN_OUT_TOP_MID, 0, -10);
		lv_led_on(led);
		
}

