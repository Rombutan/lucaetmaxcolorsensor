/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include <vector>
#include <string>

using namespace std;

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"

#include "ws2812.pio.h"

#include "WS2812.cpp"
#include "ltr381.cpp"

#define IS_RGBW true
#define NUM_PIXELS 2

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
// default to pin 2 if the board doesn't have a default WS2812 pin defined
#define WS2812_PIN 2
#endif

int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("Pico Color sensor, via Luca's pain and suffering \n");
    sleep_ms(100);
    ws28121 stripfar(true, 3, 3);
    sleep_ms(100);
    ws28120 stripclose(true, 3, 2);
    sleep_ms(100);


    i2c_init(i2c0, 400 * 1000);
    printf("i2c0 init \n");
    i2c_init(i2c1, 400 * 1000);
    printf("i2c1 init \n");

    gpio_set_function(16, GPIO_FUNC_I2C);
    gpio_set_function(17, GPIO_FUNC_I2C);
    printf("first pins set \n");

    gpio_set_function(6, GPIO_FUNC_I2C);
    gpio_set_function(7, GPIO_FUNC_I2C);
    printf("next pins set \n");

    ltr3810 close;
    ltr3811 far;

    stripclose.setWhite();
    stripfar.clearAll();
    sleep_ms(100);
    stripclose.clearAll();
    stripfar.setWhite();
    sleep_ms(100);
    stripclose.setWhite();
    stripfar.clearAll();
    sleep_ms(100);
    stripclose.clearAll();
    stripfar.setWhite();
    sleep_ms(100);
    stripclose.clearAll();
    stripfar.clearAll();
    sleep_ms(200);
    stripclose.setWhite();
    stripfar.setWhite();

    uart_init(uart0, 9600);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);

    int i=0;
    while(1){
      printf("%d %d %d %d %d %d\n", close.red(), close.blue(), close.green(), far.red(), far.blue(), far.green());
    }
}
