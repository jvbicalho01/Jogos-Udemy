#include <time.h>
#include <iostream>
#include <string>

using namespace std;

// definicao dos cabecalhos das funcoes
void menuInicial();

void limpaTela() {
  system("CLS");
}

void iniciaTabuleiro(char tabuleiro[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      tabuleiro[i][j] = '-';
    }
  }
}

void exibeTabuleiro(char tabuleiro[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << tabuleiro[i][j];
    }
    cout << endl;
  }

  cout << endl;
}

// retorna o vencedor: 1 = jogador 'x', 2 = jogador 'o'
int confereTabuleiro(char tabuleiro[3][3]) {
  // confere se o jogo acabou atraves das linhas
  for (int i = 0; i < 3; i++) {
    if (tabuleiro[i][0] == 'x' && tabuleiro[i][0] == tabuleiro[i][1] &&
        tabuleiro[i][1] == tabuleiro[i][2]) {
      return 1;

    } else if (tabuleiro[i][0] == 'o' && tabuleiro[i][0] == tabuleiro[i][1] &&
               tabuleiro[i][1] == tabuleiro[i][2]) {
      return 2;
    }
  }

  // confere se o jogo acabou atraves das colunas
  for (int i = 0; i < 3; i++) {
    if (tabuleiro[0][i] == 'x' && tabuleiro[0][i] == tabuleiro[1][i] &&
        tabuleiro[1][i] == tabuleiro[2][i]) {
      return 1;

    } else if (tabuleiro[0][i] == 'o' && tabuleiro[0][i] == tabuleiro[1][i] &&
               tabuleiro[1][i] == tabuleiro[2][i]) {
      return 2;
    }
  }

  // confere se o jogo acabou atraves da diagonal principal
  if (tabuleiro[0][0] != '-' && tabuleiro[0][0] == tabuleiro[1][1] &&
      tabuleiro[1][1] == tabuleiro[2][2]) {
    if (tabuleiro[0][0] == 'x') {
      return 1;
    } else if (tabuleiro[0][0] == 'o') {
      return 2;
    }
  }

  // confere se o jogo acabou atraves da diagonal invertida
  if (tabuleiro[0][2] != '-' && tabuleiro[0][2] == tabuleiro[1][1] &&
      tabuleiro[1][1] == tabuleiro[2][0]) {
    if (tabuleiro[0][2] == 'x') {
      return 1;
    } else if (tabuleiro[0][2] == 'o') {
      return 2;
    }
  }

  return 0;
}

void exibeInstrucoes() {
  cout << "Mapa de Posicoes: " << endl;

  cout << "7 | 8 | 9" << endl << "4 | 5 | 6" << endl << "1 | 2 | 3" << endl;
}

