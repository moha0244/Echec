#include "Fenetre.h"
#include "Fenetreaffichage.h"


using iter::range;
namespace vue {

	Window::Window(modele::Board& boardGame, modele::Player& whitePlayer, modele::Player blackPlayer, QWidget* parent) :
		boardGame_(boardGame), whitePlayer_(whitePlayer), blackPlayer_(blackPlayer), QMainWindow(parent)
	{
		auto widgetPrincipal = new QWidget(this);
		auto layoutPrincipal = new QVBoxLayout(widgetPrincipal);  // Donner un parent à un layout est comme un setLayout.
		layoutPrincipal->setSpacing(0);

		// Pouvoir choisir le nom pour le joueur blanc(Optionnel)
		QLabel* nameLabel = new QLabel;
		nameLabel->setText("Nom du joueur blanc:");
		QLineEdit* nameEditor = new QLineEdit;
		QHBoxLayout* nameLayout = new QHBoxLayout;
		nameLayout->addWidget(nameLabel);
		nameLayout->addWidget(nameEditor);
		layoutPrincipal->addLayout(nameLayout);

		// Pouvoir choisir le nom pour le joueur noir(Optionnel)
		QLabel* nameLabel1 = new QLabel;
		nameLabel1->setText("Nom du joueur noir:");
		QLineEdit* nameEditor1 = new QLineEdit;
		QHBoxLayout* nameLayout1 = new QHBoxLayout;
		nameLayout->addWidget(nameLabel1);
		nameLayout->addWidget(nameEditor1);
		layoutPrincipal->addLayout(nameLayout1);

		// Création d'un bouton restart pour recommencer la game
		auto boutonReStart = new QPushButton(this);
		boutonReStart->setText(QString("recommencer"));
		boutonReStart->setFixedSize(90, 45);

		// création d'une ligne de colonnes
		auto colonnes = new QHBoxLayout();
		layoutPrincipal->addLayout(colonnes);
		colonnes->setSpacing(0);

		for (int i : range(8))
		{
			// Création de 8 lignes pour l'échiquier
			auto lignes = new QHBoxLayout();
			layoutPrincipal->addLayout(lignes);
			lignes->setSpacing(0);

			//Dans chaque ligne, ajouter un numéro 
			auto ligne = new QLabel();
			std::string texteLigne = std::to_string(i);
			ligne->setText(QString(texteLigne.c_str()));
			lignes->addWidget(ligne);

			// Dnas chaque colonne, ajouter un numéro
			auto colonne = new QLabel();
			std::string texteColonne = std::to_string(i);
			colonne->setText(QString(texteColonne.c_str()));
			colonne->setAlignment(Qt::AlignCenter);
			colonnes->addWidget(colonne);

			for (int j : range(8))
			{
				// Pour chaque ligne de l'échiquier ajouter un bouton
				auto bouton = newButton(QString(""));
				bouton->setProperty("position", QVariant::fromValue<QPair<int, int>>(QPair<int, int>(i, j)));
				board_[i][j] = bouton;
				lignes->addWidget(bouton);

				// connection du bouton à la fonction selectSpot qui nous permet de choisir n'importe quel case de l'échiquier
				QObject::connect(bouton, &QPushButton::clicked, this, &Window::selectSpot);

				// connection du bouton à la fonction changementDeCase qui nous permet de déplacer la pièce choisi dans selectspot
				QObject::connect(bouton, &QPushButton::released, this, &Window::changementDeCase);
			}
		}

		// Ajouter le bouton restart à l'échiquier pour pouvoir recommencer
		auto ligneReStart = new QVBoxLayout();
		layoutPrincipal->addLayout(ligneReStart);
		ligneReStart->setSpacing(0);
		//ligneReStart->setAlignment(Qt::AlignCenter);
		ligneReStart->addWidget(boutonReStart);

		// Connecter ce bouton à la fonction recommencerPartie qui nous permettra de recommencer ola game en pleine partie
		QObject::connect(boutonReStart, &QPushButton::released, this, &Window::recommencerPartie);

		// le signal pieceBouge de la fonction playerMove dans la classe Game qui va nous permettre de mettre à jour l'écran à chaque fois que la piece bouge
		QObject::connect(&game_, &modele::Game::pieceBouge, this, &Window::screen);

		setCentralWidget(widgetPrincipal);
		setWindowTitle("Jeu d'echec");
	}

