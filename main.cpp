
#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/configuration_model.h"

using namespace std;

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
 */

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


    Configuration current("../Eternity/instances_puzzles/pieces_04x04.txt");
    current.initRandomConfig();
    Configuration best("../Eternity/instances_puzzles/pieces_04x04.txt");
    Configuration neighboor("../Eternity/instances_puzzles/pieces_04x04.txt");
    best = current;

     // Critères arrêts :
     //  - Optimum global
     //- nb_iter_max atteint. Défini par 1000 T log(T) avec T nbPièces

    double max_iter = 1000* best.get_nbCols()* best.get_nbRows() * log(best.get_nbCols()* best.get_nbRows());
    double nb_iter = 0;
    int nbPermut = (int)current.get_permut().size();
    size_t seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    int last_modif = 0;

    /*
    while(best.evaluateNbErrors() > 0 || nb_iter < max_iter ){

        // Pour sélectionner une solution voisine, on va tirer un nombre
        // aléatoire entre nb_iter et nb_permut-1
        if(last_modif < max_ss_modif ){
            int ind_permut = rand() % nbPermut + lastmodif;

            pair<int,int> testingPermut = pair<int,int>(current.get_permut().at(ind_permut).first,current.get_permut().at(ind_permut).second);

            // current.evaluate retourne *pair< int, pair<int, int> > ou 1 représente le score et 2 et 3 les rotations
            if( current.evaluate_local(testingPermut) == NULL ){
                ++nb_iter;
                ++lastModif;
            }
            else if( current.evaluate_local(testingPermut).first == 0 ){
                pair<int,int> rot = current.evaluate_local(testingPermut).second;
                current.reverse_permut(last_modif,ind_permut);
                current.update(testingPermut, rot.first, rot.second);
                best = current;
                ++lastModif;
                ++nb_iter;
            }else{
                pair<int,int> rot = current.evaluate_local(testingPermut).second;
                current.reverse_permut(last_modif,ind_permut);
                current.update(testingPermut, rot.first, rot.second);
                best = current;
                lastModif = 0;
                ++nb_iter;
            }
        }
        else{
            current.degenerate();
            best = current;
            ++nb_iter;
            cout  << "Dégenerescence due à max_ss_modif atteint" << endl;
        }


    }
    */

}