void jogo(string nome_jogador_um,
          string nome_jogador_dois,
          int pontuacao_jogador_um,
          int pontuacao_jogador_dois) {
  // nomes dos jogadores
  string nome_jogador_atual;

  // tabuleiro do jogo
  char tabuleiro[3][3];

  // posicoes que o jogador escolhe para fazer a jogada
  int linha_jogada;
  int coluna_jogada;
  int posicao_jogada;

  // 0 = sem jogo, 1 = em jogo
  int estado_jogo = 1;

  // indica qual jogador esta jogando: 1 = x, 2 = o
  int turno_jogador = 1;

  // numero de rodadas jogadas
  int rodada = 0;

  // opcao de reinicio
  int opcao = 0;

  // verifica se o jogador colocou um marcador no tabuleiro
  bool posicionou_jogada;

  // matriz de posicoes possiveis
  int posicoes[9][2] = {{2, 0}, {2, 1}, {2, 2}, {1, 0}, {1, 1},
                        {1, 2}, {0, 0}, {0, 1}, {0, 2}};

  // populando o tabuleiro com valores nulos
  iniciaTabuleiro(tabuleiro);

  while (rodada < 9 && estado_jogo == 1) {
    limpaTela();

    cout << "Pontuacao :" << endl;
    cout << nome_jogador_um << " " << pontuacao_jogador_um << " X "
         << pontuacao_jogador_dois << " " << nome_jogador_dois << endl;

    cout << "Rodada: " << rodada << endl;

    // exibindo o tabuleiro
    exibeTabuleiro(tabuleiro);

    // exibe qual numero corresponde a cada posicao
    exibeInstrucoes();

    // atualiza o nome do jogador atual
    if (turno_jogador == 1) {
      nome_jogador_atual = nome_jogador_um;
    } else {
      nome_jogador_atual = nome_jogador_dois;
    }

    posicionou_jogada = false;

    while (posicionou_jogada == false) {
      // le a jogada
      cout << nome_jogador_atual
           << ", digite uma posicao conforme o mapa acima: " << endl;
      cin >> posicao_jogada;

      // passa a linha e coluna de acordo com a matriz de posicoes exibida no
      // mapa
      linha_jogada = posicoes[posicao_jogada - 1][0];
      coluna_jogada = posicoes[posicao_jogada - 1][1];

      // verifica se a posicao eh vazia
      if (tabuleiro[linha_jogada][coluna_jogada] == '-') {
        // conseguiu posicionar um marcador
        posicionou_jogada = true;

        // verifica de quem e a vez de jogar
        if (turno_jogador == 1) {
          tabuleiro[linha_jogada][coluna_jogada] = 'x';
          turno_jogador = 2;
        } else {
          tabuleiro[linha_jogada][coluna_jogada] = 'o';
          turno_jogador = 1;
        }
      }
    }

    // verifica todas as possibilidades de vitoria e retorna quem venceu
    if (confereTabuleiro(tabuleiro) == 1) {
      cout << "Parabens " << nome_jogador_um << ", voce venceu!!" << endl;
      pontuacao_jogador_um++;
      estado_jogo = 0;
    } else if (confereTabuleiro(tabuleiro) == 2) {
      cout << "Parabens " << nome_jogador_dois << ", voce venceu!!" << endl;
      pontuacao_jogador_dois++;
      estado_jogo = 0;
    }

    rodada++;
  }

  exibeTabuleiro(tabuleiro);

  cout << "Rodada em que terminou o jogo: " << rodada << endl;

  cout << "Fim de jogo!" << endl;

  cout << "O que deseja fazer?" << endl;
  cout << "1 - Continuar jogando" << endl;
  cout << "2 - Menu inicial" << endl;
  cout << "3 - Sair" << endl;
  cin >> opcao;

  if (opcao == 1) {
    jogo(nome_jogador_um, nome_jogador_dois, pontuacao_jogador_um,
         pontuacao_jogador_dois);
  } else if (opcao == 2) {
    menuInicial();
  }
}

void menuInicial() {
  // opcao escolhida pelo usuario
  int opcao = 0;

  // nomes dos jogadores
  string nome_jogador_um, nome_jogador_dois;

  // enquanto o jogador nao digita uma opcao valida
  // motra o menu novamente
  while (opcao < 1 || opcao > 3) {
    limpaTela();

    // faz algo de acordo com a opcao escolhida
    cout << "Bem-vindo ao jogo da velha!" << endl;
    cout << "1 - Jogar" << endl;
    cout << "2 - Sobre" << endl;
    cout << "3 - Sair" << endl;
    cout << "Escolha uma opcao e aperte ENTER!" << endl;

    // faz a leitura da opcao
    cin >> opcao;

    switch (opcao) {
      case 1:

        // inicia o jogo
        cout << "Digite o nome do jogador 1 e aperte ENTER: " << endl;
        cin >> nome_jogador_um;
        cout << "Digite o nome do jogador 2 e aperte ENTER: " << endl;
        cin >> nome_jogador_dois;
        jogo(nome_jogador_um, nome_jogador_dois, 0, 0);
        break;

      case 2:

        // mostra informacoes do jogo
        limpaTela();
        cout << "Jogo desenvolvido por Joao Vitor Bicalho da Silva em 2022 "
                "usando como base um curso da Udemy de C e C++"
             << endl;
        cout << "1 - Voltar" << endl;
        cout << "2 - Sair" << endl;
        cin >> opcao;
        if (opcao == 1) {
          menuInicial();
        }

        break;

      case 3:

        // sai do jogo
        cout << "Ate mais!";
        break;
    }
  }
}

int main() {
  menuInicial();

  return 0;
}