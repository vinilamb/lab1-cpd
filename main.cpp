#include <iostream>
#include <fstream>

#include "include/Dados.h"

void geraEstatisticas();

int main()
{
//    geraEstatisticas();
//    return 0;
    std::cout << "LAB 1" << std::endl;

    Dados dados;
    Timer timer;
    Estatisticas est;
    float tempo;

    std::vector<int> tamanhosTeste = {1000, 5000, 25000, 100000};
    for(int i = 0; i < tamanhosTeste.size(); i++){
        int tamanho = tamanhosTeste[i];

        dados.geraVetorAleatorio(tamanho,1,tamanho);
//        dados.geraVetorOrdenado(tamanho,1,tamanho);
//        dados.geraVetorQuaseOrdenado(tamanho,1,tamanho);
//        dados.geraVetorReverso(tamanho,1,tamanho);

        std::cout << "N " << tamanho;
        std::cout.flush();

        timer.iniciaContagem();

//        est = dados.ordenaComBubbleSort();
        est = dados.ordenaComInsertionSort();
//        est = dados.ordenaComShellSort(SHELL59);
//        est = dados.ordenaComShellSort(KNUTH71);
//        est = dados.ordenaComShellSort(TOKUDA92);
//        est = dados.ordenaComShellSort(CIURA01);

        tempo = timer.finalizaContagem();

        std::cout << " tempo " << tempo << " trocas " << est.trocas << " comparacoes " << est.comparacoes << std::endl;

        bool estaOrdenado = dados.checaSeRegistrosOrdenados();
        bool ordenacaoEstavel = dados.checaSeOrdenacaoFoiEstavel();
        std::cout << (estaOrdenado ? "Vetor ordenado" : "Vetor NAO ordenado") << " - "
                  << (ordenacaoEstavel ? "Ordenacao foi estavel" : "Ordenacao NAO foi estavel") << std::endl;
    }

    return 0;
}

// Gera estatisticas para todas as configuriações necessárias e salva o resultado em uma linha de um arquivo
void geraEstatisticas() {
    std::vector<int> tamanhosDeTeste = {1000, 5000, 25000, 100000};
    std::vector<std::string> tipoVetor = {"RAND", "SEMI", "ORD", "REV"};
    std::vector<std::string> listaDeAlgoritmos = {"INS", "BUBBLE", "SS_SHELL59", "SS_KNUTH71", "SS_TOKUDA92", "SS_CIURA01"};

    std::cout << "MEDINDO ALGORITMOS" << std::endl;

    std::ofstream file ("medidas.txt");
    if (!file.is_open()) {
        std::cout << "Não foi possível abrir arquivo." << std::endl;
    }

    for (auto n : tamanhosDeTeste) {
        for (auto tipo: tipoVetor) {
            for (auto algo : listaDeAlgoritmos) {
                    Dados dados;
                    Timer timer;
                    Estatisticas est;
                    float tempo;

                    if (tipo == "RAND") {
                        dados.geraVetorAleatorio(n,1,n);
                    } else if (tipo == "SEMI") {
                        dados.geraVetorQuaseOrdenado(n,1,n);
                    } else if (tipo == "ORD") {
                        dados.geraVetorOrdenado(n,1,n);
                    } else if (tipo == "REV") {
                        dados.geraVetorReverso(n,1,n);
                    }

                    if (algo == "INS") {
                        timer.iniciaContagem();
                        est = dados.ordenaComInsertionSort();
                    } else if (algo == "BUBBLE") {
                        timer.iniciaContagem();
                        est = dados.ordenaComBubbleSort();
                    } else if (algo == "SS_SHELL59") {
                        timer.iniciaContagem();
                        est = dados.ordenaComShellSort(SHELL59);
                    } else if (algo == "SS_KNUTH71") {
                        timer.iniciaContagem();
                        est = dados.ordenaComShellSort(KNUTH71);
                    } else if (algo == "SS_TOKUDA92") {
                        timer.iniciaContagem();
                        est = dados.ordenaComShellSort(TOKUDA92);
                    } else if (algo == "SS_CIURA01") {
                        timer.iniciaContagem();
                        est = dados.ordenaComShellSort(CIURA01);
                    }

                    tempo = timer.finalizaContagem();

                    std::cout << n << " " << tipo << " " << algo << " " << tempo << " " << est.comparacoes << " " << est.trocas << " " << std::endl;
                    file << n << " " << tipo << " " << algo << " " << tempo << " " << est.comparacoes << " " << est.trocas << " " << std::endl;

            }
        }
    }

    file.close();
}
