#ifndef PIECE_H
#define PIECE_H

#include "include.h"
#include "Spot.h"
#include "Board.h"


namespace modele 
{
	class Spot;
	class Board;
	class Piece {
	public:
		Piece() {};
		Piece(bool White);
		virtual ~Piece() = default;
		virtual const std::string pieceColor() const = 0;
		virtual const std::string getPieceName() const = 0;
		virtual bool canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY) = 0;
		bool isKilled() const;
		bool canBeKilled(Board& board, Spot* start, Spot* end) const;
		void setKill();

	protected:
		bool killed_ = false;
		bool white_ = false;
	};

	class King : public Piece {
	public:
		King(bool white);
		~King();
		const std::string getPieceName() const override;
		const std::string pieceColor() const override;
		bool canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY) override;
		static int count;
	};

	class Rook : public Piece {
	public:
		Rook(bool white);
		const std::string getPieceName() const override;
		const std::string pieceColor() const override;
		bool canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY) override;
	};

	class Bishop : public Piece {
	public:
		Bishop(bool white);
		const std::string getPieceName() const override;
		const std::string pieceColor() const override;
		bool canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY) override;

	};

	class Empty : public Piece {
	public:
		Empty() : Piece() {};
		const std::string getPieceName() const override;
		const std::string pieceColor() const override;
		bool canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY) override;
	};
}
# endif