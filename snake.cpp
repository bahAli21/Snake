/*Auteur: BAH Mamadou a young guinean programmer*/
/*
  Semaine 1:
  Aujourd'huit je gere l'initialisation du snake a 4 , l'init du fruit et son deplacement
  Semaine 2:
  je genere le fruit et j'agrandit le snake,
  L'utilisateur peut changer sa direction , mais il va memoriser  l'ancienne position
  J'ai aussi géré le SCORE
  j'ai rajouté un menu pause et play, et j'ai terminé avec un gameOver s'il se mange la queue
*/

#include<Grapic.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace grapic;
using namespace std;

const int DIMW = 700;
const int SIZE = 400;

/*structure complexe */
struct complexe
{
  float x,y;
};

/*Fonction make_complexe*/
complexe make_complexe(float a,float b)
{
  complexe c;
  c.x=a;
  c.y=b;
  return c;
}

complexe make_complexe_expo(float r,float angle)
{
  complexe c;
  float theta=(angle*M_PI)/180;
  c.x=r*cos(theta);
  c.y=r*sin(theta);
  return c;
}

/*Fonction operator+*/
complexe operator+(complexe c1,complexe c2)
{
  complexe res;
  res.x=c1.x+c2.x;
  res.y=c1.y+c2.y;
  return res;
}

/*Fonction operator+*/
complexe operator-(complexe c1,complexe c2)
{
  complexe res;
  res.x=c1.x-c2.x;
  res.y=c1.y-c2.y;
  return res;
}

/*Fonction operator+*/
complexe operator*(complexe c1,complexe c2)
{
  complexe res;
  res.x=c1.x*c2.x-c1.y*c2.y;
  res.y=c1.y*c2.x+c2.y*c1.x;
  return res;
}

/*Fonction lambda*complexe*/
complexe operator*(float lambda,complexe c)
{
  complexe res;
  res.x=lambda*c.x;
  res.y=lambda*c.y;
  return res;
}

/*Fonction translate*/
complexe translate(complexe c,float dx,float dy)
{
  return (c+make_complexe(dx,dy));
}

//Represente une case du corp
struct cellule
{
	int type; //0=cellule libre; 1=cellule occupée
	complexe position;
};

//Permetl de remonter la fenêtre dès que l'utilisateur choisi de jouer avec le boutton space
struct affiche
{
  float y1;
};

//La structure du serpent
struct snake
{
  affiche aff;   //Affichage de la grille qui monte
  int menuClick; //Permet de dire si l'utilisateur a clicker sur le menu (niveau) gere l'affichage du menu
	complexe snakeHead;
  Image backgroundImage;
	complexe snakeTail;
	complexe snakeFruit;
	int snakeLength; //Taille du snake
	cellule matrice[2][SIZE]; //La matrice qui stock tous les evenement du jeux
  int score; //Le score
  int index; //Permet d'indexer la direction prise par le snake
  float vitesse; //Gere le pas de deplacement du snake
  int testFruitMagic; //L'appariton du fruit magic est gerer par cette variable
  int niveau;  //Une variable qui prend 1 si le niveau est sur facile 2 sinon
  int restart;  //La variable qui passe a 1 si l'utilisateur souhaite rejouer

  int openWindow;  //L'ouverture de la fenêtre d'acceuil
};

//Cette fonction permet de retourner 1 si la variable choisie par le random est inferieur a 19
//Permet de definire l'apparition du fruit magic
int returnVal()
{
  int val=rand()%21;
  if(val<=18)
    return 1;
  return 2;
}

