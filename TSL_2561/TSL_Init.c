#include "TSL_Init.h"


void TSL2561_Init(void) {
    // Bat cam bien 
    I2C1_WriteData(TSL2561_ADDR, TSL2561_CMD | TSL2561_CTRL, 0x03); // POWER ON
    
    // Cau hinh thoi gian tich hop (402ms)
    I2C1_WriteData(TSL2561_ADDR, TSL2561_CMD | TSL2561_TIMING, 0x02);
}

float TSL2561_ReadLight(void) {
    uint8_t ch0_low, ch0_high;
    uint8_t ch1_low, ch1_high;
    uint16_t ch0, ch1;
    float ratio, lux;

    // �?c d? li?u t? thanh ghi DATA0 (k�nh �nh s�ng kh? ki?n + h?ng ngo?i)
    I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA0_LOW, &ch0_low, 1);
    I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA0_HIGH, &ch0_high, 1);
    ch0 = (ch0_high << 8) | ch0_low;

    // �?c d? li?u t? thanh ghi DATA1 (k�nh �nh s�ng h?ng ngo?i)
    I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA1_LOW, &ch1_low, 1);
    I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA1_HIGH, &ch1_high, 1);
    ch1 = (ch1_high << 8) | ch1_low;

    // Neu gia tri kenh CH0, lux = 0
    if (ch0 == 0) {
        return 0.0;
    }

    // Tinh ratio (CH1/CH0)
    ratio = (float)ch1 / (float)ch0;

    if (ratio <= 0.50) {
        lux = 0.0304 * ch0 - 0.062 * ch0 * pow(ratio, 1.4);
    } else if (ratio <= 0.61) {
        lux = 0.0224 * ch0 - 0.031 * ch1;
    } else if (ratio <= 0.80) {
        lux = 0.0128 * ch0 - 0.0153 * ch1;
    } else if (ratio <= 1.30) {
        lux = 0.00146 * ch0 - 0.00112 * ch1;
    } else {
        lux = 0.0; // Ngoai dai do 40000 lux
    }

    // Điều chỉnh theo thời gian phơi sáng và hệ số khuếch đại
    lux /= (INTEGRATION_TIME_SCALE_10 * GAIN_SCALE);

    return lux;
}

uint16_t Read_Chanel0(void)
{
	uint8_t ch0_low, ch0_high;
	
	I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA0_LOW, &ch0_low, 1);
    I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA0_HIGH, &ch0_high, 1);
    
	return (ch0_high << 8) | ch0_low;
}

uint16_t Read_Chanel1(void)
{
	uint8_t ch1_low, ch1_high;
	
	I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA1_LOW, &ch1_low, 1);
    I2C1_ReadData(TSL2561_ADDR, TSL2561_CMD | TSL2561_DATA1_HIGH, &ch1_high, 1);
    
	return (ch1_high << 8) | ch1_low;
}
