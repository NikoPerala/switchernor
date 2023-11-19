#ifndef SWITCHERNOR_GUI_UTILS_H
#define SWITCHERNOR_GUI_UTILS_H

#include <raylib.h>
#include <stdint.h>
#include <stdio.h>

#define LED_SIZE 20
#define IO_BLOCK_SIZE LED_SIZE * 4

#define BUTTON_COLOR (Color) { 0x77, 0x77, 0x77, 0xff }
#define BUTTON_HIGHLIGHT_COLOR (Color) { 0x97, 0x97, 0x97, 0xff }

typedef struct led {
    Vector2 position;
    char name[16];
    uint8_t state : 1;
    Color color;
} Led;

typedef struct button {
    Vector2 position;
    Vector2 size;
    Color color;
} Button;

typedef struct io {
    Vector2 position;
    Button button;
    Led input_led;
    Led output_led;
} IO;

int button_hovered(Button *btn, Vector2 pos);
void button_display(Button *btn);
void io_initialize(IO *io, Vector2 position, int index, Color color);
void io_display(IO *io);

void led_display(Led *led);

#endif // SWITCHERNOR_GUI_UTILS_H
