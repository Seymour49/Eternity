#ifndef CONFIGURATION_MODEL_H
#define CONFIGURATION_MODEL_H

#include "instance_model.h"
#include <algorithm>
#include <iterator>

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

public:

    Configuration(const std::string instancePath);

    std::vector< std::pair <int, int> > get_vectPos() const {return vectPos;}

    /**
     * Impression sur un flux de l'instance
     * @param out
     * @return le flux donné en paramètre avec l'instance 'imprimé'
     */
    std::ostream& print(std::ostream& out);

    friend std::ostream& operator<<(std::ostream& out, Configuration& r)
    { return r.print(out); }


    /**
     * Chargement d'un graphe sous forme de matrice
     * à partir d'un fichier d'exemple
     * @param fileName
     * @return
     */
    bool tryLoadFile(const std::string& fileName);

    /**
     * Création des placements aléatoires des pièces (nécessaire pour l'affichage)
     */
    void randomConfiguration();

    int* rotate(int motif[], int nbRot);

};


#endif
