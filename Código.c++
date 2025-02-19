#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Funcao para contar o numero de colisoes (ataques entre rainhas)
int contarColisoes(const vector<int>& tabuleiro) {
    int colisoes = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = i + 1; j < 8; ++j) {
            if (tabuleiro[i] == tabuleiro[j] || abs(tabuleiro[i] - tabuleiro[j]) == abs(i - j)) {
                ++colisoes;
            }
        }
    }
    return colisoes;
}

// Funcao para gerar um vizinho aleatorio
vector<int> gerarVizinho(const vector<int>& tabuleiro) {
    vector<int> novoTabuleiro = tabuleiro;
    int coluna = rand() % 8;
    novoTabuleiro[coluna] = rand() % 8;
    return novoTabuleiro;
}

// Algoritmo Stochastic Hill Climbing
vector<int> stochasticHillClimbing(int& iteracoes) {
    srand(time(0));

    // Inicializacao do tabuleiro com uma configuracao aleatoria
    vector<int> tabuleiro(8);
    for (int i = 0; i < 8; ++i) {
        tabuleiro[i] = rand() % 8;
    }

    int fitnessAtual = contarColisoes(tabuleiro);
    int movimentosSemMelhoria = 0;
    const int maxMovimentosSemMelhoria = 500;

    // Inicio do contador de iteracoes
    iteracoes = 0;

    while (movimentosSemMelhoria < maxMovimentosSemMelhoria && fitnessAtual > 0) {
        vector<int> vizinho = gerarVizinho(tabuleiro);
        int fitnessVizinho = contarColisoes(vizinho);

        if (fitnessVizinho < fitnessAtual) {
            tabuleiro = vizinho;
            fitnessAtual = fitnessVizinho;
            movimentosSemMelhoria = 0;
        } else {
            ++movimentosSemMelhoria;
        }
        ++iteracoes; // Incrementa o contador de iteracoes
    }

    return tabuleiro;
}

// Funcao para imprimir o tabuleiro
void imprimirTabuleiro(const vector<int>& tabuleiro) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (tabuleiro[j] == i) {
                cout << "1 ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

int main() {

    int iteracoes;
    
    // Inicio do calculo do tempo
    auto inicio = high_resolution_clock::now();
    
    // Execucao do algoritmo
    vector<int> solucao = stochasticHillClimbing(iteracoes);
    
    // Fim do calculo do tempo
    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<microseconds>(fim - inicio).count();
    
    // Exibir o tabuleiro final, numero de colisoes e tempo gasto
    cout << "Tabuleiro final:\n";
    imprimirTabuleiro(solucao);
    cout << "Colisoes: " << contarColisoes(solucao) << endl;
    cout << "Numero de iteracoes: " << iteracoes << endl;
    cout << "Tempo gasto: " << duracao << " microsegundo(s)" << endl;

    return 0;
}
