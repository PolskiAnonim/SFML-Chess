#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>
#include "Chessboard.hpp"
#include "ChessPieces.hpp"


class GameEngine;
class ChessPiece;
class Chessboard;

class GameEngine
{
private:
    sf::RenderWindow window; //Window
    sf::Image icon; //Window icon
    Chessboard* chessboard = new Chessboard; //Pointer to chessboard
    bool player = 0;    //Player: 0 - white, 1 - black
    bool moved = 0;      //To check if there was moved piece
    bool danger = 0;    //To check if king is in danger
    //moves for 50-moves rule - reset when pawn move or captured piece
    int moveswhite = 0; 
    int movesblack = 0;
    std::map<std::string, short> repetition; //positions repetition for threefold repetition
    bool gameend = 0;   //Draw or Win - end of game
    bool promotion = 0; //If there is Promotion of Pawn
    sf::Vector2i promotion_coordinates = { 0,0 };  //Which Pawn promotion
    sf::Vector2i chosen = { 0, 0 };     //Position of chosen piece
    sf::Vector2i king = { 0,0 }; //King position
    //Vector of all legal pieces moves
    //First element of pair - position of piece
    //Second element - vector with legal moves of piece
    std::vector <std::pair<sf::Vector2i, std::vector<sf::Vector2i>>> allMoves; 
    //text
    sf::Font font;//font
    sf::Text text_draw;//draw by agreement text/'button'
    sf::Text text_player;//player's turn
    sf::Text text_winordraw;//end of game, win or draw
    sf::Text text_winner;//winner of the game
    sf::Text text_reset; //text how to reset
    sf::Text informations;  //informations about repetitions and move rules
    //texture for chosen piece
    sf::Texture t_ch;
    sf::Sprite ch;
    //texture for moves
    sf::Texture t_square;
    sf::Sprite moves_square;

public:
    GameEngine() : window(sf::VideoMode(900, 900), "Chess") {}//window 900x900 and enmpty constructor
    void Start();//start of the game
    void Engine();//main loop
    void Change();//change something on chessboard if mouse button clicked
    void DrawGame();//draw all pieces and chessboard
    void ChoosePiece(sf::Vector2i&);//choose piece to move 
    void MovesLoop(bool, sf::Vector2i = {1,1});//draw moves or change piece position
    void WinOrDraw();//check for win and draw
    void Win();//if player win
    void Draw();//if there is draw
    void Reset();//reset game
    void CalcMoves();//calculate possible player moves and find king
};