#include "Piece.h"
using namespace std;


namespace modele {
	Piece::Piece(bool white) :white_(white) {}

	bool Piece::isKilled() const
	{
		return killed_;
	}

	bool Piece::canBeKilled(Board& board, Spot* start, Spot* end) const
	{
		// Verifie si la piece choisie(start) peu capturer l'autre piece(end)
		if (start->getPiece()->pieceColor() != end->getPiece()->pieceColor()) {		// Verifie que la piece qu'on veut capturer n'est pas de la meme couleur
			if (start->getPiece()->canMove(board, start->getX(), start->getY(), end->getX(), end->getY())) {	// Verifie que le move est possible
				if (dynamic_cast<Empty*>(end->getPiece().get()) == nullptr) {		// Verifie qu'on ne capture pas une case vide
					return true;
				}
			}
		}
		return false;
	}

	void Piece::setKill()
	{
		killed_ = true;
	}

	// Classe du roi
	int King::count = 0;

	King::King(bool white) : Piece(white)
	{
		try {
			++count;
			if (count > 2)
			{
				throw logic_error("2");
			}

		}
		catch (logic_error& e) {
			cout << "il ne peut pas avoir plus de " << e.what() << " rois\n";
		}
	}

	King::~King()
	{
		--count;
	}


	const string King::getPieceName() const
	{
		return "Roi";
	}

	const string King::pieceColor() const
	{
		if (white_ == true)
			return "Blanc";
		else
			return "Noir";
	}

	bool King::canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY)
	{
		// Verifie que le move ne depasse pas les dimension de l'echequier
		if (startX < 0 || startY < 0 || endX < 0 || endY < 0) {
			return false;
		}
		if (startX > 7 || startY > 7 || endX > 7 || endY > 7) {
			return false;
		}

		int axisXAbs = abs(startX - endX);
		int axisYAbs = abs(startY - endY);

		// Verifie que le move est de 1 case
		if (axisXAbs <= 1 && axisYAbs <= 1) {
			// Verifie que le move n'est pas sur une piece de la meme couleur
			if (board.boxes[endX][endY].get()->getPiece()->pieceColor() != this->pieceColor() || dynamic_cast<Empty*>(board.boxes[endX][endY].get()->getPiece().get()) != nullptr) {
				return true;
			}
		}
		return false;
	}

	// Classe de la tour
	Rook::Rook(bool white) : Piece(white) {}

	const string Rook::getPieceName() const
	{
		return "Tour";
	}

	const string Rook::pieceColor() const
	{
		if (white_ == true)
			return "Blanc";
		else
			return "Noir";
	}

	bool Rook::canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY)
	{
		// Verifie que le move ne depasse pas les dimension de l'echequier
		if (startX < 0 || startY < 0 || endX < 0 || endY < 0) {
			return false;
		}
		if (startX > 7 || startY > 7 || endX > 7 || endY > 7) {
			return false;
		}

		int axisXAbs = abs(startX - endX);
		int axisYAbs = abs(startY - endY);

		// verifier que le case est vide ou contient une piece d'une autre couleur
		if (board.boxes[endX][endY].get()->getPiece()->pieceColor() != this->pieceColor() || dynamic_cast<Empty*>(board.boxes[endX][endY].get()->getPiece().get()) != nullptr) {

			// Direction horizontale
			if (axisYAbs == 0) {
				int sens = 0;
				if (startX < endX) {
					sens = 1;
				}
				else {
					sens = -1;
				}

				// Verifie qu'aucune piece bloque le move
				if (sens > 0) {
					for (int i = startX + 1; i != endX; i += sens) {
						if (dynamic_cast<Empty*>(board.boxes[i][startY].get()->getPiece().get()) == nullptr) {
							return false;
						}
					}
				}
				else {
					for (int i = startX - 1; i != endX; i += sens) {
						if (dynamic_cast<Empty*>(board.boxes[i][startY].get()->getPiece().get()) == nullptr) {
							return false;
						}
					}
				}
				return true;
			}

			// Direction verticale
			if (axisXAbs == 0) {
				int sens = 0;
				if (startY < endY) {
					sens = 1;
				}
				else {
					sens = -1;
				}
				if (sens > 0) {
					for (int i = startY + 1; i != endY; i += sens) {
						if (dynamic_cast<Empty*>(board.boxes[startX][i].get()->getPiece().get()) == nullptr)
							return false;
					}
				}
				else {
					for (int i = startY - 1; i != endY; i += sens) {
						if (dynamic_cast<Empty*>(board.boxes[startX][i].get()->getPiece().get()) == nullptr)
							return false;
					}
				}
				return true;
			}
		}
		return false;
	}


	// Classe du fou
	Bishop::Bishop(bool white) : Piece(white) {}

	const string Bishop::getPieceName() const
	{
		return "Fou";
	}

	const string Bishop::pieceColor() const
	{
		if (white_ == true)
			return "Blanc";
		else
			return "Noir";
	}

	bool Bishop::canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY)
	{
		// Verifie que le move ne depasse pas les dimension de l'echequier
		if (startX < 0 || startY < 0 || endX < 0 || endY < 0) {
			return false;
		}
		if (startX > 7 || startY > 7 || endX > 7 || endY > 7) {
			return false;
		}

		int axisXAbs = abs(startX - endX);
		int axisYAbs = abs(startY - endY);

		// verifier que le case est vide ou contient une piece d'une autre couleur
		if (board.boxes[endX][endY].get()->getPiece()->pieceColor() != this->pieceColor() || dynamic_cast<Empty*>(board.boxes[endX][endY].get()->getPiece().get()) != nullptr) {

			// Verifie que le mouvement est diagonale
			if (axisXAbs == axisYAbs) {
				int sensX = 0;
				if (startX < endX) {
					sensX = 1;
				}
				else {
					sensX = -1;
				}
				int sensY = 0;
				if (startY < endY) {
					sensY = 1;
				}
				else {
					sensY = -1;
				}

				int caseX = startX + sensX;
				int caseY = startY + sensY;

				// Verifie qu'il n'y aucune piece qui bloque le mouve
				while (caseX != endX && caseY != endY) {
					if (dynamic_cast<Empty*>(board.boxes[caseX][caseY].get()->getPiece().get()) == nullptr) {
						return false;
					}
					caseX += sensX;
					caseY += sensY;
				}
				return true;
			}
		}
		return false;
	}


	// Classe Empty represente une case vide
	const string Empty::getPieceName() const
	{
		return "Vide";
	}

	const string Empty::pieceColor() const
	{
		return "rien";
	}
	
	bool Empty::canMove(Board& board, const int& startX, const int& startY, const int& endX, const int& endY)
	{
		return false;
	}
}
