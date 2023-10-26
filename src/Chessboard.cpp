#include "Chessboard.hpp"

Chessboard::Chessboard() :pieces(8, std::vector<ChessPiece*>(8, NULL)) //creating 8x8 pointer matrix with NULLs 
{
    texture.loadFromFile("./Textures/chessboard.png"); //loading texture
    setTexture(texture);
}

void Chessboard::SetPieces()//create pieces at the beginning of the game
{
    for (int i = 0; i < 8; i++) //pawns
    {
        pieces[i][1] = new Pawn('b', i, 1,'P', this);
        pieces[i][6] = new Pawn('w', i, 6,'P', this);
    }
    //rooks
    pieces[0][0] = new Rook('b', 0, 0,'R', this);
    pieces[7][0] = new Rook('b', 7, 0, 'R', this);
    pieces[0][7] = new Rook('w', 0, 7, 'R', this);
    pieces[7][7] = new Rook('w', 7, 7, 'R', this);
    //knights
    pieces[1][0] = new Knight('b', 1, 0, 'N', this);
    pieces[6][0] = new Knight('b', 6, 0, 'N', this);
    pieces[1][7] = new Knight('w', 1, 7, 'N', this);
    pieces[6][7] = new Knight('w', 6, 7, 'N', this);
    //bishops
    pieces[2][0] = new Bishop('b', 2, 0, 'B', this);
    pieces[5][0] = new Bishop('b', 5, 0, 'B', this);
    pieces[2][7] = new Bishop('w', 2, 7, 'B', this);
    pieces[5][7] = new Bishop('w', 5, 7, 'B', this);
    //queens
    pieces[3][0] = new Queen('b', 3, 0, 'Q', this);
    pieces[3][7] = new Queen('w', 3, 7, 'Q', this);
    //kings
    pieces[4][0] = new King('b', 4, 0, 'K', this);
    pieces[4][7] = new King('w', 4, 7, 'K', this);
}

ChessPiece* Chessboard::GetPiece(int x, int y) //return pointer to piece
{
    return pieces[x - 1][y - 1];
}

void Chessboard::ChangePieces(int& x1, int& y1, int& x2, int& y2,bool& promotion,sf::Vector2i& promcoord)//move piece
{
    sf::Vector2i chosen = { x1 - 1,y1 - 1 };
    sf::Vector2i moving = { x2 - 1,y2 - 1 };
    //begin check for castling
    if ((pieces[chosen.x][chosen.y]->GetType() == 'K') && (moving.x==chosen.x-2 || moving.x == chosen.x + 2))
            return Castling(chosen.y, moving.x == chosen.x - 2 ? 0:1);
    if (pieces[chosen.x][chosen.y]->GetType() == 'R')
        ((Rook*)pieces[chosen.x][chosen.y])->Moved(1);
    if (pieces[chosen.x][chosen.y]->GetType() == 'K')
        ((King*)pieces[chosen.x][chosen.y])->Moved();
    //end check for castling
    //capture opponent's piece if any
    if (pieces[moving.x][moving.y] != NULL) 
        delete pieces[moving.x][moving.y];
    //check for en passant
    if (pieces[chosen.x][chosen.y]->GetType() == 'P' && abs(chosen.y - moving.y) == 2) //if moved 2 tiles change variable
        ((Pawn*)pieces[chosen.x][chosen.y])->EnPassant(true);

    if (pieces[chosen.x][chosen.y]->GetType()=='P' && moving.x!=chosen.x)//if Pawn and capturing
        if (pieces[moving.x][chosen.y] != NULL &&
            pieces[moving.x][chosen.y]->GetType() == 'P'//if second Pawn next to it
            && ((Pawn*)pieces[moving.x][chosen.y])->Moved2Tiles()) //if second Pawn moved 2 tiles on the previous turn
            {
                delete pieces[moving.x][chosen.y]; //capture pawn
                pieces[moving.x][chosen.y] = NULL; //change captured pawn pointer to NULL
            }
    //end checking for en passant
    //begin change piece position
    pieces[moving.x][moving.y] = pieces[chosen.x][chosen.y];
    pieces[chosen.x][chosen.y] = NULL;
    pieces[moving.x][moving.y]->ChangePosition(moving.x, moving.y);
    //end change piece position
    if (pieces[moving.x][moving.y]->GetType() == 'P' && (moving.y == 0 || moving.y == 7)) //promotion
    {
        promotion = true;
        promcoord = { moving.x,moving.y };
    }

}

void Chessboard::Castling(int& y,bool t)
{
    if (t == 0) //long castling
    {
        pieces[2][y] = pieces[4][y]; //king move
        pieces[4][y] = NULL;
        pieces[2][y]->ChangePosition(2, y);
        pieces[3][y] = pieces[0][y]; //rook move
        pieces[0][y] = NULL;
        pieces[3][y]->ChangePosition(3, y);
    }
    else //short castling
    {
        pieces[6][y] = pieces[4][y]; //king move
        pieces[4][y] = NULL;
        pieces[6][y]->ChangePosition(6, y);
        pieces[5][y] = pieces[7][y]; //rook move
        pieces[7][y] = NULL;
        pieces[5][y]->ChangePosition(5, y);
    }
    //there is no change of moved variables in king and rook, but there's no need for them 
    //because it's impossible to do that move again without other moves
}

