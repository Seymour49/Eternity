#include "configuration_model.h"

using namespace std;

Configuration::Configuration(const string instancePath){
    Instance::tryLoadFile(instancePath);
    cout << instancePath << endl;
}

int* Configuration::rotate(int motif[], int nbRot){
    int* result = new int;

    copy(motif, motif+MAX_CARD, result);

    for(int i=0; i < nbRot; ++i){
        std::rotate(result, result+3, result+4);
    }
    return result;
}

ostream& Configuration::print(ostream &out){

        for(unsigned i=0; i < vectPos.size(); ++i){
                pair<int, int> p = vectPos.at(i);

                int cc = i % nbCols;
                int cr = i / nbRows;
                out << "Case (" << cr << "," << cc << ") : " << p.first << " Rotation : " << p.second ;
                out << " Motif initial : ";
                int tmp[MAX_CARD];
                for( int j=0; j < MAX_CARD; ++j){
                    tmp[j] = vectPieces.at( (cr*nbCols) + cc).get_motif()[j];
                    out << tmp[j] << " ";
                }

                out  << " ; Motif après rotation : " ;

                int* result = rotate(tmp, p.second);
                for(int l=0; l < MAX_CARD; ++l){
                    out << result[l] << " ";
                }
                out << endl;
            }

        return out;
}

bool Configuration::tryLoadFile(const string &fileName){
    if( nbRows * nbCols == 0){
        cerr << "Aucune instance n'est chargée" << endl;
        return false;
    }else{
        ifstream f(fileName.c_str());

        if(!f){
            cerr << "Erreur pendant l'ouverture du fichier" << endl;
            return false;
        } else {

            string line;

            while(getline(f,line)){

                vector<string>& tokens = explode(line);

                vectPos.push_back( pair<int,int>( atoi(tokens[0].c_str()) , atoi(tokens[1].c_str()) ) );
            }

            if(vectPos.size() != (unsigned)(nbRows * nbCols) ){
                cerr << "Fichier de configuration incomplet" << endl;
                return false;
            } else {
                return true;
            }
        }
    }
}
