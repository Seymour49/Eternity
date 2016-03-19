#ifndef CONFIGURATION_MODEL_H
#define CONFIGURATION_MODEL_H

#include "instance_model.h"
#include <algorithm>
#include <iterator>
#include <time.h>
#include <random>
#include <chrono>


/**
 * Classe définissant une configuration, qui correspond à un ensemble
 * de position ( case, rotation ) pour une instance donnée. La classe
 * hérite d'instance car une instance peut disposer de plusieurs configurations
 * mais une configuration dépend d'une et une seule instance.
 * @author Ugo
 */

class Configuration : public Instance {
private:
    std::vector< std::pair< int, int> > vectPos;
    std::vector< std::pair< int, int> > permut;
    int nbConflicts;

public:

    Configuration(const std::string instancePath);

    std::vector< std::pair <int, int> > get_vectPos() const { return vectPos;}
    std::vector< std::pair <int, int> > get_permut()  const { return permut;}

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out, Configuration& r)
    { return r.print(out); }

    /**
     * Getters and setters
     *
     */
    int get_nbConflicts() const { return nbConflicts; }

    /**
     * Chargement d'un graphe sous forme de matrice
     * à partir d'un fichier d'exemple
     * @param fileName
     * @return
     */
    bool tryLoadFile(const std::string& fileName);

    /**
     * @brief verifNeighboor
     * @param indVoisin
     * @param card
     * @param motifToTest
     * @return
     */
    int verifNeighboor(int indVoisin, int card, int motifToTest);
    /**
     * @brief evaluateNbErrors
     * Evalue le nombre de conflits au sein de la configuration.
     * Est utilisé comme fonction de fitness de la recherche locale
     */
    void evaluateNbErrors();

    /**
     * @brief evaluate_local
     * Permet d'évaluer l'impact potentiel
     * d'une permutation. On récupère d'abord
     * le score actuel local puis on évalue les
     * scores possibles après permutation pour chaque
     * rotation possible.
     * En cas de déplacement d'un bord ou d'un coin, il
     * n'y a pas besoin de tester les rotations, celle-ci ne
     * pouvant changer en raison des contraintes qui leurs sont propres.
     *
     * En revanche, pour une pice interne, deux cas de figures se présentent.
     * Soit les pièces sont voisines, et dans ce cas nous devons tester toutes
     * les rotations. (16)
     *
     * Soit les pièces ne sont pas voisines et nous devons tester seulement
     *
     */

    void evaluate_local(std::pair< int, int>p);

    /**
     * @brief nbConflictsHere
     * @param indice
     * @return
     * Teste le nombre de conflits sur la case indice
     */
    int nbConflictsHere(std::pair<int, int> p, int indice);

    /**
     * @brief initRandomConfig
     * Fonction d'initialisation aléatoire de la configuration.
     * Calcule en même temps les différentes permutations possibles.
     * Les contraintes suivantes sont respectés :
     * Les pièces (coins, bords et internes) sont placées aléatoirement.
     * Les coins et bords disposent de la rotation leur permettant de
     * respecter
     */
    void initRandomConfig();

};


#endif
