#ifndef __MENU_H
#define __MENU_H


#include "sys.h"
#include "ZTM.h"
#include "key.h"
#include "iap.h"
#include "delay.h"
#include "usart.h"
#include "usb.h"
#include "fatfs.h"

#if 0

void RCC_init(void);
void Lcd_init(void);
void menu_item_display(void);
void menu_pocess(void);

#else
void RCC_init(void);
void Lcd_init(void);
void menu_pocess(void);

#endif

#endif