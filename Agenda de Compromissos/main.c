#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAREFAS 50

typedef int TIPOCHAVE;
typedef char dataRef[11];

typedef struct {
    TIPOCHAVE chave;
    dataRef dataCompromisso[20];
    char descricaoCompromisso[300];
} Agenda;

bool validarData(const char *data) {
    int anos, meses, dias;
    if (sscanf(data, "%d-%d-%d", &anos, &meses, &dias) != 3) {
        return false;
    }

    if (meses <= 0 || meses > 12 || dias <= 0 || dias > 31) {
        return false;
    }

    return true;
}

bool validarHora(const char *hora) {
    int horas, minutos, segundos;
    if (sscanf(hora, "%d:%d:%d", &horas, &minutos, &segundos) != 3) {
        return false;
    }

    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59 || segundos < 0 || segundos > 59) {
        return false;
    }

    return true;
}

void criarTimestamp(char *timestamp) {
    char data[11], hora[9];

    do {
        printf("Digite a data do seu novo compromisso (aaaa-mm-dd): ");
        scanf("%s", data);
    } while (!validarData(data));

    do {
        printf("Digite o horário do seu novo compromisso (hh:mm:ss): ");
        scanf("%s", hora);
    } while (!validarHora(hora));

    snprintf(timestamp, 30, "%s %s", data, hora);
}

void obterDescricaoCompromisso(char *compromisso) {
    printf("Digite a descrição do seu novo compromisso: ");
    fflush(stdin);
    fgets(compromisso, 300, stdin);
    compromisso[strcspn(compromisso, "\n")] = '\0';
    if (strlen(compromisso) == 0) {
        printf("Descrição vazia. Digite novamente.\n");
    }
}

void exibirElementos(Agenda *lista, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Chave: %d, Data: %s, Descrição: %s\n", lista[i].chave, lista[i].dataCompromisso, lista[i].descricaoCompromisso);
    }
}

void adicionarTarefa(Agenda *lista, int *tamanho, int *chave, char *novaData, char *novaDescricao) {
    if (*tamanho >= MAX_TAREFAS) {
        printf("A lista de tarefas está cheia. Não é possível adicionar mais tarefas.\n");
        return;
    }

    lista[*tamanho].chave = *chave;
    (*chave)++;
    strcpy(lista[*tamanho].dataCompromisso, novaData);
    strcpy(lista[*tamanho].descricaoCompromisso, novaDescricao);
    (*tamanho)++;

}

void editarCompromisso(Agenda lista[], int chave, const char *descricao, const char *data) {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (lista[i].chave == chave) {
            strncpy(lista[i].dataCompromisso, data, sizeof(lista[i].dataCompromisso));
            strncpy(lista[i].descricaoCompromisso, descricao, sizeof(lista[i].descricaoCompromisso));
            break;  // Se encontrou a chave, pode sair do loop
        }
    }
}


void removerCompromisso(Agenda lista[], int *tamanho, int chave) {
    int encontrado = 0;
    for (int i = 0; i < *tamanho; i++) {
        if (lista[i].chave == chave) {
            encontrado = 1;
            for (int j = i; j < *tamanho - 1; j++) {
                lista[j] = lista[j + 1];
            }
            lista[*tamanho - 1].chave = -1;
            (*tamanho)--;
            break;
        }
    }
    if (!encontrado) {
        printf("Chave não encontrada. Nenhum compromisso foi removido.\n");
    }
}


void consultarElemento(Agenda lista[], int chave) {
    for (int i = 0; i < MAX_TAREFAS; i++) {
        if (lista[i].chave == chave) {
            printf("Chave: %d, Data: %s, Descrição: %s\n", lista[i].chave, lista[i].dataCompromisso, lista[i].descricaoCompromisso);
            return;
        }
    }
    printf("Chave não encontrada. Nenhum compromisso foi encontrado.\n");
}


int comparar_agenda(const void *a, const void *b) {
    Agenda *compromisso_a = (Agenda *)a;
    Agenda *compromisso_b = (Agenda *)b;

    return strcmp(compromisso_a->dataCompromisso, compromisso_b->dataCompromisso);
}

int comprimentoAgenda(Agenda lista[], int tamanho) {
    int contador = 0;
    for (int i = 0; i < tamanho; i++) {
        if (lista[i].chave != -1) {
            contador++;
        }
    }
    return contador;
}

void limparAgenda(Agenda *lista, int *tamanho) {
    for (int i = 0; i < *tamanho; i++) {
        lista[i].chave = -1;
    }
    *tamanho = 0;
    printf("Todos os compromissos foram apagados.\n");
}

void limparTela() {
    printf("Pressione qualquer tecla para continuar.");
    fflush(stdin);
    getchar();
    system("cls");
}

int main() {
    Agenda lista[MAX_TAREFAS];
    int chave = 1; // Inicialize a chave sequencial com 1
    int tamanho = 0;
    int escolha;
    int indice;
    int acao;
    int app = 1;
    int comprimento_agenda;
    char data[11];
    char novaData[11];
    char descricao[50];
    char novaDescricao[50];

    while (app == 1) {
        printf("\nMenu:\n");
        printf("1. Verificar Compromisso\n");
        printf("2. Buscar Compromisso\n");
        printf("3. Inserir Novo Compromisso\n");
        printf("4. Mostrar Numero de compromissos\n");
        printf("5. Editar/Remover Compromisso\n");
        printf("6. Reinicializar Agenda\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (tamanho == 0) {
                    printf("Você não possui compromissos na sua agenda.\n");
                } else {
                    exibirElementos(lista, tamanho);
                }
                limparTela();
                break;
            case 2:
                if (tamanho == 0) {
                    printf("Você não possui compromissos na sua agenda.\n");
                } else {
                    printf("Digite a chave a ser consultado: ");
                    scanf("%d", &indice);
                    printf("Elemento %d: \n", indice);
                    consultarElemento(lista, indice);
                }
                limparTela();
                break;
            case 3:
                obterDescricaoCompromisso(novaDescricao);
                criarTimestamp(novaData);
                adicionarTarefa(lista, &tamanho, &chave, novaData, novaDescricao);
                qsort(lista, tamanho, sizeof(Agenda), comparar_agenda);
                limparTela();
                break;
            case 4:
                comprimento_agenda = comprimentoAgenda(lista, tamanho);
                printf("Você tem %d compromissos em sua agenda.\n", comprimento_agenda);
                limparTela();
                break;
            case 5:
                exibirElementos(lista, tamanho);
                printf("Digite a chave do compromisso: ");
                scanf("%d", &chave);
                printf("1. Editar \n");
                printf("2. Remover \n");
                scanf("%d", &acao);
                switch (acao)
                {
                    case 1:
                        obterDescricaoCompromisso(novaDescricao);
                        criarTimestamp(novaData);
                        editarCompromisso(lista, chave, novaDescricao, novaData);
                        qsort(lista, tamanho, sizeof(Agenda), comparar_agenda);
                        printf("Compromisso Editado.\n");
                        break;
                    case 2:
                        removerCompromisso(lista, &tamanho, chave);
                        qsort(lista, tamanho, sizeof(Agenda), comparar_agenda);
                        printf("Compromisso Removido.\n");
                        break;
                }
                limparTela();
                break;
            case 6:
                if (tamanho == 0) {
                    printf("A lista está vazia.\n");
                } else {
                    limparAgenda(lista, &tamanho);
                }
                limparTela();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                app = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                limparTela();
        }
    }

    return 0;
}
