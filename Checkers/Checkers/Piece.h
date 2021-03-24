#pragma once
#include "Structures.h"

class Gameboard;

class Piece //bierka, po niej dziedziczy pionek i krolowa
{
public:
	Piece(Gameboard * motherboard_, int file, int rank, Color pieceColor_); //konstruktor
	Color getPieceColor(); //zwraca kolor pionka
	virtual bool canMove() = 0; //funkcja wirtualna, sprawdza, czy dany pionek moze sie ruszyc
	virtual bool makeSingleStep(Position source, Position target) = 0;
	virtual void printPiece() = 0;
	virtual ~Piece(); //destruktor

protected:
	Gameboard * motherboard; //wskaznik na szachownice, na ktorej ustawiony jest pionek
	Color pieceColor; //kolor pionka
	int rank; //rzad, liczy sie od dolu
	int file; //kolumna, liczy sie od lewej
};