// une procedure pour generer un fruit
void putFruit(snake & s)
{
  //Je recupère la valeur retourner par la fonction returnVal
  s.testFruitMagic=returnVal();
  /* ICI je definie sur quel cas il y'a un obstacle pour le snake */
      bool test1=((s.snakeHead.x>=120 && s.snakeHead.y>=200) && (s.snakeHead.x<=180 && s.snakeHead.y<=220));
      bool test2=((s.snakeHead.x>=100 && s.snakeHead.y>=200) && (s.snakeHead.x<=120 && s.snakeHead.y<=280));
      bool test3=((s.snakeHead.x>=120 && s.snakeHead.y>=480) && (s.snakeHead.x<=180 && s.snakeHead.y<=500));
      bool test4=((s.snakeHead.x>=100 && s.snakeHead.y>=420) && (s.snakeHead.x<=120 && s.snakeHead.y<=500));
      bool test5=((s.snakeHead.x>=500 && s.snakeHead.y>=200) && (s.snakeHead.x<=560 && s.snakeHead.y<=220));
      bool test6=((s.snakeHead.x>=560 && s.snakeHead.y>=200) && (s.snakeHead.x<=580 && s.snakeHead.y<=280));
      bool test7=((s.snakeHead.x>=500 && s.snakeHead.y>=480) && (s.snakeHead.x<=560 && s.snakeHead.y<=500));
      bool test8=((s.snakeHead.x>=560 && s.snakeHead.y>=420) && (s.snakeHead.x<=580 && s.snakeHead.y<=500));

  	  int line, column;

   	  	for(int j=0;j<SIZE;++j)
   		  {
          //je teste pour ne pas que le fruit se genere sur un corp
           do {
                   line=rand()%541+60;
                   column=rand()%541+60;

               } while( (column==s.matrice[1][j].position.y && line==s.matrice[1][j].position.x) || test1 || test2  || test3 || test4 || test5 || test6 || test7 || test8);
        }
        //Le fruit est creer une fois que les critère du while sont tous satisfait
        s.snakeFruit=make_complexe(line,column);
    //Je stock le fruit dans une matrice case fixé a [0][0]
    //Je l'allume en mettant son type a 1 pour que le draw puisse le dessiner;
    s.matrice[0][0].position=s.snakeFruit;
    s.matrice[0][0].type=1;


}

//Procedure pour init du snake
void init(snake & s)
{
    //Zone couvert par le gazon
    s.backgroundImage=image("data/ImSnakeGazon.jpg");
    //La tête du serpent je la met au milieu de la matrice de SIZE/2 colonne
		s.snakeHead=make_complexe(DIMW/2,DIMW/2);
    //Pour un debut je mets la tête du snake a 4
    s.snakeLength=4;
    //le score a 0
    s.score=0;
    // J'ettein toute les cellules ; Je me suis referer au jeu de la vie
			for(int j=0;j<SIZE;++j)
			{
				s.matrice[1][j].type=0;
			}
}

// Pour un debut le serpent il existe , commme le jeu de la vie il y'a deja un eta initiale
void etat_initiale(snake & s)
{
  //Je definie le pas du snake a 13
    s.vitesse=13;

    // acceuil ICI y1=0 parceque le volet acceuil est fermé
    s.aff.y1=0;
    //La tête du snake est stocker dans une cellule [1][SIZE/2] SIZE/2=SIZE/2 une constante
  	s.matrice[1][SIZE/2].position=s.snakeHead;
    //Et une fois stocker je l'allume
  	s.matrice[1][SIZE/2].type=1;

    //J'init mon snake en parcourant la matrice
     for(int i=201;i<(s.snakeLength+(SIZE/2));++i)
  	 {
       //J'effectue une translation de la tête pour
       // trouver les patie du corpŝ en fonction de la longueur du snake
  		  s.matrice[1][i].position=translate(s.matrice[1][i-1].position,15,0);

          //Et une fois stocker je l'allume
  		 	s.matrice[1][i].type=1;
  	 }

}

