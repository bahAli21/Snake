# Snake

Bienvenue dans le README du jeu Snake! 

Ce jeu est implémenté en utilisant
des nombres complexes et une matrice (2D). Voici une explication détaillée du
jeu et de ses fonctionnalités:

##Objectif:
Le but du jeu est de diriger le serpent à travers l'écran
en ramassant des fruits.
À chaque fois que le serpent mange un fruit, 
le score augmente de 10 points. 
Le joueur perd la partie s'il se mange la queue.

##Mécanique de jeu:
  Le serpent est représenté par une série de blocs(en circleFill) 
  en mouvement. Le joueur peut contrôler la direction du serpent
  en utilisant les touches fléchées du clavier.
  Le fruit est généré aléatoirement sur l'écran à chaque fois que le
  serpent mange un fruit.

##Fonctionnalités:

    Menu Play, Pause et Restart: Le joueur peut démarrer le jeu en appuyant 
    sur le bouton "Play". Si le joueur veut faire une pause ou 
    redémarrer le jeu, il peut utiliser les boutons "Pause" et "Restart" 
    respectivement.
    Score: Le score du joueur est affiché en haut de l'écran. 
    Chaque fois que le serpent mange un fruit, le score augmente de 10 points.
    Fin de partie: Si le serpent touche les bords 
    il sort de l'autre coté du bord
    s'il mange la queue ,il perd,
   le jeu se termine et le joueur doit redémarrer le jeu pour continuer à jouer.

##Technologies utilisées:

    Nombres complexes: Les nombres complexes sont utilisés pour représenter
    la position de chaque bloc du serpent sur l'écran.
    Matrice: Une matrice est utilisée pour représenter gerer la grille et 
    les position du snake et fruit .

##Installation et utilisation:

    Pour jouer à Snake, vous devez d'abord télécharger le code source.
    Ensuite, vous pouvez ouvrir le fichier avec un environnement C/C++ et 
    exécuter le programme.
    Pour contrôler le serpent, utilisez les touches fléchées du clavier.

##Conclusion:
Le jeu Snake est un jeu simple mais amusant qui met à l'épreuve les compétences 
de réflexion et de coordination œil-main.
Avec son utilisation de nombres complexes et de matrices,
il offre une introduction intéressante à la programmation en C/C++.
Bonne chance et amusez-vous bien en jouant à Snake!
