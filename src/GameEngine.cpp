#include "GameEngine.hpp"

void GameEngine::Start()
{
    //setting icon
    icon.loadFromFile("./Textures/icon.png");
    window.setIcon(64, 64, icon.getPixelsPtr());
    //load font
    font.loadFromFile("./Textures/arial.ttf");
    //load textures
    t_ch.loadFromFile("./Textures/chosen.png"); //chosen piece
    ch.setTexture(t_ch);
    t_square.loadFromFile("./Textures/square.png"); //moves
    moves_square.setTexture(t_square);
    //text attributes
    //player
    text_player.setFont(font);
    text_player.setCharacterSize(20); //character size in pixels
    text_player.setFillColor(sf::Color::Black);
    text_player.setPosition(200, 20);
    //draw text/"button"
    text_draw.setFont(font);
    text_draw.setCharacterSize(20);
    text_draw.setFillColor(sf::Color::Black);
    text_draw.setPosition(600, 20);
    text_draw.setString("Draw by agreement/reset");
    //end game
    text_winordraw.setFont(font);
    text_winordraw.setCharacterSize(80);
    text_winordraw.setFillColor(sf::Color::Color(189, 192, 184));
    text_winordraw.setPosition(350, 350);
    //winner
    text_winner.setFont(font);
    text_winner.setCharacterSize(60);
    text_winner.setFillColor(sf::Color::Color(189, 192, 184));
    text_winner.setPosition(340, 450);
    //how to reset
    text_reset.setFont(font);
    text_reset.setCharacterSize(50); //character size in pixels
    text_reset.setFillColor(sf::Color::Color(189, 192, 184));
    text_reset.setPosition(220, 550);
    text_reset.setString("Press space to reset");
    //informations - for draws
    informations.setFont(font);
    informations.setCharacterSize(20); //character size in pixels
    informations.setFillColor(sf::Color::Black);
    informations.setPosition(370, 20);
    //generating pieces on chessboard
    chessboard->SetPieces();
    //first drawing
    CalcMoves();
    DrawGame();
    //go to main loop
    Engine();
}

void GameEngine::Engine() //main loop
{
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event
            if (event.type == sf::Event::Closed)
                window.close();
            //press Escape to exit
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (gameend && event.key.code == sf::Keyboard::Space)
                    Reset();
            }
            //pres left mouse button to do something
            if (!gameend && event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left)
                    Change();
        }
    }
}

void GameEngine::ChoosePiece(sf::Vector2i& position) //chose piece to move by clicking on it
{
    if (position.x > 0 && position.x < 9 && position.y>0 && position.y < 9)
    {
        if (chessboard->GetPiece(position.x, position.y) != NULL)
        {
            if (chosen == position) //uncheck piece
            {
                chosen = { 0,0 };
                return;
            }
            //if already chosen and clicked to move conditions not meet else chose new piece to move
            if (!player && chessboard->GetPiece(position.x, position.y)->GetColor() == 'w')
            {
                chosen = position;
                return;
            }
            if (player && chessboard->GetPiece(position.x, position.y)->GetColor() == 'b')
            {
                chosen = position;
                return;
            }

        }
    }
}

void GameEngine::MovesLoop(bool drawing,sf::Vector2i position) //draw all chosen piece moves or move it to clicked square if possible
{
    if (chosen.x > 0 && chosen.x < 9 && chosen.y>0 && chosen.y < 9) //if there is chosen piece
    {
        for (auto& piece : allMoves) //look for piece
        {
            if (piece.first.x == chosen.x && piece.first.y == chosen.y)
                for (auto& move : piece.second) //look for possible piece moves
                {
                    if (drawing) //for drawing - draw move
                    {
                        moves_square.setPosition(float(50 + (move.x - 1) * 100), float(50 + (move.y - 1) * 100));
                        window.draw(moves_square);
                    }
                    else if (position == move) //for moving pieces - move piece
                    {
                        //50/75-move rule
                        if (chessboard->GetPiece(chosen.x, chosen.y)->GetType() == 'P' || chessboard->GetPiece(position.x, position.y) != NULL)
                        {
                            moveswhite = 0;
                            movesblack = 0;
                        }
                        else
                        {
                            if (!player) ++moveswhite;
                            if (player) ++movesblack;

                        }
                        //end 50/75-move rule
                        chessboard->ChangePieces(chosen.x, chosen.y, position.x, position.y, promotion, promotion_coordinates);//moving
                        moved = 1;//piece was moved
                        break;
                    }
                }
        }
    }
}

void GameEngine::CalcMoves()
{
            king = chessboard->FindKing(player); //find player king
            danger = chessboard->Check(king); //check if king is in check
            allMoves = chessboard->AllMoves(king, danger); //find all legal moves
}

void GameEngine::Change() //do something after clicking mouse button
{

    sf::Vector2i position = { 0,0 };    //Position of mouse on chessboard (squares)
    sf::Vector2i mouse = sf::Mouse::getPosition(window); //Position of mouse on chessboard (pixels)
    //calculate position (squares)
    position.x = ceil((mouse.x - 50) / 100.0);
    position.y = ceil((mouse.y - 50) / 100.0);
    //button - Draw by agreement or Resetting game
    if (position.y == 0 && (position.x >= 6 && position.x <= 8))
        Draw();
    //promotion of pawn
    if (promotion)
    {
        if (position.x == 9 && position.y > 2 && position.y < 7)
        {
            chessboard->Promotion(position.y, promotion_coordinates);
            promotion = false;
        }   
    }
    //choose piece to move
    ChoosePiece(position);

    //if piece chosen to move where it is possible
    MovesLoop(0, position);

    if (moved) //if piece was moved
    {
        chosen = { 0,0 }; //clear chosen piece - no mater if there is promotion
        if (!promotion) //if there is no promotion change player, calculate movement and check for win and draw
        {
            player = !player;
            moved = 0;
            CalcMoves();
            WinOrDraw();
        }
    }
            
    return DrawGame(); //draw everything on chessboard
}

