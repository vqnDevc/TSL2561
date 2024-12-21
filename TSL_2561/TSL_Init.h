#include "stm32f10x.h"
#include "I2C.h"
#include <math.h>

#define I2C_WRITE 0
#define I2C_READ  1

#define TSL2561_ADDR  0x39 // Dia chi cua TSL2561
#define TSL2561_CMD   0x80 // Bit CMD de truy cap thanh ghi
#define TSL2561_CTRL  0x00 // Thanh ghi dieu khien (Control Register)
#define TSL2561_TIMING 0x01 // Thanh ghi th?i gian tích h?p
#define TSL2561_DATA0_LOW  0x0C // Thanh ghi ánh sáng (kênh 0, byte th?p)
#define TSL2561_DATA0_HIGH 0x0D // Thanh ghi ánh sáng (kênh 0, byte cao)

#define TSL2561_DATA1_LOW  0x0E // Thanh ghi ánh sáng (kênh 1, byte th?p)
#define TSL2561_DATA1_HIGH 0x0F // Thanh ghi ánh sáng (kênh 1, byte cao)

#define INTEGRATION_TIME_SCALE_00 0.034  // Tuong ?ng th?i gian tích h?p 13.7 ms
#define INTEGRATION_TIME_SCALE_01 0.252  // Tuong ?ng th?i gian tích h?p 101 ms
#define INTEGRATION_TIME_SCALE_10 1.0  // Tuong ?ng th?i gian tích h?p 402 ms

#define GAIN_SCALE             1.0 // Tuong ?ng m?c khu?ch d?i th?p (Low-gain)

void TSL2561_Init(void);
float TSL2561_ReadLight(void);

uint16_t Read_0(void);
uint16_t Read_1(void);
