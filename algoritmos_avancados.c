#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//strucrts------------------------------------
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

#define TAM_HASH 10

typedef struct hash {
    char pista[100];
    char suspeito[50];
    struct hash* prox;
} Hash;


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
//funcao da hash--------
int funcaoHash(char pista[]) {
    int soma = 0;
    for (int i = 0; pista[i] != '\0'; i++)
        soma += pista[i];
    return soma % TAM_HASH;
}

//Inserir pista → suspeito
void inserirHash(Hash* tabela[], char pista[], char suspeito[]) {
    int indice = funcaoHash(pista);

    Hash* novo = (Hash*) malloc(sizeof(Hash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}
//Contar pistas de um suspeito
int contarPistasSuspeito(Hash* tabela[], char suspeito[]) {
    int contador = 0;

    for (int i = 0; i < TAM_HASH; i++) {
        Hash* atual = tabela[i];
        while (atual != NULL) {
            if (strcmp(atual->suspeito, suspeito) == 0)
                contador++;
            atual = atual->prox;
        }
    }
    return contador;
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
void explorarMansao(sala* atual, pista** pistas, Hash* tabela[]) { 
//Pista** pistas
//Isso permite atualizar a raiz da BST fora da função
    char opcao;

    while (atual != NULL) {
        printf("\nVoce esta em: %s\n", atual->nome);
        printf("Pista encontrada: %s\n", atual->pista);

        // adiciona automaticamente a pista
        *pistas = inserirPista(*pistas, atual->pista);

        // associação pista → suspeito (fixa, definida pelo sistema)
        if (strcmp(atual->pista, "Pegadas suspeitas no chao") == 0)
            inserirHash(tabela, atual->pista, "Mordomo");
        else if (strcmp(atual->pista, "Janela aberta") == 0)
            inserirHash(tabela, atual->pista, "Jardineiro");
        else if (strcmp(atual->pista, "Faca com manchas estranhas") == 0)
            inserirHash(tabela, atual->pista, "Cozinheira");
        else if (strcmp(atual->pista, "Livro fora do lugar") == 0)
            inserirHash(tabela, atual->pista, "Jardineiro");
        else if (strcmp(atual->pista, "Terra remexida") == 0)
            inserirHash(tabela, atual->pista, "Jardineiro");

        if (!atual->esquerda && !atual->direita)
            break;


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
    char acusado[50];

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

    // Tabela hash
    Hash* tabela[TAM_HASH];
    for (int i = 0; i < TAM_HASH; i++)
        tabela[i] = NULL;

    // Exploração
    explorarMansao(hall, &pistas, tabela);

    // Exibição final
    printf("\nPistas coletadas:\n");
    exibirPistaEmOrdem(pistas);

printf("\nSuspeitos possiveis:\n");
printf("- Mordomo\n");
printf("- Jardineiro\n");
printf("- Cozinheira\n");
printf("- Bibliotecaria\n");


    printf("\nQuem voce acusa? ");
    scanf(" %[^\n]", acusado);

    int total = contarPistasSuspeito(tabela, acusado);

    if (total >= 2) {
        printf("\nACUSACAO CONFIRMADA! %s e o culpado.\n", acusado);
    } else {
        printf("\nProvas insuficientes. %s nao pode ser acusado.\n", acusado);
    }

    return 0;
}



