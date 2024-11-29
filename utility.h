#pragma once
#include<Windows.h>
enum color { White, Black, NoColor };

inline void getrowcolbyleftclick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.EventType == MOUSE_EVENT && InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = (InputRecord.Event.MouseEvent.dwMousePosition.X) / 3; 
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}

inline void gotoRowCol(int row, int col)
{
    COORD coord;
    coord.X = col;
    coord.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}