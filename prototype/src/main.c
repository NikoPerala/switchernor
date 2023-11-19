#include <raylib.h>

#include <sys/time.h>

#include "gui_utils.h"

#define W_WIDTH 1000
#define W_HEIGHT 800
#define W_TITLE "Switchernor virtual prototype"

#define IO_AMOUNT 8
#define IOS_OFFSET_X 100
#define IOS_MARGINAL 20

enum BUTTON_PRESS_TYPES {
    NONE,
    CLICK,
    LONG
};

unsigned long long millis() {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    
    return (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
}

int main(void)
{
    int i, hovered, input_selected = -1;
    Vector2 mouse;

    InitWindow(W_WIDTH, W_HEIGHT, W_TITLE);
    SetTargetFPS(60);

    IO ios[8];

    for (i = 0; i < IO_AMOUNT; ++i){
        io_initialize(&ios[i], (Vector2) { IOS_OFFSET_X + (IO_BLOCK_SIZE + IOS_MARGINAL) * i, 200 }, i + 1, ColorFromHSV(360 / IO_AMOUNT * i, 1, 1));
    }
     
    while (!WindowShouldClose()){
        BeginDrawing();

        mouse = GetMousePosition();

        for (i = 0; i < IO_AMOUNT; ++i){ 
            if (button_hovered(&ios[i].button, mouse) && IsMouseButtonPressed(0)){
                if (input_selected < 0) {
                    input_selected = i;
                    ios[i].input_led.state = 1;
                } else {
                    ios[i].output_led.state = 1;
                    ios[i].output_led.color = ios[input_selected].input_led.color;
                    input_selected = -1;
                }
            }
            io_display(&ios[i]);
        }

        EndDrawing();
    }

    return 0;
}
