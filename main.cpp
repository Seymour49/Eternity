
#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/configuration_model.h"

using namespace std;

int main(int argc, char *argv[])
{

    Configuration c("../Eternity/instances_puzzles/pieces_04x04.txt");
    Configuration c2("../Eternity/instances_puzzles/pieces_04x04.txt");
    c.initRandomConfig();
    c2 = c; // Fonctionne

    for(int i=0; i < c.get_nbRows()*c.get_nbCols(); ++i){

        int x = c.get_vectPos().at(i).first;
        int y = c.get_vectPos().at(i).second;
//        cout <<c.get_vectPos().at(i).first << " : " << c.nbConflictsHere(c.get_vectPos().at(i),i) << endl;
    }

//    cout << c  << c2;


    /*
     * Le principe de cette recherche locale sur le problème Eternity2
     * et ses sous-instances d'effectuer une recherche locale de type
     * Hill-Climbing stochastique itéré ayant pour stratégie de sélect-
     * ionner le meilleur améliorant pendant un certains
     * nombre d'itérations. Lorsqu'aucune amélioration n'aura été détec-
     * tée depuis un certains nombre d'itérations, nous nous considérerons
     * alors dans un optimum local et effectuerons un nombre de perturbations
     * suffisants pour se déplacer facilement dans l'espace de recherche.
     * Nos critères d'arrêts généraux sont l'atteinte de l'optimum global
     * ou celui du nombre maximal d'itérations autorisées.
     * De plus, notre fonction d'évaluation évalue le nombre de conflit d'une
     * configuration.
     *

    Configuration current("../Eternity/instances_puzzles/pieces_04x04.txt");
    current.initRandomConfig();
    Configuration best("../Eternity/instances_puzzles/pieces_04x04.txt");
    Configuration neighboor("../Eternity/instances_puzzles/pieces_04x04.txt");
    best = current;
    /*
     * Critères arrêts :
     *  - Optimum global
     *  - nb_iter_max atteint. Défini par 1000 T log(T) avec T nbPièces
     ///
    double max_iter = 1000* best.get_nbCols()* best.get_nbRows() * log(best.get_nbCols()* best.get_nbRows());
    double nb_iter = 0;
    while(best.evaluateNbErrors() > 0 || nb_iter != max_iter ){

        /* Pour sélectionner une solution voisine, on va tirer un nombre
         * aléatoire entre nb_iter et nb_permut-1
         *
//       /



    }
*/

}