// void dessineobstacle()
// {
//
// }
void draw(snake & s)
{
  //Si l'utilisateur click sur la touche space cela veut dire qu'il souhaite ouvrire le volet accueil et jouer
    if(isKeyPressed(SDLK_SPACE))
      s.openWindow=1;
    image_draw(s.backgroundImage,50,50,600,581);
    fontSize(30);
    color(255,255,255);
    print(300,660,"[SCORE]");
    print(318,630,s.score);
    print(SIZE/2,10,"Auteur : BAH Mamadou");  //oui c'est moi même

    color(0,0,0);
    rectangle(50,50,650,630); // couvre la zone du gazon
  	for(int i=0;i<2;++i)
  	{
  		for(int j=0;j<SIZE;++j)
  		{
        //J'affiche que les cellules allumé
  			if(s.matrice[i][j].type==1)
        {
            color(255,0,0);
            //Je dessine mon snake en parcourant la matrice
            circleFill(s.matrice[i][j].position.x,s.matrice[i][j].position.y,13);
        }
  		}
  	}

       //Je change la couleur de la tête du snake
      color(SIZE/2,32,150);
      circleFill(s.snakeHead.x,s.snakeHead.y,13);
      int test=floor(elapsedTime());
      //Si la variable testFruitMagic est a 2 je color en jaune pour designé le fruit magic sinon en rouge pour le fruit normal
      if(s.testFruitMagic==2)
        color(255,165,0);
      else
        color(255,25,0);

        //Je dessine le fruit
      circleFill(s.snakeFruit.x,s.snakeFruit.y,11);
      color(0,0,0);
      //Je dessine la queue
      circleFill(s.matrice[1][s.snakeLength+(SIZE/2)-1].position.x,s.matrice[1][s.snakeLength+(SIZE/2)-1].position.y,13);
      color(255,0,0);





}
void drawBloc(snake s)
{

    rectangleFill(120,200,180,220);
    rectangleFill(100,200,120,280);

    rectangleFill(120,480,180,500);
    rectangleFill(100,420,120,500);

    rectangleFill(500,200,560,220);
    rectangleFill(560,200,580,280);

    rectangleFill(500,480,560,500);
    rectangleFill(560,420,580,500);


}


//Cette fonction gere la collision du snake avec les obstacles
bool collisionsBlocAndSnake(snake s)
{
  bool test1=((s.snakeHead.x>=120 && s.snakeHead.y>=200) && (s.snakeHead.x<=180 && s.snakeHead.y<=220));
  bool test2=((s.snakeHead.x>=100 && s.snakeHead.y>=200) && (s.snakeHead.x<=120 && s.snakeHead.y<=280));
  bool test3=((s.snakeHead.x>=120 && s.snakeHead.y>=480) && (s.snakeHead.x<=180 && s.snakeHead.y<=500));
  bool test4=((s.snakeHead.x>=100 && s.snakeHead.y>=420) && (s.snakeHead.x<=120 && s.snakeHead.y<=500));
  bool test5=((s.snakeHead.x>=500 && s.snakeHead.y>=200) && (s.snakeHead.x<=560 && s.snakeHead.y<=220));
  bool test6=((s.snakeHead.x>=560 && s.snakeHead.y>=200) && (s.snakeHead.x<=580 && s.snakeHead.y<=280));
  bool test7=((s.snakeHead.x>=500 && s.snakeHead.y>=480) && (s.snakeHead.x<=560 && s.snakeHead.y<=500));
  bool test8=((s.snakeHead.x>=560 && s.snakeHead.y>=420) && (s.snakeHead.x<=580 && s.snakeHead.y<=500));

  if(test1 || test2 || test3 || test4 || test5 || test6 || test7 || test8)
  {
    return true;
  }
  return false;
}

//Cette fonction gere le grossissement du snake en fonction du nb fruit manger
void growTheSnake(snake & s)
{
  //Si la tête touche le fruit
   if((s.snakeHead.y>=s.snakeFruit.y-15 && s.snakeHead.y<=s.snakeFruit.y+15) && (s.snakeHead.x>=s.snakeFruit.x-15 && s.snakeHead.x<=s.snakeFruit.x+15))
   {
       //Je translate la dernière case du snke de 15  pour former un nouvel corp
   		  s.matrice[1][s.snakeLength+SIZE/2].position=translate(s.matrice[1][s.snakeLength+SIZE/2-1].position,15,0);
        //J'allume cette cellule pour que le draw puisse le dessiné
       	s.matrice[1][s.snakeLength+SIZE/2].type=1;
        //Si c'est un fruit magic qu'il a manger j'augmente le score de 20 sinon de 10
        if(s.testFruitMagic==2)
        {
          s.snakeLength+=1;
            s.score+=20;
        }
        else
        {
          s.snakeLength+=1;
            s.score+=10;
        }

       //Je regenere un autre fruit
        putFruit(s);
   }
}

