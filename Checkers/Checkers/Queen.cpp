#include "Queen.h"
#include "Gameboard.h"
#include <iostream>
using namespace std;

Queen::Queen(Gameboard * motherboard_, int file_, int rank_, Color pieceColor_) : Piece{ motherboard_, file_, rank_, pieceColor_ }
{
}

bool Queen::makeSingleStep(Position source, Position target)
{
	if (pieceColor == white)
	{
		if (abs(target.rank - source.rank) == abs(target.file - source.file)) //jesli ruszamy sie po przekatnej
		{
			if (motherboard->whatStandsThere(target.file, target.rank) == emptySquare) //jezeli jest tam pusto to zwracamy prawde
			{
				if (target.rank - source.rank > 0 && target.file - source.file > 0) //ruch w gore i w prawo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file + i, source.rank + i) == whitePiece) return false;
						if (motherboard->whatStandsThere(source.file + i, source.rank + i) == blackPiece)
						{
							motherboard->removePiece(source.file + i, source.rank + i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
				if (target.rank - source.rank < 0 && target.file - source.file > 0) //ruch w dol i w prawo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file + i, source.rank - i) == whitePiece) return false;
						if (motherboard->whatStandsThere(source.file + i, source.rank - i) == blackPiece)
						{
							motherboard->removePiece(source.file + i, source.rank - i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
				if (target.rank - source.rank < 0 && target.file - source.file < 0) //ruch w dol i w lewo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file - i, source.rank - i) == whitePiece) return false;
						if (motherboard->whatStandsThere(source.file - i, source.rank - i) == blackPiece)
						{
							motherboard->removePiece(source.file - i, source.rank - i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
				if (target.rank - source.rank > 0 && target.file - source.file < 0) //ruch w gore i w lewo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file - i, source.rank + i) == whitePiece) return false;
						if (motherboard->whatStandsThere(source.file - i, source.rank + i) == blackPiece)
						{
							motherboard->removePiece(source.file - i, source.rank + i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
			}
		}
	}
	else //(pieceColor == black)
	{
		if (abs(target.rank - source.rank) == abs(target.file - source.file)) //jesli ruszamy sie po przekatnej
		{
			if (motherboard->whatStandsThere(target.file, target.rank) == emptySquare) //jezeli jest tam pusto
			{
				if (target.rank - source.rank > 0 && target.file - source.file > 0) //ruch w gore i w prawo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file + i, source.rank + i) == blackPiece) return false;
						if (motherboard->whatStandsThere(source.file + i, source.rank + i) == whitePiece)
						{
							motherboard->removePiece(source.file + i, source.rank + i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
				if (target.rank - source.rank < 0 && target.file - source.file > 0) //ruch w dol i w prawo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file + i, source.rank - i) == blackPiece) return false;
						if (motherboard->whatStandsThere(source.file + i, source.rank - i) == whitePiece)
						{
							motherboard->removePiece(source.file + i, source.rank - i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
				if (target.rank - source.rank < 0 && target.file - source.file < 0) //ruch w dol i w lewo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file - i, source.rank - i) == blackPiece) return false;
						if (motherboard->whatStandsThere(source.file - i, source.rank - i) == whitePiece)
						{
							motherboard->removePiece(source.file - i, source.rank - i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
				if (target.rank - source.rank > 0 && target.file - source.file < 0) //ruch w gore i w lewo
				{
					for (int i = 1; i < abs(target.rank - source.rank); i++)
					{
						if (motherboard->whatStandsThere(source.file - i, source.rank + i) == blackPiece) return false;
						if (motherboard->whatStandsThere(source.file - i, source.rank + i) == whitePiece)
						{
							motherboard->removePiece(source.file - i, source.rank + i);
						}
					}
					motherboard->movePiece(source.file, source.rank, target.file, target.rank);
					return true;
				}
			}
		}
	}
	return false;
}

void Queen::printPiece()
{
	if (pieceColor == white)
		cout << "W";
	else cout << "B";
}

bool Queen::canMove()
{
	return true;
}



Queen::~Queen()
{
}
