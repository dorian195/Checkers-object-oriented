#include "Gameboard.h"
#include "Structures.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include "Pawn.h"
#include "Queen.h"
#include <regex>

using namespace std;

Gameboard::Gameboard(int boardSize_, int rowOfPawns_) : boardSize{ boardSize_ }, rowOfPawns{ rowOfPawns_ }
{
	if (boardSize_ < 8 || boardSize_ > 20) throw exception("Niewymiarowa szachownica."); //wyjatek
	if (rowOfPawns_ < 1 || rowOfPawns_ >= (boardSize_ / 2)) throw exception("Niepoprawna liczba pionow."); //wyjatek
	board.resize(boardSize); //inicjalizuje szachownice
	board_temp.resize(boardSize); //inicjalizuje szachownice
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i].push_back(Square{ static_cast<Color>((i + j + 1) % 2) });
			board_temp[i].push_back(Square{ static_cast<Color>((i + j + 1) % 2) });
		}
	}
	for (int i = 0; i < boardSize; i++)  //ustawia pionki
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (board[i][j].getSquareColor() == black)
			{
				if (i < rowOfPawns)
				{
					Piece * temp = new Pawn{ this, i, j, white };
					board[i][j].setPiece(temp);
					board_temp[i][j].setPiece(temp);
					blackPieces.push_back(temp);
				}
				else if (i >= boardSize - rowOfPawns)
				{
					Piece * temp = new Pawn{ this, i, j, black };
					board[i][j].setPiece(temp);
					board_temp[i][j].setPiece(temp);
					whitePieces.push_back(temp);
				}
			}
		}
	}
}

void Gameboard::play() //rozpoczyna gre
{
	while (checkForAnyPossibleMoves()) //dopoki aktualny gracz ma jakikolwiek mozliwy ruch
	{
		print(); //drukuje
		waitForCorrectMove(); //czeka na poprawny ruch
		changePlayerToMove(); //przekazuje ruch drugiemu graczowi
	}
	print(); //po zakonczeniu drukuje szachownice jeszcze raz
	if (whoseMove == white) cout << "No possible moves for white. Black won. GGWP!"; //jesli bialemu skonczyly sie ruchy, czarny wygral
	if (whoseMove == black) cout << "No possible moves for black. White won. GGWP!"; //jesli to czarnemu skonczyly sie ruchy, bialy wygral
}

int Gameboard::getSize()
{
	return boardSize;
}

void Gameboard::movePiece(int source_file, int source_rank, int target_file, int target_rank)
{
	Piece * pieceToMove = board_temp[source_rank][source_file].getPiece();
	board_temp[source_rank][source_file].removePiece();
	board_temp[target_rank][target_file].setPiece(pieceToMove);
}

void Gameboard::removePiece(int file, int rank)
{
	board_temp[rank][file].removePiece();
}

void Gameboard::promotePawn(int file, int rank)
{
	Color pieceColor = board_temp[rank][file].getPiece()->getPieceColor();
	board_temp[rank][file].removePiece();
	Piece * queen = new Queen{ this, file, rank, pieceColor };
	board_temp[rank][file].setPiece(queen);
	if (pieceColor == white) whitePieces.push_back(queen);
	else blackPieces.push_back(queen);
}

void Gameboard::copyRealToTempBoard()
{
	for (int i = 0; i < board.size(); i++) //przygotowuje tablice pomocnicza
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			board_temp[i][j].setPiece(board[i][j].getPiece());
		}
	}
}

void Gameboard::copyTempToRealBoard()
{
	for (int i = 0; i < board.size(); i++)
	{
		for (int j = 0; j < board[i].size(); j++)
		{
			board[i][j].setPiece(board_temp[i][j].getPiece());
		}
	}
}

whatsStandingThere Gameboard::whatStandsThere(int file, int rank) //sprawdza co stoi na polu o danych wspolrzednych
{
	if (file < 0 || file >= boardSize || rank < 0 || rank >= boardSize) return OutOfRange; //jesli wspolrzedne niepoprawne - zwraca wartosc OutOfRange
	else if (board_temp[rank][file].getPiece() == nullptr) return emptySquare; // jesli pole jest puste
	else return (whatsStandingThere)board_temp[rank][file].getPiece()->getPieceColor(); //jesli pole jest zajete - zwraca kolor bierki, ktora tam stoi
}

