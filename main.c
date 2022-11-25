#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Definindo booleanos e quantidade de players
#define TRUE 1
#define FALSE 0
#define PLAYERS 10

// Definindo a struct do jogador
struct dados_jogador {
  char nome[25];
  int vitoria, derrota, empate;
};

// Definindo vari�veis globais
struct dados_jogador jogador[PLAYERS];
char tabuleiro[3][3];
char posicaoSigla[9][3] = {"ES", "CS", "DS", "EM", "CM", "DM", "EI", "CI", "DI"};
int id = -1;

// Registrando Fun��es Criadas ap�s o MAIN
void limpar_tela();
void ordenarJogadores();
void exibirTabela();
void exibirJogoDaVelha();
void aguardar(float tempoEmSegundos);
int validarSimbolo(char caracter);
int validarPosicao(char posicao[5]);

int main() {
  // Definindo a localiza��o do idioma
   setlocale(LC_ALL, "Portuguese_Brazil");

  // Declarando vari�veis locais do MAIN
  int jogando, jogadorUm, jogadorDois, option, validar, aux;
  char simboloJogando, simboloJogadorUm, simboloJogadorDois, optionChar, posicao[5];

  // Definindo semi loop para o jogo
  do {
    // Loop de valida��o do input
    do {
      // Menu principal do jogo
      printf("1 - Iniciar um novo jogo\n");
      printf("2 - Ver placar\n");
      printf("3 - Sair\n");
      printf("\nOp��o: ");
      validar = scanf("%d", &option);
      fflush(stdin);
      limpar_tela();
      // Verificando se o que foi digitado e um n�mero
    } while (validar != TRUE);

    // Definindo a funcionalidade das op��es do menu principal
    switch (option) {

      case 1:
        // Incrementa sempre que iniciar um novo jogo para cadastrar um novo jogador
          id += 1;
          if (id < PLAYERS) {
            for (int i = 0; i < 2; i++) {
              if (i == 0)
                jogadorUm = id;
              else
                jogadorDois = id;
              printf("Informe o nome dos jogadores:\n");
              printf("%d� Jogador: ", i + 1);
              fgets(jogador[id].nome, 25, stdin);
              fflush(stdin);

              // Remove a quebra de linha da string
              jogador[id].nome[strlen(jogador[id].nome) - 1] = '\0';

              // Transformar o nome em uppercase
              aux = strlen(jogador[id].nome);
              for (int j = 0; j < aux; j++)
                jogador[id].nome[j] = toupper(jogador[id].nome[j]);

              // Inicializa WIN, LOSE e DRAW em zero
              jogador[id].vitoria = 0;
              jogador[id].derrota = 0;
              jogador[id].empate = 0;
              limpar_tela();
              if (i == 0)
                id += 1;
            }

            // Escolher quem ser� o primeiro a jogar
            do {
              do {
                printf("Quem ser� o primeiro a jogar?\nDigite 1 para %s e 2 para %s", jogador[jogadorUm].nome, jogador[jogadorDois].nome);
                printf("\nOp��o: ");
                validar = scanf("%d", &option);
                fflush(stdin);
                limpar_tela();
              } while (validar != TRUE);

              validar = FALSE;
              if (option == 1)
                validar = TRUE;
              else if (option == 2) {
                aux = jogadorUm;
                jogadorUm = jogadorDois;
                jogadorDois = aux;
                validar = TRUE;
              } else {
                  printf("Op��o inv�lida!\n");
                  aguardar(3);
                }
            } while (validar != TRUE);

            printf("Primeiro a jogar: %s\nSegundo a jogar: %s\n", jogador[jogadorUm].nome, jogador[jogadorDois].nome);
            system("pause");
            limpar_tela();

            // O primeiro a jogar escolhe qual vai ser: O ou X
            do {
              printf("%s, qual deseja ser? X ou O (digite a letra)\n", jogador[jogadorUm].nome);
              printf("Quero ser: ");
              scanf("%c", &optionChar);
              optionChar = toupper(optionChar);
              fflush(stdin);
              limpar_tela();
            } while (validarSimbolo(optionChar) == FALSE);

            // Atribui��o da escolha ao primeiro jogador e segundo
            if (optionChar == 'X') {
              simboloJogadorUm = 'X';
              simboloJogadorDois = 'O';
            } else {
                simboloJogadorUm = 'O';
                simboloJogadorDois = 'X';
              }

            // Inicializa��o da partida com tabuleiro limpo
            for (int y = 0; y < 3; y++)
              for (int x = 0; x < 3; x++)
                tabuleiro[y][x] = ' ';

            aux = -1;
            do {
              aux += 1;
              if (aux % 2 == 0) {
                jogando = jogadorUm;
                simboloJogando = simboloJogadorUm;
              } else {
                jogando = jogadorDois;
                simboloJogando = simboloJogadorDois;
              }
              if (aux < 9) {
                do {
                  exibirJogoDaVelha();
                  printf("\n");
                  if (tabuleiro[0][0] == ' ')
                    printf("ES - Esquerda Superior\n");
                  if (tabuleiro[0][1] == ' ')
                    printf("CS - Centro Superior\n");
                  if (tabuleiro[0][2] == ' ')
                    printf("DS - Direita Superior\n");
                  if (tabuleiro[1][0] == ' ')
                    printf("EM - Esquerda do Meio\n");
                  if (tabuleiro[1][1] == ' ')
                    printf("CM - Centro do Meio\n");
                  if (tabuleiro[1][2] == ' ')
                    printf("DM - Direita do Meio\n");
                  if (tabuleiro[2][0] == ' ')
                    printf("EI - Esquerda Inferior\n");
                  if (tabuleiro[2][1] == ' ')
                    printf("CI - Centro Inferior\n");
                  if (tabuleiro[2][2] == ' ')
                    printf("DI - Direita Inferior\n");

                  printf("\n%s, Digite a sigla para preencher a posi��o: ", jogador[jogando].nome);
                  fgets(posicao, 5, stdin);
                  fflush(stdin);
                  limpar_tela();
                  // Transformar o input em uppercase
                  for (int i = 0; i < strlen(posicao); i++)
                    posicao[i] = toupper(posicao[i]);
                  // Remove a quebra de linha
                  posicao[strlen(posicao) - 1] = '\0';
                } while (validarPosicao(posicao) != TRUE);
                // Inserindo na posi��o digitada
                int y = 0, x = 0;
                for (int i = 0; i < 9; i++) {
                  if (i == 3 || i == 6 ) {
                    y += 1;
                    x = 0;
                  }
                  if (strcmp(posicao, posicaoSigla[i]) == 0 && tabuleiro[y][x] == ' ')
                    tabuleiro[y][x] = simboloJogando;
                  x += 1;
                }
              }
            } while (aux < 9);

            if (aux == 9) {
              jogador[jogadorUm].empate += 1;
              jogador[jogadorDois].empate += 1;
              exibirJogoDaVelha();
              printf("\n\tEMPATE!");
              aguardar(3);
              system("pause");
              limpar_tela();
            }

          } else {
              id = PLAYERS - 1;
              printf("Limite m�ximo de cadastro atingido!\n");
              aguardar(3);
              limpar_tela();
            }
        limpar_tela();
        break;

      case 2:
        // Condional pra caso nao tenha nenhum jogador cadastrado
        if (id < 0) {
          printf("NENHUM PLACAR DISPON�VEL!\n\n");
          aguardar(3);
        } else {
            exibirTabela();
            printf("\n");
            aguardar(3);
            printf("\n");
            system("pause");
          }
        limpar_tela();
        break;

      case 3:
        limpar_tela();
        break;

      default:
        printf("Op��o Inv�lida!\n");
        aguardar(3);
        limpar_tela();
        break;
    }
  } while (option != 3);

  return 0;
}

