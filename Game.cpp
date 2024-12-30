#include "Game.h"
using namespace std;


namespace modele {

	// Initialise la partie en initialisition l'echequier et les joueurs
	void Game::initializeNormal(Player& p1, Player& p2, Board& board)
	{
		player1_ = p1;
		player2_ = p2;

		board.resetBoardNormal();

		if (p1.PlayerColor() == "Blanc") {
			isWhiteTurn_ = true;
		}
		else {
			isWhiteTurn_ = false;
		}

		status_ = GameStatus::ACTIVE;
	}

	void Game::initializeThreeBishopOneRook(Player& p1, Player& p2, Board& board)
	{
		player1_ = p1;
		player2_ = p2;

		board.resetBoardThreeBishopOneRook();

		if (p1.PlayerColor() == "Blanc") {
			isWhiteTurn_ = true;
		}
		else {
			isWhiteTurn_ = false;
		}

		status_ = GameStatus::ACTIVE;
	}

	void Game::initializeThreeKing(Player& p1, Player& p2, Board& board)
	{
		player1_ = p1;
		player2_ = p2;

		board.resetBoardThreeKing();

		if (p1.PlayerColor() == "Blanc") {
			isWhiteTurn_ = true;
		}
		else {
			isWhiteTurn_ = false;
		}

		status_ = GameStatus::ACTIVE;
	}

