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
                    tmp[j] = vectPieces.at( p.first).get_motif()[j];
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
                cerr << "Fichier de configuration incompatible ou imcomplet" << endl;
                return false;
            } else {
                return true;
            }
        }
    }
}

void Configuration::randomConfiguration() {
    int i_rot;
    vector<int> pieces_id;

    // Travail uniquement sur l'id des pieces
    for(vector<Piece>::iterator i = vectPieces.begin(); i != vectPieces.end(); ++i ) {
        pieces_id.push_back(i->get_id());
    }
    // Mélange aléatoire
    random_shuffle(pieces_id.begin(), pieces_id.end());

    while(!pieces_id.empty()) {
        // Récupération de la pièce (id)
        int p = pieces_id.back();
        pieces_id.pop_back();
        // Choix aléatoire de la rotation
        i_rot = rand() % 4;
        pair<int, int> piece;
            piece.first = p;
            piece.second = i_rot;
        // Ajout de la pair
        vectPos.push_back(piece);
    }
}

/*
 * Vérifie l'appareillage entre la pièce en indVoisin
 * et le motif à tester.
 *
 * Utiliser dans l'évaluation d'une configuration, elle est
 * appellée avec l'indice courant + 1 pour une vérification
 * à l'est et avec l'indice courant + nbCols pour une vérif
 * au Sud
 *
 */
int Configuration::verifNeighboor(int indVoisin,int card, int motifToTest){

    int motifVoisin[MAX_CARD];
    int* motifVoisinAR;
    int idPieceToTest = vectPos.at(indVoisin).first;
    int rotation = vectPos.at(indVoisin).second;

    for(int j = 0; j < MAX_CARD; ++j){
        motifVoisin[j] = vectPieces.at(idPieceToTest).get_motif()[j];
    }

    motifVoisinAR = rotate(motifVoisin, rotation);

    if( motifToTest != motifVoisinAR[card])
        return 1;
    else
        return 0;
}


/* On considère la nécessité de vérifier pour chaque case les
 * appareillements Est et Sud sauf pour :
 * - la case 0,0 (vérification totale)
 * - les cases en première ligne ( vérif Nord, Sud, Est )
 * - les cases en première colonne ( vérif Ouest, Sud, Est )
 * - les cases en dernière colonne (vérif Est = 0, vérif Sud)
 * - les cases en dernière ligne (vérif Sud = 0, vérif Est)
 *
 */
int Configuration::evaluateNbErrors(){
    // A tester bordel de merde

    /*
     * Vérif à faire signifie récupérer le motif de la pièce dans vectPieces
     * à la position indX dans le vectPos et vérifier la pré-
     * sence d'un éventuel conflit.
     */
    int result = 0;
    int currentMotif[MAX_CARD];
    int* currentMotifAR;

    for(unsigned i=0; i < vectPos.size(); ++i){
        pair<int, int> p = vectPos.at(i);
        // Id de la pièce en position courante
        int idPiece = p.first;

        // Récupération du motif de cette pièce
        for(int j=0; j < MAX_CARD; ++j){
            currentMotif[j] = vectPieces.at(idPiece).get_motif()[j];
        }
        currentMotifAR = rotate(currentMotif, p.second);

//        /*
        if( i == 0 ){
            // Pas de voisins Nord et Ouest -> Nord == 0, Ouest == 0
            if( currentMotifAR[1] != 0 )
                ++result;
            if( currentMotifAR[2] != 0 )
                ++result;

            // Vérif Sud
            result += verifNeighboor(i+nbCols,2, currentMotifAR[0]);
            // Vérif Est
            result += verifNeighboor(i+1, 1,currentMotifAR[3]);

        }

        else if( i == nbCols -1 ){
            // Pas de voisins Nord et Est -> Nord == 0, Est == 0
            if( currentMotifAR[2] != 0 )
                ++result;
            if( currentMotifAR[3] != 0 )
                ++result;

            // Vérif Sud
            result += verifNeighboor(i+nbCols,2, currentMotifAR[0]);

        }
        else if ( i == (nbRows * (nbCols - 1) ) ){
            // Pas de voisins Sud et Ouest -> Sud == 0, Ouest == 0
            if( currentMotifAR[0] != 0)
                ++result;
            if( currentMotifAR[1] != 0 )
                ++result;

            // Vérif Est
            result += verifNeighboor(i+1, 1,currentMotifAR[3]);

        }
        else if( i == ((nbRows * nbCols) -1) ){
            // Pas de voisins Sud et Est -> Sud == 0, Est == 0
            if( currentMotifAR[0] != 0 )
                ++result;
            if( currentMotifAR[3] != 0 )
                ++result;

        }
        else if( i > 0 && i < (nbCols - 1) ) {
            // Bord Nord -> Pas de voisin Nord -> Nord == 0
            if( currentMotifAR[2] != 0)
                ++result;

            // Vérif Sud
            result += verifNeighboor(i+nbCols,2, currentMotifAR[0]);
            // Vérif Est
            result += verifNeighboor(i+1, 1,currentMotifAR[3]);

        }
        else if( i > (nbRows * (nbCols - 1) ) && i < ((nbRows * nbCols) -1) ){
            // Bord Sud -> Pas de voisin Sud -> Sud == 0
            if( currentMotifAR[0] != 0 )
                ++result;

            // Vérif Est
            result += verifNeighboor(i+1, 1,currentMotifAR[3]);

        }
        else if( (i % nbCols) == 0 ){ // Rajoutez contrainte > < sur i ?
            // Bord Ouest -> Pas de voisin Ouest -> Ouest ==0
            if( currentMotifAR[1] != 0 )
                ++result;

            // Vérif Sud
            result += verifNeighboor(i+nbCols,2, currentMotifAR[0]);
            // Vérif Est
            result += verifNeighboor(i+1, 1,currentMotifAR[3]);

        }
        else if( (i % nbCols ) == (nbCols - 1) ){ // Rajoutez contrainte > < sur i ?
            // Bord Est -> Pas de voisins Est -> Est == 0
            if( currentMotifAR[3] != 0 )
                ++result;

            // Vérif Sud
            result += verifNeighboor(i+nbCols,2, currentMotifAR[0]);
        }
        else{
            // Vérif Sud
            result += verifNeighboor(i+nbCols,2, currentMotifAR[0]);
            // Vérif Est
            result += verifNeighboor(i+1, 1,currentMotifAR[3]);

        }

    }
    return result;
}

