#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Chessboard.hpp"

class Chessboard;
class ChessPiece;

class ChessPiece : public sf::Sprite
{
protected:
    sf::Texture texture;
    sf::Vector2i position; //piece position
    Chessboard* chessboard; //Pointer to chessboard to look for other pieces
    char color;//white or black
    char type; //Type of piece

public:
    //Constructor - loading textures, position, pointer to chessboard and saving type of piece
    ChessPiece(int, std::string, int, int, char, Chessboard*); 
    //Changing positon of piece
    void ChangePosition(int, int); 
    //Get color of piece - 'b' - black, 'w' - white
    char GetColor();
    //Get type of piece: N - knight, B - bishop, R - rook, Q - queen, K - king, P - pawn
    char GetType();
    //Return positions where piece can move - for loops in chessboard class
    virtual sf::Vector2i Moves(int) = 0; //pure virtual function
    //Max number of moves for specific piece (never achieved because it ignores positions of pieces)
    //(it's only for loop)
    virtual int CountMoves()=0; //pure virtual function
    virtual ~ChessPiece() {}; //virtual deconstructor
};

class Rook : public ChessPiece
{
private:
    bool unblocked = 1; //to block moves in one direction
    bool moved = 0; //for castling
public:
    bool Moved(bool);
    Rook(char c, int x, int y, char t, Chessboard* ptr) : ChessPiece(c, "rook", x, y, t, ptr) {}; //using Chesspiece constructor
    sf::Vector2i Moves(int);
    int CountMoves();
};

class Bishop : public ChessPiece
{
private:
    bool unblocked = 1; //to block moves in one direction
public:
    Bishop(char c, int x, int y, char t, Chessboard* ptr) : ChessPiece(c, "bishop", x, y,t, ptr) {}; //using Chesspiece constructor
    sf::Vector2i Moves(int);
    int CountMoves();
};

class Knight : public ChessPiece
{
public:
    Knight(char c, int x, int y, char t, Chessboard* ptr) : ChessPiece(c, "knight", x, y,t, ptr) {};//using Chesspiece constructor
    sf::Vector2i Moves(int);
    int CountMoves();
};

class Queen : public ChessPiece
{
private:
    bool unblocked = 1; //to block moves in one direction
public:
    Queen(char c, int x, int y, char t, Chessboard* ptr) : ChessPiece(c, "queen", x, y,t, ptr) {}; //using Chesspiece constructor
    sf::Vector2i Moves(int);
    int CountMoves();
};

class King : public ChessPiece
{
private:
    bool moved = 0; //for castling
public:
    void Moved();
    King(char c, int x, int y, char t, Chessboard* ptr) : ChessPiece(c, "king", x, y,t, ptr) {}; //using Chesspiece constructor
    sf::Vector2i Moves(int);
    int CountMoves();
};

class Pawn : public ChessPiece
{
private:
    bool unblocked = 1; //to block moves forward
    bool move2 = false; //for en passant/capture in passing - moved 2 tiles forward
public:
    //for en passant/capture in passing
    void EnPassant(bool);
    bool Moved2Tiles();
    Pawn(char c, int x, int y, char t, Chessboard* ptr) : ChessPiece(c, "pawn", x, y,t, ptr) {}; //using Chesspiece constructor
    //movement
    sf::Vector2i Moves(int);
    int CountMoves();
};