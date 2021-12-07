#include <iostream>
#include <sstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include "conio.h"

#define KEY_DOWN 80
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define BYEBYE 'q'
using namespace std;

typedef vector<vector<int>> Plateau;
/** Des fonctions peuvent Ãªtre ajoutÃ©s Ã  ce fichier si besoin est (fonctions pour mettre Ã  jour le score par exemple)
 * //


/** gÃ©nÃ¨re un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide()
{
	Plateau t;
	int score = 0;
	t = Plateau(4); // allocation de la taille du tableau principal

	for (int i = 0; i < 4; i++)
	{
		t[i] = vector<int>(4);
		for (int j = 0; j < 4; j++)
		{

			t[i][j] = 0; // crÃ©ation de tableaux de quatre cases dans chaque case prÃ©-Ã©xistente
		}
	}

	return t;
}

/** gÃ©nÃ¨re alÃ©atoirement un 2 ou un 4 avec des probabilitÃ©s respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre()
{
	int a = rand() % 10;
	if (a == 2)
	{                    // la probabilitÃ© de tirer un 4 Ã©tant de 1/10, peu-impporte la valeur tirÃ©e par le rand, elle nous servira de repÃ¨re pour return un quatre car on a une chance sur 10 de trouver la valeur trouvÃ©e
		return 4;
	}
	else
	{
		return 2;
	}
}

/** gÃ©nÃ¨re deux nombres sur des cases alÃ©atoires d'un Plateau vide
 *  @return un Plateau en dÃ©but de jeu
 **/
Plateau plateauInitial()
{
	Plateau plateau = plateauVide();

	srand(time(NULL));	  // ici figurait un srand(time(NULL)) mais cela faisait buguer la fonction et ne retournait qu'une case remplie dans le tableau
	int b = (rand() % 4); // on donne une valeur alÃ©atoire qui correspondra Ã  l'indice de la ligne du tableau
	int c = (rand() % 4); // on donne une valeur alÃ©atoire qui correspondra a l'indice de la colonne du tableau
	int d = (rand() % 4); // on donne une valeur alÃ©atoire qui correspondra Ã  l'indice de la ligne du tableau
	int e = (rand() % 4); // on donne une valeur alÃ©atoire qui correspondra a l'indice de la colonne du tableau
	int a = tireDeuxOuQuatre();
	int z = tireDeuxOuQuatre();
	while (b == d && c == e)
	{ // boucle permettant de ne pas placer deux fois la mÃªme case sur le tableau ( pas avoir les mÃªmes indices lors du tirage)
		b = (rand() % 4);
		c = (rand() % 4);
	}
	plateau[b][c] = a; //  donne une valeur aleatoire entre 2 et 4 Ã  une case alÃ©atoire du tableau
	plateau[d][e] = z; // de mÃªme ici avec des valeurs diffÃ©rentes
	return plateau;
}


/**
 * gÃ©nÃ©re un nombre aleatoire sur une tuile vide alÃ©atoire
 * @param plateau de jeu
 * @return plateau de jeu avec une case remplie en plus
 **/
Plateau Generetkt(Plateau plateau)
{
	srand(time(NULL));
	int a = rand() % 4; // on donne une valeur alÃ©atoire qui correspondra Ã  l'indice de la ligne du tableau
	int b = rand() % 4; // on donne une valeur alÃ©atoire qui correspondra a l'indice de la colonne du tableau
	while (plateau[a][b] != 0)
	{ // boucle permettant de gÃ©nÃ©rer une tuile sur une tuile vide du tableau
		srand(time(NULL));
		a = rand() % 4;
		b = rand() % 4;
	}
	plateau[a][b] = tireDeuxOuQuatre(); // donne une valeur aleatoire entre 2 et 4 Ã  une case alÃ©atoire du tableau
	return plateau;
}

/** dÃ©place les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois dÃ©placÃ© vers la gauche
 **/
