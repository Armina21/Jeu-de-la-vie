Vang Amanda P2104130

* Mini Projet *

--------------------------------------------------------------------------------------------------------------------------------------------------------
description du jeu :

Ce mini projet est inspire du jeu de la vie avec des caracteristiques en plus :
    - chasseur : chassera les animaux selon la zone du chasseur.
    - policier : arretera le chasseur s'il le rencontre

Chaque espece se deplacera de maniere aleatoire s'il n'y a aucune rencontre.

Ce jeu suit l'évolution de lapin et de renard dans la nature, cependant des chasseurs apparaitront dans certaines zones.
Les policiers ne partent que si tous les chasseurs sont trouvés.
--------------------------------------------------------------------------------------------------------------------------------------------------------
Deux touches permettent l'évolution, 
	- "fleche du haut": avance d'un jour.
	- "fleche de gauche": avance de cinq jours.
et deux dans le menu:
	- initialisation: initialise le jeu.
	- run: qui permet l'evolution du programme.

Il y a 8 parties: 
	1) les constantes .
	2) la construction des structures.
	3) l'initialisation qui initialise les structures et grille.
	4) les fonctions et procedures qui sont appeles par l'update.
	5) les updates qui permettent l'evolution du programme.
	7) draw et affiche qui permettent de montrer l'evolution du systeme.
	8) cout pour verifier et debugger.
	9) le main qui execute les programmes.
--------------------------------------------------------------------------------------------------------------------------------------------------------
29/04
Presque que toutes les fonctions et procedures ont ete refaite.
Les déplacements sont améliorés ainsi que le menu.
--------------------------------------------------------------------------------------------------------------------------------------------------------
06/05
Procédure naissance, manger et ajouter.
Problème dans le draw pour afficher les autres espèces.
Etat_suivant_vie qui permet de calculer la duree de vie.
Affichage amelioré.
--------------------------------------------------------------------------------------------------------------------------------------------------------
13/05
ajout de la procedure "ajoute_animal" qui ajoute des animaux lorsqu'ils sont en extinction.
Les policiers partent lorsque les chasseurs sont tous capturer.