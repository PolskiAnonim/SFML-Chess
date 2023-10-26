#include "ChessPieces.hpp"

ChessPiece::ChessPiece(int c, std::string n, int x, int y, char t, Chessboard* ptr)
{
    //variables
    chessboard = ptr;
    type = t;
    color = c;
    //position
    position.x = x + 1;
    position.y = y + 1;
    setPosition((position.x - 1) * 100 + 50, (position.y - 1) * 100 + 50);
    //loading texture
    if (c == 'w')
        n += "_w.png";
    else
        n += "_b.png";
    n = "./Textures/" + n; //from folder Textures
    texture.loadFromFile(n);
    setTexture(texture);
}


void ChessPiece::ChangePosition(int x, int y) //x and y from vector in chessboard
{//change saved position
    position.x = x + 1;
    position.y = y + 1;
    setPosition((position.x - 1) * 100 + 50, (position.y - 1) * 100 + 50);
}

char ChessPiece::GetColor()
{
    return color;
}

char ChessPiece::GetType()
{
    return type;
}

bool Rook::Moved(bool z) //for castling
{
    if (z)
        moved = 1;
    return moved;
}

int Rook::CountMoves()
{
    return 28;
}

sf::Vector2i Rook::Moves(int mc)
{
    if (mc > 21) //down
    {
        if (mc == 22)
            unblocked = 1; //unblocking next direction - it's the same for all pieces which move that way (rook,bishop and queen)
        if (position.y + (mc - 21) <9 && unblocked)
        {
            if (chessboard->GetPiece(position.x, position.y + (mc - 21)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x, position.y + (mc - 21))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x,position.y + (mc - 21) };
        }
        else
            return { 0,0 };
    }

    if (mc > 14) //up
    {
        if (mc == 15)
            unblocked = 1;
        if (position.y - (mc - 14) > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x, position.y - (mc - 14)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x, position.y - (mc - 14))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x,position.y - (mc - 14) };
        }
        else
            return { 0,0 };
    }

    if (mc > 7) //right
    {
        if (mc == 8)
            unblocked = 1;
        if (position.x + (mc-7) < 9 && unblocked)
        {
            if (chessboard->GetPiece(position.x + (mc - 7), position.y) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x + (mc - 7), position.y)->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x + (mc - 7),position.y };
        }
        else
            return { 0,0 };
    }
    if (mc > 0) //left
    {
        if (mc == 1)
            unblocked = 1;
        if (position.x - mc > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x - mc, position.y) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x - mc, position.y)->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x - mc,position.y };
        }
        else
            return { 0,0 };
    }

}

int Bishop::CountMoves()
{
    return 28;
}

sf::Vector2i Bishop::Moves(int mc)
{
    if (mc > 21)
    {
        if (mc == 22) //right-up
            unblocked = 1;
        if (position.x + (mc - 21) <9 && position.y - (mc - 21) > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x + (mc - 21), position.y - (mc - 21)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x + (mc - 21), position.y - (mc - 21))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x + (mc - 21),position.y - (mc - 21) };
        }
        else
            return { 0,0 };
    }

    if (mc > 14) //right-down
    {
        if (mc == 15)
            unblocked = 1;
        if (position.x + (mc - 14) <9 && position.y + (mc - 14) <9 && unblocked)
        {
            if (chessboard->GetPiece(position.x + (mc - 14), position.y + (mc - 14)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x + (mc - 14), position.y + (mc - 14))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x + (mc - 14),position.y + (mc - 14) };
        }
        else
            return { 0,0 };
    }

    if (mc > 7) //left-down
    {
        if (mc == 8)
            unblocked = 1;
        if (position.x - (mc - 7) > 0 && position.y + (mc - 7) < 9 && unblocked)
        {
            if (chessboard->GetPiece(position.x - (mc - 7), position.y + (mc - 7)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x - (mc - 7), position.y + (mc - 7))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x - (mc - 7),position.y + (mc - 7) };
        }
        else
            return { 0,0 };
    }
    if (mc > 0) //left-up
    {
        if (mc == 1)
            unblocked = 1;
        if (position.x - mc > 0 && position.y - mc > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x - mc, position.y - mc) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x - mc, position.y - mc)->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x - mc,position.y-mc };
        }
        else
            return { 0,0 };
    }
}

int Knight::CountMoves()
{
    return 8;
}

