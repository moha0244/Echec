#include "Fenetreaffichage.h"
#include "Fenetre.h"


using iter::range;
namespace vue 
{
	WindowAffichage::WindowAffichage(modele::Player& whitePlayer, modele::Player& blackPlayer, modele::Board& boardGame, QWidget* parent) :
		whitePlayer_(whitePlayer), blackPlayer_(blackPlayer), boardGame_(boardGame), QMainWindow(parent)
	{
		auto widgetPrincipal = new QWidget(this);
		auto layoutPrincipal = new QVBoxLayout(widgetPrincipal);  // Donner un parent à un layout est comme un setLayout.
		layoutPrincipal->setSpacing(0);

		// Permet de pouvoir écrire une question sur la première
		auto titre = new QHBoxLayout();
		layoutPrincipal->addLayout(titre);
		titre->setSpacing(0);
		auto question = new QLabel();
		std::string name = "Quel échiquier voulez vous prendre ";
		question->setText(QString(name.c_str()));
		question->setAlignment(Qt::AlignCenter);
		titre->addWidget(question);

		// Création d'une deuxième ligne pour ajoueter plusieurs boutons
		auto ligne = new QHBoxLayout();
		layoutPrincipal->addLayout(ligne);
		ligne->setSpacing(0);

		// Création de trois nouveaux boutons à l'aide de la fonction newbutton
		auto boutonEchiquier1 = newButton(QString("Echiquier 1:Voulez vous commencer avec l'Echiquier normale"));
		auto boutonEchiquier2 = newButton(QString("Echiquier 2: Voulez vous commencer avec l'Echiquier avec trois tours et un fou"));
		auto boutonEchiquier3 = newButton(QString("Echiquier 3:Voulez vous commencer avec l'Echiquier avec trois rois"));

		boutonEchiquier1->setProperty("chiffre", QVariant::fromValue<int>(0));
		boutonEchiquier2->setProperty("chiffre", QVariant::fromValue<int>(1));
		boutonEchiquier3->setProperty("chiffre", QVariant::fromValue<int>(2));

		// Mettre ces trois boutons sur la même ligne
		ligne->addWidget(boutonEchiquier1);
		ligne->addWidget(boutonEchiquier2);
		ligne->addWidget(boutonEchiquier3);

		// Ajouter une couleur pour chacun de ces boutons
		boutonEchiquier1->setStyleSheet("background-color: red");
		boutonEchiquier2->setStyleSheet("background-color: green");
		boutonEchiquier3->setStyleSheet("background-color: blue");

		// Connecter chaque bouton à une fonction qui va chacun ouvrir une nouvelle fenetre de classe window
		Window window(boardGame_, whitePlayer_, blackPlayer_);
		QObject::connect(boutonEchiquier1, &QPushButton::clicked, this, &WindowAffichage::ouvertureDeFenetreNormal);
		QObject::connect(boutonEchiquier2, &QPushButton::clicked, this, &WindowAffichage::ouvertureDeFenetreThreeBishopOneRook);
		QObject::connect(boutonEchiquier3, &QPushButton::clicked, this, &WindowAffichage::ouvertureDeFenetreThreeKing);

		setCentralWidget(widgetPrincipal);
		setWindowTitle("Jeu d'echec");
	}

	QPushButton* WindowAffichage::newButton(const QString& text)// Permet d'initialiser les boutons utilisés dans la fenêtre
	{
		auto bouton = new QPushButton(this);
		bouton->setText(text);
		bouton->setFixedSize(400, 300);
		return bouton;
	}

	void WindowAffichage::ouvertureDeFenetreNormal() {//Permet d'ouvrir la fenetre pour l'échiquier 1
		// on demande à l'utilisateur s'il est sur de vouloir ouvrir cette fenetre
		QMessageBox::StandardButton msgBoxBeginNormal;
		msgBoxBeginNormal = QMessageBox::question(this, "Début de partie!",
			"Etes vous sure de vouloir commencer avec cet échiquier(Yes) sinon revenez au menu (No)?",
			QMessageBox::Yes | QMessageBox::No);
		
		// Si oui on ferme la fenêtre affichage et on ouvre celle de la fenetre avec l'échiquier correspondant
		if (msgBoxBeginNormal == QMessageBox::Yes) {
			this->hide();
			window.get()->putBoardNormal();
			window.get()->show();
		}
		// Si non on revient à cette écran
		else if (msgBoxBeginNormal == QMessageBox::No) {
			this->hide();
			this->show();

		}
	}

	void WindowAffichage::ouvertureDeFenetreThreeBishopOneRook() {//Permet d'ouvrir la fenetre pour l'échiquier 2
		// on demande à l'utilisateur s'il est sur de vouloir ouvrir cette fenetre
		QMessageBox::StandardButton msgBoxBeginThreeBishopOneRook;
		msgBoxBeginThreeBishopOneRook = QMessageBox::question(this, "Début de partie!",
			"Etes vous sure de vouloir commencer avec cet échiquier(Yes) sinon revenez au menu (No)?",
			QMessageBox::Yes | QMessageBox::No);
		
		// Si oui on ferme la fenêtre affichage et on ouvre celle de la fenetre avec l'échiquier correspondant
		if (msgBoxBeginThreeBishopOneRook == QMessageBox::Yes) {
			this->hide();

			window.get()->putBoardThreeBishopOneRook();
			window.get()->show();
		}
		// Si non on revient à cette écran
		else if (msgBoxBeginThreeBishopOneRook == QMessageBox::No) {
			this->hide();
			this->show();
		}
	}

	void WindowAffichage::ouvertureDeFenetreThreeKing() {//Permet d'ouvrir la fenetre pour l'échiquier 3
		// on demande à l'utilisateur s'il est sur de vouloir ouvrir cette fenetre
		QMessageBox::StandardButton msgBoxBeginThreeKing;
		msgBoxBeginThreeKing = QMessageBox::question(this, "Début de partie!",
			"Etes vous sure de vouloir commencer avec cet échiquier(Yes) sinon revenez au menu (No)?",
			QMessageBox::Yes | QMessageBox::No);
		
		// Si oui on ferme la fenêtre affichage et on ouvre celle de la fenetre avec l'échiquier correspondant
		if (msgBoxBeginThreeKing == QMessageBox::Yes) {
			this->hide();
			window.get()->putBoardThreeKing();
			window.get()->show();
		}
		// Si non on revient à cette écran
		else if (msgBoxBeginThreeKing == QMessageBox::No) {
			this->hide();
			this->show();
		}
	}
}