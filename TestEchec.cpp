#include "Game.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Game, formedebase) {
	// ce test sert à savoir si le board est bien rempli, on essaye pour le premier board vu qu'ils ont tous le meme fonctionnement
	modele::Game game;
	modele::Board board;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Vérifier que la taille de l'échiquier est correct
	EXPECT_EQ(size(board.boxes), 8);
	for (int i = 0; i < 8; i++)
		EXPECT_EQ(size(board.boxes[i]), 8);

	modele::King king(true);
	// Vérifier que le roi blanc est à la bonne place
	EXPECT_EQ(board.boxes[0][3].get()->getPiece().get()->getPieceName(), king.getPieceName());
	EXPECT_EQ(board.boxes[0][3].get()->getPiece().get()->pieceColor(), king.pieceColor());
	modele::King king1(false);
	// Vérifier que le roi noir est à la bonne place
	EXPECT_EQ(board.boxes[7][3].get()->getPiece().get()->getPieceName(), king1.getPieceName());
	EXPECT_EQ(board.boxes[7][3].get()->getPiece().get()->pieceColor(), king1.pieceColor());
	modele::Rook rook(true);
	// Vérifier que la tour blanche est à la bonne place
	EXPECT_EQ(board.boxes[0][0].get()->getPiece().get()->getPieceName(), rook.getPieceName());
	EXPECT_EQ(board.boxes[0][0].get()->getPiece().get()->pieceColor(), rook.pieceColor());
	modele::Rook rook1(false);
	// Vérifier que la tour noire est à la bonne place
	EXPECT_EQ(board.boxes[7][0].get()->getPiece().get()->getPieceName(), rook1.getPieceName());
	EXPECT_EQ(board.boxes[7][0].get()->getPiece().get()->pieceColor(), rook1.pieceColor());
	modele::Bishop bishoop(true);
	// Vérifier que le fou blanc est à la bonne place
	EXPECT_EQ(board.boxes[0][5].get()->getPiece().get()->getPieceName(), bishoop.getPieceName());
	EXPECT_EQ(board.boxes[0][5].get()->getPiece().get()->pieceColor(), bishoop.pieceColor());
	modele::Bishop bishop1(false);
	EXPECT_EQ(board.boxes[7][5].get()->getPiece().get()->getPieceName(), bishop1.getPieceName());
	EXPECT_EQ(board.boxes[7][5].get()->getPiece().get()->pieceColor(), bishop1.pieceColor());
	
	// Vérifier pour empty
	game.clearGame(board);
	// Vérifier que l'échiquier est vide
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			EXPECT_EQ(board.boxes[i][j].get()->getPiece().get()->getPieceName(), "Vide");
}

TEST(king, movement) {// Vérifer tous les mouvements du roi
	modele::Game game;
	modele::Board board;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Roi blanc (un pas à droite) vraie
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[0][4].get()));
	// Roi blanc, un pas à la diagonale vraie
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[1][4].get()));
	// Roi blanc un pas à gauche(est vraie en temps normale mais cet emplacement est occupée par une autre pièce de la meme couleur donc faux)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[0][2].get()));
	// Roi blanc un pas en diagnole en haut à gauche (vrai)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[1][2].get()));
	// Roi Blanc, un pas en avant (vraie)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[1][3].get()));
	// Roi blanc, un pas en diagonale gauche (vraie)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[1][2].get()));
	// roi blanc deux pas en avant (faux)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[2][3].get()));
	// Roi blanc deux pas en avant et un pas à gauche (faux)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[2][2].get()));

	try {
		board.boxes[6][4] = make_unique<modele::Spot>(6, 4, std::make_shared<modele::King>(false));
	}
	catch (std::logic_error& e)	{}
	EXPECT_EQ(dynamic_cast<modele::King*>(board.boxes[6][4].get()->getPiece().get())->count, 3);

	game.clearGame(board);
}

