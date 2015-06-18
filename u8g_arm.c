#include "u8g_arm.h"
#include "Common.h"
#include "PreenFM.h"

#define _CS  GPIO_Pin_6  // PB 6
#define _DC  GPIO_Pin_7  // PB 7
#define _RST GPIO_Pin_10 // PC 10 
#define _DO  GPIO_Pin_15 // PB 15 [DATA/MOSI]
#define _CLK GPIO_Pin_10 // PB 10 [CLK]


extern void SPI2_Config();


////////////////////// delay : 

void u8g_Delay(uint16_t val)
{
  PreenFM2_uDelay(1000UL*(uint32_t)val);
}

void u8g_MicroDelay(void)
{
  PreenFM2_uDelay(1);
}

void u8g_10MicroDelay(void)
{
  PreenFM2_uDelay(10);
}


////////////////////// com : 


uint8_t u8g_com_hw_sh1106_128x64(u8g_t *u8g, uint8_t msg, uint8_t arg_val, void *arg_ptr)
{
  switch(msg)
  {
    case U8G_COM_MSG_STOP:
      break;
    
    case U8G_COM_MSG_INIT:

      SPI2_Config();
      PreenFM2_uDelay(10);  
      GPIOC->BSRRL = _RST; 
      PreenFM2_uDelay(10); 
      GPIOC->BSRRH = _RST;  
      PreenFM2_uDelay(10); 
  

      break;
    
    case U8G_COM_MSG_ADDRESS:                               
      arg_val ? GPIOB->BSRRL = _DC : GPIOB->BSRRH = _DC;   // set/reset (datamode / cmd)
      PreenFM2_uDelay(1);  
     break;

    case U8G_COM_MSG_CHIP_SELECT:
      arg_val ? GPIOB->BSRRH = _CS : GPIOB->BSRRL = _CS;   // reset/set
      PreenFM2_uDelay(1); 
      break;
      
    case U8G_COM_MSG_RESET:
      arg_val ? GPIOC->BSRRL = _RST : GPIOC->BSRRH = _RST;  // set/reset
      PreenFM2_uDelay(1); 
      break;
      
    case U8G_COM_MSG_WRITE_BYTE:
      //while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
      SPI_I2S_SendData(SPI2, arg_val);
      PreenFM2_uDelay(1); 
      break;
    
    case U8G_COM_MSG_WRITE_SEQ:
    case U8G_COM_MSG_WRITE_SEQ_P:
      {
        register uint8_t *ptr = (uint8_t*)arg_ptr;
        while( arg_val > 0 )
        { 
           //while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
           SPI_I2S_SendData(SPI2, *ptr++);
           PreenFM2_uDelay(1); 
           arg_val--;
        }
      }
      break;
  }
  return 1;
}
