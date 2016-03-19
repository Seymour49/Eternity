#include "configuration_model.h"

using namespace std;

Configuration::Configuration(const string instancePath){
    Instance::tryLoadFile(instancePath);
    nbConflicts = -1;
}

ostream& Configuration::print(ostream &out){

        for(unsigned i=0; i < vectPos.size(); ++i){
                pair<int, int> p = vectPos.at(i);

                int cc = i % nbCols;
                int cr = i / nbRows;
                out << "Case (" << cr << "," << cc << ") : " << p.first << " Rotation : " << p.second ;
                out << " Motif initial : ";

                for( int j=0; j < MAX_CARD; ++j){
                    out << vectPieces.at(p.first).get_motif()[j] << " ";
                }

                out  << " ; Motif après rotation : " ;


                for(int l=0; l < MAX_CARD; ++l){
                    out << vectPieces.at(p.first).get_motif(l,p.second) << " ";
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

/**
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

    int idPieceToTest = vectPos.at(indVoisin).first;
    int rotation = vectPos.at(indVoisin).second;

    if( motifToTest != vectPieces.at(idPieceToTest).get_motif(card, rotation) )
    {
        return 1;
    }else
        return 0;
}


/**
 *  On considère la nécessité de vérifier pour chaque case les
 * appareillements Est et Sud sauf pour :
 * - la case 0,0 (vérification totale)
 * - les cases en première ligne ( vérif Nord, Sud, Est )
 * - les cases en première colonne ( vérif Ouest, Sud, Est )
 * - les cases en dernière colonne (vérif Est = 0, vérif Sud)
 * - les cases en dernière ligne (vérif Sud = 0, vérif Est)
 *
 */
void Configuration::evaluateNbErrors(){

    nbConflicts = 0;
    int motifToTest;

    for(unsigned i=0; i < vectPos.size(); ++i){
        pair<int, int> p = vectPos.at(i);
        // Id de la pièce en position courante
        int idPiece = p.first;

        if( i == (unsigned)0 ){
            motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
            // Pas de voisins Nord et Ouest -> Nord == 0, Ouest == 0
            if( motifToTest != 0 ){
                ++nbConflicts;

            }

            motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }

            // Vérif Sud
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            nbConflicts += verifNeighboor(i+nbCols,2, motifToTest);
            // Vérif Est
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            nbConflicts += verifNeighboor(i+1, 1,motifToTest);

        }

        else if( i == (unsigned)(nbCols -1) ){
            // Pas de voisins Nord et Est -> Nord == 0, Est == 0
            motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }
            // Vérif Sud
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            nbConflicts += verifNeighboor(i+nbCols,2, motifToTest);

        }
        else if ( i == (unsigned)(nbRows * (nbCols - 1) ) ){
            // Pas de voisins Sud et Ouest -> Sud == 0, Ouest == 0
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            if( motifToTest != 0){
                ++nbConflicts;

            }
            motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }
            // Vérif Est
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            nbConflicts += verifNeighboor(i+1, 1,motifToTest);

        }
        else if( i == (unsigned)((nbRows * nbCols) -1) ){
            // Pas de voisins Sud et Est -> Sud == 0, Est == 0
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;
            }
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;
            }
        }
        else if( i > 0 && i < (unsigned)(nbCols - 1) ) {
            // Bord Nord -> Pas de voisin Nord -> Nord == 0
            motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
            if( motifToTest != 0){
                ++nbConflicts;
            }

            // Vérif Sud
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            nbConflicts += verifNeighboor(i+nbCols,2, motifToTest);
            // Vérif Est
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            nbConflicts += verifNeighboor(i+1, 1,motifToTest);

        }
        else if( i > (unsigned)(nbRows * (nbCols - 1) ) && i < (unsigned)((nbRows * nbCols) -1) ){
            // Bord Sud -> Pas de voisin Sud -> Sud == 0
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }
            // Vérif Est
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            nbConflicts += verifNeighboor(i+1, 1,motifToTest);

        }
        else if( (unsigned)(i % nbCols) == 0 ){ // Rajoutez contrainte > < sur i ?
            // Bord Ouest -> Pas de voisin Ouest -> Ouest ==0
            motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }
            // Vérif Sud
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            nbConflicts += verifNeighboor(i+nbCols,2, motifToTest);
            // Vérif Est
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            nbConflicts += verifNeighboor(i+1, 1,motifToTest);

        }
        else if( (unsigned)(i % nbCols ) == (unsigned)(nbCols - 1) ){ // Rajoutez contrainte > < sur i ?
            // Bord Est -> Pas de voisins Est -> Est == 0
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            if( motifToTest != 0 ){
                ++nbConflicts;

            }
            // Vérif Sud
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            nbConflicts += verifNeighboor(i+nbCols,2, motifToTest);
        }
        else{
            // Vérif Sud
            motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
            nbConflicts += verifNeighboor(i+nbCols,2, motifToTest);
            // Vérif Est
            motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
            nbConflicts += verifNeighboor(i+1, 1,motifToTest);

        }

    }

}