// Fun��o para limpar tela no Win ou Linux
void limpar_tela() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif // _WIN32
}

// Fun��o para Aguardar um tempo
void aguardar(float tempoEmSegundos) {
  tempoEmSegundos /= 5;
  printf("\nAguarde");
  for (int i = 0; i < 5; i++) {
    Sleep(tempoEmSegundos * 1000);
    printf(" .");
  }
}

// Fun��o para validar entrada do X ou O
int validarSimbolo(char caracter) {
  if (caracter == 'X' || caracter == 'O')
    return 1;
  else
    return 0;
}

// Fun��o para validar preenchimento de posi��o
int validarPosicao(char posicao[5]) {
  int y = 0, x = 0;
  for (int i = 0; i < 9; i++) {
    if (i == 3 || i == 6 ) {
      y += 1;
      x = 0;
    }
    if (((strcmp(posicao, posicaoSigla[i]) == 0) && (tabuleiro[y][x] == ' ')) == TRUE)
      return 1;
    x += 1;
    if (i == 9)
      return 0;
  }
}

// Fun��o para exibir o tabuleiro do jogo da velha
void exibirJogoDaVelha() {
  printf("\t\tJOGO DA VELHA\n\n");
  printf("\t\t %c | %c | %c \n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
  printf("\t\t-----------\n");
  printf("\t\t %c | %c | %c \n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
  printf("\t\t-----------\n");
  printf("\t\t %c | %c | %c \n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
}

// Fun��o para exibir a tabela do placar de todos jogadores registrados
void exibirTabela() {
  // Declara��o de variaveis locais da fun��o
  float porcentagemWin[PLAYERS], auxFloat;
  int ordemJogador[PLAYERS], aux;

  // Armazenar os dados de compara��o e organiza��o dos jogadores
  for (int i = 0; i <= id; i++) {
    ordemJogador[i] = (int) i;
    // Calcular a porcentagem de WIN em compara��o a LOSE e DRAW
    porcentagemWin[i] = (float) jogador[i].vitoria * 100 / (jogador[i].vitoria + jogador[i].derrota + jogador[i].empate);
  }

  // Ordena��o do melhor para o pior jogador
  for (int i = 0; i <= id; i++) {
    for (int j = i; j <= id; j++) {
      if (porcentagemWin[i] < porcentagemWin[j]) {
        auxFloat = porcentagemWin[i];
        porcentagemWin[i] = porcentagemWin[j];
        porcentagemWin[j] = auxFloat;

        aux = ordemJogador[i];
        ordemJogador[i] = ordemJogador[j];
        ordemJogador[j] = aux;
      }
    }
  }

  char indiceString[4];
  int difCaracteres = 0;
  // Inicia a Exibi��o da Tabela
  printf("==================================================================================\n");
  printf("||   Posi��o   ||            Nome            ||   Win   ||   Lose   ||   Draw   ||\n");
  printf("==================================================================================");
  for (int i = 0; i <= id; i++) {
    // Exibe a coluna POSI��O
    sprintf(indiceString, "%d", i + 1);
    if (strlen(indiceString) == 1)
      printf("\n||      %d�     ||", i+1);
    else if (strlen(indiceString) == 2)
      printf("\n||     %d�     ||", i+1);

    // Armazena a diferen�a de caracteres entre a string e a coluna NOME
    difCaracteres = 28 - strlen(jogador[ordemJogador[i]].nome);

    // Exibe a coluna NOME
    if (difCaracteres % 2 != 0) {
      difCaracteres /= 2;
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < difCaracteres + j; k++)
          printf(" ");
        if (j == 0)
          printf("%s", jogador[ordemJogador[i]].nome);
      }
      printf("||");
    } else {
        difCaracteres /= 2;
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < difCaracteres; k++)
            printf(" ");
          if (j == 0)
            printf("%s", jogador[ordemJogador[i]].nome);
        }
        printf("||");
      }

    char resultado[7];
    // Exibe a coluna WIN
    sprintf(resultado, "%d", jogador[ordemJogador[i]].vitoria);
    if (strlen(resultado) == 1)
      printf("    %d    ||", jogador[ordemJogador[i]].vitoria);
    else if (strlen(resultado) == 2)
      printf("   %d    ||", jogador[ordemJogador[i]].vitoria);

    // Exibe a coluna LOSE
    sprintf(resultado, "%d", jogador[ordemJogador[i]].derrota);
    if (strlen(resultado) == 1)
      printf("     %d    ||", jogador[ordemJogador[i]].derrota);
    else if (strlen(resultado) == 2)
      printf("    %d   ||", jogador[ordemJogador[i]].derrota);

    // Exibe a coluna DRAW
    sprintf(resultado, "%d", jogador[ordemJogador[i]].empate);
    if (strlen(resultado) == 1)
      printf("     %d    ||", jogador[ordemJogador[i]].empate);
    else if (strlen(resultado) == 2)
      printf("    %d   ||", jogador[ordemJogador[i]].empate);
  }
  printf("\n==================================================================================");
}
