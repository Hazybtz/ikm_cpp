#include <iostream>
#include <vector>
#include <string>
#include <conio.h> //Для функций _kbhit() и _getch()
#include <windows.h> //Для управления консоли
#include "header.h"

int main() 
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 2); //Цвет текста в консоле - зеленый

    //Список уровней
    std::vector<Level> levels = {
        {
            {
                "###############",
                "#             #",
                "#  o          #",
                "#      П      #",
                "#             #",
                "#      @      #",
                "#             #",
                "###############"
            },
            {
                "###############",
                "#             #",
                "#  o          #",
                "#      П      #",
                "#             #",
                "#      @      #",
                "#             #",
                "###############"
            }, 
            7, 5, 
            7, 5
        },
        {
            {
                "###############",
                "#             #",
                "#    o        #",
                "#    #####    #",
                "#    # П      #",
                "#    # П      #",
                "#     @       #",
                "#    #####    #",
                "#    o        #",
                "###############"
            },
            {   "###############",
                "#             #",
                "#    o        #",
                "#    #####    #",
                "#    # П      #",
                "#    # П      #",
                "#     @       #",
                "#    #####    #",
                "#    o        #",
                "###############"
            },
            6, 6, 
            6, 6
        }
    };

    size_t currLevel = 0; //Номер уровня
    while (true) 
    {
        showMenu();
        char choice = _getch();
        switch (choice) 
        {
            case '1': 
                for (; currLevel < levels.size(); currLevel++) 
                {
                    if (!playLevel(levels[currLevel], currLevel))
                    {
                        break;
                    }
                } 
                if (currLevel == levels.size())
                {
                    clearScreen();
                    std::cout << "\n\nВы прошли все уровени. Нажмите любую клавишу чтобы выйти из игры.";
                    _getch();
                    return 0;
                }
                break;
            case '2': showRules(); break;
            case '3': showControls(); break;
            case '4': return 0; 
            default: continue;
        }
    }
}