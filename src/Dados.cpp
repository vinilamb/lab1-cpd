#include "../include/Dados.h"

#include <iostream>     // std::cout
#include <algorithm>    // std::sort


//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

Dados::Dados()
{
    //construtor

    // Inicializa gerador de numeros aleatorios (da biblioteca random)
    std::random_device r;
    gerador = new std::default_random_engine(r());

}

Dados::~Dados()
{
    // destrutor

    delete(gerador);
}

////////////////////////////
/// METODOS DE ORDENACAO ///
////////////////////////////

Estatisticas Dados::ordenaComBubbleSort()
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    // TODO: implementar codigo do bubbleSort

    int m = registros.size() - 1, k = 0;
    bool troca;
    do {
      troca = false;
      for (long long i = 0; i < m; i++) {

        est.comparacoes++;
        if (registros[i] > registros[i+1]) {
            Registro temp = registros[i];
            registros[i] = registros[i+1];
            registros[i+1] = temp;

            troca = true;
            k = i;
            est.trocas++;
        }
      }
      m = k;
    } while(troca);

    return est;
}

Estatisticas Dados::ordenaComInsertionSort()
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    // TODO: implementar codigo do insertionSort
    for (long long j = 1; j < registros.size(); j++) {
        Registro chave = registros[j];
        long long i = j - 1;
        while (i >= 0) {
            est.comparacoes++;
            if (registros[i] > chave) {
                registros[i + 1] = registros[i];
                i--;
                est.trocas++;
            } else {
                break;
            }
        }
        registros[i + 1] = chave;
    }
    return est;

}

Estatisticas Dados::ordenaComShellSort(TipoShellSort tipo)
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    int n = registros.size();

    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n,tipo);

//    for(int i=0;i<sequenciaDeGaps.size();i++)
//        std::cout << sequenciaDeGaps[i] << ' ';

    // TODO: implementar codigo do shellSort
    for (int p = sequenciaDeGaps.size() - 1; p >= 0; p--) {
        int h = sequenciaDeGaps[p];
        for (int inicio = 0; inicio < h; inicio++) {
            insercaoDiretaDoShellSort(inicio, h, est);
        }
    }

    return est;
}

void Dados::insercaoDiretaDoShellSort(int inicio, int incremento, Estatisticas& est) {
    for (long long j = inicio + incremento; j < registros.size(); j += incremento) {
        Registro chave = registros[j];

        long long i = j - incremento;

        while (i >= 0) {
            est.comparacoes++;
            if (registros[i] > chave) {
                registros[i + incremento] = registros[i];
                i = i - incremento;
                est.trocas++;
            } else {
                break;
            }
        }

        est.trocas++;
        registros[i + incremento] = chave;
    }
}

bool Dados::checaSeOrdenacaoFoiEstavel()
{
    bool ehEstavel=true;

    // TODO: checar se elementos com chave igual mantem a ordem inicial analisando seus dados satelites
    for (long long i = 0; i < registros.size() - 1; i++) {
        if ((registros[i] == registros[i + 1]) && (registros[i].getDadoSatelite() > registros[i + 1].getDadoSatelite()))
        {
            ehEstavel = false;
            break;
        }
    }

    return ehEstavel;
}

bool Dados::checaSeRegistrosOrdenados()
{
    for(unsigned int i=0; i<registros.size() - 1; i++)
        if(registros[i]>registros[i+1])
            return false;

    return true;
}

//////////////////////////
/// METODOS AUXILIARES ///
//////////////////////////

std::vector<int> Dados::geraSequenciaDeGaps(int tamanho, TipoShellSort tipo)
{
    std::vector<int> v;

    int e=1;
    v.push_back(e);

    if(tipo==SHELL59){         // (Shell,1959) - sequencia 1, 2, 4, 8, 16, 32, ...
        while(e<tamanho){
            e *= 2;
            v.push_back(e);
        }

    }else if(tipo==KNUTH71){   // (Knuth,1971) - sequencia 1, 4, 13, 40, 121, 364, ...
        while(e<tamanho){
            e = e*3+1;
            v.push_back(e);
        }

    }else if(tipo==TOKUDA92){  // (Tokuda,1992) - sequencia 1, 4, 9, 20, 46, 103, ...
        int i=1;
        while((e=ceil((9.0 * pow(9.0,i)/pow(4.0,i) - 4.0)/5.0)) < tamanho){
            v.push_back(e);
            i++;
        }
    }else if(tipo==CIURA01){  // (Ciura,2001) - sequencia 1, 4, 10, 23, 57, 132, 301, 701 - daqui em diante nao tem prova de otimalidade
        int seq[8]={1,4,10,23,57,132,301,701};

        int i=1;
        while(i<8 && seq[i]<tamanho){
            v.push_back(seq[i]);
            i++;
        }

        int e=701;
        while((e=floor(2.25*(float)e))<tamanho)
            v.push_back(e);
    }

    return v;
}

void Dados::inicializaRegistrosComVetor(const std::vector<int>& vetor_auxiliar)
{
    // Reseta vetor de registros
    registros.clear();

    // Reserva novo tamanho do vetor de registros
    unsigned int tamanho = vetor_auxiliar.size();
    registros.reserve(tamanho);

    // Copia valores para vetor de registros
    for(unsigned int i=0; i<tamanho; i++){
        int c = vetor_auxiliar[i];
        int s = i+1;

        registros.push_back(Registro(c,s));
    }
}

void Dados::geraVetorAleatorio(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Seta distribuicao de chaves como valor aleatorio uniforme entre 'minimo_possivel' e 'maximo_possivel'
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);

    // Cria vetor auxiliar e preenche com valores aleatorios
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++){
        vetor_auxiliar[i] = chave_aleatoria(*gerador);
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorQuaseOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Da uma leve embaralhada, dentro de uma distancia 'range'
    int range=tamanho/50;
    if(range<5)
        range=5;
    std::uniform_int_distribution<int> gap_para_troca(0,range);

    for(unsigned int i=0; i<tamanho; i++){
        int k = gap_para_troca(*gerador);
        if(k%5==0 && i+k<tamanho){
            int temp = vetor_auxiliar[i+k];
            vetor_auxiliar[i+k] = vetor_auxiliar[i];
            vetor_auxiliar[i] = temp;
        }
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorReverso(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end(), std::greater<int>());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::imprime_registros()
{
    for(unsigned int i=0; i<registros.size(); i++){
        std::cout << registros[i] << ' ';
    }
    std::cout << std::endl;
}

