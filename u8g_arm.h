
#ifndef _U8G_ARM_H
#define _U8G_ARM_H
 
//adjust this path:
#include "u8glib/u8g.h"
 
//main com function. 
uint8_t u8g_com_hw_sh1106_128x64(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr); 

#endif