sf::Vector2i Knight::Moves(int mc)
{
    switch (mc)
    {
    case 1:
        if (position.x + 1 < 9 && position.y + 2 < 9)
        {
            if (chessboard->GetPiece(position.x + 1, position.y + 2) != NULL &&
                chessboard->GetPiece(position.x + 1, position.y + 2)->GetColor() == color)
                break;
            return { position.x + 1,position.y + 2 };
        }
        break;
    case 2:
        if (position.x - 1 > 0 && position.y + 2 < 9)
        {
            if (chessboard->GetPiece(position.x - 1, position.y + 2) != NULL &&
                chessboard->GetPiece(position.x - 1, position.y + 2)->GetColor() == color)
                break;
            return { position.x - 1,position.y + 2};
        }
        break;
    case 3:
        if (position.x + 1 < 9 && position.y - 2 > 0)
        {
            if (chessboard->GetPiece(position.x + 1, position.y - 2) != NULL &&
                chessboard->GetPiece(position.x + 1, position.y - 2)->GetColor() == color)
                break;
            return { position.x + 1,position.y - 2 };
        }
        break;
    case 4:
        if (position.x - 1 > 0 && position.y - 2 > 0)
        {
            if (chessboard->GetPiece(position.x - 1, position.y - 2) != NULL &&
                chessboard->GetPiece(position.x - 1, position.y - 2)->GetColor() == color)
                break;
            return { position.x - 1,position.y - 2 };
        }
        break;
    case 5:
        if (position.x + 2 < 9 && position.y + 1 < 9)
        {
            if (chessboard->GetPiece(position.x + 2, position.y + 1) != NULL &&
                chessboard->GetPiece(position.x + 2, position.y + 1)->GetColor() == color)
                break;
            return { position.x + 2,position.y + 1 };
        }
        break;
    case 6:
        if (position.x + 2 < 9 && position.y - 1 > 0)
        {
            if (chessboard->GetPiece(position.x + 2, position.y - 1) != NULL &&
                chessboard->GetPiece(position.x + 2, position.y - 1)->GetColor() == color)
                break;
            return { position.x + 2,position.y - 1 };
        }
        break;
    case 7:
        if (position.x - 2 > 0 && position.y + 1 < 9)
        {
            if (chessboard->GetPiece(position.x - 2, position.y + 1) != NULL &&
                chessboard->GetPiece(position.x - 2, position.y + 1)->GetColor() == color)
                break;
            return { position.x - 2,position.y + 1 };
        }
        break;
    case 8:
        if (position.x - 2 > 0 && position.y - 1 > 0)
        {
            if (chessboard->GetPiece(position.x - 2, position.y - 1) != NULL &&
                chessboard->GetPiece(position.x - 2, position.y - 1)->GetColor() == color)
                break;
            return { position.x - 2,position.y - 1 };
        }
        break;
    }
    return { 0,0 };
}

int Queen::CountMoves()
{
    return 56;
}

sf::Vector2i Queen::Moves(int mc)
{
    if (mc > 49) //down
    {
        if (mc == 50)
            unblocked = 1;
        if (position.y + (mc - 49) < 9 && unblocked)
        {
            if (chessboard->GetPiece(position.x, position.y + (mc - 49)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x, position.y + (mc - 49))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x,position.y + (mc - 49) };
        }
        else
            return { 0,0 };
    }

    if (mc > 42) //up
    {
        if (mc == 43)
            unblocked = 1;
        if (position.y - (mc - 42) > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x, position.y - (mc - 42)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x, position.y - (mc - 42))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x,position.y - (mc - 42) };
        }
        else
            return { 0,0 };
    }

    if (mc > 35) //right
    {
        if (mc == 36)
            unblocked = 1;
        if (position.x + (mc - 35) < 9 && unblocked)
        {
            if (chessboard->GetPiece(position.x + (mc - 35), position.y) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x + (mc - 35), position.y)->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x + (mc - 35),position.y };
        }
        else
            return { 0,0 };
    }
    if (mc > 28) //left
    {
        if (mc == 29)
            unblocked = 1;
        if (position.x - (mc - 28) > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x - (mc - 28), position.y) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x - (mc - 28), position.y)->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x - (mc - 28),position.y };
        }
        else
            return { 0,0 };
    }

    if (mc > 21) //right-up
    {
        if (mc == 22)
            unblocked = 1;
        if (position.x + (mc - 21) < 9 && position.y - (mc - 21) > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x + (mc - 21), position.y - (mc - 21)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x + (mc - 21), position.y - (mc - 21))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x + (mc - 21),position.y - (mc - 21) };
        }
        else
            return { 0,0 };
    }

    if (mc > 14) //right-down
    {
        if (mc == 15)
            unblocked = 1;
        if (position.x + (mc - 14) < 9 && position.y + (mc - 14) < 9 && unblocked)
        {
            if (chessboard->GetPiece(position.x + (mc - 14), position.y + (mc - 14)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x + (mc - 14), position.y + (mc - 14))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x + (mc - 14),position.y + (mc - 14) };
        }
        else
            return { 0,0 };
    }

    if (mc > 7) //left-down
    {
        if (mc == 8)
            unblocked = 1;
        if (position.x - (mc - 7) > 0 && position.y + (mc - 7) < 9 && unblocked)
        {
            if (chessboard->GetPiece(position.x - (mc - 7), position.y + (mc - 7)) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x - (mc - 7), position.y + (mc - 7))->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x - (mc - 7),position.y + (mc - 7) };
        }
        else
            return { 0,0 };
    }
    if (mc > 0) //left-up
    {
        if (mc == 1)
            unblocked = 1;
        if (position.x - mc > 0 && position.y - mc > 0 && unblocked)
        {
            if (chessboard->GetPiece(position.x - mc, position.y - mc) != NULL)
            {
                unblocked = 0;
                if (chessboard->GetPiece(position.x - mc, position.y - mc)->GetColor() == color)
                    return { 0,0 };
            }
            return { position.x - mc,position.y - mc };
        }
        else
            return { 0,0 };
    }
}