//Cette fonction gere si la partie est perdu ou pas
bool gameOver(snake  s)
{
    for(int j=201;j<SIZE;++j)
    {
      //Je regarde si lma valeur de la tête du snake est egal a une valeur du corp
      if(s.matrice[1][SIZE/2].position.x==s.matrice[1][j].position.x  &&  s.matrice[1][SIZE/2].position.y== s.matrice[1][j].position.y)
       {
         //Je retourn vraie si oui
         return true;
       }


     }

     //Si le niveau est sur Difficile je test la collision sur les bloc

       if(collisionsBlocAndSnake(s) && s.niveau==2)
       {
         return true;
       }

    return false;
}

//direction vers le haut
void goUP(snake & s)
{
      growTheSnake(s);
      cellule oldTab[SIZE]; // un tableau pour les ancienne valeur de la matrice comme le jeu de la vie
      //Je teste que l'utilisateur ne fait pas le con en essayant d'aller vers le haut alors que la tête est tourné vers le bas
      //J'evite aussi q'un testeur plante mon programme, haha
      if(s.matrice[1][SIZE/2].position.y>=s.matrice[1][201].position.y)
       {
             for(int i=SIZE/2;i<SIZE;++i)
             {
               //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
               oldTab[i-SIZE/2]=s.matrice[1][i];
               oldTab[i-SIZE/2].type=1;
             }
             //je modifie la tête et je re-stock
             s.matrice[1][SIZE/2].position.y+=s.vitesse;

             //Je teste si la tête sort par le haut
             if(s.matrice[1][SIZE/2].position.y>=630)
             {
               //si oui je lui ramene en bas
                 s.matrice[1][SIZE/2].position.y=57;
             }

             s.snakeHead.y=s.matrice[1][SIZE/2].position.y;
             //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
             s.matrice[1][199]=  s.matrice[1][SIZE/2];
             //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
             //Ainsi de suite
             for(int i=SIZE/2;i<SIZE;++i)
             {
                 if(s.matrice[1][i+1].type==1)
                  s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
             }
       }
       else if(s.matrice[1][SIZE/2].position.y==57)
       {
         for(int i=SIZE/2;i<SIZE;++i)
         {
           //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
           oldTab[i-SIZE/2]=s.matrice[1][i];
           oldTab[i-SIZE/2].type=1;
         }
         //je modifie la tête et je re-stock
         //la variable vitesse facilite de géré les niveau
         s.matrice[1][SIZE/2].position.y+=s.vitesse;

         s.snakeHead.y=s.matrice[1][SIZE/2].position.y;
         //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
         s.matrice[1][199]=  s.matrice[1][SIZE/2];
         //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
         //Ainsi de suite
         for(int i=SIZE/2;i<SIZE;++i)
         {
             if(s.matrice[1][i+1].type==1)
              s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
         }
       }


}

  //direction vers la gauche