pair<Plateau, int> deplacementGauche(Plateau plateau)
{
	int score = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (plateau[i][j] == 0)
			{
				for (int count = j + 1; count < 4; count++) // boucle permettant dans un premier point de tout dÃ©caller Ã  gauche
					if (plateau[i][count])
					{
						plateau[i][j] = plateau[i][count]; // prend la valeur de la case d'Ã  cÃ´tÃ© (gauche)
						plateau[i][count] = 0;			   // et vide la valeur de cette derniere
						break;
					}
			}
		}
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (plateau[i][j] == 0) // cas dans lequel la case est vide
			{
				for (int count = j + 1; count < 3; count++) // ne prend pas en compte la ligne de gauche et commence directement a la  deuxieme case
				{

					if (plateau[i][count] == plateau[i][count + 1])
					{
						plateau[i][j] = plateau[i][count] + plateau[i][count + 1]; // additionne les tuiles si elles ont une valeur identique
						plateau[i][count + 1] = 0;								   // remet a 0 la case de droite qui vient d'Ãªtre ajouter a celle a sa gauche
						plateau[i][count] = 0;
						score += plateau[i][j];
					}
					else if (plateau[i][count]) // si elles ne sont pas Ã©gales alors on dÃ©cale seulement pour faire disparaire la tuile vide
					{
						plateau[i][j] = plateau[i][count];
						plateau[i][count] = plateau[i][count + 1];
						plateau[i][count + 1] = 0;
					}
				}
			}
			else if (plateau[i][j] == plateau[i][j + 1]) // on teste bien que la tuile ne soit pas vide et que les deux adjacentes soient le rÃ©sultat de 2^n pour un certain n
			{
				plateau[i][j] = plateau[i][j] + plateau[i][j + 1]; // on affecte donc Ã  la tuile la valeur des deux adjacentes
				plateau[i][j + 1] = 0;							   // on vide la tuile du gauche car elle a fusionÃ© avec la tuile initiale
				score += plateau[i][j];
			}
		}
	pair<Plateau, int> ok = {plateau, score};
	return ok;
}

/** dÃ©place les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois dÃ©placÃ© vers la droite
 **/

pair<Plateau, int> deplacementDroite(Plateau plateau)
{
	int score = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 0; j--)                   
		{
			if (plateau[i][j] == 0)
			{
				for (int count = j - 1; count >= 0; count--) // boucle permettant dans un premier point de tout dÃ©caller Ã  droite
					if (plateau[i][count])
					{
						plateau[i][j] = plateau[i][count]; // prend la valeur de la case d'Ã  cÃ´tÃ© (droite)
						plateau[i][count] = 0;			   // et vide la valeur de cette derniere
						break;
					}
			}
		}
	}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (plateau[i][j] == 0) // cas dans lequel la case est vide
			{
				for (int count = j - 1; count > 0; count--) // ne prend pas en compte la ligne de droite et commence directement a la 3 eme cases
				{

					if (plateau[i][count] == plateau[i][count - 1])
					{
						plateau[i][j] = plateau[i][count] + plateau[i][count - 1]; // additionne les tuiles si elles ont une valeur identique
						plateau[i][count - 1] = 0;								   // remet a 0 la case de gauche qui vient d'Ãªtre ajouter a la tuile initiale
						plateau[i][count] = 0;
						score += plateau[i][j];
					}
					else if (plateau[i][count]) // si elles ne sont pas Ã©gales alors on dÃ©cale seulement pour faire disparaire la tuile vide
					{
						plateau[i][j] = plateau[i][count];
						plateau[i][count] = plateau[i][count - 1];
						plateau[i][count - 1] = 0;
					}
				}
			}
			else if (plateau[i][j] == plateau[i][j - 1]) // on teste bien que la tuile ne soit pas vide et que les deux adjacentes soient le rÃ©sultat de 2^n pour un certain n
			{
				plateau[i][j] = plateau[i][j] + plateau[i][j - 1]; // on affecte donc Ã  la tuile la valeur des deux adjacentes
				plateau[i][j - 1] = 0;							   // on vide la tuile de gauche car elle vient de fusionner avec la tuile initiale
				score += plateau[i][j];
			}
		}
	pair<Plateau, int> ok = {plateau, score};
	return ok;
}

/** dÃ©place les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois dÃ©placÃ© vers le haut
 **/