void King::Moved()
{
    moved = 1;
}

int King::CountMoves() //with castling
{
    return 10;
}

sf::Vector2i King::Moves(int mc) //default moves
{
    switch (mc)
    {
    //normal moves
    case 1:
        if (position.x - 1 > 0)
        {
            if (chessboard->GetPiece(position.x - 1, position.y) != NULL &&
                chessboard->GetPiece(position.x - 1, position.y)->GetColor() == color)
                break;
            return { position.x - 1,position.y };
        }
        break;
    case 2:
        if (position.x + 1 < 9)
        {
            if (chessboard->GetPiece(position.x + 1, position.y) != NULL &&
                chessboard->GetPiece(position.x + 1, position.y)->GetColor() == color)
                break;
            return { position.x + 1,position.y };
        }
        break;
    

    case 3:
        if (position.y - 1 > 0)
        {
            if (chessboard->GetPiece(position.x, position.y - 1) != NULL &&
                chessboard->GetPiece(position.x, position.y - 1)->GetColor() == color)
                break;
            return { position.x,position.y - 1 };
        }
        break;
    case 4:
        if (position.y + 1 < 9)
        {
            if (chessboard->GetPiece(position.x, position.y + 1) != NULL &&
                chessboard->GetPiece(position.x, position.y + 1)->GetColor() == color)
                break;
            return { position.x,position.y + 1 };
        }
        break;
    case 5:
        if (position.x - 1 > 0 && position.y - 1 > 0)
        {
            if (chessboard->GetPiece(position.x - 1, position.y - 1) != NULL &&
                chessboard->GetPiece(position.x - 1, position.y - 1)->GetColor() == color)
                break;
            return { position.x - 1,position.y - 1 };
        }
        break;
    case 6:
        if (position.x + 1 < 9 && position.y - 1 > 0)
        {
            if (chessboard->GetPiece(position.x + 1, position.y - 1) != NULL &&
                chessboard->GetPiece(position.x + 1, position.y - 1)->GetColor() == color)
                break;
            return { position.x + 1,position.y - 1 };
        }
        break;
    case 7:
        if (position.x + 1 < 9 && position.y + 1 < 9)
        {
            if (chessboard->GetPiece(position.x + 1, position.y + 1) != NULL &&
                chessboard->GetPiece(position.x + 1, position.y + 1)->GetColor() == color)
                break;
            return { position.x + 1,position.y + 1 };
        }
        break;
    case 8:
        if (position.x - 1 > 0 && position.y + 1 < 9)
        {
            if (chessboard->GetPiece(position.x - 1, position.y + 1) != NULL &&
                chessboard->GetPiece(position.x - 1, position.y + 1)->GetColor() == color)
                break;
            return { position.x - 1,position.y + 1 };
        }
        break;
    case 9: //long castling
        if (!moved)
            if (chessboard->GetPiece(2, position.y) == NULL &&
                chessboard->GetPiece(3, position.y) == NULL &&
                chessboard->GetPiece(4, position.y) == NULL &&
                chessboard->GetPiece(1, position.y) != NULL &&
                chessboard->GetPiece(1, position.y)->GetType() == 'R' &&
                ((Rook*)chessboard->GetPiece(1, position.y))->Moved(0)==0)
                return { 3,position.y };
        break;
    case 10: //short castling
        if (!moved)
            if (chessboard->GetPiece(6, position.y) == NULL &&
                chessboard->GetPiece(7, position.y) == NULL &&
                chessboard->GetPiece(8, position.y) != NULL &&
                chessboard->GetPiece(8, position.y)->GetType() == 'R' &&
                ((Rook*)chessboard->GetPiece(8, position.y))->Moved(0) == 0)
                return { 7,position.y };
        break;
    
    }
    return { 0,0 };
}