/**
 * @brief Configuration::initRandomConfig
 * Testée et validée
 */
void Configuration::initRandomConfig(){
    // On initialise des tableaux d'indices que l'on va ensuite mélanger
    // afin de placer aléatoirement coins, bords et pièces internes
    int nbBords = 2*(nbRows+nbCols-4);
    int nbInternes = nbRows * nbCols - 2*(nbRows + nbCols-2);

    vector<int> coins;
    vector<int> bords;
    vector<int> internes;
    coins.push_back(0);
    coins.push_back(1);
    coins.push_back(2);
    coins.push_back(3);

    for(int i = 0; i < nbBords; ++i){
        bords.push_back(4+i);
    }

    for(int i= 0; i < nbInternes; ++i){
        internes.push_back(2*(nbRows + nbCols-2) + i);
    }

    size_t seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(bords.begin(),bords.end(),std::default_random_engine(seed));
    std::shuffle(coins.begin(),coins.end(),std::default_random_engine(seed));
    std::shuffle(internes.begin(),internes.end(),std::default_random_engine(seed));

    int placedCorner = 0;
    int placedBord = 0;
    int placedIntern = 0;
    // Boucle de remplissage de vectPos
    for(int i= 0; i < nbRows*nbCols; ++i){
        pair<int,int> pos;

        pos.second = 0;
        if(i == 0 ){
            pos.first = coins[placedCorner];
            ++placedCorner;
            // Vérification rotation
            while( !(vectPieces.at(pos.first).get_motif(1,pos.second) == 0 &&
                   vectPieces.at(pos.first).get_motif(2,pos.second) == 0)   ){
                ++pos.second;
            }

            // Permutations
            permut.push_back(pair<int,int>(i,nbCols-1));
            permut.push_back(pair<int,int>(i, (nbRows *(nbCols-1))));
            permut.push_back(pair<int,int>(i,nbRows*nbCols-1));
        }
        else if(i == (nbCols-1) ){
            pos.first = coins[placedCorner];
            ++placedCorner;
            // Vérification rotation
            while( !(vectPieces.at(pos.first).get_motif(2,pos.second) == 0 &&
                   vectPieces.at(pos.first).get_motif(3,pos.second) == 0)   ){
                ++pos.second;
            }

            // Permutations
            permut.push_back(pair<int,int>(i, (nbRows *(nbCols-1))));
            permut.push_back(pair<int,int>(i,nbRows*nbCols-1));
        }
        else if(i == (nbRows * (nbCols-1)) ){
            pos.first = coins[placedCorner];
            ++placedCorner;
            // Vérification rotation
            while( !(vectPieces.at(pos.first).get_motif(0,pos.second) == 0 &&
                   vectPieces.at(pos.first).get_motif(1,pos.second) == 0)   ){
                ++pos.second;
            }

            // Permutations
            permut.push_back(pair<int,int>(i,nbRows*nbCols-1));
        }
        else if(i == ((nbRows * nbCols) -1 )){
            pos.first = coins[placedCorner];
            ++placedCorner;
            // Vérification rotation
            while( !(vectPieces.at(pos.first).get_motif(0,pos.second) == 0 &&
                   vectPieces.at(pos.first).get_motif(3,pos.second) == 0)   ){
                ++pos.second;
            }

        }
        else if(( i > 0 && i < (nbCols - 1) ) ){
            pos.first = bords[placedBord];
            ++placedBord;
            // Vérif rotation bord nord
            while( vectPieces.at(pos.first).get_motif(2,pos.second) != 0){
                ++pos.second;
            }

            // Permutations
            for(int j = i + 1; j < nbCols*nbRows; ++j){
                if(  j < nbCols-1)
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == 0 && j != (nbRows *(nbCols-1)))
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == (nbCols-1) &&  j != (nbCols-1) && j != (nbCols*nbRows -1))
                    permut.push_back(pair<int,int>(i,j));
                else if( j > (nbRows*(nbCols-1)) && j < (nbRows*nbCols -1))
                    permut.push_back(pair<int,int>(i,j));
            }
        }
        else if( ( i > (nbRows * (nbCols - 1) ) && i < ((nbRows * nbCols) -1) ) ){
            pos.first = bords[placedBord];
            ++placedBord;
            // Vérif rotation bord Sud
            while( vectPieces.at(pos.first).get_motif(0,pos.second) != 0){
                ++pos.second;
            }
            // Permutations
            for(int j = i + 1; j < nbCols*nbRows; ++j){
                if(  j < nbCols-1)
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == 0 && j != (nbRows *(nbCols-1)))
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == (nbCols-1) &&  j != (nbCols-1) && j != (nbCols*nbRows -1))
                    permut.push_back(pair<int,int>(i,j));
                else if( j > (nbRows*(nbCols-1)) && j < (nbRows*nbCols -1))
                    permut.push_back(pair<int,int>(i,j));
            }

        }
        else if(  (i % nbCols) == 0   ){
            pos.first = bords[placedBord];
            ++placedBord;
            // Vérif rotation bord Ouest
            while( vectPieces.at(pos.first).get_motif(1,pos.second) != 0){
                ++pos.second;
            }

            // Permutations
            for(int j = i + 1; j < nbCols*nbRows; ++j){
                if(  j < nbCols-1)
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == 0 && j != (nbRows *(nbCols-1)))
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == (nbCols-1) &&  j != (nbCols-1) && j != (nbCols*nbRows -1))
                    permut.push_back(pair<int,int>(i,j));
                else if( j > (nbRows*(nbCols-1)) && j < (nbRows*nbCols -1))
                    permut.push_back(pair<int,int>(i,j));
            }
        }
        else if( (i % nbCols ) == (nbCols - 1) ){
            pos.first = bords[placedBord];
            ++placedBord;
            // Vérif rotation bord Est
            while( vectPieces.at(pos.first).get_motif(3,pos.second) != 0){
                ++pos.second;
            }

            // Permutations
            for(int j = i + 1; j < nbCols*nbRows; ++j){
                if(  j < nbCols-1)
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == 0 && j != (nbRows *(nbCols-1)))
                    permut.push_back(pair<int,int>(i,j));
                else if( (j&3) == (nbCols-1) &&  j != (nbCols-1) && j != (nbCols*nbRows -1))
                    permut.push_back(pair<int,int>(i,j));
                else if( j > (nbRows*(nbCols-1)) && j < (nbRows*nbCols -1))
                    permut.push_back(pair<int,int>(i,j));
            }
        }
        else{
            pos.first = internes[placedIntern];
            ++placedIntern;

            // Permutations
            for(int j = i+1; j < nbCols*nbRows; ++j){
                if((j&3) > 0 && (j&3)< (nbCols-1) && j < (nbRows*(nbCols-1)))
                    permut.push_back(pair<int,int>(i,j));
            }

        }

        vectPos.push_back(pos);
    }

    for(unsigned i=0; i < permut.size(); ++i)
        cout << permut.at(i).first<< "," << permut.at(i).second << endl;
}


