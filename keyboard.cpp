#include "keyboard.h"

void printf(char *);

KeyboardDriver::KeyboardDriver(InterruptManager *manager)
    : InterruptHandler(0x21, manager),
      dataport(0x60),
      commandPort(0x64)
{
    while (commandPort.Read() & 0x1) //waits till we stop pressing a key
        dataport.Read();
    commandPort.Write(0xAE);                        //activate interrupts
    commandPort.Write(0x20);                        //get current state
    uint8_t status = (dataport.Read() | 1) & ~0x10; //setting leftmost bit 1 and clearing 5th bit
    commandPort.Write(0x60);                        //set state
    dataport.Write(status);

    dataport.Write(0xF4); //activates keyboard
}

KeyboardDriver::~KeyboardDriver()
{
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    if (key < 0x80) //everything after 0x80 is key release
    {
        switch (key)
        {
        case 0xFA:
            break;

        case 0x1E:
            printf("a");
            break;
        case 0x30:
            printf("b");
            break;
        case 0x2E:
            printf("c");
            break;
        case 0x20:
            printf("d");
            break;
        case 0x12:
            printf("e");
            break;
        case 0x21:
            printf("f");
            break;
        case 0x22:
            printf("g");
            break;
        case 0x23:
            printf("h");
            break;
        case 0x17:
            printf("i");
            break;
        case 0x24:
            printf("j");
            break;
        case 0x25:
            printf("k");
            break;
        case 0x26:
            printf("l");
            break;
        case 0x32:
            printf("m");
            break;
        case 0x31:
            printf("n");
            break;
        case 0x18:
            printf("o");
            break;
        case 0x19:
            printf("p");
            break;
        case 0x10:
            printf("q");
            break;
        case 0x13:
            printf("r");
            break;
        case 0x1F:
            printf("s");
            break;
        case 0x14:
            printf("t");
            break;
        case 0x16:
            printf("u");
            break;
        case 0x2F:
            printf("v");
            break;
        case 0x11:
            printf("w");
            break;
        case 0x2D:
            printf("x");
            break;
        case 0x15:
            printf("y");
            break;
        case 0x2C:
            printf("z");
            break;
        case 0x02:
            printf("1");
            break;
        case 0x03:
            printf("2");
            break;
        case 0x04:
            printf("3");
            break;
        case 0x05:
            printf("4");
            break;
        case 0x06:
            printf("5");
            break;
        case 0x07:
            printf("6");
            break;
        case 0x08:
            printf("7");
            break;
        case 0x09:
            printf("8");
            break;
        case 0x0A:
            printf("9");
            break;
        case 0x0B:
            printf("0");
            break;
        case 0x1C:
            printf("\n");
            break;
        case 0x39:
            printf(" ");
            break;
        case 0x34:
            printf(".");
            break;
        case 0x33:
            printf(",");
            break;
        case 0x35:
            printf("-");
            break;
        case 0x45:
        case 0xC5:
            break;
        default:
            char *foo = "KEYBOARD 0x00";
            char *hex = "0123456789ABCDEF";

            foo[11] = hex[(key >> 4) & 0x0F];
            foo[12] = hex[key & 0x0F];
            printf(foo);
        }
    }
    return esp;
}

//0x1E - a 0x30 - b 0x2E - c 0x20 - d 0x12 - e 0x21 - f
//0x22 - g 0x23 - h 0x17 - i 0x24 - j 0x25 - k 0x26 - l
//0x32 - m 0x31 - n 0x18 - o 0x19 - p 0x10 - q 0x13 - r
//0x1F - s 0x14 - t 0x16 - u 0x2F - v 0x11 - w 0x2D - x
//0x15 - y 0x2C - z
//0x02 - 1 0x03 - 2 0x04 - 3 0x05 - 4 0x06 - 5 0x07 - 6
//0x08 - 7 0x09 - 8 0x0A - 9 0x0B - 0
//0x1C - enter