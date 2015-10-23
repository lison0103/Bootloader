#ifndef __FATFS_H
#define __FATFS_H

#include "ff.h"  
#include "exfuns.h"

#include "malloc.h" 
#include "iap.h"
#include "delay.h"
#include "usart.h"

void Fatfs_init(void);
u8 isFileExist(char *filename);
u8 UpdateApp(void);
u8 DeleteFile(void);
#endif