void goLEFT(snake & s)
{
      growTheSnake(s);
      cellule oldTab[SIZE]; // un tableau pour les ancienne valeur de la matrice comme le jeu de la vie
      //Je teste que l'utilisateur ne fait pas le con en essayant d'aller vers la gauche alors que la tête est tourné vers la droite
      //J'evite aussi q'un testeur plante mon programme, haha
      if(s.matrice[1][SIZE/2].position.x<=s.matrice[1][201].position.x)
       {
             for(int i=SIZE/2;i<SIZE;++i)
             {
               //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
               oldTab[i-SIZE/2]=s.matrice[1][i];
               oldTab[i-SIZE/2].type=1;
             }
              //je modifie la tête et je re-stock
             s.matrice[1][SIZE/2].position.x-=s.vitesse;

             if(s.matrice[1][SIZE/2].position.x<=50)
             {
                 s.matrice[1][SIZE/2].position.x=642;
             }

             s.snakeHead.x=s.matrice[1][SIZE/2].position.x;
             //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
             s.matrice[1][199]=  s.matrice[1][SIZE/2];
             //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
             //Ainsi de suite
             for(int i=SIZE/2;i<SIZE;++i)
             {
                 if(s.matrice[1][i+1].type==1)
                  s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
             }
       }
       else if(s.matrice[1][SIZE/2].position.x==642)
       {
         for(int i=SIZE/2;i<SIZE;++i)
         {
           //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
           oldTab[i-SIZE/2]=s.matrice[1][i];
           oldTab[i-SIZE/2].type=1;
         }
          //je modifie la tête et je re-stock
         s.matrice[1][SIZE/2].position.x-=s.vitesse;
         s.snakeHead.x=s.matrice[1][SIZE/2].position.x;
         //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
         s.matrice[1][199]=  s.matrice[1][SIZE/2];
         //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
         //Ainsi de suite
         for(int i=SIZE/2;i<SIZE;++i)
         {
             if(s.matrice[1][i+1].type==1)
              s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
         }
       }
}

//direction vers la droite
void goRIGHT(snake & s)
{
    growTheSnake(s);
    cellule oldTab[SIZE]; // un tableau pour les ancienne valeur de la matrice comme le jeu de la vie
      //Je teste que l'utilisateur ne fait pas le con en essayant d'aller vers la droite alors que la tête est tourné vers la gauche
      //J'evite aussi q'un testeur plante mon programme, haha
    if(s.matrice[1][SIZE/2].position.x>=s.matrice[1][201].position.x)
    {
        for(int i=SIZE/2;i<SIZE;++i)
        {
          //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
          oldTab[i-SIZE/2]=s.matrice[1][i];
          oldTab[i-SIZE/2].type=1;
        }
         //je modifie la tête et je re-stock
        s.matrice[1][SIZE/2].position.x+=s.vitesse;

        if(s.matrice[1][SIZE/2].position.x>=650)
        {
            s.matrice[1][SIZE/2].position.x=57;
        }

        s.snakeHead.x=s.matrice[1][SIZE/2].position.x;
        //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
        s.matrice[1][199]=  s.matrice[1][SIZE/2];
        //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
        //Ainsi de suite
        for(int i=SIZE/2;i<SIZE;++i)
        {
            if(s.matrice[1][i+1].type==1)
             s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
        }
    }
    else if(s.matrice[1][SIZE/2].position.x==57)
    {
      for(int i=SIZE/2;i<SIZE;++i)
      {
        //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
        oldTab[i-SIZE/2]=s.matrice[1][i];
        oldTab[i-SIZE/2].type=1;
      }
       //je modifie la tête et je re-stock
      s.matrice[1][SIZE/2].position.x+=s.vitesse;

      s.snakeHead.x=s.matrice[1][SIZE/2].position.x;
      //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
      s.matrice[1][199]=  s.matrice[1][SIZE/2];
      //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
      //Ainsi de suite
      for(int i=SIZE/2;i<SIZE;++i)
      {
          if(s.matrice[1][i+1].type==1)
           s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
      }
    }
}

