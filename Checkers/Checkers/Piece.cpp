#include "Piece.h"
#include "Gameboard.h"


Piece::Piece(Gameboard * board_, int file_, int rank_, Color pieceColor_)
	: motherboard{ board_ }, pieceColor{ pieceColor_ }, file{ file_ }, rank{ rank_ }
{
}

Color Piece::getPieceColor()
{
	return pieceColor;
}


Piece::~Piece()
{
}
