---------------------CHESS--------------------

------------COMPILATION PROCESS---------------
Requirements:
Microsoft Visual Studio 2015 Update 3 or newer
vcpkg - Microsoft C/C++ Package Manager
vcpkg integration with Visual Studio
SFML installed with vcpkg

Installing SFML in vcpkg:
Download vcpkg from website: https://github.com/Microsoft/vcpkg
Place it in easly accessed folder
(or clone it with git - git clone https://github.com/Microsoft/vcpkg.git)
Run the bootstrap script to build vcpkg
(bootstrap-vcpkg.bat)
Open Terminal/Command line/Windows PowerShell as an administrator
Find folder (in console) with vcpkg.exe
Integrate vcpkg with Visual Studio
.\vcpkg integrate install
Download sfml package:
.\vcpkg install sfml:x64-windows

Compilation
Open src\Chess.sln
Change configuration to release x64
Compile/run program

--------------OPENING APPLICATION---------------
Open with Visual Studio or
Run chess.exe

-----------------DESCRIPTION--------------------
Chess is a board game between two players. It is played on a chessboard with 64 squares arranged in an eight-by-eight grid.
At the start, each player controls sixteen pieces: one king, one queen, two rooks, two bishops, two knights, and eight pawns.
The player controlling the white pieces moves first, followed by the player controlling the black pieces. 
None of players moves can make their kings in check. The object of the game is to checkmate the opponent's king,
whereby the king is under immediate attack (in "check") and there is no way for it to escape.
There are also several ways a game can end in a draw.
There are implemented all possible ways to win (checkmate) and several draw conditions:
Dead position for king vs king; bishop,king vs king and knight,king vs king.
50-moves rule
Threefold position
Stalemate
Draw by agreement

------------------CONTROLS---------------------
ESC - exit game
SPACE - reset game when it ended (there is draw or win writing)
LEFT MOUSE BUTTON - moving/choosing piece to move. Action depends of cursor position
Draw by agreement/reset - button - when clicked with left mouse button end game with draw