	void Window::recommencerPartie()// Qui va nous permettre de recommencer la partie en pleine en faisant le choix entre trois échiquier
	{
		// fermer la fenetre ouverte
		this->hide();
		// Mettre tout l'échiquier avec des cases vides
		game_.clearGame(boardGame_);

		// Demander à l'utilisateur s'il veut recommencer en pleine partie
		QMessageBox::StandardButton msgBoxRecommencer;
		msgBoxRecommencer = QMessageBox::question(this, "Recommencer",
			"Voulez - vous recommencer la partie(Yes) sinon pour quitter (No)?",
			QMessageBox::Yes | QMessageBox::No);
		// Si oui, on lui demande s'il veut reprendre avec l'échiquier 1
		if (msgBoxRecommencer == QMessageBox::Yes) {
			QMessageBox::StandardButton msgBoxEchiquier1;
			msgBoxEchiquier1 = QMessageBox::question(this, "Recommencer",
				"Voulez - vous recommencer avec l'échiquier 1(Yes) sinon pour aller à l'échiquier 2(No)?",
				QMessageBox::Yes | QMessageBox::No);
			// Si oui, affichage de l'échiquier 1
			if (msgBoxEchiquier1 == QMessageBox::Yes) {

				this->putBoardNormal();
				screen();
				this->show();
			}
			// Si non, on lui demande s'il veut reprendre avec l'échiquier 2
			else if (msgBoxEchiquier1 == QMessageBox::No) {
				QMessageBox::StandardButton msgBoxEchiquier2;
				msgBoxEchiquier2 = QMessageBox::question(this, "Recommencer",
					"Voulez - vous recommencer avec l'échiquier 2(Yes) sinon pour aller à l'échiquier 3(No)?",
					QMessageBox::Yes | QMessageBox::No);
				// Si oui, affichage de l'échiquier 2
				if (msgBoxEchiquier2 == QMessageBox::Yes) {

					this->putBoardThreeBishopOneRook();
					screen();
					this->show();
				}
				// Si non, on lui demande s'il veut reprendre avec l'échiquier 3
				else if (msgBoxEchiquier2 == QMessageBox::No) {
					QMessageBox::StandardButton msgBoxEchiquier3;
					msgBoxEchiquier3 = QMessageBox::question(this, "Recommencer",
						"Voulez - vous recommencer avec l'échuiquer 3 (Yes) sinon pour quitter (No)?",
						QMessageBox::Yes | QMessageBox::No);
					// Si oui, affichage de l'échiquier 3
					if (msgBoxEchiquier3 == QMessageBox::Yes) {
						this->putBoardThreeKing();
						screen();
						this->show();
					}
					// Si non, l'application se ferme
					else
						QApplication::quit;
				}
			}
		}
		// Si non, l'application se ferme
		else
			QApplication::quit;
	}

