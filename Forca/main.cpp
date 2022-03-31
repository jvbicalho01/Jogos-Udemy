#include <time.h>
#include <iostream>
#include <string>

using namespace std;

void limpaTela() {
  system("CLS");
}

string retornaPalavraAleatoria() {
  string palavras[12] = {"abacaxi",       "manga",     "morango",
                         "banana",        "futebol",   "camiseta",
                         "programacao",   "faculdade", "paralelepipedo",
                         "ornintorrinco", "zoologico", "chocolate"};

  // gera numeros aleatorios entre 0 e 12 (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11)
  int indice_aleatorio = rand() % 12;

  return palavras[indice_aleatorio];
}

string retornaPalavraComMascara(string palavra, int tamanho_palavra) {
  int cont = 0;
  string palavra_mascara;

  // coloca uma mascara
  while (cont < tamanho_palavra) {
    palavra_mascara += "_";
    cont++;
  }

  return palavra_mascara;
}

void exibeStatus(string palavra_mascara,
                 int tamanho_palavra,
                 int tentativas_restantes,
                 string letras_arriscadas,
                 string mensagem) {
  cout << mensagem << endl;

  cout << "Palavra: " << palavra_mascara << "(Tamanho: " << tamanho_palavra
       << ")" << endl;

  cout << "Tentativas restante: " << tentativas_restantes << endl;

  // exibe as letras arriscadas
  cout << "Letras arriscadas: ";
  for (int i = 0; i < letras_arriscadas.size(); i++) {
    cout << letras_arriscadas[i] << ", ";
  }

  cout << endl;
}

int jogar(int num_jogadores) {
  // palavra que deve ser adivinhada
  string palavra;

  // confere o numero de jogadores
  // se for 1, gera uma palavra aleatoria
  // se for 2, pede para o usuario digitar uma palavra
  if (num_jogadores == 1) {
    palavra = retornaPalavraAleatoria();
  } else {
    cout << "Digite uma palavra" << endl;
    cin >> palavra;
  }

  int tamanho_palavra = palavra.size();

  // palavra com a resposta escondida
  string palavra_mascara = retornaPalavraComMascara(palavra, tamanho_palavra);

  // numero de tentativas e erros
  int tentativas = 0, max_tentativas = 10;
  // opcoes para reiniciar ou nao o jogo
  int opcao;
  // letra arrsicada pelo usuario
  char letra;
  // armazena as tentativas do jogador
  string letras_arriscadas;
  // feedback para o jogador
  string mensagem = "Bem-vindo ao jogo!";
  // usada na tentativa de arriscar uma palavra
  string palavra_arriscada;
  // auxiliar para saber se a letra ja foi digitada ou nao
  bool letra_repetida = false, acertou_letra = false;

  while (palavra != palavra_mascara && max_tentativas - tentativas > 0) {
    limpaTela();

    // exibe o status atual do jogo
    exibeStatus(palavra_mascara, tamanho_palavra, max_tentativas - tentativas,
                letras_arriscadas, mensagem);

    // le uma tentativa e aumenta as tentativas
    cout << "Digite uma letra: (Ou digite 1 para arriscar a palavra)";
    cin >> letra;
    if (letra == '1') {
      cout << "Arrisque uma palavra: " << endl;
      cin >> palavra_arriscada;

      if (palavra_arriscada == palavra) {
        palavra_mascara = palavra_arriscada;
      } else {
        tentativas = max_tentativas;
      }
    }

    // percorre as letras ja arriscadas
    for (int i = 0; i < tentativas; i++) {
      // se encontrar a letra
      if (letras_arriscadas[i] == letra) {
        mensagem = "Essa letra ja foi digitada!";
        // indica com a variavel booleana
        letra_repetida = true;
      } else {
        letra_repetida = false;
      }
    }

    // se for uma letra nova
    if (letra_repetida == false) {
      // incrementa a letra digitada nas letras ja arriscadas
      letras_arriscadas += tolower(letra);

      // percorre a palavra real
      for (int i = 0; i < tamanho_palavra; i++) {
        // se a palavra existir na palavra escondida
        if (palavra[i] == tolower(letra)) {
          // faz a letra aparecer na palavra "mascarada"

          palavra_mascara[i] = palavra[i];

          acertou_letra = true;
        }
      }

      if (acertou_letra == false) {
        mensagem = "Voce errou uma letra!";
      } else {
        mensagem = "Parabens! Voce acertou uma letra!";
        acertou_letra = false;
      }

      tentativas++;
    }
  }

  if (palavra == palavra_mascara) {
    limpaTela();
    cout << "Parabens!! Voce venceu :)!!" << endl;

    cout << "Deseja jogar novamente?" << endl
         << "1 - Sim" << endl
         << "2 - Nao" << endl;
    cin >> opcao;

    return opcao;

  } else {
    cout << "Que pena! Voce perdeu :(!" << endl;

    cout << "Deseja jogar novamente?" << endl
         << "1 - Sim" << endl
         << "2 - Nao" << endl;
    cin >> opcao;

    return opcao;
  }
}

void menuInicial() {
  // opcao escolhida pelo usuario
  int opcao = 0;

  // enquanto o jogador nao digita uma opcao valida o menu e mostrado novamente
  while (opcao < 1 || opcao > 4) {
    limpaTela();

    cout << "Bem-vindo ao jogo da forca!!" << endl;
    cout << "1 - Jogar sozinho" << endl;
    cout << "2 - Jogar em dupla" << endl;
    cout << "3 - Sobre" << endl;
    cout << "4 - Sair" << endl;

    cout << "Escolha uma opcao e aperte ENTER!" << endl;
    cin >> opcao;

    // realiza algo de acordo com a opcao escolhida
    switch (opcao) {
      // opcao de jogar sozinho, passa 1 jogador como parametro
      case 1:

        if (jogar(1) == 1) {
          menuInicial();
        }
        break;
      // opcao de jogar em dupla, passa 2 jogadores como parametro
      case 2:

        if (jogar(2) == 1) {
          menuInicial();
        }

        break;

      case 3:
        // informacoes do jogo

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

      case 4:
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