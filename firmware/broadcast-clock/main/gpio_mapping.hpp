#ifndef GPIO_MAPPING_HPP
#define GPIO_MAPPING_HPP

#include <driver/gpio.h>

// Piezo transducer GPIO
#define PIEZO_TRANSDUCER GPIO_NUM_5

// Dial GPIO mapping
#define DIAL_SIN    GPIO_NUM_33
#define DIAL_SOUT   GPIO_NUM_32
#define DIAL_GSCLK  GPIO_NUM_27
#define DIAL_SCLK   GPIO_NUM_26
#define DIAL_XLAT   GPIO_NUM_25
#define DIAL_DCPRG  GPIO_NUM_23
#define DIAL_VPRG   GPIO_NUM_19
#define DIAL_BLANK  GPIO_NUM_18
#define DIAL_XERR   GPIO_NUM_39

// Dot matrix GPIO mapping
#define DISP_SPI_CS GPIO_NUM_15
#define DISP_SPI_CLK GPIO_NUM_14
#define DISP_SPI_MOSI GPIO_NUM_13
#define DISP_SPI_MISO GPIO_NUM_12

// I2C GPIO mapping
#define I2C_SCL GPIO_NUM_22
#define I2C_SDA GPIO_NUM_21

#endif // GPIO_MAPPING_HPP