#include "tp4.hpp"

#include "Point.hpp"
#include "Ligne.hpp"
#include "Rectangle.hpp"
#include "Polygone.hpp"
#include "Ellipse.hpp"
#include "Cercle.hpp"
#include "Texte.hpp"
#include "Couleurs.h"

/* Fonction à appeler à la fin de faireDessin */
void ecrireFrame(const Canevas* c);


/*Cercle* nouveauCercle(Coord centre, unsigned int rayon, unsigned int couleur) {
	return new Cercle(centre,rayon,couleur);
}*/

/*void faireDessin(Forme** formes, unsigned int n) {

    Canevas* c = new Canevas(LARGEUR_CANEVAS, HAUTEUR_CANEVAS,  COULEUR_CANEVAS);
    for(int i=0; i< n; i++)
    {
        c->dessinerForme(formes[i]);
    }

    ecrireFrame(c);
    delete(c);
}*/


/*void desallouerForme(Forme* forme) {

    delete(forme);
}*/

/*void Canevas::dessinerForme(Forme *forme)
{
    forme->dessiner(this);
}*/

/*void Canevas::assignerPixel(int x, int y, unsigned int couleur)
{
    if(x >= this->_w || y >= this->_h || x < 0 || y < 0)
          return;

    this->_canevas[y*this->_w+x] = couleur;
}*/

void Canevas::assignerPixel(Coord coord, unsigned int couleur)
{
    assignerPixel(coord.x,coord.y, couleur);
}
