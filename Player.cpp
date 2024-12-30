
#include <cmath>
#include <memory>
#include <iostream>
#include <list>
#include <array>
#include <functional>
#include "Player.h"
#include "Piece.h"

using namespace std;
namespace modele {
	Player::Player(bool whiteSide) : whiteSide_(whiteSide) {}

	string Player::PlayerColor() const
	{
		if (whiteSide_ == true)
			return "Blanc";
		else
			return "Noir";
	}

	Piece* Player::PlayerPiece(Piece* piece)
	{
		if (this->PlayerColor() == piece->pieceColor())
			return piece;
		else
			return nullptr;
	}
}