//direction vers le bas
void goDOWN(snake & s)
{
      growTheSnake(s);
      cellule oldTab[SIZE]; // un tableau pour les ancienne valeur de la matrice comme le jeu de la vie
      //Je teste que l'utilisateur ne fait pas le con en essayant d'aller vers le bas alors que la tête est tourné vers le haut
      //J'evite aussi q'un testeur plante mon programme, haha

      if(s.matrice[1][SIZE/2].position.y<=s.matrice[1][201].position.y)
       {
             for(int i=SIZE/2;i<SIZE;++i)
             {
               //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
               oldTab[i-SIZE/2]=s.matrice[1][i];
               oldTab[i-SIZE/2].type=1;
             }
              //je modifie la tête et je re-stock
             s.matrice[1][SIZE/2].position.y-=s.vitesse;

             //Je teste si la tête sort par le bas
             if(s.matrice[1][SIZE/2].position.y<=50)
             {
                  //si oui je lui ramène en haut
                  s.matrice[1][SIZE/2].position.y=625;
             }

             s.snakeHead.y=s.matrice[1][SIZE/2].position.y;
             //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
             s.matrice[1][199]=  s.matrice[1][SIZE/2];
             //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
             //Ainsi de suite
             for(int i=SIZE/2;i<SIZE;++i)
             {
                 if(s.matrice[1][i+1].type==1)
                  s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
             }
       }
       else if(s.matrice[1][SIZE/2].position.y==625)
       {
           for(int i=SIZE/2;i<SIZE;++i)
           {
             //Je stocke les anciennes coordonnées dans un tableau 1D et j'allume leur type
             oldTab[i-SIZE/2]=s.matrice[1][i];
             oldTab[i-SIZE/2].type=1;
           }
            //je modifie la tête et je re-stock
           s.matrice[1][SIZE/2].position.y-=s.vitesse;
           s.snakeHead.y=s.matrice[1][SIZE/2].position.y;
           //Je mets les nouvelles coordonnées de la tête dans la case [1][199]
           s.matrice[1][199]=  s.matrice[1][SIZE/2];
           //L'ancienne coordonnées de la tête devient les nouvelles coordonnées du bout de corp derrière la tête
           //Ainsi de suite
           for(int i=SIZE/2;i<SIZE;++i)
           {
               if(s.matrice[1][i+1].type==1)
                s.matrice[1][i+1].position=oldTab[i-SIZE/2].position;
           }
       }

}

void update(snake & s)
{
   if(!gameOver(s) && s.restart!=1)
   {
     if(isKeyPressed(SDLK_UP))
      {
        //Ici je teste que la tete est superieur au 1er bout du corps
        if(s.matrice[1][SIZE/2].position.y>=s.matrice[1][201].position.y)
        //Si oui il p monter
             s.index=1;
             //Si la tete sort de l'autre cote je lui laisse monter
        else if(s.matrice[1][SIZE/2].position.y==57)
             s.index=1;
        else
        //Sinon il descent
          s.index=4;
      }

      if(isKeyPressed(SDLK_LEFT))
      {
             if(s.matrice[1][SIZE/2].position.x<=s.matrice[1][201].position.x)
                  s.index=2;
             else if(s.matrice[1][SIZE/2].position.x==642)
                  s.index=2;
             else
                s.index=3;
      }

      if(isKeyPressed(SDLK_RIGHT))
      {
          if(s.matrice[1][SIZE/2].position.x>=s.matrice[1][201].position.x)
               s.index=3;
          else if(s.matrice[1][SIZE/2].position.x==57)
               s.index=3;
          else
              s.index=2;
      }

      if(isKeyPressed(SDLK_DOWN))
      {
           if(s.matrice[1][SIZE/2].position.y<=s.matrice[1][201].position.y)
                s.index=4;
           else if(s.matrice[1][SIZE/2].position.y==625)
                s.index=4;
           else
                s.index=1;
      }

      if(s.index==1)
      {
        if(elapsedTime()>1)
           goUP(s);
      }

      if(s.index==2)
      {
        if(elapsedTime()>1)
           goLEFT(s);
      }

      if(s.index==3)
      {
        if(elapsedTime()>1)
           goRIGHT(s);
      }

      if(s.index==4)
      {
        if(elapsedTime()>1)
           goDOWN(s);
      }
   }

   else
   {
     if(gameOver(s) && s.restart!=1)
     {
       fontSize(50);
       color(255,255,255);
       print(SIZE/2,330,"GAME OVER");

       fontSize(20);

       print(SIZE/2-100,280,"appuyer sur le boutton r pour recommencer la partie");

     }

     if(isKeyPressed('r'))
     {
      //Je donne a index une valeur bizarre pour que le serpent prend aucune direction l'orsque le user fais restart
       s.index=20;
       //La variable passe a 1
       s.restart=1;

     }
   }
}


