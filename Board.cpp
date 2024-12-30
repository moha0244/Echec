#include "Board.h"
using namespace std;


namespace modele {
	Board::Board() {}

	void Board::resetBoardNormal()
	{
		//initialiser les pieces blanches
		boxes[0][0] = make_unique<Spot>(0, 0, std::make_shared<Rook>(true));
		boxes[0][7] = make_unique<Spot>(0, 7, std::make_shared<Rook>(true));
		boxes[0][2] = make_unique<Spot>(0, 2, std::make_shared<Bishop>(true));
		boxes[0][5] = make_unique<Spot>(0, 5, std::make_shared<Bishop>(true));
		boxes[0][3] = make_unique<Spot>(0, 3, std::make_shared<King>(true));

		//initialiser les pieces noires
		boxes[7][0] = make_unique<Spot>(7, 0, std::make_shared<Rook>(false));
		boxes[7][7] = make_unique<Spot>(7, 7, std::make_shared<Rook>(false));
		boxes[7][2] = make_unique<Spot>(7, 2, std::make_shared<Bishop>(false));
		boxes[7][5] = make_unique<Spot>(7, 5, std::make_shared<Bishop>(false));
		boxes[7][3] = make_unique<Spot>(7, 3, std::make_shared<King>(false));

		//initialiser les cases restantes avec des case vides
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<Spot*>(boxes[i][j].get()) == nullptr) {
					boxes[i][j] = make_unique<Spot>(i, j, std::make_shared<Empty>());
				}
			}
		}
	}

	void Board::resetBoardThreeBishopOneRook()
	{
		//initialiser les pieces blanches
		boxes[0][0] = make_unique<Spot>(0, 0, std::make_shared<Rook>(true));
		boxes[0][7] = make_unique<Spot>(0, 7, std::make_shared<Bishop>(true));
		boxes[1][2] = make_unique<Spot>(1, 2, std::make_shared<Bishop>(true));
		boxes[1][5] = make_unique<Spot>(1, 5, std::make_shared<Bishop>(true));
		boxes[0][3] = make_unique<Spot>(0, 3, std::make_shared<King>(true));

		//initialiser les pieces noires
		boxes[7][0] = make_unique<Spot>(7, 0, std::make_shared<Rook>(false));
		boxes[7][7] = make_unique<Spot>(7, 7, std::make_shared<Bishop>(false));
		boxes[6][2] = make_unique<Spot>(6, 2, std::make_shared<Bishop>(false));
		boxes[6][5] = make_unique<Spot>(6, 5, std::make_shared<Bishop>(false));
		boxes[7][3] = make_unique<Spot>(7, 3, std::make_shared<King>(false));

		//initialiser les cases restantes avec des case vides
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<Spot*>(boxes[i][j].get()) == nullptr) {
					boxes[i][j] = make_unique<Spot>(i, j, std::make_shared<Empty>());
				}
			}
		}
	}

	void Board::resetBoardThreeKing()
	{
		//initialiser les pieces blanches
		boxes[0][0] = make_unique<Spot>(0, 0, std::make_shared<Rook>(true));
		boxes[0][6] = make_unique<Spot>(0, 6, std::make_shared<Rook>(true));
		boxes[1][2] = make_unique<Spot>(1, 2, std::make_shared<Bishop>(true));
		boxes[0][5] = make_unique<Spot>(0, 5, std::make_shared<Bishop>(true));
		boxes[1][4] = make_unique<Spot>(1, 4, std::make_shared<King>(true));
		boxes[1][5] = make_unique<Spot>(1, 5, std::make_shared<King>(true));

		//initialiser les pieces noires
		boxes[7][0] = make_unique<Spot>(7, 0, std::make_shared<Rook>(false));
		boxes[7][6] = make_unique<Spot>(7, 6, std::make_shared<Rook>(false));
		boxes[6][2] = make_unique<Spot>(6, 2, std::make_shared<Bishop>(false));
		boxes[7][5] = make_unique<Spot>(7, 5, std::make_shared<Bishop>(false));
		boxes[6][4] = make_unique<Spot>(6, 4, std::make_shared<King>(false));

		//initialiser les cases restantes avec des case vides
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<Spot*>(boxes[i][j].get()) == nullptr) {
					boxes[i][j] = make_unique<Spot>(i, j, std::make_shared<Empty>());
				}
			}
		}
	}

	void Board::clearBoard() // remplaceer toutes les pièces par des cases vides
	{
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<Empty*>(boxes[i][j].get()->getPiece().get()) == nullptr) {
					boxes[i][j] = make_unique<modele::Spot>(i, j, std::make_shared<Empty>());
				}
			}
		}
	}

}
