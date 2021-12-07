#include <iostream>
#include <sstream>
#include <random>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <assert.h>
#include "conio.h"
using namespace std;



typedef vector<vector<int> > Plateau;

/** Des fonctions peuvent �tre ajout�s � ce fichier si besoin est (fonctions pour mettre � jour le score par exemple)
 * //


/** g�n�re un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide();

/** g�n�re al�atoirement un 2 ou un 4 avec des probabilit�s respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** g�n�re deux nombres sur des cases al�atoires d'un Plateau vide
 *  @return un Plateau en d�but de jeu
 **/
Plateau plateauInitial();

/**
* g�n�re un nombre aleatoire sur une tuile vide al�atoire
* @param plateau de jeu
* @return plateau de jeu avec une case remplie en plus
**/
Plateau Generetkt(Plateau plateau);

/** d�place les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois d�plac� vers la gauche
 **/
pair<Plateau, int> deplacementGauche(Plateau plateau);


/** d�place les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois d�plac� vers la droite
 **/

pair<Plateau, int> deplacementDroite(Plateau plateau);

/** d�place les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois d�plac� vers le haut
 **/
pair<Plateau, int> deplacementHaut(Plateau plateau);

/** d�place les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois d�plac� vers le bas
 **/
pair<Plateau, int> deplacementBas(Plateau plateau);

/** d�place les tuiles d'un Plateau dans la direction donn�e et g�n�re une nouvelle tuile si le d�placement est valide
 *  @param plateau le Plateau
 *  @return le Plateau d�plac� dans la direction
 **/
pair<Plateau, int> deplacement(Plateau plateau);

/** affiche un Plateau
 * @param p le Plateau
 **/
void dessine(Plateau plateau);

/** permet de savoir si une partie est termin�e
 *  @param plateau un Plateau
 *  @return true si le plateau retourn� en fin de fonction est similaire au tableau donn� en entr�, false sinon
 **/
bool estTermine(Plateau plateau);

/** permet de savoir si une partie est gagn�e
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);

/** permet de lancer une partie et jouer au jeu
*
*
* */
void jeu();
