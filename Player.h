#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"


namespace modele 
{
	class Piece;
	class Player {
	public:
		Player() {};
		Player(bool whiteSide);
		std::string PlayerColor() const;
		Piece* PlayerPiece(Piece* piece);

	private:
		bool whiteSide_;
	};
}
#endif

