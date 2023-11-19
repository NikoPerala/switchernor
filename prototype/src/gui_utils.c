#include "gui_utils.h"
#include "string.h"

void led_display(Led *led)
{
    Color color = led->state ? led->color : BLACK;

    DrawCircleV(led->position, LED_SIZE, color);
    //if (!led->state) DrawCircleV(led->position, LED_SIZE - 3, BLACK);
    DrawText(led->name, led->position.x - 5, led->position.y - 5, 14, (Color) { 0x77, 0x77, 0x77, 0xff});
}

void io_initialize(IO *io, Vector2 position, int index, Color color)
{
    char tmpstr[16];
    float led_y = position.y + LED_SIZE;
    
    io->position = position;

    sprintf(tmpstr, "I%d", index);
    strcpy(io->input_led.name, tmpstr);

    sprintf(tmpstr, "O%d", index);
    strcpy(io->output_led.name, tmpstr);
    
    io->input_led.color = color;
    io->output_led.color = BLACK;

    io->input_led.state = 0;
    io->output_led.state = 0;
    
    io->input_led.position = 
        (Vector2) {
           position.x + LED_SIZE,
           led_y
        };

    io->output_led.position = 
        (Vector2) {
           position.x + LED_SIZE * 3,
           led_y
        };

    io->button.position = (Vector2) { position.x + LED_SIZE / 2, position.y + LED_SIZE * 2.5};
    io->button.size = (Vector2) { IO_BLOCK_SIZE - LED_SIZE, LED_SIZE };

}   

void button_display(Button *btn)
{
    DrawRectangleV(btn->position, btn->size, btn->color);
}

int button_hovered(Button *btn, Vector2 pos)
{
    int hovered = (pos.x > btn->position.x &&
            pos.x < btn->position.x + btn->size.x &&
            pos.y > btn->position.y &&
            pos.y < btn->position.y + btn->size.y
            );

    btn->color = hovered ? BUTTON_HIGHLIGHT_COLOR : BUTTON_COLOR;

    return hovered;
}

void io_display(IO *io)
{
    DrawRectangleV(io->position, (Vector2) { IO_BLOCK_SIZE, IO_BLOCK_SIZE}, (Color) { 0x18, 0x18, 0x18, 0xff});

    led_display(&io->input_led);
    led_display(&io->output_led);

    button_display(&io->button);
}
