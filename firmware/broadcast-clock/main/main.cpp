#include <memory.h>
#include <time.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/gpio.h>
#include <driver/ledc.h>
#include <hal/gpio_types.h>

#define DIAL_SIN GPIO_NUM_33
#define DIAL_SOUT GPIO_NUM_32
#define DIAL_GSCLK GPIO_NUM_27
#define DIAL_SCLK GPIO_NUM_26
#define DIAL_XLAT GPIO_NUM_25
#define DIAL_DCPRG GPIO_NUM_23
#define DIAL_VPRG GPIO_NUM_19
#define DIAL_BLANK GPIO_NUM_18

void delay() {
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
    __asm__ __volatile__ ("nop");
}

void set_dot_correction() {

    gpio_set_level( DIAL_SOUT, 0 );
    gpio_set_level( DIAL_GSCLK, 0 );
    gpio_set_level( DIAL_XLAT, 0 );
    gpio_set_level( DIAL_SCLK, 0 );

    //gpio_set_level( DIAL_BLANK, 0 );
    gpio_set_level( DIAL_VPRG, 1 );
    delay();

    for( int i = 0; i < 5; i++ ) {
        for( int j = 0; j < 16; j++ ) {
            const int led_id = 60 - ( ( ( i * 16 ) + j ) - 20 );
            for( int k = 0; k < 6; k++ ) {
                delay();
                gpio_set_level( DIAL_SOUT, 0 );
                delay();
                gpio_set_level( DIAL_SCLK, 1 );
                delay();
                gpio_set_level( DIAL_SCLK, 0 );
                //gpio_set_level( DIAL_BLANK, 1 );
            }
        }
        gpio_set_level( DIAL_XLAT, 1 );
        delay();
        gpio_set_level( DIAL_XLAT, 0 );
        delay();
        //gpio_set_level( DIAL_BLANK, 0 );
        //delay();
    }
    gpio_set_level( DIAL_VPRG, 1 );
}

void update_dial( int seconds ) {

    gpio_set_level( DIAL_SOUT, 0 );
    gpio_set_level( DIAL_GSCLK, 0 );
    gpio_set_level( DIAL_XLAT, 0 );
    gpio_set_level( DIAL_SCLK, 0 );

    //gpio_set_level( DIAL_BLANK, 0 );
    gpio_set_level( DIAL_VPRG, 1 );
    delay();
    gpio_set_level( DIAL_VPRG, 0 );

    for( int i = 0; i < 5; i++ ) {
        for( int j = 0; j < 16; j++ ) {
            const int led_id = 60 - ( ( ( i * 16 ) + j ) - 20 );
            for( int k = 0; k < 12; k++ ) {
                delay();
                //gpio_set_level( DIAL_SOUT, ( ( k < 3 ) ) ? 1 : 0 );                
                if( k == 2 && led_id > seconds ) {
                    gpio_set_level( DIAL_SOUT, 1 );
                }
                else {
                    gpio_set_level( DIAL_SOUT, 0 );
                }
                delay();
                gpio_set_level( DIAL_SCLK, 1 );
                delay();
                gpio_set_level( DIAL_SCLK, 0 );
                //gpio_set_level( DIAL_BLANK, 1 );
            }
        }
        gpio_set_level( DIAL_XLAT, 1 );
        delay();
        gpio_set_level( DIAL_XLAT, 0 );
        delay();
        //gpio_set_level( DIAL_BLANK, 0 );
        //delay();
    }
    gpio_set_level( DIAL_VPRG, 1 );
}

extern "C" void app_main() {
    
    int seconds = 0;

    gpio_set_direction( DIAL_GSCLK, GPIO_MODE_OUTPUT );
    gpio_set_direction( DIAL_SOUT, GPIO_MODE_OUTPUT );
    gpio_set_direction( DIAL_VPRG, GPIO_MODE_OUTPUT );
    gpio_set_direction( DIAL_SCLK, GPIO_MODE_OUTPUT );
    gpio_set_direction( DIAL_BLANK, GPIO_MODE_OUTPUT );

    set_dot_correction();
    update_dial( 0 );

    while ( true ) {
        vTaskDelay( 1 );
        gpio_set_level( DIAL_BLANK, 1 );
        gpio_set_level( DIAL_BLANK, 1 );
        time_t now = time( NULL );
        struct tm timeinfo;
        localtime_r( &now, &timeinfo );
        if( seconds != timeinfo.tm_sec ) {
            seconds = timeinfo.tm_sec;
            ESP_LOGI( "main", "Seconds: %d", seconds );
            update_dial( seconds );
        }
        gpio_set_level( DIAL_BLANK, 0 );
        for( int l = 0; l < 4096; l++) {
            gpio_set_level( DIAL_GSCLK, 1 );
            delay();
            gpio_set_level( DIAL_GSCLK, 0 );
            delay();
        }
    }
    
}