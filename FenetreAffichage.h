#ifndef WINDOWAFFICHAGE_H
#define WINDOWAFFICHAGE_H

#include "Fenetre.h"


namespace vue 
{
	class Window;

	class WindowAffichage : public QMainWindow {
		Q_OBJECT;
	public:
		WindowAffichage(modele::Player& whitePlayer, modele::Player& blackPlayer, modele::Board& boardGame, QWidget* parent = nullptr);
		~WindowAffichage() override = default;

	//signals:

	public slots:
		void ouvertureDeFenetreNormal();	// permet d'avoir accès à la classe window ouvrant l'échiquier normal
		void ouvertureDeFenetreThreeBishopOneRook();	//permet d'avoir accès à la classe window ouvrant l'échiquier avec trois fous et une tour
		void ouvertureDeFenetreThreeKing();		//permet d'avoir accès à la classe window ouvrant l'échiquier avec trois rois

	private:
		QPushButton* newButton(const QString& text);
		modele::Player& whitePlayer_;
		modele::Player& blackPlayer_;
		modele::Board& boardGame_;	// Echiquier
		std::unique_ptr<Window> window = std::make_unique<Window>(boardGame_, whitePlayer_, blackPlayer_);	// pointeur intelligent de la classe window
	};
}
#endif