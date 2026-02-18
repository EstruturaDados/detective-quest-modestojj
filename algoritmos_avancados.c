#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sala {
    char nome[50]; //nome do comodo
    char pista[100];
    struct sala* esquerda;//direcao
    struct sala* direita;//direcao
}sala;

//Nó da árvore de pistas (BST)
typedef struct pista {
    char descricao[100];
    struct pista* esquerda;
    struct pista* direita;
} pista;

//funcao de criar a sala com alocação dinamica
//cria uma sala nova na memoria
sala* criarSala(char nome[], char pistaTexto[]) {
    sala* nova = (sala*) malloc(sizeof(sala));

    if (nova == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    strcpy(nova->nome, nome);
    strcpy(nova->pista, pistaTexto);
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
//INSERÇÃO NA BST DE PISTAS (ordem alfabética)
pista* inserirPista(pista* raiz, char descricao[]) {
    if (raiz == NULL) {
        pista* nova = (pista*) malloc(sizeof(pista));
        strcpy(nova->descricao, descricao);
        nova->esquerda = NULL;
        nova->direita = NULL;
        return nova;
    }

    if (strcmp(descricao, raiz->descricao) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, descricao);
    }else if (strcmp(descricao, raiz->descricao) > 0) {
        raiz->direita = inserirPista(raiz->direita, descricao);
    }

    return raiz;
}

//exibe me ordem alfabetica
void exibirPistaEmOrdem(pista* raiz) {
    if (raiz != NULL) {
        exibirPistaEmOrdem(raiz->esquerda);
        printf("- %s\n", raiz->descricao);
        exibirPistaEmOrdem(raiz->direita);
    }
}


//funcao explorar sala--interativa
void explorarMansao(sala* atual, pista** pistas) { 
//Pista** pistas
//Isso permite atualizar a raiz da BST fora da função
    char opcao;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);
        printf("Pista encontrada: %s\n", atual->pista);

        // adiciona automaticamente a pista
        *pistas = inserirPista(*pistas, atual->pista);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Fim da exploracao. Nao ha mais caminhos.\n");
            break;
        }

        printf("\nEscolha o caminho:\n");
        if (atual->esquerda) printf(" (e) Esquerda\n");
        if (atual->direita) printf(" (d) Direita\n");
        printf(" (s) Sair\n");

        printf("Opcao: ");
        scanf(" %c", &opcao);

        if (opcao == 'e' && atual->esquerda)
            atual = atual->esquerda;
        else if (opcao == 'd' && atual->direita)
            atual = atual->direita;
        else if (opcao == 's')
            break;
        else
            printf("Opcao invalida.\n");
    }
}


int main() {
    // Árvore da mansão
    sala* hall = criarSala("Hall de Entrada", "Pegadas suspeitas no chao");
    sala* salaEstar = criarSala("Sala de Estar", "Janela aberta");
    sala* cozinha = criarSala("Cozinha", "Faca com manchas estranhas");
    sala* biblioteca = criarSala("Biblioteca", "Livro fora do lugar");
    sala* jardim = criarSala("Jardim", "Terra remexida");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    cozinha->direita = jardim;

    // BST de pistas
    pista* pistas = NULL;

    // Exploração
    explorarMansao(hall, &pistas);

    // Exibição final
    printf("\nPistas coletadas (ordem alfabetica):\n");
    exibirPistaEmOrdem(pistas);

    return 0;
}


