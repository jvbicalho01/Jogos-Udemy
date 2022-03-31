#include <time.h>
#include <iostream>
#include <string>

using namespace std;

// cabecalhos de funcoes
void menuInicial();

void limpaTela() {
  system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      tabuleiro[i][j] = 'A';
      mascara[i][j] = '*';
    }
  }
}

void exibeMapa() {
  // Mapa indicador de colunas
  for (int i = 0; i < 10; i++) {
    if (i == 0) {
      cout << "    ";
    }
    cout << i << " ";
  }
  cout << endl;

  for (int i = 0; i < 10; i++) {
    if (i == 0) {
      cout << "    ";
    }
    cout << "| ";
  }
  cout << endl;
}

void exibeTabuleiro(char tabuleiro[10][10],
                    char mascara[10][10],
                    bool mostra_gabarito) {
  char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
  char green[] = {0x1b, '[', '1', ';', '3', '2', 'm', 0};
  char normal[] = {0x1b, '[', '1', ';', '3', '9', 'm', 0};

  // Exibe o tabuleiro
  for (int i = 0; i < 10; i++) {
    cout << i << " -";
    for (int j = 0; j < 10; j++) {
      switch (mascara[i][j]) {
        case 'A':
          cout << blue << " " << mascara[i][j] << normal;
          break;

        case 'P':
          cout << green << " " << mascara[i][j] << normal;
          break;

        default:
          cout << " " << mascara[i][j];
          break;
      }
    }
    cout << endl;
  }

  if (mostra_gabarito == true) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        cout << " " << tabuleiro[i][j];
      }
      cout << endl;
    }
  }
}

void posicionaBarcos(char tabuleiro[10][10]) {
  int quantidade_barcos = 10;
  int quantidade_posicionada = 0;
  int linha, coluna;

  // verifica se posicionou todos os barcos
  while (quantidade_posicionada < quantidade_barcos) {
    // gera numeros aleatorios entre 0 e 10 (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
    linha = rand() % 10;
    coluna = rand() % 10;

    if (tabuleiro[linha][coluna] == 'A') {
      // posiciona 10 barcos aleatoriamente
      // P = barco pequeno
      tabuleiro[linha][coluna] = 'P';
      // aumenta o contador de barcos posicionados
      quantidade_posicionada++;
    }
  }
}

void verificaTiro(char tabuleiro[10][10],
                  int linha_jogada,
                  int coluna_jogada,
                  int* pontos,
                  string* mensagem) {
  // verifica quantos pontos adicionar
  switch (tabuleiro[linha_jogada][coluna_jogada]) {
    case 'P':
      *pontos += 10;
      *mensagem = "Voce acertou um barco pequeno!(10 pontos)";
      tabuleiro[linha_jogada][coluna_jogada] = 'X';
      break;

    case 'A':
      *mensagem = "Voce acertou na agua!";
      break;

    case 'X':
      *mensagem = "Voce desperdicou uma chance! Essa posicao ja foi acertada!";
      break;
  }
}

void jogo(string nome_jogador) {
  // tabuleiro do jogo
  char tabuleiro[10][10];
  // tabuleiro com as respostas escondidas
  char mascara[10][10];

  // posicao escolhida pelo jogador
  int linha_jogada, coluna_jogada;

  // responsavel pela pontuacao do jogador
  int pontos = 0;

  // 1 = jogo acontecendo, 0 = fim de jogo
  int estado_jogo = 1;

  int tentativas = 0, max_tentativas = 20;

  // opcoes de fim de jogo
  int opcao = 0;

  // mensagem de feedback para o jogodor
  string mensagem = "Bem-vindo ao jogo!";

  // preenche o tabuleiro com a letra 'A' que representa um espaco com agua
  iniciaTabuleiro(tabuleiro, mascara);

  // posiciona os barcos aleatoriamente
  posicionaBarcos(tabuleiro);

  while (tentativas < max_tentativas) {
    limpaTela();

    // exibe o mapa de indicacoes
    exibeMapa();

    // exibe o tabuleiro com a "mascara"
    exibeTabuleiro(tabuleiro, mascara, false);

    cout << "Pontuacao: " << pontos << endl;
    cout << "Tentativas restantes: " << max_tentativas - tentativas << endl;
    cout << mensagem << endl;

    // verificacao de dados
    linha_jogada = -1;
    coluna_jogada = -1;

    while ((linha_jogada < 0 || coluna_jogada < 0) ||
           (linha_jogada > 9 || coluna_jogada > 9)) {
      cout << nome_jogador;
      cout << ", digite uma linha: " << endl;
      cin >> linha_jogada;

      cout << nome_jogador;
      cout << ", digite uma coluna: " << endl;
      cin >> coluna_jogada;
    }

    // verifica o que aconteceu
    verificaTiro(tabuleiro, linha_jogada, coluna_jogada, &pontos, &mensagem);

    // revela o que esta no tabuleiro
    mascara[linha_jogada][coluna_jogada] =
        tabuleiro[linha_jogada][coluna_jogada];

    tentativas++;
  }

  cout << "Fim de jogo! O que deseja fazer?" << endl;
  cout << "1 - Jogar novamente" << endl;
  cout << "2 - Voltar para o menu" << endl;
  cout << "3 - Sair" << endl;

  cin >> opcao;

  switch (opcao) {
    case 1:
      jogo(nome_jogador);
      break;

    case 2:
      menuInicial();
      break;

    case 3:
      cout << "Ate mais!";
      break;
  }
}

void menuInicial() {
  // opcao escolhida pelo usuario
  int opcao = 0;

  // nome do usuario
  string nome_jogador;

  // enquanto o jogador nao digita uma opcao valida
  // mostra o menu novamente
  while (opcao < 1 || opcao > 3) {
    limpaTela();

    cout << "Bem-vindo ao jogo de batalha naval!!" << endl;
    cout << "1 - Jogar" << endl;
    cout << "2 - Sobre" << endl;
    cout << "3 - Sair" << endl;

    cout << "Escolha uma opcao e aperte ENTER!" << endl;
    // faz a leitura da opcao
    cin >> opcao;

    // faz algo de acordo com a opcao escolhida
    switch (opcao) {
      case 1:
        // inicia o jogo
        cout << "Qual o seu nome?" << endl;
        cin >> nome_jogador;
        jogo(nome_jogador);
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
        // sair do jogo
        cout << "Ate mais!";
        break;
    }
  }
}

int main() {
  // permite a geracao de numeros aleatorios
  srand((unsigned)time(NULL));

  menuInicial();

  return 0;
}