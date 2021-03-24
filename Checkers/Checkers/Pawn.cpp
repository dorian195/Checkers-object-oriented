#include "Pawn.h"
#include "Gameboard.h"
#include <iostream>
using namespace std;

Pawn::Pawn(Gameboard * motherboard_, int file_, int rank_, Color pieceColor_) : Piece{motherboard_, file_, rank_, pieceColor_}
{
}

bool Pawn::makeSingleStep(Position source, Position target)
{
	if (pieceColor == white)
	{
		if (target.rank - source.rank == 1 && abs(target.file - source.file) == 1) //jesli ruszamy sie do gory o jeden po skosie
		{
			if (motherboard->whatStandsThere(target.file, target.rank) == emptySquare) //jezeli jest tam pusto to zwracamy prawde
			{
				motherboard->movePiece(source.file, source.rank, target.file, target.rank);
				if (target.rank == motherboard->getSize() - 1) motherboard->promotePawn(target.file, target.rank);
				return true;
			}
		}
		if (abs(target.rank - source.rank) == 2 && abs(target.file - source.file) == 2) //jesli bijemy cos
		{
			if (motherboard->whatStandsThere(target.file, target.rank) == emptySquare) //jezeli miejsce docelowe jest puste
			{
				if (motherboard->whatStandsThere((target.file + source.file) / 2, (target.rank + source.rank) / 2) == blackPiece) //jesli bijemy czarnego
				{
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					motherboard->removePiece((source.file + target.file) / 2, (source.rank + target.rank) / 2);
					if (target.rank == motherboard->getSize() - 1) motherboard->promotePawn(target.file, target.rank);
					return true;
				}
			}
		}
	}
	else //(pieceColor == black)
	{
		if (target.rank - source.rank == -1 && abs(target.file - source.file) == 1) //jesli ruszamy sie w dol o jeden po skosie
		{
			if (motherboard->whatStandsThere(target.file, target.rank) == emptySquare) //jezeli jest tam pusto to zwracamy prawde
			{
				motherboard->movePiece(source.file, source.rank, target.file, target.rank);
				if (target.rank == 0) motherboard->promotePawn(target.file, target.rank);
				return true;
			}
		}
		if (abs(target.rank - source.rank) == 2 && abs(target.file - source.file) == 2) //jesli bijemy cos
		{
			if (motherboard->whatStandsThere(target.file, target.rank) == emptySquare) //jezeli miejsce docelowe jest puste
			{
				if (motherboard->whatStandsThere((target.file + source.file) / 2, (target.rank + source.rank) / 2) == whitePiece) //jesli bijemy bialego
				{
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					motherboard->removePiece((source.file + target.file) / 2, (source.rank + target.rank) / 2);
					if (target.rank == 0) motherboard->promotePawn(target.file, target.rank);
					return true;
				}
			}
		}
	}
	return false;
}

void Pawn::printPiece()
{
	if (pieceColor == white)
		cout << "w";
	else cout << "b";
}

bool Pawn::canMove()
{
	whatsStandingThere there;
	if (pieceColor == white)
	{
		there = motherboard->whatStandsThere(file + 1, rank + 1);
		if (there == emptySquare) return true;
		else if (there == blackPiece)
			if (motherboard->whatStandsThere(file + 2, rank + 2) == emptySquare)
				return true;
		there = motherboard->whatStandsThere(file - 1, rank + 1);
		if (there == emptySquare) return true;
		else if (there == blackPiece)
			if (motherboard->whatStandsThere(file - 2, rank + 2) == emptySquare)
				return true;
		there = motherboard->whatStandsThere(file - 1, rank - 1);
		if (there == blackPiece)
			if (motherboard->whatStandsThere(file - 2, rank - 2) == emptySquare)
				return true;
		there = motherboard->whatStandsThere(file + 1, rank - 1);
		if (there == blackPiece)
			if (motherboard->whatStandsThere(file + 2, rank - 2) == emptySquare)
				return true;
		return false;
	}
	else //(pieceColor == black)
	{
		there = motherboard->whatStandsThere(file + 1, rank - 1);
		if (there == emptySquare) return true;
		else if (there == whitePiece)
			if (motherboard->whatStandsThere(file + 2, rank - 2) == emptySquare)
				return true;
		there = motherboard->whatStandsThere(file - 1, rank - 1);
		if (there == emptySquare) return true;
		else if (there == whitePiece)
			if (motherboard->whatStandsThere(file - 2, rank - 2) == emptySquare)
				return true;
		there = motherboard->whatStandsThere(file - 1, rank + 1);
		if (there == whitePiece)
			if (motherboard->whatStandsThere(file - 2, rank + 2) == emptySquare)
				return true;
		there = motherboard->whatStandsThere(file + 1, rank + 1);
		if (there == whitePiece)
			if (motherboard->whatStandsThere(file + 2, rank + 2) == emptySquare)
				return true;
		return false;
	}
}

Pawn::~Pawn()
{
}
