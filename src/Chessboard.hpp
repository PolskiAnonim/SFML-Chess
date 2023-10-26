#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "ChessPieces.hpp"

class Chessboard;
class ChessPiece;

class Chessboard : public sf::Sprite
{
private:
    std::vector<std::vector<ChessPiece*>> pieces;
    sf::Texture texture;
public:
    Chessboard() ;//constructor
    void SetPieces(); //setting starting positions
    ChessPiece* GetPiece(int, int); //get pointer to piece on given position
    void ChangePieces(int&, int&, int& , int&,bool&,sf::Vector2i& ); //moving pieces
    void Castling(int& ,bool);
    void Promotion(int&, sf::Vector2i&);
    std::vector <std::pair<sf::Vector2i, std::vector<sf::Vector2i>>> AllMoves(sf::Vector2i&,bool&);//find all possible moves for player
    sf::Vector2i FindKing(bool&);
    bool Check(sf::Vector2i&); //check if king is in check...
    void Clear(); //delete all pieces on chessboard - for reset
};