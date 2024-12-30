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
		void resetBoardNormal();	// Pemet d'initialiser un �chiquier avec les positions de bases pour chaque pi�ce demand�
		void resetBoardThreeBishopOneRook();	// Permet d'initialiser un �chiquier avec trois fous et une tour
		void resetBoardThreeKing();	// Permet d'initialiser un �chiquer avec trois King
		void clearBoard();
		
		std::unique_ptr<Spot> boxes[8][8];	// cr�e une matrice qui correspondra � notre �chiquier avec une taille 8X8

	};
}
# endif