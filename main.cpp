#include <QApplication>

#include "Model/piece_model.h"
#include "Model/instance_model.h"
#include "Model/configuration_model.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    */

    cout << "Debut debug instance" << endl;
    Instance inst;
    inst.tryLoadFile("../Eternity/instances_puzzles/pieces_04x04.txt");
    cout << inst;

    Instance *inst2 = new Instance("../Eternity/instances_puzzles/pieces_04x04.txt");
    cout << *inst2;

    cout << "Fin debug instance" << endl;


    Configuration c("../Eternity/instances_puzzles/pieces_04x04.txt");
    c.tryLoadFile("../Eternity/instances_results/pieces_04x04-result_01.txt");
    cout << c;
/*

*/
}
