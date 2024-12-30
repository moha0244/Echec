#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QmessageBox>
#include <QApplication>
#include <QVariant>
#include <QLine>
#include <QDialog>
#include <QLineEdit>

#include "Game.h"
#include "FenetreAffichage.h"


namespace vue 
{
	class Window : public QMainWindow {
		Q_OBJECT;

	public:
		Window(modele::Board& boardGame, modele::Player& whitePlayer, modele::Player blackPlayer, QWidget* parent = nullptr);// Création de la fenêtre
		~Window() override = default;

		void putBoardNormal(); // Rétroaction visuelle du premier échiquier normale
		void putBoardThreeBishopOneRook();	// Rétroaction visuelle de l'échiquier possédant trois fous et une tour pour chaque joueur
		void putBoardThreeKing();	// rétroaction visuelle de l'échiquer ayant trois rois. 
		void mouvemmentpossible(int x, int y); // retroaction visuelle de tous les mouvements possible de la pièce

	//signals:

	public slots:
		void selectSpot();	// rétroaction visuelle lorsque l'utilisateur clique sur une case
		void changementDeCase();	// rétroaction visuelle lorsque l'utilisateur clique sur une autre case
		void screen();	// Affichage de toutes les pièces ainsi que de leur position dans l'échiquier
		void recommencerPartie();	// Message permettant à l'utilisateur de changer d'échiquier. 

	private:
		QPushButton* newButton(const QString& text);
		QPushButton* board_[8][8];	//Une matrice de boutons représentant la vue(chaque bouton représentant une case)
		modele::Game game_;		// représente la partie
		modele::Player& whitePlayer_;	
		modele::Player& blackPlayer_;	
		modele::Board& boardGame_;	// représente l'échiquier
		modele::Spot* start_;	
		modele::Spot* end_;	
		int pointActuelX_;	//emplacement actuel de la pièce selon l'axe X
		int pointActuelY_;	//emplacement actuel de la pièce selon l'axe Y
	};
}
#endif