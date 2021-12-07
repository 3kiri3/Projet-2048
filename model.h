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

/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 * //


/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 **/
Plateau plateauVide();

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre();

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 **/
Plateau plateauInitial();

/**
* génére un nombre aleatoire sur une tuile vide aléatoire
* @param plateau de jeu
* @return plateau de jeu avec une case remplie en plus
**/
Plateau Generetkt(Plateau plateau);

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
pair<Plateau, int> deplacementGauche(Plateau plateau);


/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/

pair<Plateau, int> deplacementDroite(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
pair<Plateau, int> deplacementHaut(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
pair<Plateau, int> deplacementBas(Plateau plateau);

/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @return le Plateau déplacé dans la direction
 **/
pair<Plateau, int> deplacement(Plateau plateau);

/** affiche un Plateau
 * @param p le Plateau
 **/
void dessine(Plateau plateau);

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau retourné en fin de fonction est similaire au tableau donné en entré, false sinon
 **/
bool estTermine(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);

/** permet de lancer une partie et jouer au jeu
*
*
* */
void jeu();