pair<Plateau, int> deplacementHaut(Plateau plateau)
{
	int score = 0;
	for (int i = 0; i < 4; i++)                   //
	{
		for (int j = 0; j < 4; j++)
		{
			if (plateau[i][j] == 0)
			{
				for (int count = i + 1; count < 4; count++) // boucle permettant dans un premier point de tout dÃ©caller en haut, on commence la boucle a la deuxieme ligne
					if (plateau[count][j])
					{
						plateau[i][j] = plateau[count][j]; // prend la valeur de la case d'en dessous 
						plateau[count][j] = 0;			   // et vide la valeur de cette derniere
						break;
					}
			}
		}
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
		{
			if (plateau[i][j] == 0) // cas dans lequel la case est vide
			{
				for (int count = i + 1; count < 3; count++) // ne prend pas en compte la premiere ligne
				{

					if (plateau[count][j] == plateau[count + 1][j])
					{
						plateau[i][j] = plateau[count][j] + plateau[count + 1][i]; // additionne les tuiles si elles ont une valeur identique
						plateau[count + 1][j] = 0;								   // remet a 0 la case du dessous qui vient d'Ãªtre ajouter a celle d'au dessus
						plateau[count][j] = 0;
						score += plateau[i][j];
					}
					else if (plateau[count][j]) // si elles ne sont pas Ã©gales alors on dÃ©cale seulement pour faire disparaire la tuile vide
					{
						plateau[i][j] = plateau[count][j];
						plateau[count][j] = plateau[count + 1][j];
						plateau[count + 1][j] = 0;
					}
				}
			}
			else if (plateau[i][j] == plateau[i + 1][j]) // on teste bien que la tuile ne soit pas vide et que les deux adjacentes soient le rÃ©sultat de 2^n pour un certain n
			{
				plateau[i][j] = plateau[i][j] + plateau[i + 1][j]; // on affecte donc Ã  la tuile la valeur des deux adjacentes
				plateau[i + 1][j] = 0;							   // on vide la tuile du bas car elle a fusionÃ© avec la tuile initiale
				score += plateau[i][j];
			}
		}
	pair<Plateau, int> ok = {plateau, score};
	return ok;
}

/** dÃ©place les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois dÃ©placÃ© vers le bas
 **/
pair<Plateau, int> deplacementBas(Plateau plateau)
{
	int score = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j >= 0; j--)
		{
			if (plateau[j][i] == 0)
			{
				for (int count = j - 1; count >= 0; count--) // boucle permettant dans un premier point de tout dÃ©caller en bas
					if (plateau[count][i])
					{
						plateau[j][i] = plateau[count][i]; // prend la valeur de la case du dessus
						plateau[count][i] = 0;			   // et vide la valeur de cette derniere
						break;
					}
			}
		}
	}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (plateau[j][i] == 0) // cas dans lequel la case est vide
			{
				for (int count = j - 1; count > 0; count--) // ne prend pas en compte la derniere ligne et commence directement a la troisieme
				{

					if (plateau[count][i] == plateau[count - 1][i])
					{
						plateau[j][i] = plateau[count][i] + plateau[count - 1][i]; // additionne les tuiles si elles ont une valeur identique
						plateau[count - 1][i] = 0;								   // remet a 0 la case du dessus qui vient d'Ãªtre ajouter a la tuile initiale
						plateau[count][i] = 0;
						score += plateau[j][i];
					}
					else if (plateau[count][i]) // si elles ne sont pas Ã©gales alors on dÃ©cale seulement pour faire disparaire la tuile vide
					{
						plateau[j][i] = plateau[count][i];
						plateau[count][i] = plateau[count - 1][i];
						plateau[count - 1][i] = 0;
					}
				}
			}
			else if (plateau[j][i] == plateau[j - 1][i]) // on teste bien que la tuile ne soit pas vide et que les deux adjacentes soient le rÃ©sultat de 2^n pour un certain n
			{
				plateau[j][i] = plateau[j][i] + plateau[j - 1][i]; // on affecte donc Ã  la tuile la valeur des deux adjacentes
				plateau[j - 1][i] = 0;							   // on vide la tuile du dessus car elle vient de fusionner avec la tuile initiale
				score += plateau[j][i];
			}
		}
	pair<Plateau, int> ok = {plateau, score};
	return ok;
}

