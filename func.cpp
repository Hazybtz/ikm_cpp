#include <iostream>
#include <vector>
#include <string>
#include <conio.h> //Для функций _kbhit() и _getch()
#include <windows.h> //Для управления консоли
#include "header.h"

//Очистка консоли
void clearScreen() 
{
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

//Вывод текущего уровня
void draw(const Level& level, int levelNumber) 
{
    clearScreen();
    std::cout << "Уровень " << levelNumber + 1 << "\n\n";
    for (const auto& row : level.map) 
    {
        std::cout << row << std::endl;
    }
}

//Проверка победы
bool checkWin(const Level& level) 
{
    for (size_t x = 0; x < level.map.size(); x++) 
    {
        for (size_t y = 0; y < level.map[x].size(); y++) 
        {
            if (level.start_map[x][y] == TARGET) 
            {
                if (level.map[x][y] != BOX) 
                {
                    return false;
                }

            }
        }
    }
    return true;
}

//Сброс уровня до стартого значения
void resetLevel(Level& level) 
{
    level.map = level.start_map;  
    level.playerX = level.startX;
    level.playerY = level.startY;
}

//Перемещение игрока
void movePlayer(Level& level, int dx, int dy) 
{
    int newX = level.playerX + dx; //Новая позиция игрока по X 
    int newY = level.playerY + dy; //Новая позиция игрока по Y

    //Проверка выхода за границы карты
    if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT) return;

    char& targetCell = level.map[newY][newX]; //Символ позиции куда встает игрок

    //Если символ позиции - стена, движение невозможно
    if (targetCell == WALL) return;

    //Если символ позиции - ящик, двигаем его
    if (targetCell == BOX) 
    {
        int boxNewX = newX + dx; //Новая позиция ящика по X 
        int boxNewY = newY + dy; //Новая позиция ящика по Y

        //Проверка выхода за границы карты
        if (boxNewX < 0 || boxNewX >= WIDTH || boxNewY < 0 || boxNewY >= HEIGHT) return;

        char& boxTargetCell = level.map[boxNewY][boxNewX]; //Символ позиции куда встает ящик

        //Двигаем ящик, если за ящиком пусто или наша цель
        if (boxTargetCell == EMPTY || boxTargetCell == TARGET) 
        {
            boxTargetCell = BOX; 
            targetCell = (targetCell == TARGET) ? TARGET : EMPTY; 

        } 
        else 
        {
            return; //Если за ящиком стена или другой ящик, движение невозможно
        }
    }

    //Перемещение игрока
    char& currentCell = level.map[level.playerY][level.playerX];
    currentCell = (currentCell == PLAYER && level.start_map[level.playerY][level.playerX] == TARGET) ? TARGET : EMPTY;
    level.playerX = newX;
    level.playerY = newY;
    targetCell = PLAYER;
}

//Осноной игровой цикл
bool playLevel(Level& level, int levelNumber) 
{
    draw(level, levelNumber);
    while (true) 
    {
        if (checkWin(level)) 
        {
            draw(level, levelNumber); //Финальное состояние урованя
            std::cout << "\nВы прошли " << levelNumber + 1 << " уровень. Нажмите любую клавишу чтобы продолжить.";
            _getch(); //Ожидание нажатия клавиши
            return true;
        }

        if (_kbhit()) //Если нажата клавиша
        {
            char key = _getch(); 
            switch (key) 
            {
                case 'w': movePlayer(level, 0, -1); break;
                case 'W': movePlayer(level, 0, -1); break;
                case 'Ц': movePlayer(level, 0, -1); break;
                case 'ц': movePlayer(level, 0, -1); break;
                case 's': movePlayer(level, 0, 1); break;
                case 'S': movePlayer(level, 0, 1); break;
                case 'ы': movePlayer(level, 0, 1); break;
                case 'Ы': movePlayer(level, 0, 1); break;
                case 'a': movePlayer(level, -1, 0); break;
                case 'A': movePlayer(level, -1, 0); break;
                case 'ф': movePlayer(level, -1, 0); break;
                case 'Ф': movePlayer(level, -1, 0); break;
                case 'd': movePlayer(level, 1, 0); break;
                case 'D': movePlayer(level, 1, 0); break;
                case 'в': movePlayer(level, 1, 0); break;
                case 'В': movePlayer(level, 1, 0); break;
                case 'r': resetLevel(level); break; 
                case 'R': resetLevel(level); break; 
                case 'к': resetLevel(level); break; 
                case 'К': resetLevel(level); break; 
                case 'q': return false; 
                case 'Q': return false; 
                case 'й': return false; 
                case 'Й': return false; 
            }
            draw(level, levelNumber);   
        }
    }
}

//Гланое меню
void showMenu() 
{
    clearScreen();
    std::cout << "Добро пожаловать в игру Сокобан!\n";
    std::cout << "1. Играть\n";
    std::cout << "2. Правила\n";
    std::cout << "3. Управление\n";
    std::cout << "4. Выход\n";
    std::cout << "Выберите действие: ";
}

//Правила игры
void showRules() 
{
    clearScreen();
    std::cout << "Правила игры:\n";
    std::cout << "1. Цель игры: игрок (@) должен переместить все ящики (П) на цели (o).\n";
    std::cout << "2. Ты можешь толкать только один ящик.\n";
    std::cout << "3. Ты выигрываешь, когда все ящики будут на нужном месте.\n\n";
    std::cout << "Нажмите любую клавишу, чтобы вернуться в меню.";
    _getch();
}

//Инфорипция о управлении
void showControls() 
{
    clearScreen();
    std::cout << "Управление:\n";
    std::cout << "W - Вверх\n";
    std::cout << "A - Влево\n";
    std::cout << "S - Вниз\n";
    std::cout << "D - Вправо\n";
    std::cout << "R - Перезапустить уровень\n";
    std::cout << "Q - Выйти в меню\n\n";
    std::cout << "Нажмите любую клавишу, чтобы вернуться в меню.";
    _getch();
}