int Configuration::nbConflictsHere(pair<int,int> p ,int indice){
    int result = 0;
    int motifToTest;
    int idPiece = p.first;

    if( indice == 0){
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        // Pas de voisins Nord et Ouest -> Nord == 0, Ouest == 0
        if( motifToTest != 0 ){
            ++result;

        }

        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        if( motifToTest != 0 ){
            ++result;

        }

        // Vérif Sud
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        result += verifNeighboor(indice+nbCols,2, motifToTest);
        // Vérif Est
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        result += verifNeighboor(indice+1, 1,motifToTest);
    }
    else if( indice == (nbCols-1) ){
        // Pas de voisins Nord et Est -> Nord == 0, Est == 0
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        // Vérif Sud
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        result += verifNeighboor(indice+nbCols,2, motifToTest);
        // Vérif Ouest
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        result += verifNeighboor(indice-1,3, motifToTest);

    }
    else if( indice == (nbRows * (nbCols-1)) ){
        // Pas de voisins Sud et Ouest -> Sud == 0, Ouest == 0
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        if( motifToTest != 0){
            ++result;
        }
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        // Vérif Est
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        result += verifNeighboor(indice+1, 1,motifToTest);
        // Vérif Nord
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        result += verifNeighboor(indice-nbCols,0, motifToTest);
    }
    else if( indice == ((nbRows * nbCols) -1 )){
        // Pas de voisins Sud et Est -> Sud == 0, Est == 0
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        if( motifToTest != 0 ){
            ++result;

        }
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        // Vérif Ouest
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        result += verifNeighboor(indice-1,3, motifToTest);
        // Vérif Nord
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        result += verifNeighboor(indice-nbCols,0, motifToTest);
    }
    else if( ( indice > 0 && indice < (nbCols - 1) ) ){
        // Bord Nord -> Pas de voisin Nord -> Nord == 0
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        if( motifToTest != 0){
            ++result;
        }
        // Vérif Ouest
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        result += verifNeighboor(indice-1,3, motifToTest);
        // Vérif Sud
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        result += verifNeighboor(indice+nbCols,2, motifToTest);
        // Vérif Est
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        result += verifNeighboor(indice+1, 1,motifToTest);

    }
    else if( ( indice > (nbRows * (nbCols - 1) ) && indice < ((nbRows * nbCols) -1) ) ){
        // Bord Sud -> Pas de voisin Sud -> Sud == 0
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        // Vérif Est
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        nbConflicts += verifNeighboor(indice+1, 1,motifToTest);
        // Vérif Nord
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        result += verifNeighboor(indice-nbCols,0, motifToTest);
        // Vérif Ouest
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        result += verifNeighboor(indice-1,3, motifToTest);
    }
    else if( (indice % nbCols) == 0 ){
        // Bord Ouest -> Pas de voisin Ouest -> Ouest ==0
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        // Vérif Nord
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        result += verifNeighboor(indice-nbCols,0, motifToTest);
        // Vérif Sud
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        result += verifNeighboor(indice+nbCols,2, motifToTest);
        // Vérif Est
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        result += verifNeighboor(indice+1, 1,motifToTest);
    }
    else if((indice % nbCols ) == (nbCols - 1) ){
        // Bord Est -> Pas de voisins Est -> Est == 0
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        if( motifToTest != 0 ){
            ++result;
        }
        // Vérif Sud
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        result += verifNeighboor(indice+nbCols,2, motifToTest);
        // Vérif Ouest
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        result += verifNeighboor(indice-1,3, motifToTest);
        // Vérif Nord
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        result += verifNeighboor(indice-nbCols,0, motifToTest);

    }else{
        // Vérif Est
        motifToTest = vectPieces.at(idPiece).get_motif(3,p.second);
        result += verifNeighboor(indice+1, 1,motifToTest);
        // Vérif Sud
        motifToTest = vectPieces.at(idPiece).get_motif(0,p.second);
        result += verifNeighboor(indice+nbCols,2, motifToTest);
        // Vérif Ouest
        motifToTest = vectPieces.at(idPiece).get_motif(1,p.second);
        result += verifNeighboor(indice-1,3, motifToTest);
        // Vérif Nord
        motifToTest = vectPieces.at(idPiece).get_motif(2,p.second);
        result += verifNeighboor(indice-nbCols,0, motifToTest);

    }

    return result;
}