/** dÃ©place les tuiles d'un Plateau dans la direction donnÃ©e et gÃ©nÃ¨re une nouvelle tuile si le dÃ©placement est valide
 *  @param plateau le Plateau
 *  @return le Plateau dÃ©placÃ© dans la direction
 **/
pair<Plateau, int> deplacement(Plateau plateau)
{
	char direction;
	bool stop = false;
	int score = 0;
	pair<Plateau, int> i;
	cout << "Choisir une direction ! : ";
	while (stop == false)
	{
		char y = _getch(); // recupere la valeur de la touche appuyÃ©e
		switch (y)
		{ // attend de l'utilisateur d'appuyer sur une touche (ici dÃ©finie prÃ©alablement

		case KEY_LEFT: // dans le cas ou la touche de gauche est pressÃ©e
			i = deplacementGauche(plateau);
			plateau = i.first;   // plateau est Ã©gale au premier element de la pair renvoyÃ©e par deplacementgauche
			score += i.second;   // incrÃ©mentation du score	avec le second element de la pair de dezplacemntgauche
			stop == true;         // arrete la demande 
			break;
		case KEY_RIGHT: // dans le cas ou la touche de droite est pressÃ©e
			i = deplacementDroite(plateau);
			plateau = i.first;
			score += i.second;
			stop == true;
			break;
		case KEY_DOWN: // dans le cas ou la touche du bas est pressÃ©e
			i = deplacementBas(plateau);
			plateau = i.first;
			score += i.second;
			stop == true;
			break;
		case KEY_UP: // dans le cas ou la touche du haut est pressÃ©e
			i = deplacementHaut(plateau);
			plateau = i.first;
			score += i.second;
			stop == true;
			break;
		case BYEBYE:
			cout << "La partie est terminÃ©e pour vous. A bientÃ´t" << endl;
			exit(0);
			stop == true;
			break;
		}
		pair<Plateau, int> m = {plateau, score};

		return m;
	}
}

/** affiche un Plateau
 * @param p le Plateau
 **/
void dessine(Plateau plateau)
{
	cout << "*****************" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << "* " << plateau[i][j] << " ";
		}
		cout << "*" << endl
			 << "*****************" << endl;
	}
}

/** permet de savoir si une partie est terminÃ©e
 *  @param plateau un Plateau
 *  @return true si le plateau retournÃ© en fin de fonction est similaire au tableau donnÃ© en entrÃ©, false sinon
 **/
bool estTermine(Plateau plateau)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (plateau[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}

/** permet de savoir si une partie est gagnÃ©e
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (plateau[i][j] == 2048)
			{				 // dans cette version classique du 2048, si on rencontre une tuille valant 2048
				return true; // alors la partie est gagnÃ©e
			}
		}
	}
	return false;
}
/** permet de lancer une partie et jouer au jeu
 *
 *
 * */
void jeu()
{
	Plateau plateau = plateauInitial();
	dessine(plateau);
	int score = 0;
	pair<Plateau, int> poil;
	do
	{
		poil = deplacement(plateau);
		score += poil.second;
		plateau = poil.first;
		plateau = Generetkt(poil.first);
		system("cls"); // efface le tableau prÃ©cÃ¨dant aprÃ¨s avoir entrÃ©e un nouveau dÃ©placement
		dessine(plateau);
		cout << score << endl;
		if (estGagnant(plateau) == true)
		{
			cout << "Bravo, vous avez gagnez ! voulez-vous quand mÃªme continuer Ã  jouer ? Si oui, press c sinon press ";
			char u;
			cin >> u;
			if (u == 'q')
			{
				exit(0);
			}
		}

	} while (estTermine(plateau) == false);
	if (estTermine(plateau) == true)
	{
		cout << " Dommage, vous avez perdu:( "
			 << " voulez-vous rÃ©essayer ? press m. Sinon press q pour quitter" << endl;
		char n;
		cin >> n;
		if (n == 'q')
		{
			exit(0);
		}
		jeu();
	}
}
/**int main()
{
	system("color 0D"); // couleur du fond et du tableau
	system("cls");		// refresh Ã  chaque fois la console.
	jeu();

	return 0;
}
