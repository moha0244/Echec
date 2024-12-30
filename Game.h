#ifndef GAME_H
#define GAME_H

#include "Include.h"
#include "Player.h"
#include "Board.h"
#include <QObject>


namespace modele {
	enum class GameStatus
	{
		ACTIVE,
		ECHEC,
	};

	class Game : public QObject {
		Q_OBJECT;
	public:
		Game() {}; 
		GameStatus getStatus() const;
		void setStatus(GameStatus status);
		bool isWhitePlayerCheck(Board& board);
		bool isBlackPlayerCheck(Board& board);
		bool isWhitePlayerCheckmate(Board& board);
		bool isBlackPlayerCheckmate(Board& board);
		void initializeNormal(Player& p1, Player& p2, Board& board);
		void initializeThreeBishopOneRook(Player& p1, Player& p2, Board& board);
		void initializeThreeKing(Player& p1, Player& p2, Board& board);
		void clearGame(Board& board);
		bool canMakeMove(Board& board, Spot* start, Spot* end);

	public slots:
		void playerMove(Player player, Board& board, Spot* start, Spot* end);
		void movecase(Board& board, int i_, int j_, int i, int j);

	signals:
		void pieceBouge(Piece* piece);

	protected:
		Player player1_;
		Player player2_;
		bool isWhiteTurn_;
		GameStatus status_;
	};
}
#endif
