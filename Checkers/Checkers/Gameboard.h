#pragma once
#include <vector>
#include "Square.h"
#include "Piece.h"
#include "Structures.h"
#include <string>

class Gameboard
{
public:
	Gameboard(int boardSize = 8, int rowOfPawns = 3); //konstruktor z parametrami domyslnymi
	void play(); //rozpoczyna gre
	int getSize(); //zwraca wymair planszy
	void movePiece(int source_file, int source_rank, int target_file, int target_rank);
	void removePiece(int file, int rank);
	void promotePawn(int file, int rank); //pionek -> krolowa
	void copyRealToTempBoard();
	void copyTempToRealBoard();
	whatsStandingThere whatStandsThere(int file, int rank); //sprawdza, co stoi na danym polu
	~Gameboard();

private:
	void print(); //drukuje szachownice
	void waitForCorrectMove(); //czeka na wprowadzenie poprawnego ruchu
	bool makeMoveIfCorrect(); //sprawdza czy ruch jest poprawny
	void changePlayerToMove(); //przekazuje ruch drugiemu graczowi
	bool checkForAnyPossibleMoves(); //sprawdza, czy gracz ma do dyspozycji jakikolwiek ruch, jesli nie to przegral
	bool tryToParse(std::string move_line); //probuje przerobic linie wpisana przez gracza na ruch do wykonania

	std::vector<Position> actualMove;
	const int boardSize; //rozmiar szachownicy
	const int rowOfPawns; //ile rzedow pionkow ma kazdy gracz
	std::vector<std::vector<Square>> board; //reprezentacja szachownicy
	std::vector<std::vector<Square>> board_temp; //reprezentacja szachownicy
	std::vector<Piece*> whitePieces; //wektor bierek bialego
	std::vector<Piece*> blackPieces; //wektor bierek czarnego
	Color whoseMove; //czyj ruch
};

