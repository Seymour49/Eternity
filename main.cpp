
#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/configuration_model.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    cout << "Debut debug instance" << endl;
    Instance inst;
    inst.tryLoadFile("../Eternity/instances_puzzles/pieces_04x04.txt");
    cout << inst;

    Instance *inst2 = new Instance("../Eternity/instances_puzzles/pieces_04x04.txt");
    cout << *inst2;

    cout << "Fin debug instance" << endl;

    cout << "Debut debug config" << endl;
    cout << "config via fichier" << endl;
    Configuration c("../Eternity/instances_puzzles/pieces_03x03.txt");
    c.tryLoadFile("../Eternity/instances_results/pieces_03x03-result_01.txt");
    cout << c;

    Configuration c2("../Eternity/instances_puzzles/pieces_04x04.txt");
    c2.randomConfiguration();
    cout << " Config via randomconfiguration()" << endl;

    cout << c2;

    cout << "fin debug config" << endl;
    */
   /*
    Configuration c("../Eternity/instances_puzzles/pieces_04x04.txt");
    c.tryLoadFile("../Eternity/instances_results/pieces_04x04-result_01.txt");
    cout << c;

    c.evaluateNbErrors();

    cout << c.get_nbConflicts() << " error(s)";
    */
    Configuration c("../Eternity/instances_puzzles/pieces_16x16.txt");
//    Configuration c2("../Eternity/instances_puzzles/pieces_04x04.txt");
    c.initRandomConfig();
//    c2.initRandomConfig();
//    cout << c ;
    /*
     * Mise en place de l'algo
     *
     *
     */
//    c2 = c;  Fonctionne

}
