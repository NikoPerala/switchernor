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
    MOUSE_PRESS_NONE,
    MOUSE_PRESS_CLICK,
    MOUSE_PRESS_LONG
};

typedef unsigned long long time;

time millis() {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    
    return (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
}

int main(void)
{
    int i, hovered, input_selected = -1;
    
    Vector2 mouse_pos;
    time mouse_l_button_pressed = 0;
    uint8_t mouse_l_button_press_type = MOUSE_PRESS_NONE;
    uint16_t long_press_interval = 500;

    char dbgmsg[100];

    time current_time;

    InitWindow(W_WIDTH, W_HEIGHT, W_TITLE);
    SetTargetFPS(60);

    IO ios[8];
    int8_t input_connected_to[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };

    for (i = 0; i < IO_AMOUNT; ++i){
        io_initialize(&ios[i], (Vector2) { IOS_OFFSET_X + (IO_BLOCK_SIZE + IOS_MARGINAL) * i, 200 }, i + 1, ColorFromHSV(360 / IO_AMOUNT * i, 1, 1));
    }

    Color bgColor = (Color) { 0x40, 0x6f, 0x6f, 0xff };

    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(bgColor);


        current_time = millis();
        mouse_pos = GetMousePosition();
  
        if (IsMouseButtonPressed(0) && !mouse_l_button_pressed) mouse_l_button_pressed = millis();
        else if (mouse_l_button_pressed && current_time - mouse_l_button_pressed >= long_press_interval) {
           mouse_l_button_press_type = MOUSE_PRESS_LONG;
           mouse_l_button_pressed = 0;
           sprintf(dbgmsg, "LONG PRESS %d", mouse_l_button_press_type);
        }
        else if (mouse_l_button_pressed && IsMouseButtonReleased(0)) {
           mouse_l_button_press_type = MOUSE_PRESS_CLICK;
           mouse_l_button_pressed = 0;
           sprintf(dbgmsg, "CLICK %d", mouse_l_button_press_type);
        }
        else if (!mouse_l_button_pressed && mouse_l_button_press_type) mouse_l_button_press_type = 0;
        
        DrawText(dbgmsg, 20, 20, 20, RED);

        for (i = 0; i < IO_AMOUNT; ++i){
            if (button_hovered(&ios[i].button, mouse_pos) && mouse_l_button_press_type != MOUSE_PRESS_NONE){ 
                switch (mouse_l_button_press_type){ 
                    case MOUSE_PRESS_CLICK:
                        if (input_selected < 0) {
                            input_selected = i;
                            ios[i].input_led.state = 1;
                        } else {
                            ios[i].output_led.state = 1;
                            ios[i].output_led.color = ios[input_selected].input_led.color;
                            input_connected_to[input_selected] = i;
                            input_selected = -1;
                        }
                        break;
                    case MOUSE_PRESS_LONG:
                        ios[i].input_led.state = 0;
                        if (input_connected_to[i] >= 0){
                            ios[input_connected_to[i]].output_led.state = 0;
                        }
                        input_selected = -1;
                        break;
                }
            }
            io_display(&ios[i]);
        }

        EndDrawing();
    }

    return 0;
}
