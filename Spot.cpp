#include "Spot.h"
#include "Piece.h"

using namespace std;
namespace modele {
	Spot::Spot(int axisX, int axisY, std::shared_ptr<Piece>piece) :axisX_(axisX), axisY_(axisY), piece_(piece) {}

	std::shared_ptr<Piece>Spot::getPiece() const
	{
		return piece_;
	}

	void Spot::setPiece(std::shared_ptr<Piece>piece)
	{
		piece_ = piece;

	}

	const int Spot::getX() const
	{
		return axisX_;
	}

	void Spot::setX(int x)
	{
		axisX_ = x;
	}

	const int Spot::getY() const
	{
		return axisY_;
	}

	void Spot::setY(int y)
	{
		axisY_ = y;
	}
}