#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sala {
    char nome[50]; //nome do comodo
    struct sala* esquerda;//direcao
    struct sala* direita;//direcao
}sala;

//funcao de criar a sala com alocação dinamica
//cria uma sala nova na memoria
sala* criarSala(char nome[]) {
    sala* nova = (sala*) malloc(sizeof(sala));

    if (nova == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;

    return nova;
/* 
malloc cria espaço na memória

copiamos o nome da sala

começamos sem caminhos (NULL)

devolvemos a sala pronta */
}
/*        Hall
         /    \
   Sala Estar  Cozinha
      /            \
  Biblioteca      Jardim 
  
*/

//funcao explorar sala--interativa
void explorarSala(sala* atual) {
        char opcao;

     while (atual != NULL) {
        printf("\nVoce esta na sala: %s\n", atual->nome);

        // Se for folha, acabou
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Nao ha mais caminhos. Fim da exploracao.\n");
            break;
        }

        printf("Escolha um caminho:\n");
        if (atual->esquerda != NULL)
            printf(" (e) Esquerda\n");
        if (atual->direita != NULL)
            printf(" (d) Direita\n");
        printf(" (s) Sair\n");

        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (opcao == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (opcao == 's') {
            printf("Exploracao encerrada pelo jogador.\n");
            break;
        } else {
            printf("Opcao invalida!\n");
        }
    }
}

int main() {
    //criando as salas
    sala* hall = criarSala("Hall de entrada");
    sala* salaEstar = criarSala("Sala de Estar");
    sala* cozinha = criarSala("Cozinha");
    sala* biblioteca = criarSala("Biblioteca");
    sala* jardim = criarSala("Jardim");

    //ligando as salas (arvore binaria)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    cozinha->direita = jardim;

    //inicia a exploracao
    explorarSala(hall);

    return 0;
}