void Chessboard::Promotion(int& choise, sf::Vector2i& coordinates)
{
    char color = pieces[coordinates.x ][coordinates.y]->GetColor();
    delete pieces[coordinates.x][coordinates.y];//delete pawn
    switch (choise)//create new piece
    {
    case 3:
        pieces[coordinates.x][coordinates.y] = new Bishop(color, coordinates.x, coordinates.y, 'B', this);
        break;
    case 4:
        pieces[coordinates.x][coordinates.y] = new Queen(color, coordinates.x, coordinates.y, 'Q', this);
        break;
    case 5:
        pieces[coordinates.x][coordinates.y] = new Rook(color, coordinates.x, coordinates.y, 'R', this);
        break;
    case 6:
        pieces[coordinates.x][coordinates.y] = new Knight(color, coordinates.x, coordinates.y, 'N', this);
        break;
    }
}

sf::Vector2i Chessboard::FindKing(bool& player)
{
    char color;
    sf::Vector2i king;
    color = player ? 'b' : 'w'; //player: 0 - white, 1 - black
    //find king
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (pieces[i][j] != NULL && pieces[i][j]->GetType() == 'K' && pieces[i][j]->GetColor() == color)
                king = { i + 1,j + 1 };
    return king;
}

std::vector <std::pair<sf::Vector2i, std::vector<sf::Vector2i>>> Chessboard::AllMoves(sf::Vector2i& king,bool &danger) 
{//king in positions on chessboard not in vector, danger - for blocking castling
    std::vector <std::pair<sf::Vector2i,std::vector<sf::Vector2i>>> possibleMoves;
    char color;
    color = pieces[king.x - 1][king.y - 1]->GetColor();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieces[i][j] != NULL && pieces[i][j]->GetColor() == color) //for all player pieces
            {
                if (pieces[i][j]->GetType() == 'P')//erase en passant possibility for player pieces - after 1 opponents turn
                    ((Pawn*)pieces[i][j])->EnPassant(false);
                std::vector<sf::Vector2i> onePieceMoves;
                sf::Vector2i piece = { i + 1,j + 1 };
                //piece movement
                int n = pieces[i][j]->CountMoves(); //max number of possible moves
                int a = 1;

                int castlingflag = 0; //king - castling
                //0 - two sides permitted
                //1 - impossible short castling
                //2 - impossible long castling
                //3 - impossible castling

                while (a <= n)//one piece movement
                {
                    sf::Vector2i piecemove = pieces[i][j]->Moves(a);
                    a++;
                    //castling+king movement 1 start
                    if (pieces[i][j]->GetType() == 'K')
                    {
                        if (danger && a >=10)   //king in check - castling impossible
                            continue;
                    }
                    //castling+king movement 1 end

                    if (piecemove.x == 0 && piecemove.y == 0) //move impossible
                        continue;

                    if (pieces[i][j]->GetType() == 'K') //change saved king position
                        king = { piecemove.x,piecemove.y };

                    //temporary change position and check if it is legal move
                    ChessPiece* tmp;
                    tmp = pieces[piecemove.x - 1][piecemove.y - 1];
                    pieces[piecemove.x - 1][piecemove.y - 1] = pieces[i][j];
                    pieces[i][j] = NULL;

                    bool check=Check(king);
                    
                    //castling+king movement 2 start
                    if (pieces[piecemove.x-1][piecemove.y-1]->GetType() == 'K' && check) //if king in check after move
                    {                                                                    //block castling on the same side
                        if (a == 2)//a was 1
                        {
                            castlingflag += 1;
                        }
                        if (a == 3)//a was 2
                        {
                            castlingflag += 2;
                        }
                    }
                    if (pieces[piecemove.x-1][piecemove.y-1]->GetType() == 'K' && !check) //possible moves for king (with castling)
                    {
                        if (a>=10)
                        {
                            if (castlingflag==0)
                                onePieceMoves.push_back(piecemove);
                            if (castlingflag == 2 && a==10)
                                onePieceMoves.push_back(piecemove);
                            if (castlingflag == 1 && a == 11)
                                onePieceMoves.push_back(piecemove);
                        }
                        else
                            onePieceMoves.push_back(piecemove);
                    }
                    //castling+king movement 2 end
                    //add move to vector if king not in check (don't work for king)
                    if (!check && pieces[piecemove.x-1][piecemove.y-1]->GetType() != 'K')
                        onePieceMoves.push_back(piecemove);
                    //go back to previous position (that was made by players)
                    pieces[i][j] = pieces[piecemove.x - 1][piecemove.y - 1];
                    pieces[piecemove.x - 1][piecemove.y - 1] = tmp;

                }//end one piece movement
                possibleMoves.push_back(std::make_pair(piece, onePieceMoves));//add piece moves to all moves

                if (pieces[i][j]->GetType() == 'K') //change variable with king position to original
                    king = { i + 1,j + 1 };
            } //end one piece
        }
    }
    return possibleMoves;
}

bool Chessboard::Check(sf::Vector2i& king)//if king is in check
{
    char color = pieces[king.x - 1][king.y - 1]->GetColor();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (pieces[i][j] != NULL && pieces[i][j]->GetColor() != color)
            {
                int n = pieces[i][j]->CountMoves(); //max number of possible moves
                int a = 1;

                while (a <= n)
                {
                    sf::Vector2i piecemove = pieces[i][j]->Moves(a);
                    a++;

                    if (piecemove == king)
                        return true;
                }
            }
        }
    }
    return false;
}

void Chessboard::Clear()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (pieces[i][j] != NULL)
                delete pieces[i][j];
}