	bool Game::isWhitePlayerCheck(Board& board)
	{
		// Verifier si le joueur blanc est en echec
		if (isWhiteTurn_ == true) {

			// Trouver la position du Roi blanc sur lechequier
			int x = 0;
			int y = 0;
			bool isWhiteKingFound = false;
			while (x < 8) {
				while (y < 8) {
					// Verifie si la piece est un Roi de couleur blanc
					if (dynamic_cast<King*>(board.boxes[x][y].get()->getPiece().get()) != nullptr && board.boxes[x][y].get()->getPiece()->pieceColor() == "Blanc") {
						isWhiteKingFound = true;
						break;
					}
					++y;
				}
				if (isWhiteKingFound) {
					break;
				}
				y = 0;
				++x;
			}
			Spot* whiteKing = board.boxes[x][y].get();

			// Trouver chaque piece noir et voir si elle peuvent capturer le roi blanc
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					// Verifie qu'une case contient une piece et que cette piece est noir
					if (dynamic_cast<Empty*>(board.boxes[i][j].get()->getPiece().get()) == nullptr && board.boxes[i][j].get()->getPiece()->pieceColor() == "Noir") {
						// Une fois la piece noir trouver, verifier quel peut capturer le roi Blanc
						if (board.boxes[i][j].get()->getPiece()->canBeKilled(board, board.boxes[i][j].get(), whiteKing)) {
							this->setStatus(GameStatus::ECHEC);
							return true;
						}
					}
				}
			}
			this->setStatus(GameStatus::ACTIVE);
			return false;
		}
		return false;
	}

	bool Game::isBlackPlayerCheck(Board& board)
	{
		// Verifier si le joueur noir est en echec
		if (isWhiteTurn_ == false) {
			// Trouver la position du Roi Noir sur lechequier
			int x = 0;
			int y = 0;
			bool isBlackKingFound = false;
			while (x < 8) {
				while (y < 8) {
					// Verifie si la piece est un Roi de couleur noir
					if (dynamic_cast<King*>(board.boxes[x][y].get()->getPiece().get()) != nullptr && board.boxes[x][y].get()->getPiece()->pieceColor() == "Noir") {
						isBlackKingFound = true;
						break;
					}
					++y;
				}
				if (isBlackKingFound) {
					break;
				}
				y = 0;
				++x;
			}
			Spot* blackKing = board.boxes[x][y].get();

			// Trouver chaque piece blanche et voir si elle peuvent capturer le roi noir
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					// Verifie qu'une case contient une piece et que cette piece est blanche
					if (dynamic_cast<Empty*>(board.boxes[i][j].get()->getPiece().get()) == nullptr && board.boxes[i][j].get()->getPiece()->pieceColor() == "Blanc") {
						// Une fois la piece blanche trouver, verifier quel peut capturer le roi noir
						if (board.boxes[i][j].get()->getPiece()->canBeKilled(board, board.boxes[i][j].get(), blackKing)) {
							this->setStatus(GameStatus::ECHEC);
							return true;
						}
					}
				}
			}
			this->setStatus(GameStatus::ACTIVE);
			return false;
		}
		return false;
	}

	bool Game::isWhitePlayerCheckmate(Board& board)
	{
		// Verifie l'echec et math pour le joueur blanc
		if (isWhiteTurn_ == true) {

			// Trouver la position du Roi blanc sur lechequier
			int x = 0;
			int y = 0;
			bool isWhiteKingFound = false;
			while (x < 8) {
				while (y < 8) {
					// Verifie si la piece est un Roi de couleur blanc
					if (dynamic_cast<King*>(board.boxes[x][y].get()->getPiece().get()) != nullptr && board.boxes[x][y].get()->getPiece()->pieceColor() == "Blanc") {
						isWhiteKingFound = true;
						break;
					}
					++y;
				}
				if (isWhiteKingFound) {
					break;
				}
				y = 0;
				++x;
			}
			Spot* whiteKing = board.boxes[x][y].get();	// position du roi blanc

			// Verifier que le roi est echec peut importe ses deplacements (8 deplacement possible max)
			// Si le roi est dans un coin
			if (x == 0 && y == 0) {
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}

			}
			else if (x == 7 && y == 0) {
				if (canMakeMove(board, whiteKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 0 && y == 7) {
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 7 && y == 7) {
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			// Si le roi est sur une extremite de l'echequier
			else if (x == 0) {
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 7) {
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (y == 0) {
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (y == 7) {
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			// Le roi est pas dans un coin ou extremite de l'echequier
			else {
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, whiteKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}

			// Verifier qu'aucune piece blanche peut empecher l'echec (en capturant la piece qui met le roi blanc en echec ou en bloquant l'echec)
			// Trouver tout les piece blanche de l'echequier (autre que le roi)
			int a = 0;
			int b = 0;
			int whitePieceCount = 0;	// Compte le nombre de piece pouvant capturer le roi blanc
			map<int, Spot*> whitePieces;	// Map contenant les pieces pouvant capturer le roi blanc

			while (a < 8) {
				while (b < 8) {
					// Verifie qu'une case contient une piece et que cette piece est blanche
					if (dynamic_cast<Empty*>(board.boxes[a][b].get()->getPiece().get()) == nullptr && dynamic_cast<King*>(board.boxes[a][b].get()->getPiece().get()) == nullptr &&
						board.boxes[a][b].get()->getPiece()->pieceColor() == "Blanc") {
						// Une fois la piece blanche trouver, verifier quel peut capturer le roi Blanc
						whitePieces.insert(pair<int, Spot*>(whitePieceCount, board.boxes[a][b].get())); // Ajoute la piece blanche a la liste
						++whitePieceCount;
					}
					++b;
				}
				b = 0;
				++a;
			}

			// Pour chaque piece blanche, verifier leur move possible et voir si leur move peuvent peuvent empecher l'echec
			for (auto piece : whitePieces) {

				// Verifier tout le type de mouvement possible selon le type de la piece
				// Verifier mouvement d'une tour
				if (dynamic_cast<Rook*>(piece.second->getPiece().get()) != nullptr) {
					Spot* initialSpot = piece.second;
					int initialX = piece.second->getX();
					int initialY = piece.second->getY();
					int tempValue = 0;

					// Faire une deep copy de la case contenant la piece (afin de verifier tout les mouvement sans affecter la piece original)
					unique_ptr<Spot> spotTemp = make_unique<Spot>(tempValue, initialY, make_shared<Rook>(true));

					// Verifier les mouvemens verticales de la tour blanche
					while (tempValue < 8) {

						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempValue;
						spotTemp.get()->setX(tempValue);
					}

					// Verifier les mouvemens horizontales de la tour blanche
					tempValue = 0;
					spotTemp.get()->setX(initialX);
					while (tempValue < 8) {
						spotTemp.get()->setY(tempValue);

						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempValue;
					}
				}
				// Verifier mouvement d'un fou blanc
				else if (dynamic_cast<Bishop*>(piece.second->getPiece().get()) == nullptr) {
					Spot* initialSpot = piece.second;
					int initialX = piece.second->getX();
					int initialY = piece.second->getY();
					int tempX = 0;
					int tempY = 0;

					// Faire une deep copy de la case contenant la piece (afin de verifier tout les mouvement sans affecter la piece original)
					unique_ptr<Spot> spotTemp = make_unique<Spot>(initialX, initialY, make_shared<Bishop>(true));

					// Verifier les mouvement diagonale (tant qu'on ne sort pas du board)
					// Verifier par direction 1er quadrant (++)
					tempX = initialX;
					tempY = initialY;
					while (tempX < 8 && tempY < 8) {
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempX;
						++tempY;
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
					}
					// Verifier par direction 2e quadrant (-+)
					tempX = initialX;
					tempY = initialY;
					while (tempX >= 0 && tempY < 8) {
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						--tempX;
						++tempY;
					}
					// Verifier par direction 3er quadrant (--)
					tempX = initialX;
					tempY = initialY;
					while (tempX >= 0 && tempY >= 0) {
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						--tempX;
						--tempY;
					}
					// Verifier par direction 4e quadrant (+-)
					tempX = initialX;
					tempY = initialY;
					while (tempX < 8 && tempY >= 0) {
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempX;
						--tempY;
					}
				}
			}
			return true;
		}
		return false;
	}

	bool Game::isBlackPlayerCheckmate(Board& board)
	{
		// Verifie l'echec et math pour le joueur noir
		if (isWhiteTurn_ == false) {

			// Trouver la position du Roi noir sur lechequier
			int x = 0;
			int y = 0;
			bool isBlackKingFound = false;
			while (x < 8) {
				while (y < 8) {
					// Verifie si la piece est un Roi de couleur noir
					if (dynamic_cast<King*>(board.boxes[x][y].get()->getPiece().get()) != nullptr && board.boxes[x][y].get()->getPiece()->pieceColor() == "Noir") {
						isBlackKingFound = true;
						break;
					}
					++y;
				}
				if (isBlackKingFound) {
					break;
				}
				y = 0;
				++x;
			}
			Spot* blackKing = board.boxes[x][y].get();	// position du roi noir

			// Verifier que le roi est echec peut importe ses deplacements (8 deplacement possible max)
			// Si le roi est dans un coin
			if (x == 0 && y == 0) {
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 7 && y == 0) {
				if (canMakeMove(board, blackKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 0 && y == 7) {
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 7 && y == 7) {
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			// Si le roi est sur une extremite de l'echequier
			else if (x == 0) {
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (x == 7) {
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (y == 0) {
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}
			else if (y == 7) {
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}

				if (canMakeMove(board, blackKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}

			}
			// Le roi est pas dans un coin ou extremite de l'echequier
			else {
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}

				if (canMakeMove(board, blackKing, board.boxes[x][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x + 1][y - 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
				if (canMakeMove(board, blackKing, board.boxes[x - 1][y + 1].get()) || status_ != GameStatus::ECHEC) {
					return false;
				}
			}

			// Verifier qu'aucune piece noir peut empecher l'echec (en capturant le roi ou en bloquant l'echec)
			// Trouver chaque piece noir de l'echequier pouvant potentiellement empecher l'echec (sauf le roi)
			int a = 0;
			int b = 0;
			int blackPieceCount = 0;	// Compte le nombre de piece pouvant capturer le roi noir
			map<int, Spot*> blackPieces;	// Map contenant les pieces pouvant capturer le roi noir

			while (a < 8) {
				while (b < 8) {
					// Verifie qu'une case contient une piece et que cette piece est noir
					if (dynamic_cast<Empty*>(board.boxes[a][b].get()->getPiece().get()) == nullptr && dynamic_cast<King*>(board.boxes[a][b].get()->getPiece().get()) == nullptr
						&& board.boxes[a][b].get()->getPiece()->pieceColor() == "Noir") {
						// Une fois la piece noir trouver, verifier quel peut capturer le roi noir
						blackPieces.insert(pair<int, Spot*>(blackPieceCount, board.boxes[a][b].get())); // Ajoute la piece noir a la liste
						++blackPieceCount;
					}
					++b;
				}
				b = 0;
				++a;
			}
			// Pour chaque piece, verifier leur move possible et voir si leur move peuvent peuvent empecher l'echec
			for (auto piece : blackPieces) {

				// Verifier mouvement d'une tour
				if (dynamic_cast<Rook*>(piece.second->getPiece().get()) != nullptr) {
					Spot* initialSpot = piece.second;
					int initialX = piece.second->getX();
					int initialY = piece.second->getY();
					int tempValue = 0;

					// Faire une deep copy de la case contenant la piece (afin de verifier tout les mouvement sans affecter la piece original)
					unique_ptr<Spot> spotTemp = make_unique<Spot>(tempValue, initialY, make_shared<Rook>(false));

					// Verifier tout les mouvement horizontale possible d'une tour blanche
					while (tempValue < 8) {
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempValue;
						spotTemp.get()->setX(tempValue);
					}

					// Verifier les mouvemens horizontales
					tempValue = 0;
					spotTemp.get()->setX(initialX);
					while (tempValue < 8) {
						spotTemp.get()->setY(tempValue);

						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempValue;
					}
				}
				// Verifier mouvement d'un fou
				else if (dynamic_cast<Bishop*>(piece.second->getPiece().get()) == nullptr) {
					Spot* initialSpot = piece.second;
					int initialX = piece.second->getX();
					int initialY = piece.second->getY();
					int tempX = 0;
					int tempY = 0;

					// Faire une deep copy de la case contenant la piece (afin de verifier tout les mouvement sans affecter la piece original)
					unique_ptr<Spot> spotTemp = make_unique<Spot>(initialX, initialY, make_shared<Bishop>(false));

					// Verifier tout les mouvement diagonale possible d'un fou blanc adverse
					// Verifier par direction 1er quadrant (++)
					tempX = initialX;
					tempY = initialY;
					while (tempX < 8 && tempY < 8) {
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempX;
						++tempY;
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
					}
					// Verifier par direction 2e quadrant (-+)
					tempX = initialX;
					tempY = initialY;
					while (tempX >= 0 && tempY < 8) {
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						--tempX;
						++tempY;
					}
					// Verifier par direction 3er quadrant (--)
					tempX = initialX;
					tempY = initialY;
					while (tempX >= 0 && tempY >= 0) {
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						--tempX;
						--tempY;
					}
					// Verifier par direction 4e quadrant (+-)
					tempX = initialX;
					tempY = initialY;
					while (tempX < 8 && tempY >= 0) {
						spotTemp.get()->setX(tempX);
						spotTemp.get()->setY(tempY);
						if (canMakeMove(board, initialSpot, spotTemp.get())) {	// Verifier si le move est possible
							return false;
						}
						++tempX;
						--tempY;
					}
				}
			}
			return true;
		}
		return false;
	}

	GameStatus Game::getStatus() const
	{
		return status_;
	}

	void Game::setStatus(GameStatus status)
	{
		status_ = status;
	}

	void Game::playerMove(Player player, Board& board, Spot* start, Spot* end)
	{
		if (canMakeMove(board, start, end)) {

			// Verifier si une piece est capturer
			if (start->getPiece()->canBeKilled(board, start, end) == true) {
				end->getPiece()->setKill();
			}

			// changer le tour a l'autre couleur
			if (isWhiteTurn_ && player1_.PlayerColor() == "Blanc") {
				isWhiteTurn_ = false;
			}
			else {
				isWhiteTurn_ = true;
			}

			if (end->getPiece()->isKilled() == true) {	// Verifie si une piece a été capturé
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());
			}
			else {
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());
			}
			emit pieceBouge(start->getPiece().get()); //signal pour dire que la piece a bougé
		}
	}

	bool Game::canMakeMove(Board& board, Spot* start, Spot* end)
	{
		// Verifier que c'est le bon joueur qui joue (cote blanc)
		if (start->getPiece()->pieceColor() == "Blanc" && isWhiteTurn_ == false) {
			return false;
		}

		// Verifier que c'est le bon joueur qui joue (cote noir)
		if (start->getPiece()->pieceColor() == "Noir" && isWhiteTurn_ == true) {
			return false;
		}

		// Verifier que le joueur veut bouger une piece et non une case vide
		if (dynamic_cast<Empty*>(start->getPiece().get()) != nullptr) {
			return false;
		}

		// Verifier que le move est valide
		if (!start->getPiece()->canMove(board, start->getX(), start->getY(), end->getX(), end->getY())) {
			return false;
		}

		// Verifier que le joueur n'essaye pas de capturer directement le roi adverse
		if (dynamic_cast<King*>(end->getPiece().get()) != nullptr) {
			return false;
		}

		// Verifier que le move ne cause pas un echec
		if (isWhiteTurn_ == true) {

			// Joueur blanc fait son move
			if (dynamic_cast<Empty*>(end->getPiece().get()) != nullptr) {
				shared_ptr<Piece> endTemp = dynamic_pointer_cast<Empty>(end->getPiece());
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());

				// Verifie si le move met le joueur blanc en echec
				if (isWhitePlayerCheck(board) == true) {
					// Annuler le move
					start->setPiece(end->getPiece());
					end->setPiece(endTemp);
					return false;
				}
				// Annuler le move
				start->setPiece(end->getPiece());
				end->setPiece(endTemp);
			}
			else if (dynamic_cast<Rook*>(end->getPiece().get()) != nullptr) {
				shared_ptr<Piece> endTemp = dynamic_pointer_cast<Rook>(end->getPiece());
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());

				// Verifie si le move met le joueur blanc en echec
				if (isWhitePlayerCheck(board) == true) {
					// Annuler le move
					start->setPiece(end->getPiece());
					end->setPiece(endTemp);
					return false;
				}
				// Annuler le move
				start->setPiece(end->getPiece());
				end->setPiece(endTemp);
			}
			else if (dynamic_cast<Bishop*>(end->getPiece().get()) != nullptr) {
				shared_ptr<Piece> endTemp = dynamic_pointer_cast<Bishop>(end->getPiece());
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());

				// Verifie si le move met le joueur blanc en echec
				if (isWhitePlayerCheck(board) == true) {
					// Annuler le move
					start->setPiece(end->getPiece());
					end->setPiece(endTemp);
					return false;
				}
				// Annuler le move
				start->setPiece(end->getPiece());
				end->setPiece(endTemp);
			}
			return true;
		}
		else if (isWhiteTurn_ == false) {
			// Joueur blanc fait son move
			if (dynamic_cast<Empty*>(end->getPiece().get()) != nullptr) {
				shared_ptr<Piece> endTemp = dynamic_pointer_cast<Empty>(end->getPiece());
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());

				// Verifie si le move met le joueur blanc en echec
				if (isBlackPlayerCheck(board) == true) {
					// Annuler le move
					start->setPiece(end->getPiece());
					end->setPiece(endTemp);
					return false;
				}
				// Annuler le move
				start->setPiece(end->getPiece());
				end->setPiece(endTemp);
			}
			else if (dynamic_cast<Rook*>(end->getPiece().get()) != nullptr) {
				shared_ptr<Piece> endTemp = dynamic_pointer_cast<Rook>(end->getPiece());
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());

				// Verifie si le move met le joueur blanc en echec
				if (isBlackPlayerCheck(board) == true) {
					// Annuler le move
					start->setPiece(end->getPiece());
					end->setPiece(endTemp);
					return false;
				}
				// Annuler le move
				start->setPiece(end->getPiece());
				end->setPiece(endTemp);
			}
			else if (dynamic_cast<Bishop*>(end->getPiece().get()) != nullptr) {
				shared_ptr<Piece> endTemp = dynamic_pointer_cast<Bishop>(end->getPiece());
				end->setPiece(start->getPiece());
				start->setPiece(make_shared<Empty>());

				// Verifie si le move met le joueur blanc en echec
				if (isBlackPlayerCheck(board) == true) {
					// Annuler le move
					start->setPiece(end->getPiece());
					end->setPiece(endTemp);
					return false;
				}
				// Annuler le move
				start->setPiece(end->getPiece());
				end->setPiece(endTemp);
			}
			return true;
		}
	}

	void Game::movecase(Board& board, int i_, int j_, int i, int j)
	{
		if (board.boxes[i_][j_].get()->getPiece()->pieceColor() == this->player1_.PlayerColor())
			this->playerMove(player1_, board, board.boxes[i_][j_].get(), board.boxes[i][j].get());
		else if (board.boxes[i_][j_].get()->getPiece()->pieceColor() == this->player2_.PlayerColor())
			this->playerMove(player2_, board, board.boxes[i_][j_].get(), board.boxes[i][j].get());
	}

	void Game::clearGame(Board& board)
	{
		board.clearBoard();
	}
}