void acceuil(affiche & a ,snake & s)
{
   color(0,255,0);
   rectangleFill(0,a.y1 ,DIMW,DIMW);


   if(a.y1<DIMW/2-30)
   {
     fontSize(50);
     color(255,255,255);
     print(DIMW/2-150,DIMW/2+20,"BIENVENUE");

     fontSize(20);
     color(255,255,255);
     print(DIMW/2-180,DIMW/2-20,"touch Button space to start the GAME");
   }

  //S'il decide de faire monter le volet j'augmente le y1 comme ça ont le vois monter en temps reèl
   if(s.openWindow==1)
      a.y1+=5;
}

//procedure qui choisie le delay qui sera utiliser
void delayChoix(snake s)
{
  if(s.niveau==1)
    delay(50);
  else
    delay(40);
}



//procedure qui reinitialise la partie
void restartAll(snake s ,Menu m)
{

}

int main(int , char** )
{
    bool stop=false;
    winInit("JEU DU SNAKE", DIMW, DIMW);
    backgroundColor( SIZE/2,100,0);
    snake s;
    affiche a;
    srand(time(NULL));
    //Le menu
    Menu myMenu;

    Menu niv;

    menu_add(niv,"Facile");
    menu_add(niv,"Difficile");

    menu_add(myMenu,"PAUSE");
    menu_add(myMenu,"PLAY");
    //menu_add(myMenu,"RESTART");

    init(s);
    etat_initiale(s);

    putFruit(s);

    while(!stop )
    {
        winClear();

        delayChoix(s);


        //j'ai pas reussi a enlever le delay et faire que ca marche



        menu_draw(myMenu,60,DIMW-50,120,DIMW);
        //delay(50);

        switch (menu_select(myMenu))
        {

          case 0:
             /*sur pause*/
             //Si le niveau est sur Difficile cet a dire s.niveau==2 je dessine les obstacle sinon je le fais pas
             if(s.niveau==2)
               drawBloc(s);

             draw(s);
             break;
          case 1:
            /*sur play*/
            draw(s);
            //Si le niveau est sur Difficile cet a dire s.niveau==2 je dessine les obstacle sinon je le fais pas
            if(s.niveau==2)
              drawBloc(s);
            update(s);
            s.menuClick=1;
            break;

        }


        switch (menu_select(niv))
        {
          case 0:
             /*sur facile*/
             s.niveau=1;

             break;
          case 1:
           /*sur difficile*/
             s.niveau=2;

            break;
        }

        //Si la variable est a 1 c'est qu'il a choisie un niveau , donc je dessine plus les niveau pour l'empêcher de changer de niveau en plein game
         if(s.menuClick!=1)
             menu_draw(niv,DIMW-100,DIMW-50,DIMW-30,DIMW);
         else
         {
           if(s.niveau==2)
           {
             fontSize(20);
             color(255,255,255);
             print(DIMW-250,DIMW-25,"Votre niveau est sur difficile");
           }
           else
           {
             fontSize(20);
             color(255,255,255);
             print(DIMW-250,DIMW-25,"Votre niveau est sur facile");
           }

         }

         //Si restart est a 1, j'init tout et on recommence la partie
         if(s.restart==1)
         {
           init(s);
           etat_initiale(s);
           menu_setSelect(myMenu,0);
           s.menuClick=0;
           s.restart=2;

         }

       //Je dessine le volet d'acceuil
        acceuil(a,s);
        stop = winDisplay();
    }
    winQuit();
    return 0;
}