//Autor:
//Code: Kacper Kuras
//Chessboard texture: Kacper Kuras
// 
//Piece textures taken from: 
//https://opengameart.org/content/chess-pieces-and-board-squares
//Copyright / Attribution Notice :
//JohnPablok's improved Cburnett chess set.

//Additional info:
//There is no scaling - chess must be left in 900x900 resolution

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "GameEngine.hpp"

int main() 
{
    //hide console
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    //starting game engine...
    GameEngine engine;
    engine.Start();

    return 0;
}