void Pawn::EnPassant(bool p) //change move2 to true if moved 2 squares and change to false with changing player turn again
{//to player which have the same color as this piece
    move2 = p;
}

bool Pawn::Moved2Tiles() //check if EnPassant is possible
{
    return move2;
}

int Pawn::CountMoves()
{
    if ((position.y == 7 && color == 'w') || (position.y == 2 && color == 'b')) //if on starting position
        return 4;
    else
        return 3;
}

sf::Vector2i Pawn::Moves(int mc)
{
    if (position.y == 1 || position.y == 8) //last tile
        return { 0,0 };

    switch (mc)
    {
    case 1:     //left side
        unblocked = 1; //to unblock move forward after changing position
        if (position.x - 1 > 0)
        {
            
            if (color == 'b')   //black
            {
                if (chessboard->GetPiece(position.x - 1, position.y + 1) != NULL &&
                    chessboard->GetPiece(position.x - 1, position.y + 1)->GetColor() != color)
                        return { position.x - 1, position.y + 1 };
            }
            else              //white
            {
            if (chessboard->GetPiece(position.x - 1, position.y - 1) != NULL &&
                chessboard->GetPiece(position.x - 1, position.y - 1)->GetColor() != color)
                    return { position.x - 1, position.y - 1 };
            }
            if (chessboard->GetPiece(position.x - 1, position.y) != NULL &&         //check for En Passant
                chessboard->GetPiece(position.x - 1, position.y)->GetType() == 'P' &&
                chessboard->GetPiece(position.x - 1, position.y)->GetColor() != color &&
                ((Pawn*)chessboard->GetPiece(position.x - 1, position.y))->Moved2Tiles()) 
                {
                    if (color == 'b') 
                        return { position.x - 1, position.y + 1 };
                    else
                        return { position.x - 1, position.y - 1 };
                }
        }
        break;
    case 2: //right side
        if (position.x + 1 < 9)
        {
            if (color == 'b') //black
            {
                if (chessboard->GetPiece(position.x + 1, position.y + 1) != NULL)
                    if (chessboard->GetPiece(position.x + 1, position.y + 1)->GetColor() != color)
                        return { position.x + 1, position.y + 1 };
            }
            else              //white
            {
                if (chessboard->GetPiece(position.x + 1, position.y - 1) != NULL)
                    if (chessboard->GetPiece(position.x + 1, position.y - 1)->GetColor() != color)
                        return { position.x + 1, position.y - 1 };
            }
            if (chessboard->GetPiece(position.x + 1, position.y) != NULL &&         //check for En Passant
                chessboard->GetPiece(position.x + 1, position.y)->GetType() == 'P' &&
                chessboard->GetPiece(position.x + 1, position.y)->GetColor() != color &&
                ((Pawn*)chessboard->GetPiece(position.x + 1, position.y))->Moved2Tiles())
                {
                    if (color == 'b')
                        return { position.x + 1, position.y + 1 };
                    else
                        return { position.x + 1, position.y - 1 };
                }
        }
        break;
    case 3:
        if (color == 'b') //black
        {
            if (chessboard->GetPiece(position.x, position.y + 1) == NULL)
                return { position.x, position.y + 1 };
            else
                unblocked = 0;
        }
        else             //white
        {
            if (chessboard->GetPiece(position.x, position.y - 1) == NULL)
                return { position.x, position.y - 1 };
            else
                unblocked = 0;
        }
        break;
    case 4:
        if (color == 'b') //black
        {
            if (unblocked && chessboard->GetPiece(position.x, position.y + 2) == NULL)
            {
                return { position.x, position.y + 2 };
            }
        }
        else              //white
        {
            if (unblocked && chessboard->GetPiece(position.x, position.y - 2) == NULL)
            {
                return { position.x, position.y - 2 };
            }
        }
        break;
    }
    return { 0,0 };
}