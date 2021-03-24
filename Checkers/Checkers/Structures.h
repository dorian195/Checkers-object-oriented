#pragma once

enum Color{ white = 0, black = 1};
enum whatsStandingThere{whitePiece = 0, blackPiece = 1, emptySquare, OutOfRange};

struct Position //repzezentuje pojedynczy punkt na szachownicy
{
	int file; //kolumna, rosnie od lewej do prawej
	int rank; //rzad, rosnie od dolu do gory
	Position(int file_, int rank_) : file{ file_ }, rank{ rank_ }{}; //prosty konstruktor
};