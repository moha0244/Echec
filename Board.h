#ifndef BOARD_H
#define BOARD_H

#include "Include.h"
#include "Spot.h"

namespace modele 
{
	class Spot;
	class Board {
	public:
		Board();
		void resetBoardNormal();	// Pemet d'initialiser un échiquier avec les positions de bases pour chaque pièce demandé
		void resetBoardThreeBishopOneRook();	// Permet d'initialiser un échiquier avec trois fous et une tour
		void resetBoardThreeKing();	// Permet d'initialiser un échiquer avec trois King
		void clearBoard();
		
		std::unique_ptr<Spot> boxes[8][8];	// crée une matrice qui correspondra à notre échiquier avec une taille 8X8

	};
}
# endif