TEST(Rook, movement) {
	modele::Game game;
	modele::Board board;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Tour blanche 4 pas à droite (faux car il y'a des pièces de la meme couleur sur le chemin)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][0].get(), board.boxes[0][4].get()));
	// Tour blanche un pas à droite, vraie
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][0].get(), board.boxes[0][1].get()));
	// Tour blanche , 6 pas en avant (vraie)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][0].get(), board.boxes[6][0].get()));
	// Tour blanche 4 pas en avant et un pas à droite(faux, pas de diagonale)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][0].get(), board.boxes[4][1].get()));
	// Tour blanche 3 pas en avant et 3 pas à droite(faux, pas de diagonale)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][0].get(), board.boxes[3][3].get()));
	// Tour blanche, un pas à gauche vraie
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][7].get(), board.boxes[0][6].get()));

	game.clearGame(board);
}

TEST(bishop, movement) {
	modele::Game game;
	modele::Board board;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// fou blanc 1 pas en diagonale en haut à gauche
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][2].get(), board.boxes[1][1].get()));
	// Fou blanc, 4 pas en diagonale droite, vraie
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][2].get(), board.boxes[4][6].get()));
	// fou blanc, 2 pas en avant, faux (que des diagonales)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][2].get(), board.boxes[4][2].get()));
	// fou blanc en  2 pas diagonale droite (vraie)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][2].get(), board.boxes[2][0].get()));
	// fou blanc en 5 pas en avant et 3 pas à gauche(faux vu que le nobre de pas en avant est supérieure à celle de gauche)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][2].get(), board.boxes[5][3].get()));
	// fou blanc, un pas à droite (faux, seulement en diagonale)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][2].get(), board.boxes[0][1].get()));

	game.clearGame(board);
}
TEST(partie, simple) {// Pour vérifier que le joueur joue chacun à son tour
	modele::Game game;
	modele::Board board;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Joueur noire qui essaye de commencer (faux, c'est l'une des raisons pour laquelle on a testé les mouvements avec le joueur blanc dans les autres tests)
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[7][7].get(), board.boxes[5][7].get()));
	// Joueur Blanc qui commence la game (vrai)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[0][3].get(), board.boxes[0][4].get()));
	game.playerMove(whitePlayer, board, board.boxes[0][3].get(), board.boxes[0][4].get());
	// Vérifier que la pièce est vide après le départ du roi blanc;
	EXPECT_EQ(board.boxes[0][3].get()->getPiece().get()->getPieceName(), "Vide");
	// Joueur blanc qui essaye de rejouer une game alors que ce n'est pas son tour
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[0][4].get(), board.boxes[1][4].get()));
	// Tour du joueur noire qui essaye de jouer après le joueur blanc(vraie)
	EXPECT_TRUE(game.canMakeMove(board, board.boxes[7][5].get(), board.boxes[5][7].get()));
	game.playerMove(blackPlayer, board, board.boxes[7][5].get(), board.boxes[5][7].get());
	// joueur noire qui essaye de rejouer une game alors que ce n'est pas son tour
	EXPECT_FALSE(game.canMakeMove(board, board.boxes[5][7].get(), board.boxes[3][7].get()));

	game.clearGame(board);
}


TEST(game, echec) {
	//Initialiser la partie
	modele::Game game;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	modele::Board board;
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Test echec
	EXPECT_FALSE(game.isWhitePlayerCheck(board));	// Verifie que le roi blanc est en echec des le depart
	game.playerMove(whitePlayer, board, board.boxes[0][0].get(), board.boxes[2][0].get());
	EXPECT_FALSE(game.isBlackPlayerCheck(board));		// Verifie que le roi noir est en echec des le depart
	game.playerMove(blackPlayer, board, board.boxes[7][5].get(), board.boxes[5][3].get());
	game.playerMove(whitePlayer, board, board.boxes[2][0].get(), board.boxes[2][3].get());
	EXPECT_FALSE(game.isWhitePlayerCheck(board));	// Verifie que le roi noir est protege par son fou et n'est donc pas en echec
	game.playerMove(blackPlayer, board, board.boxes[7][0].get(), board.boxes[5][0].get());
	game.playerMove(whitePlayer, board, board.boxes[2][3].get(), board.boxes[7][3].get());
	game.playerMove(whitePlayer, board, board.boxes[2][3].get(), board.boxes[5][3].get());
	EXPECT_TRUE(game.isBlackPlayerCheck(board));	// Tour blanche capture le fou noir et met le roi noir en echec
	game.playerMove(blackPlayer, board, board.boxes[7][3].get(), board.boxes[7][4].get());
	EXPECT_FALSE(game.isBlackPlayerCheck(board));	// Roi noir move et enleve l'echec
	game.playerMove(whitePlayer, board, board.boxes[0][3].get(), board.boxes[1][3].get());
	game.playerMove(blackPlayer, board, board.boxes[7][7].get(), board.boxes[1][7].get());
	EXPECT_TRUE(game.isWhitePlayerCheck(board));	// Le tour noir se deplace en diagonale et met le roi blanc en echec
	game.playerMove(whitePlayer, board, board.boxes[1][3].get(), board.boxes[2][3].get());
	EXPECT_FALSE(game.isWhitePlayerCheck(board));	// Roi blanc avance tout droit pour sortire de l'echec

	game.clearGame(board);
}

