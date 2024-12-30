#ifndef SPOT_H
#define SPOT_H
#include"include.h"
#include "Piece.h"


namespace modele 
{
	class Piece;
	class Spot {
	public:
		Spot(int axisX, int axisY, std::shared_ptr<Piece> piece);
		std::shared_ptr<Piece> getPiece() const;	// Acc�de � la pi�ce qui est sur la case
		void setPiece(std::shared_ptr<Piece> piece); // Permet de modifier la pi�ce de la case
		const int getX() const;
		void setX(int x);	
		const int getY() const;
		void setY(int y);	

	private:
		std::shared_ptr<Piece> piece_;
		int axisX_;
		int axisY_;
	};
}
#endif