void Gameboard::print() //drukuje szachownice
{
	system("cls");
	cout << "   ";
	//for (auto it = board.begin(); it != board.end(); ++it)
	for (int i = 0; i < boardSize; i++)
	{
		cout << char('A' + i) << " ";
	}
	cout << endl;
	for (int i = boardSize - 1; i >= 0; i--)
	{
		cout << setw(2) << i + 1 << " ";
		for (auto it = board[i].begin(); it != board[i].end(); ++it) //iterator
		{
			if (auto piece = (*it).getPiece())
			{
				piece->printPiece();
			}
			else
				cout << " ";
			cout << " ";
		}
		cout << i + 1 << " \n";
	}
	cout << "   ";
	for (int i = 0; i < boardSize; i++)
	{
		cout << char('A' + i) << " ";
	}
	cout << endl;
}

bool Gameboard::checkForAnyPossibleMoves() //sprawdza, czy aktualny gracz ma jakikolwiek mozliwy ruch
{
	if (whoseMove == white)
	{
		for (Piece * piece : whitePieces) //iteruj po wszystkich bierkach gracza
		{
			if (piece->canMove() == true) return true; //jesli jakis pionek moze sie ruszyc, przerwij petle i zwroc true
		}
	}
	else //(whoseMove == black)
	{
		for (Piece * piece : blackPieces) //iteruj po wszystkich bierkach gracza
		{
			if (piece->canMove() == true) return true; //jesli jakis pionek moze sie ruszyc, przerwij petle i zwroc true
		}
	}
	return false; //jesli petle nie znalazly zadnej bierki, ktora moze sie ruszyc, zwroc false
}


bool Gameboard::tryToParse(string move_line) //probuje parsowac linie gracza, przerobic ja na ruchy //GOTOWE
{
	actualMove.clear();
	regex line_regex{ "^[a-zA-Z0-9 ]*$" }; //regex
	if (!regex_match(move_line, line_regex)) //jesli string zawiera znaki specjalne
	{
		cout << "string zawiera znaki specjalne" << endl;
		return false;
	}
	stringstream ss;
	ss << move_line;
	string single_move;
	while (ss >> single_move) //pobranie slowa ze stringa
	{
		int firstCord = static_cast<int>(single_move[0]);
		if (firstCord >= 'A' && firstCord <= 'Z') firstCord -= 'A';
		else if (firstCord >= 'a' && firstCord <= 'z') firstCord -= 'a';
		if (firstCord >= 0 && firstCord < boardSize)
		{
			string ingle_move = single_move.substr(1); //single_move ale bez pierwszej literki
			stringstream s(ingle_move);
			int secondCord;
			if (s >> secondCord) //proba przerobienia stringa na liczbe int
			{
				secondCord -= 1;
				if (secondCord >= 0 && secondCord < boardSize)
				{
					actualMove.push_back(Position{ firstCord, secondCord });
					continue;
				}
			}
		}
		return false;
	}
	if (actualMove.size() < 2) return false;
	else return true;
}

bool Gameboard::makeMoveIfCorrect() //sprawdza poprawnosc logiczna actualMove
{
	copyRealToTempBoard();
	if (actualMove.size() < 2) return false;
	if (whatStandsThere(actualMove[0].file, actualMove[0].rank) == emptySquare) return false;
	if (whoseMove == white)
	{
		if (whatStandsThere(actualMove[0].file, actualMove[0].rank) == blackPiece) return false;
		for (int i = 1; i < actualMove.size(); i++)
		{
			if (board_temp[actualMove[i-1].rank][actualMove[i-1].file].getPiece()->makeSingleStep(actualMove[i-1], actualMove[i]) == false) return false;
		}
		copyTempToRealBoard();
		return true;
	}
	if (whoseMove == black)
	{
		if (whatStandsThere(actualMove[0].file, actualMove[0].rank) == whitePiece) return false;
		for (int i = 1; i < actualMove.size(); i++)
		{
			if (board_temp[actualMove[0].rank][actualMove[0].file].getPiece()->makeSingleStep(actualMove[i - 1], actualMove[i]) == false) return false;
		}
		copyTempToRealBoard();
		return true;
	}
}

void Gameboard::waitForCorrectMove() //sprawdza kolejne ruchy wprowadzane przez gracza az trafi na poprawny
{
	string move_line;
	do
	{
		getline(cin, move_line);
		if(tryToParse(move_line) == false) actualMove.clear();
	}
	while (makeMoveIfCorrect() == false);
}

void Gameboard::changePlayerToMove() //przekazuje ruch drugiemu graczowi
{
	if (whoseMove == black) whoseMove = white;
	else whoseMove = black;
}

Gameboard::~Gameboard()
{
	for (Piece * pieceToDelete : blackPieces)
		delete pieceToDelete;
	for (Piece * pieceToDelete : whitePieces)
		delete pieceToDelete;

	for (auto row : board)
		for (auto square : row)
			square.setPiece(nullptr);
	for (auto row : board_temp)
		for (auto square : row)
			square.setPiece(nullptr);
}