TEST(game, echecMatBlanc) {
	//Initialiser la partie
	modele::Game game;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	modele::Board board;
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Sequence de move qui va mettre le roi blanc en echec et mat
	EXPECT_FALSE(game.isWhitePlayerCheckmate(board));
	game.playerMove(whitePlayer, board, board.boxes[0][2].get(), board.boxes[2][0].get());
	game.playerMove(blackPlayer, board, board.boxes[7][0].get(), board.boxes[2][0].get());
	game.playerMove(whitePlayer, board, board.boxes[0][5].get(), board.boxes[2][7].get());
	game.playerMove(blackPlayer, board, board.boxes[7][7].get(), board.boxes[2][7].get());
	EXPECT_FALSE(game.isWhitePlayerCheckmate(board));
	game.playerMove(whitePlayer, board, board.boxes[0][0].get(), board.boxes[1][0].get());
	game.playerMove(blackPlayer, board, board.boxes[2][0].get(), board.boxes[1][0].get());
	game.playerMove(whitePlayer, board, board.boxes[0][7].get(), board.boxes[1][7].get());
	game.playerMove(blackPlayer, board, board.boxes[2][7].get(), board.boxes[1][7].get());
	EXPECT_FALSE(game.isWhitePlayerCheckmate(board));
	game.playerMove(whitePlayer, board, board.boxes[0][3].get(), board.boxes[0][4].get());
	game.playerMove(blackPlayer, board, board.boxes[1][0].get(), board.boxes[0][0].get());
	EXPECT_TRUE(game.isWhitePlayerCheckmate(board));

	game.clearGame(board);
}

TEST(game, echecMatNoir) {
	//Initialiser la partie
	modele::Game game;
	modele::Player whitePlayer(true);
	modele::Player blackPlayer(false);
	modele::Board board;
	game.initializeNormal(whitePlayer, blackPlayer, board);

	// Sequence de move qui va mettre le roi noir en echec et mat
	EXPECT_FALSE(game.isBlackPlayerCheckmate(board));
	game.playerMove(whitePlayer, board, board.boxes[0][0].get(), board.boxes[7][0].get());
	game.playerMove(blackPlayer, board, board.boxes[7][7].get(), board.boxes[6][7].get());
	game.playerMove(whitePlayer, board, board.boxes[0][7].get(), board.boxes[6][7].get());
	EXPECT_FALSE(game.isBlackPlayerCheckmate(board));
	game.playerMove(blackPlayer, board, board.boxes[7][5].get(), board.boxes[6][6].get());
	game.playerMove(whitePlayer, board, board.boxes[6][7].get(), board.boxes[6][6].get());
	EXPECT_FALSE(game.isBlackPlayerCheckmate(board));
	game.playerMove(blackPlayer, board, board.boxes[7][3].get(), board.boxes[7][4].get());
	game.playerMove(whitePlayer, board, board.boxes[7][0].get(), board.boxes[7][2].get());
	EXPECT_TRUE(game.isBlackPlayerCheckmate(board));

	game.clearGame(board);
}

#endif