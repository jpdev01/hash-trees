typedef struct {
    int chave;
    void* valor;
} Entrada;

typedef struct {
    int total;
    int tamanho;
    Entrada** elementos;
} Hash;

Hash* criar(int tamanho) {
    Hash* hash = malloc(sizeof(Hash));
    hash->tamanho = tamanho;
    hash->total = 0;
    hash->elementos = malloc(tamanho * sizeof(Entrada*));
    for (int i = 0; i < tamanho; i++) {
        hash->elementos[i] = NULL;
    }
    return hash;
}

void liberar(Hash* hash) {
    if (hash != NULL) {
        for (int i = 0; i < tamanho; i++) {
            if (hash->elementos[i] != NULL) {
                free(hash->elementos[i]);
            }
        }
        free(hash->elementos);
        free(hash);
    }
}

int hashingDivisao(int chave, int tamanho) {
    return (chave & 0x7FFFFFFF) % tamanho;
}

int hashingMultiplicacao(int chave, int tamanho) {
    float A = 0.61803387; //constante 0 < A < 1
    float i = chave * A; //realiza a multiplicação
    i = i - (int) i; //obtém a parte fracionária
    return (int) (tamanho * i);
}

int hashingDobra(int chave, int tamanho) {
    int k = 10;
    int parte1 = chave >> k; // move bit
    int parte2 = chave & (tamanho - 1);
    return (int) (parte1 ^ parte2);
}

void adicionar(Hash *hash, int chave, void* valor) {
    if (hash != NULL && hash->total < hash->tamanho) {
        int indice = hashingDivisao(chave, hash->tamanho);

        Entrada *entrada = malloc(sizeof(Entrada));
        entrada->chave = chave;
        entrada->valor = valor;

        hash->elementos[indice] = entrada;
        hash->total++;
    }
}

void* buscar(Hash *hash, int chave) {
    if (hash != NULL) {
        int indice = hashingDivisao(chave, hash->tamanho);
        if (hash->elementos[indice] != NULL) {
            return hash->elementos[indice]->valor;
        }
    }
    return NULL;
}