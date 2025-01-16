#ifndef HEADER_H
#define HEADER_H

//Символы для игры
const char WALL = '#';
const char BOX = 'П';
const char PLAYER = '@';
const char TARGET = 'o';
const char EMPTY = ' ';

const int WIDTH = 15; //Максимально допустимая ширена игрового поля
const int HEIGHT = 10; //Максимально допустимая высота игрового поля

//Структура уровня
struct Level 
{
    std::vector<std::string> map;      //Текущая карта 
    std::vector<std::string> start_map; //Начальная карта
    int playerX, playerY;    //Координаты игрока
    int startX, startY;      //Начальные координаты игрока
};

void clearScreen();
void draw(const Level& level, int levelNumber);
bool checkWin(const Level& level);
void resetLevel(Level& level);
void movePlayer(Level& level, int dx, int dy);
bool playLevel(Level& level, int levelNumber);
void showMenu();
void showRules(); 
void showControls(); 

#endif