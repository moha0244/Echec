Projet: Jeu d'échec
Auteurs: Bryan Tadié et Mohamed Lamine Gning
date   6 mai 2022
Créé le 4 avril 2022

Description du projet
	L'objectif de ce projet est de programmer un petit jeu d'échec à l'aide des notions c++ apprises durant toutes la session.
	Le jeu, devrait être capable d'annoncer à l'utilisateur de démarrer une partie en choisissant un échéquier parmi trois, 
	contenant des pièces à des emplacement différents. L'échéquier doit contenir 3 types de pièces différentes et le mouvement
	de chaque pièce doit être cohérent avec les règles du jeu (https://www.iechecs.com/regles.htm). Ce jeu d'échec permet, de 
	tester la mécanique de l'échec et de l'échec et mat. Pat n'est pas inclus dans le jeu. Bonne Partie! :)

	Petite Note pour l'utilisateur: Les tailles de l'affichage a été conçu selon mon écran (Bryan), vous pouvez changer celle-ci pour qu'il soit adapter a votre écran
		FenetreAffichage (ligne 63) : bouton->setFixedSize(400, 300);  (Taille du menu principale qui offre 3 echéquier différents)
		Fenetre.cpp (Ligne 262): board_[i][j]->setIconSize(QSize(80, 80));  (Taille des icones des pièces)
		Fenetre.cpp (Ligne 285): bouton->setFixedSize(105, 105); (Taille des cases de l'échéquier)
		Fenetre.cpp (Ligne 39): boutonReStart->setFixedSize(90, 45); (Taille du bouton recommencer)

Description des classes

    Modele:
		Piece
			Cette classe est une classe abstraite (viruelle pure) qui représente les pièces. 
			Elle contient les toutes les attributs et méthodes utiles pour le fonctionnement de chaque pièce.

		King (Dérivé de Piece)
			Classe qui contient tous les méthodes définie spécialement pour le fonctionnement du roi
		Rook (Dérivé de Piece)
			Classe qui contient tous les méthodes définie spécialement pour le fonctionnement de la tour
		Bishop (Dérivé de Piece)
			Classe qui contient tous les méthodes définie spécialement pour le fonctionnement du fou
		Empty (Dérivé de Piece)
			Classe representant une classe vide
		PieceTemp (Dérivé de Piece)
			Classe permettant d'ajouter une pièce temporaire

		Spot
			Classe représentant une case de l'échéquier.
			Cette classe contient l'axe x et y ainsi que la pièce qu'elle contient.

		Board
			Cette classe contient tous les cases qui forment l'échiquier.
			Celui-ci est 8x8.

		Player
			Cette classe représente un joueur qui joue une partie.
			Il peut y avoir seulement 2 joueurs (1 noir et 1 blanc)

		Game
			Cette classe représente tout le fonctionnement du jeu. C'est le coeur du modèle,
			de notre programme. Cette classe permet de commencer un partie en initialisant tout 
			les composantes néceéssaire (Board, Spot, Pieces, Player).C'est cette classe qui vérifie
			le tour de chaque joueur. De plus, elle vérifie la mise en échec et la mise en échec et mat.

	Vue:
		WindowAffichage
			Cette classe représente la fenêtre qui permet de faire le choix entre les trois différents positions d'échiquier de départ à partir de 3 boutons, en appuyer une nous permet d'avoir accès directement à la fenêtre de l'échiquier concerné fait dans la classe Window.
	
		Window
			Cette classe représente la fenêtre qui nous montre la rétroaction visuelle de l'échiquier choisi dans la fenêtre précèdente.
			En appuyant sur une case, les blocs rouges nous montrent tous les mouvements valides de la pièce.
			Puis en appuyant sur une autre case qui sera rouge, la pièce changera de place.
			Pour l'échiquer à 3 rois, un message d'erreur va s'affficher et les mouvements seront invalides.
			Lors de l'échec et de l'échec et mats, un message s'affichera jusqu'à que vous sortiez de l'échec.
			Le bouton recommencer tout en haut vous permettra de changer d'échiquier si besoin. 

Fichiers utiles
	TestJeuEchec.cpp
		Ce fichier cpp, permet de faire des tests permettant de vérifier la logique et le fonctionnement
		du modèle avant même de commencer une partie.

	Include.h
		Ce fichier contient plusieurs librairie externe de c++ qui sont utile pour l'implémentation
		du jeu.

Sources des images des pièces
	Pieces noires
		Roi : https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.symbols.com%2Fsymbol%2Fblack--king&psig=AOvVaw0he1-pjy8z9WEMWcwSzc_I&ust=1651894167804000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCLjpv8P3yfcCFQAAAAAdAAAAABAD
		Tour : https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.symbols.com%2Fsymbol%2Fblack--rook&psig=AOvVaw3U_6MyN-scJV4yHpPPDlaj&ust=1651893908109000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCKCeosv2yfcCFQAAAAAdAAAAABAD
		Fou : https://www.google.com/url?sa=i&url=https%3A%2F%2Fvector.me%2Fbrowse%2F105835%2Fchess_piece_black_bishop_clip_art&psig=AOvVaw0lOVa5xjeXHpRB6fxXAa9G&ust=1651894028904000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCPje4vr2yfcCFQAAAAAdAAAAABAD

	Pieces blanches
		Roi : https://www.google.com/imgres?imgurl=https%3A%2F%2Fupload.wikimedia.org%2Fwikipedia%2Fcommons%2Fthumb%2F4%2F42%2FChess_klt45.svg%2F2048px-Chess_klt45.svg.png&imgrefurl=https%3A%2F%2Fcommons.wikimedia.org%2Fwiki%2FFile%3AChess_klt45.svg&tbnid=YiwF7QN5t4zSNM&vet=12ahUKEwio5p6w98n3AhUPrnIEHVEdDfMQMygNegUIARD2AQ..i&docid=9kGjfYX7CujbLM&w=2048&h=2048&q=white%20king%20chess&ved=2ahUKEwio5p6w98n3AhUPrnIEHVEdDfMQMygNegUIARD2AQ
		Tour :  https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.seekpng.com%2Fipng%2Fu2e6q8u2q8t4a9w7_western-white-side-rook-chess-white-rook-png%2F&psig=AOvVaw0_e3xRzkRGSQ1bf2wxl8rP&ust=1651893286042000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCLjR5pj0yfcCFQAAAAAdAAAAABAD
		Fou : https://www.google.com/url?sa=i&url=https%3A%2F%2Fcommons.wikimedia.org%2Fwiki%2FFile%3AChess_tile_bl.svg&psig=AOvVaw2aVNn1a12xrtzIJLAEZAR-&ust=1651894130728000&source=images&cd=vfe&ved=0CAwQjRxqFwoTCIji6Kr3yfcCFQAAAAAdAAAAABAD