void Configuration::evaluate_local( pair<int, int> p){

    // p représente une permutation.
    // En premier lieu, on vérifie si les pieces sont voisines via
    // p.second - p.first
    int gap = p.second - p.first;

    // r[i] = (eval, (rot1, rot2) ) evaluation de la permutation
    // avec la rotation rot1 pour la piece 1 et rot2 pour la piece 2
//    vector< int,pair< int, int> > r;

    /*
     * On doit vérifier quel type de pièce est en permutation
     * car le traitement est différent :
     *  - bord ou coin : on ne peut pas changer les rotations
     *  - internes : on doit tester les différentes rotations
     */
    /*
    if((p.first &3) == 0 || (p.first & 3) == (nbCols-1) ||
        (p.first < nbCols) || p.first >= nbRows*(nbCols-1)){


    }
    // Traitement de cases voisines
    if( gap == 1 || gap == nbCols){

    // Traitement de cases non voisines
    }else{
        // Récupération des valeurs locales du nb de conflits
        int conflitP1 = nbConflictsHere(vectPos.at(p.first), p.first);
        int conflitP2 = nbConflictsHere(vectPos.at(p.second), p.second);

        int total = conflitP1 + conflitP2;

        int amelioration;
        // Test des différentes rotations avec la permutation
        for(int i = 0; i < MAX_CARD ; ++i){
            int tmp1, tmp2;
            pair<int,int> t;

            t.first = vectPos.at(p.second).first;
            t.second = vectPos.at(p.second).second + i&3;
            tmp1 = nbConflictsHere(t,p.first );

            r.push_back(tmp1-conflitP1, pair<int,int>(vectPos.at(p.second).second + i&3));

            t.first = vectPos.at(p.first).first;
            t.second = vectPos.at(p.first).second+i&3;
            tmp2 = nbConflictsHere(t,p.second);


        }

    }
*/
}