void GameEngine::DrawGame() //drawing everything in game
{
    //clear everything to draw new things
    window.clear(sf::Color::Black); 
    //draw chessboard
    window.draw(*chessboard); 
    //draw chosen piece moves
    MovesLoop(1); 
    //highlight square with chosen piece
    if (chosen.x != 0 && chosen.y != 0) 
    {
        ch.setPosition(float(50 + (chosen.x - 1) * 100), float(50 + (chosen.y - 1) * 100));
        window.draw(ch);
    }
    //draw all pieces
    for (int i = 1; i < 9; i++) 
        for (int j = 1; j < 9; j++)
            if (chessboard->GetPiece(i, j) != NULL)
                window.draw(*(chessboard->GetPiece(i, j)));
    //draw pieces for promotion
    if (promotion)  
    {
        sf::Texture t_prom;
        sf::Sprite prom;
        //load promtion
        if (!player)
            t_prom.loadFromFile("./Textures/promotion_w.png");
        else
            t_prom.loadFromFile("./Textures/promotion_b.png");
        prom.setPosition(851, 250);

        prom.setTexture(t_prom);
        window.draw(prom);
    }
    //draw turn
    if (!player)
        text_player.setString("Turn: White");
    if (player)
        text_player.setString("Turn: Black");

    window.draw(text_player);
    //draw draw by agreement/reset
    window.draw(text_draw); 
    //draw informations - repetitions and move rules
    window.draw(informations);
    if (gameend)
    {
        window.draw(text_winordraw);
        window.draw(text_winner);
        window.draw(text_reset);
    }
    //display everything 
    window.display();  
}

void GameEngine::Reset()
{    
    //delete chessboard and all pieces on it
    chessboard->Clear();
    delete chessboard;
    //change all variables to initial values
    moveswhite = 0;
    movesblack = 0;
    player = 0;
    moved = 0;
    gameend = 0;
    promotion = 0;
    promotion_coordinates = { 0,0 };
    chosen = { 0, 0 };
    repetition.clear();
    text_winner.setString("");
    informations.setString("");
    //create new chessboard
    chessboard = new Chessboard;
    chessboard->SetPieces();
    //first drawing
    CalcMoves();
    DrawGame();
    //go to main loop
    Engine();
}

void GameEngine::Draw()
{
    //end game
    gameend = 1;
    text_winordraw.setString("Draw");
    chosen = { 0,0 };
    DrawGame();
}

void GameEngine::Win()
{
    //end game
    gameend = 1;
    text_winordraw.setString("Win");
    if (player)
        text_winner.setString("White");
    else
        text_winner.setString("Black");
    chosen = { 0,0 };
    DrawGame();
}

void GameEngine::WinOrDraw()
{
    //checkmate and stalemate
    int countMoves = 0;
    for (auto& piece : allMoves) //count all possible moves
    {
        countMoves += piece.second.size();
    }

    if (countMoves == 0)//if there is no moves
    {
        if (danger)
            Win(); //checkmate
        else
            Draw(); //stalemate
    }
    //draw - repetitions + dead position/insufficient material
    std::string pieceslocations; //String with pieces types 
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
        {
            if (chessboard->GetPiece(i, j) == NULL)
                pieceslocations += "--";
            else
                pieceslocations = pieceslocations+ chessboard->GetPiece(i, j)->GetType()+ chessboard->GetPiece(i, j)->GetColor();
        }
    }

    //draw - dead position/insufficient material
    int countpieces[2] = { 0,0 };
    char pieces[2] = { '-','-' };
    int size = pieceslocations.size() - 1;
    for (int i = 0; i < size; i += 2)
    {    
        if (pieceslocations[i + 1] == 'w')
        {
            countpieces[0]++;
            if(pieceslocations[i]!='K')
                pieces[0] = pieceslocations[i];
        }
        if (pieceslocations[i + 1] == 'b')
        {
            countpieces[1]++;
            if (pieceslocations[i] != 'K')
                pieces[1] = pieceslocations[i];
        }
    }
    if (countpieces[0] <= 2 && countpieces[1] <= 2)
    {
        if (countpieces[0] == 1 && countpieces[1] == 1)
        {
            informations.setString("Dead position");
            Draw();
        }
        if (countpieces[0] == 1 && countpieces[1] == 2 || countpieces[0] == 2 && countpieces[1] == 1)
        {
            if (pieces[1] == 'N' || pieces[0] == 'N' || pieces[1] == 'B' || pieces[0] == 'B')
            {
                informations.setString("Dead position");
                Draw();
            }
        }
    } 
    //draw fifty-moves rule
    if (moveswhite == 50 && movesblack == 50)
    {
        informations.setString("Fifty-moves rule");
        Draw();
    }
    //draw - threefold repetition
    pieceslocations += (player ? 'b' : 'w');
    ++repetition[pieceslocations];
    for (auto& p : repetition)
    {
        if (p.second == 3)
        {
            informations.setString("Threefold repetition");
            Draw();
        }     
    }

}