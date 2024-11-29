#include <iostream>
#include <iomanip>
#include"Chess.h"
#include <Windows.h>
using namespace std;
void printLine(string text, int width) {
    cout << ". " << setw(width) << left << text << " ." << endl;
}

void printChessTitle() 
{
    printLine("           ^?YYJJYP57.  .75GGG57:  ^JPGGPJ~  ^JPGGP55555GG~    .755YY5PJ:    .!Y5YY5PY^    ", 54);
    printLine("        :J#&Y^.   !@@.    J@@@~     ^@@@Y     ^@@@5.....Y@:   ?&@J.  .Y@!   7#@Y.  .J@7    ", 54);
    printLine("      7&@#^       !P     B@@P      J@@@^     ?@@@^   .: ^   ^@@@7     ?:  :@@@?     7:     ", 54);
    printLine("      ?@@@~              !@@@5~!!!!~#@@G      B@@#~~~7#!     .P@@@BJ~.     .P@@@BY~.       ", 54);
    printLine("     .#@@B               P@@&??????5@@@7     ~@@@Y!77B#        ~YB@@@#J.     ^JG@@@#Y.     ", 54);
    printLine("     .#@@B         ~.   :&@@Y      5@@#.     5@@#.   .^ ^. .^     :J@@@7  ^     :J@@@?     ", 54);
    printLine("     !&@@?      ^PG    ?@@@^     :&@@Y     .&@@Y      ?B. ^@!     :@@B: :@7     .&@#^      ", 54);
    printLine("       :JB&GJ77?5BB~  ^7#@@&7.  .~5@@@Y^  .~5@@@5JJJJJP@J  ~##Y777JGG?.  ^B#5?77JGG?.      ", 54);
    printLine("          :^~~~~^.    ^^^^^^^.  .^^^^^^^  :^^^^^^~^^^^^^.    :^~~~^.       :^~~~^:         ", 54);
    cout << endl;
}
              

void printButton(string text, int width) {
    int padding = (width - text.length()) / 2;
    cout << ". " << setw(padding) << "" << text << setw(padding) << "" << " ." << endl;
}

void printButtons() {
    cout << ".........................................................." << endl;
    printButton("PLAY", 54);
    cout << ".........................................................." << endl;
    cout << ".........................................................." << endl;
    printButton("EXIT", 54);
    cout << ".........................................................." << endl;
}

void processMouseEvent(MOUSE_EVENT_RECORD mouseEvent, Chess& C) {
    if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
        int mouseX = mouseEvent.dwMousePosition.X;
        int mouseY = mouseEvent.dwMousePosition.Y;
        if (mouseX >= 10 && mouseX <= 50 && mouseY >= 10 && mouseY <= 12) {
            system("cls"); 
            C.play(); 
        }
        else if (mouseX >= 10 && mouseX <= 50 && mouseY >= 14 && mouseY <= 16) {
            exit(0);  
        }
    }
}

void enableMouseInput(HANDLE hInput) {
    DWORD prevMode;
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput, prevMode | ENABLE_MOUSE_INPUT);
}

int main() {
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    enableMouseInput(hInput);

    Chess C;

    DWORD numEventsRead;
    INPUT_RECORD inputRecord;
    printChessTitle();
    printButtons();
    while (true) 
    {
        ReadConsoleInput(hInput, &inputRecord, 1, &numEventsRead);
        if (inputRecord.EventType == MOUSE_EVENT) {
            processMouseEvent(inputRecord.Event.MouseEvent, C);
        }
    }

    return 0;
}