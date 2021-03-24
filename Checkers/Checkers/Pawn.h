#pragma once
#include "Piece.h"
class Pawn : public Piece //pionek dziedziczy publicznie po bierce
{
public:
	Pawn(Gameboard * motherboard_, int file, int rank, Color pieceColor_); //konstruktor
	bool makeSingleStep(Position source, Position target) override;
	void printPiece() override;
	bool canMove() override; //nadpisanie funkcji wirtualnej, ktora sprawdza, czy pionek moze sie ruszyc
	virtual ~Pawn(); //destruktor
};

