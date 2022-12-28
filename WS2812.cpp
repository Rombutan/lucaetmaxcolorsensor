#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

struct pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class ws28120 {
    public:
        ws28120(bool pIS_RGBW, int pNUM_PIXELS, int pWS2812_PIN){
            IS_RGBW = pIS_RGBW;
            NUM_PIXELS = pNUM_PIXELS;
            WS2812_PIN = pWS2812_PIN;

            //set_sys_clock_48();
            stdio_init_all();
            printf("WS2812 using pin %d", WS2812_PIN);

            PIO pio = pio0;
            sm = pio_claim_unused_sm(pio, true);
            uint offset = pio_add_program(pio, &ws2812_program);

            ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
        }
        void set(uint8_t r, uint8_t g, uint8_t b){
            put_pixel(urgb_u32(r, g, b));
        }

        void setWhite(){
            int i = 0;
            while(i<NUM_PIXELS){
                put_pixel((uint32_t) 0xffffffff);
                i++;
            }

        }

        void setAll(uint8_t r, uint8_t g, uint8_t b){
            int i = 0;
            while(i<NUM_PIXELS){
                put_pixel(urgb_u32s(r, g, b, r));
                while(!pio_sm_is_tx_fifo_empty(pio0, sm));
                put_pixel(urgb_u32s(g, b, r, g));
                while(!pio_sm_is_tx_fifo_empty(pio0, sm));
                put_pixel(urgb_u32s(b, r, g, b));
                while(!pio_sm_is_tx_fifo_empty(pio0, sm));

                i++;
            }
        }

        void setVec(vector<pixel> pixels){
            int i = pixels.size();
            int n = 0;
            while(pixels.size() % 4 != 0){
                i++;
                pixels.push_back(pixel());
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
            }
            i=0;
            while(i<pixels.size()*3){
                put_pixel(urgb_u32s(pixels[n].r, pixels[n].g, pixels[n].b, pixels[n+1].r));
                i = i + 4;
                n++;
                while(!pio_sm_is_tx_fifo_empty(pio0, sm));
                put_pixel(urgb_u32s(pixels[n].g, pixels[n].b, pixels[n+1].r, pixels[n+1].g));
                i = i + 4;
                n++;
                while(!pio_sm_is_tx_fifo_empty(pio0, sm));
                put_pixel(urgb_u32s(pixels[n].b, pixels[n+1].r, pixels[n+1].g, pixels[n+1].b));
                i = i + 4;
                n++;
                while(!pio_sm_is_tx_fifo_empty(pio0, sm));
            }
        }

        void clearAll(){
            int i = 0;
            while(i<NUM_PIXELS){
                put_pixel(0);
                i++;
            }
        }

    private:
        uint sm;
        bool IS_RGBW;
        int NUM_PIXELS;
        int WS2812_PIN;
        static inline void put_pixel_goofy(uint32_t pixel_grb) {
            pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
        }

        static inline void put_pixel(uint32_t pixel_grb) {
            pio_sm_put_blocking(pio0, 0, pixel_grb);
        }


        static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
            return
                ((uint32_t) (r) << 8) |
                ((uint32_t) (g) << 16) |
                (uint32_t) (b);
        }

        static inline uint32_t urgb_u32s(uint8_t r, uint8_t g, uint8_t b, uint8_t x) {
            return
                ((uint32_t) (r & 0xff) << 24) |
                ((uint32_t) (g & 0xff) << 16) |
                ((uint32_t) (b & 0xff) << 8) |
                (uint32_t) (x & 0xff);
        }
};

class ws28121 {
    public:
        ws28121(bool pIS_RGBW, int pNUM_PIXELS, int pWS2812_PIN){
            IS_RGBW = pIS_RGBW;
            NUM_PIXELS = pNUM_PIXELS;
            WS2812_PIN = pWS2812_PIN;

            //set_sys_clock_48();
            stdio_init_all();
            printf("WS2812 using pin %d", WS2812_PIN);

            PIO pio = pio1;
            sm = pio_claim_unused_sm(pio, true);
            uint offset = pio_add_program(pio, &ws2812_program);

            ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
        }
        void set(uint8_t r, uint8_t g, uint8_t b){
            put_pixel(urgb_u32(r, g, b));
        }

        void setWhite(){
            int i = 0;
            while(i<NUM_PIXELS){
                put_pixel((uint32_t) 0xffffffff);
                i++;
            }

        }

        void setAll(uint8_t r, uint8_t g, uint8_t b){
            int i = 0;
            while(i<NUM_PIXELS){
                put_pixel(urgb_u32s(r, g, b, r));
                while(!pio_sm_is_tx_fifo_empty(pio1, sm));
                put_pixel(urgb_u32s(g, b, r, g));
                while(!pio_sm_is_tx_fifo_empty(pio1, sm));
                put_pixel(urgb_u32s(b, r, g, b));
                while(!pio_sm_is_tx_fifo_empty(pio1, sm));

                i++;
            }
        }

        void setVec(vector<pixel> pixels){
            int i = pixels.size();
            int n = 0;
            while(pixels.size() % 4 != 0){
                i++;
                pixels.push_back(pixel());
                pixels[i].r = 0;
                pixels[i].g = 0;
                pixels[i].b = 0;
            }
            i=0;
            while(i<pixels.size()*3){
                put_pixel(urgb_u32s(pixels[n].r, pixels[n].g, pixels[n].b, pixels[n+1].r));
                i = i + 4;
                n++;
                while(!pio_sm_is_tx_fifo_empty(pio1, sm));
                put_pixel(urgb_u32s(pixels[n].g, pixels[n].b, pixels[n+1].r, pixels[n+1].g));
                i = i + 4;
                n++;
                while(!pio_sm_is_tx_fifo_empty(pio1, sm));
                put_pixel(urgb_u32s(pixels[n].b, pixels[n+1].r, pixels[n+1].g, pixels[n+1].b));
                i = i + 4;
                n++;
                while(!pio_sm_is_tx_fifo_empty(pio1, sm));
            }
        }

        void clearAll(){
            int i = 0;
            while(i<NUM_PIXELS){
                put_pixel(0);
                i++;
            }
        }

    private:
        uint sm;
        bool IS_RGBW;
        int NUM_PIXELS;
        int WS2812_PIN;
        static inline void put_pixel_goofy(uint32_t pixel_grb) {
            pio_sm_put_blocking(pio1, 0, pixel_grb << 8u);
        }

        static inline void put_pixel(uint32_t pixel_grb) {
            pio_sm_put_blocking(pio1, 0, pixel_grb);
        }


        static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
            return
                ((uint32_t) (r) << 8) |
                ((uint32_t) (g) << 16) |
                (uint32_t) (b);
        }

        static inline uint32_t urgb_u32s(uint8_t r, uint8_t g, uint8_t b, uint8_t x) {
            return
                ((uint32_t) (r & 0xff) << 24) |
                ((uint32_t) (g & 0xff) << 16) |
                ((uint32_t) (b & 0xff) << 8) |
                (uint32_t) (x & 0xff);
        }
};