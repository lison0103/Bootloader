#ifndef __TIME_DISPLAY_H
#define __TIME_DISPLAY_H

#include "ZTM.h"

//void time_display_oneline(u16 dw,u16 x,u16 y, u8 *tb, u8 set_bit);
void time_display(u16 dw,u16 tw,u8 *tb);
u32 GetDate(u8 *tb);


#endif