#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {

    // argv[1] -> Nome da pasta contendo o arquivo com os tempos de execução.
    // argv[2] -> Quantidade de imagens ou threads usadas (nome do arquivo).
    string infile_path = argv[1] + string(argv[2]);
    string outfile_path = "relatorios/reportAnalyzer/" + string(argv[2]);

    ifstream infile(infile_path);
    ofstream outfile(outfile_path, ios::app);

    if (!infile) {
        cerr << "Não foi possível abrir o arquivo no caminho " << infile_path << endl;
        exit(1);   // Chamada de sistema para parar o programa.
    }

    if (!outfile) {
        cerr << "Não foi possível abrir o arquivo no caminho " << outfile_path << endl;
        exit(1);   // Chamada de sistema para parar o programa.
    }
    
    double aux, sum;
    for(int i = 0; i < 10; i++) {
        infile >> aux;
        sum += aux;
    }

    outfile << argv[1] << " : " << sum/10 << endl;
    
    infile.close();
    outfile.close();

    return 0;
}