	void Window::putBoardNormal() //Permet d'initialiser un écran pour l'échiquier 1
	{
		// On initialise avec le board correspondant et on l'affiche
		game_.initializeNormal(whitePlayer_, blackPlayer_, boardGame_);
		screen();

		// On vérifie s'il y'a plus de 2 rois sinon message d'avertissemnt de warning et la game est injouable
		int count = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<modele::King*>((boardGame_.boxes[i][j].get()->getPiece().get())))
				{
					count++;
				}
			}
		if (count > 2) {
			QMessageBox msgWarning;
			msgWarning.setText("WARNING!\n malheuresement un jeu d'échec ne peut pas avoir plus de 2 rois.\n Choississez un autre échiquier");
			msgWarning.setIcon(QMessageBox::Critical);
			msgWarning.setWindowTitle("Erreur");
			msgWarning.exec();
			game_.clearGame(boardGame_);
			this->hide();
			QApplication::quit;
		}
	}
	void Window::putBoardThreeBishopOneRook() //permet d'initialiser un écran pour l'échiquier 2
	{
		// On initialise avec le board correspondant et on l'affiche
		game_.initializeThreeBishopOneRook(whitePlayer_, blackPlayer_, boardGame_);
		screen();

		// On vérifie s'il y'a plus de 2 rois sinon message d'avertissemnt de warning et la game est injouable
		int count = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<modele::King*>((boardGame_.boxes[i][j].get()->getPiece().get())))
				{
					count++;
				}
			}
		}

		if (count > 2) {
			QMessageBox msgWarning;
			msgWarning.setText("WARNING!\n malheuresement un jeu d'échec ne peut pas avoir plus de 2 rois.\n Choississez un autre échiquier.\n ");
			msgWarning.setIcon(QMessageBox::Critical);
			msgWarning.setWindowTitle("Erreur");
			game_.clearGame(boardGame_);
			msgWarning.exec();
			QApplication::quit;

		}
	}

	void Window::putBoardThreeKing() //permet d'initialiser un écran pour l'échiquier 3
	{
		// On initialise avec le board correspondant et on l'affiche
		game_.initializeThreeKing(whitePlayer_, blackPlayer_, boardGame_);
		screen();

		// On vérifie s'il y'a plus de 2 rois sinon message d'avertissemnt de warning et la game est injouable
		int count = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<modele::King*>((boardGame_.boxes[i][j].get()->getPiece().get())))
				{
					++count;
				}
			}
		}

		if (count > 2) {
			this->hide();

			QMessageBox msgWarning;
			msgWarning.setText("WARNING!\n malheuresement un jeu d'échec ne peut pas avoir plus de 2 rois.\n recommencez et Choississez un autre échiquier.\n ");
			msgWarning.setIcon(QMessageBox::Critical);
			msgWarning.setWindowTitle("Erreur");
			game_.clearGame(boardGame_);
			msgWarning.exec();
			QApplication::quit;
		}
	}

	void Window::mouvemmentpossible(int x, int y)// Permet de montrer tous les mouvement possibles de la pièces sélectionnés que ce soit en échec ou pas
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (game_.canMakeMove(boardGame_, boardGame_.boxes[x][y].get(), boardGame_.boxes[i][j].get())) {
					board_[i][j]->setStyleSheet("background-color: red");
				}
	}

	void Window::screen()	// Permet de mettre à jour l'affichage de l'écran
	{
		// on positionne les icones des pièces à la bonne place
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++) {
				if (dynamic_cast<modele::Empty*>(boardGame_.boxes[i][j].get()->getPiece().get()) == nullptr) {
					std::string name = "pieces_png/" + boardGame_.boxes[i][j].get()->getPiece()->getPieceName() + boardGame_.boxes[i][j].get()->getPiece()->pieceColor() + ".png";
					board_[i][j]->setIcon(QIcon(QString(name.c_str())));
					board_[i][j]->setIconSize(QSize(80, 80));
				}
				else
					board_[i][j]->setIcon(QIcon(""));

				// Initialiser les couleurs des cases de l'échiquier
				if ((i + j) % 2)
				{
					board_[i][j]->setStyleSheet("background-color: gray");
				}
				else
				{
					board_[i][j]->setStyleSheet("background-color: white"); // couleur de fond pour chaque case
				}

			}
	}


	QPushButton* Window::newButton(const QString& text)	// Permet d'initialiser les boutons utilisés dans la fenêtre
	{
		auto bouton = new QPushButton(this);
		bouton->setText(text);
		bouton->setFixedSize(105, 105);
		return bouton;
	}

	void Window::selectSpot()	// Permet de pouvoir sélectionner une case sur l'échiquier
	{
		if ((pointActuelX_ + pointActuelY_) % 2 == 1)// Pour remettre la couleur précedente de la case de pièce une fois qu'on en sélectionne une autre 
		{
			board_[pointActuelX_][pointActuelY_]->setStyleSheet("background-color: gray;color:white");
		}
		else
		{
			board_[pointActuelX_][pointActuelY_]->setStyleSheet("background-color: white;color:gray");
		}

		int x = QObject::sender()->property("position").value<QPair<int, int>>().first;
		int y = QObject::sender()->property("position").value<QPair<int, int>>().second;
		pointActuelX_ = x;
		pointActuelY_ = y;

		// permet une rétroaction visuelle de la pièce sélectionnée
		board_[x][y]->setStyleSheet("background-color: green ");

		// Permet une rétroactio visuelle de tous les mouvements possibles de la pièces sélectionnés
		this->mouvemmentpossible(pointActuelX_, pointActuelY_);
	}

	void Window::changementDeCase()
	{
		for (int i = 0; i < 8; i++)// Pour remettre la couleur précedente des cases des mouvements possible de la pièce sur la case une fois qu'on en sélectionne une autre 
			for (int j = 0; j < 8; j++)
				if (boardGame_.boxes[pointActuelX_][pointActuelY_].get()->getPiece()->canMove(boardGame_, pointActuelX_, pointActuelY_, i, j))
					if ((i + j) % 2 == 1)
					{
						board_[i][j]->setStyleSheet("background-color: gray;color:white");
					}
					else
					{
						board_[i][j]->setStyleSheet("background-color: white;color:gray");
					}

		int posFinalX = QObject::sender()->property("position").value<QPair<int, int>>().first;
		int posFinalY = QObject::sender()->property("position").value<QPair<int, int>>().second;

		if (game_.isWhitePlayerCheck(boardGame_)) {// Si le joueur blanc est en échec
			// Permet d'afficher un message disant que le joueur blanc est en échec
			QMessageBox msgBoxCheck;
			std::string checkForWhite = "Attention echec pour joueur blanche";
			msgBoxCheck.setText(QString(checkForWhite.c_str()));
			msgBoxCheck.exec();

			if (game_.isWhitePlayerCheckmate(boardGame_)) {// Si le joueur blanc est échec et mat

				// Permet d'afficher un message disant que le joueur noir a gagné
				QMessageBox msgBoxOver;
				std::string gameOverForWhite = "Échec et Mat pour le joueur blanc\n Victoire pour le joueur noir!!!";
				msgBoxOver.setText(QString(gameOverForWhite.c_str()));
				msgBoxOver.exec();
				game_.clearGame(boardGame_);

				// demande au joueur s'il veut recomencer une autre partie 
				QMessageBox::StandardButton msgBoxFin;
				msgBoxFin = QMessageBox::question(this, "Début de partie!",
					"Voulez - vous recommencer la partie(Yes) sinon (No)?",
					QMessageBox::Yes | QMessageBox::No);

				// demande au joueur s'il veut recomencer une partie avec l'échiquier 1
				if (msgBoxFin == QMessageBox::Yes) {
					QMessageBox::StandardButton msgBoxEchiquier1;
					msgBoxEchiquier1 = QMessageBox::question(this, "Recommencer",
						"Voulez - vous recommencer avec l'échiquier 1(Yes) sinon pour aller à l'échiquier 2(No)?",
						QMessageBox::Yes | QMessageBox::No);
					
					// Si oui, affichage de l'échiquier 1,
					if (msgBoxEchiquier1 == QMessageBox::Yes) {
						game_.clearGame(boardGame_);
						this->putBoardNormal();
						screen();
						this->show();
					}
					// Si non, on lui demande s'il veut reprendre avec l'échiquier 2
					else if (msgBoxEchiquier1 == QMessageBox::No) {
						QMessageBox::StandardButton msgBoxEchiquier2;
						msgBoxEchiquier2 = QMessageBox::question(this, "Recommencer",
							"Voulez - vous recommencer avec l'échiquier 2(Yes) sinon pour aller à l'échiquier 3(No)?",
							QMessageBox::Yes | QMessageBox::No);
						
						// Si oui, affichage de l'échiquier 2,
						if (msgBoxEchiquier2 == QMessageBox::Yes) {
							game_.clearGame(boardGame_);
							this->putBoardThreeBishopOneRook();
							screen();
							this->show();
						}
						// Si non, on lui demande s'il veut reprendre avec l'échiquier 3
						else if (msgBoxEchiquier2 == QMessageBox::No) {
							QMessageBox::StandardButton msgBoxEchiquier3;
							msgBoxEchiquier3 = QMessageBox::question(this, "Recommencer",
								"Voulez - vous recommencer avec l'échuiquer 3 (Yes) sinon pour quitter (No)?",
								QMessageBox::Yes | QMessageBox::No);
							
							// Si oui, affichage de l'échiquier 3
							if (msgBoxEchiquier3 == QMessageBox::Yes) {
								game_.clearGame(boardGame_);
								this->putBoardThreeKing();
								screen();
								this->show();
							}
							// Si non quitter la partie
							else
								QApplication::quit;
						}
					}
				}
				// Si non quitter la partie
				else
					QApplication::quit;
			}
		}

		if (game_.isBlackPlayerCheck(boardGame_)) {// Si le jouer noir est en échec
			// Permet d'afficher un message disant que le joueur noir est en échec
			QMessageBox msgBoxCheck;
			std::string checkForBlack = "Attention echec pour joueur noir ";
			msgBoxCheck.setText(QString(checkForBlack.c_str()));
			msgBoxCheck.exec();

			if (game_.isBlackPlayerCheckmate(boardGame_)) {// Si le joueur noir est échec et mat
				// Permet d'afficher un message disant que le joueur blanc a gagné
				QMessageBox msgBoxOver;
				std::string gameOverForBlack = "Échec et Mat pour le joueur noir!\n Victoire pour le joueur blanc!!!";
				msgBoxOver.setText(QString(gameOverForBlack.c_str()));
				msgBoxOver.exec();
				game_.clearGame(boardGame_);
				QMessageBox::StandardButton msgBoxFin;
				
				// demande au joueur s'il veut recomencer une autre partie
				msgBoxFin = QMessageBox::question(this, "Début de partie!",
					"Voulez - vous recommencer la partie(Yes) sinon (No)?",
					QMessageBox::Yes | QMessageBox::No);
				
				// demande au joueur s'il veut recomencer une partie avec l'échiquier 1
				if (msgBoxFin == QMessageBox::Yes) {
					QMessageBox::StandardButton msgBoxEchiquier1;
					msgBoxEchiquier1 = QMessageBox::question(this, "Recommencer",
						"Voulez - vous recommencer avec l'échiquier 1(Yes) sinon pour aller à l'échiquier 2(No)?",
						QMessageBox::Yes | QMessageBox::No);
					
					// Si oui, affichage de l'échiquier 1,
					if (msgBoxEchiquier1 == QMessageBox::Yes) {
						game_.clearGame(boardGame_);
						this->putBoardNormal();
						screen();
						this->show();
					}
					// Si non, on lui demande s'il veut reprendre avec l'échiquier 2
					else if (msgBoxEchiquier1 == QMessageBox::No) {
						QMessageBox::StandardButton msgBoxEchiquier2;
						msgBoxEchiquier2 = QMessageBox::question(this, "Recommencer",
							"Voulez - vous recommencer avec l'échiquier 2(Yes) sinon pour aller à l'échiquier 3(No)?",
							QMessageBox::Yes | QMessageBox::No);
						
						// Si oui, affichage de l'échiquier 2,
						if (msgBoxEchiquier2 == QMessageBox::Yes) {
							game_.clearGame(boardGame_);
							this->putBoardThreeBishopOneRook();
							screen();
							this->show();
						}
						// Si non, on lui demande s'il veut reprendre avec l'échiquier 3
						else if (msgBoxEchiquier2 == QMessageBox::No) {
							QMessageBox::StandardButton msgBoxEchiquier3;
							msgBoxEchiquier3 = QMessageBox::question(this, "Recommencer",
								"Voulez - vous recommencer avec l'échuiquer 3 (Yes) sinon pour quitter (No)?",
								QMessageBox::Yes | QMessageBox::No);
							
							// Si oui, affichage de l'échiquier 3,
							if (msgBoxEchiquier3 == QMessageBox::Yes) {
								game_.clearGame(boardGame_);
								this->putBoardThreeKing();
								screen();
								this->show();
							}
							// Sinon quitter la partie
							else
								QApplication::quit;
						}
					}
				}
			}
		}

		// Permet de déplacer la pièce d'une case à une autre
		game_.movecase(boardGame_, pointActuelX_, pointActuelY_, posFinalX, posFinalY);

		if (!game_.canMakeMove(boardGame_, boardGame_.boxes[pointActuelX_][pointActuelY_].get(), boardGame_.boxes[posFinalX][posFinalY].get())
			and boardGame_.boxes[posFinalX][posFinalY].get() != boardGame_.boxes[pointActuelX_][pointActuelY_].get()
			and dynamic_cast<modele::Empty*>(boardGame_.boxes[pointActuelX_][pointActuelY_].get()->getPiece().get()) == nullptr
			and dynamic_cast<modele::Piece*>(boardGame_.boxes[posFinalX][posFinalY].get()->getPiece().get())->pieceColor() != dynamic_cast<modele::Piece*>(boardGame_.boxes[pointActuelX_][pointActuelY_].get()->getPiece().get())->pieceColor()
			and dynamic_cast<modele::Empty*>(boardGame_.boxes[posFinalX][posFinalY].get()->getPiece().get()) != nullptr) {
			board_[posFinalX][posFinalY]->setStyleSheet("background-color: blue");
			QMessageBox msgBoxCheck;
			std::string name1 = "Attention; mouvement non valide ";
			msgBoxCheck.setText(QString(name1.c_str()));
			msgBoxCheck.exec();
		}
	}
}
