typedef struct {
    int chave;
    void* valor;
} Entrada;

typedef struct no {
    Entrada *entrada;
    struct no *proximo;
} No;

typedef struct {
    int total;
    int tamanho;
    No** elementos;
} Hash;

int hashingDivisao(int chave, int tamanho) {
    return (chave & 0x7FFFFFFF) % tamanho;
}

Hash* criar(int tamanho) {
    Hash* hash = malloc(sizeof(Hash));
    hash->tamanho = tamanho;
    hash->total = 0;
    hash->elementos = malloc(tamanho * sizeof(No*));
    for (int i = 0; i < tamanho; i++) {
        hash->elementos[i] = NULL;
    }
    return hash;
}

void adicionar(Hash *hash, int chave, void* valor) {
    if (hash != NULL) {
        int indice = hashingDivisao(chave, hash->tamanho);
        Entrada *entrada = malloc(sizeof(Entrada));
        entrada->chave = chave;
        entrada->valor = valor;
        No *no = malloc(sizeof(No));
        no->proximo = hash->elementos[indice];
        no->entrada = entrada;
        hash->elementos[indice] = no;
        hash->total++;
    }
}

void* buscar(Hash *hash, int chave) {
    if (hash != NULL) {
        int indice = hashingDivisao(chave, hash->tamanho);
        No *no = hash->elementos[indice];
        while (no != NULL) {
            if (no->entrada->chave == chave) {
                return no->entrada->valor;
            }
            no = no->proximo;
        }
    }

    return NULL;
}