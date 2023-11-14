#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ALUNOS 100
#define MAX_OCORRENCIAS 100
#define MAX_CHAMADA 100



typedef char dataRef[11];

typedef struct {
    char matricula[20];
    char nome[50];
    char periodo[20];
    char tipoOcorrencia[10];
    char dataHora[20];
} Acesso;

typedef struct {
    char matricula[20];
    char nome[50];
    char periodo[20];
} Aluno;

typedef struct {
    char matricula[20];
    char tipoOcorrencia[10];
} Ocorrencia;

// Variáveis Globais
Aluno listaAlunos[MAX_ALUNOS];
Ocorrencia listaOcorrencias[MAX_OCORRENCIAS];
Acesso filaChamada[MAX_CHAMADA];
int tamanhoLista = 0;
int tamanhoOcorrencias = 0;
int inicioChamada = 0;
int fimChamada = 0;

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

void mostrarListaAlunos() {
    printf("Lista de Alunos:\n");
    for (int i = 0; i < tamanhoLista; i++) {
        printf("Matrícula: %s, Nome: %s, Período: %s\n", listaAlunos[i].matricula, listaAlunos[i].nome, listaAlunos[i].periodo);
    }
}


void obterData(char *data) {
    do {
        printf("Digite a data de hoje (aaaa-mm-dd): ");
        scanf("%s", data);
    } while (!validarData(data));
}

int contarAlunos(const Aluno lista[], int tamanhoLista) {
    int contador = 0;
    for (int i = 0; i < tamanhoLista; i++) {
        if (lista[i].matricula[0] != '\0') {
            contador++;
        }
    }
    return contador;
}

void adicionarNaChamada(const Aluno *aluno) {
    if ((fimChamada + 1) % MAX_CHAMADA == inicioChamada) {
        printf("A chamada está cheia. Não é possível adicionar mais alunos.\n");
    } else {
        strcpy(filaChamada[fimChamada].matricula, aluno->matricula);
        strcpy(filaChamada[fimChamada].nome, aluno->nome);
        strcpy(filaChamada[fimChamada].periodo, aluno->periodo);
        fimChamada = (fimChamada + 1) % MAX_CHAMADA;
    }
}

void mostrarChamada(const char *data) {
    printf("Chamada para a data: %s\n", data);

    int i = inicioChamada;
    while (i != fimChamada) {
        printf("Matrícula: %s, Nome: %s, Período: %s\n", filaChamada[i].matricula, filaChamada[i].nome, filaChamada[i].periodo);
        i = (i + 1) % MAX_CHAMADA;
    }
}

void registrarOcorrencia(const char *matricula, const char *tipoOcorrencia, const char *data) {
    if (tamanhoOcorrencias < MAX_OCORRENCIAS) {
        strcpy(listaOcorrencias[tamanhoOcorrencias].matricula, matricula);
        strcpy(listaOcorrencias[tamanhoOcorrencias].tipoOcorrencia, tipoOcorrencia);

        tamanhoOcorrencias++;
        printf("Ocorrência registrada com sucesso para a matrícula %s.\n", matricula);
    } else {
        printf("A lista de ocorrências está cheia. Não é possível adicionar mais ocorrências.\n");
    }
}


void obterTipoOcorrencia(char *tipoOcorrencia) {
    printf("Selecione o tipo de ocorrência:\n");
    printf("1. Esqueceu\n");
    printf("2. Perdeu\n");
    printf("3. Não Possui\n");
    printf("4. Outros\n");
    printf("Escolha uma opção: ");
    int tipoEscolhido;
    scanf("%d", &tipoEscolhido);

    switch (tipoEscolhido) {
        case 1:
            strcpy(tipoOcorrencia, "Esqueceu");
            break;
        case 2:
            strcpy(tipoOcorrencia, "Perdeu");
            break;
        case 3:
            strcpy(tipoOcorrencia, "Não Possui");
            break;
        case 4:
            strcpy(tipoOcorrencia, "Outros");
            break;
        default:
            printf("Opção inválida. A ocorrência será registrada como 'Outros'.\n");
            strcpy(tipoOcorrencia, "Outros");
            break;
    }
}

void reiniciarOcorrencias() {
    // Defina o tamanho de ocorrências de volta para zero
    tamanhoOcorrencias = 0;
    printf("Ocorrências reiniciadas com sucesso.\n");
}

void reiniciarPrograma() {
    // Reinicialize todas as variáveis globais
    tamanhoLista = 0;
    tamanhoOcorrencias = 0;
    inicioChamada = 0;
    fimChamada = 0;

    // Reinicialize suas listas ou estruturas conforme necessário
    for (int i = 0; i < MAX_ALUNOS; i++) {
        listaAlunos[i].matricula[0] = '\0';
        listaAlunos[i].nome[0] = '\0';
        listaAlunos[i].periodo[0] = '\0';
    }

    for (int i = 0; i < MAX_OCORRENCIAS; i++) {
        listaOcorrencias[i].matricula[0] = '\0';
        listaOcorrencias[i].tipoOcorrencia[0] = '\0';
    }

    for (int i = 0; i < MAX_CHAMADA; i++) {
        filaChamada[i].matricula[0] = '\0';
        filaChamada[i].nome[0] = '\0';
        filaChamada[i].periodo[0] = '\0';
    }

    printf("Programa reiniciado com sucesso.\n");
}


bool validarPeriodo(char *periodo) {
    if (strcmp(periodo, "M") == 0 || strcmp(periodo, "V") == 0 || strcmp(periodo, "N") == 0) {
        return true;
    }
    return false;
}

void obterInformacaoAluno(char *matricula, char *nome, char *periodo) {
    printf("Digite a matrícula do novo aluno: ");
    scanf("%s", matricula);
    printf("Digite o nome do novo aluno: ");
    getchar();  // Limpar o buffer de entrada antes de usar fgets
    fgets(nome, sizeof(listaAlunos[0].nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';
    do {
        printf("Digite o periodo do novo aluno: \n");
        printf("Digite M para matutino\n");
        printf("Digite V para vespertino\n");
        printf("Digite N para noturno\n");
        scanf("%s", periodo);
    } while (!validarPeriodo(periodo));
}

void cadastrarAluno(const char *matricula, const char *nome, const char *periodo) {
    if (tamanhoLista < MAX_ALUNOS) {
        strcpy(listaAlunos[tamanhoLista].matricula, matricula);
        strcpy(listaAlunos[tamanhoLista].nome, nome);
        strcpy(listaAlunos[tamanhoLista].periodo, periodo);
        tamanhoLista++;
        printf("Aluno cadastrado com sucesso!\n");
    } else {
        printf("A lista de alunos está cheia. Não é possível cadastrar mais alunos.\n");
    }
}

bool buscarAlunoPorMatricula(const char *matricula, Aluno *alunoEncontrado) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaAlunos[i].matricula, matricula) == 0) {
            *alunoEncontrado = listaAlunos[i];
            return true;
        }
    }
    return false;
}

void removerAluno(const char *matricula) {
    int indiceAluno = -1;  // Índice do aluno a ser removido

    // Procura o índice do aluno na lista
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(listaAlunos[i].matricula, matricula) == 0) {
            indiceAluno = i;
            break;
        }
    }

    if (indiceAluno != -1) {
        // Move os elementos para preencher o espaço do aluno removido
        for (int i = indiceAluno; i < tamanhoLista - 1; i++) {
            strcpy(listaAlunos[i].matricula, listaAlunos[i + 1].matricula);
            strcpy(listaAlunos[i].nome, listaAlunos[i + 1].nome);
            strcpy(listaAlunos[i].periodo, listaAlunos[i + 1].periodo);
        }

        // Decrementa o tamanho da lista
        tamanhoLista--;

        printf("Aluno removido com sucesso.\n");
    } else {
        printf("Aluno com matrícula %s não encontrado.\n", matricula);
    }
}


void editarOuRemoverAluno(Aluno *lista, int tamanhoLista) {
    char matricula[20];
    printf("Digite a matrícula do aluno a ser editado: ");
    scanf("%s", matricula);

    int encontrado = -1; // Índice do aluno encontrado
    for (int i = 0; i < tamanhoLista; i++) {
        if (strcmp(lista[i].matricula, matricula) == 0) {
            encontrado = i;
            printf("Aluno encontrado: Matrícula: %s, Nome: %s, Período: %s\n", lista[i].matricula, lista[i].nome, lista[i].periodo);

            int opcao;
            printf("Escolha a opção:\n");
            printf("1. Editar nome\n");
            printf("2. Editar turno\n");
            printf("3. Remover aluno\n");
            printf("Opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    scanf("%s", lista[encontrado].nome);
                    break;
                case 2:
                    do {
                        printf("Digite o novo periodo do aluno: \n");
                        printf("Digite M para matutino\n");
                        printf("Digite V para vespertino\n");
                        printf("Digite N para noturno\n");
                        scanf("%s", lista[encontrado].periodo);
                    } while (!validarPeriodo(lista[encontrado].periodo));
                    scanf("%s", lista[encontrado].periodo);
                    break;
                case 3:
                    removerAluno(matricula);
                    break;
                default:
                    printf("Opção inválida.\n");
            }

            break;  // Se encontrou a matrícula, pode sair do loop
        }
    }

    if (encontrado == -1) {
        printf("Aluno com matrícula %s não encontrado.\n", matricula);
    }
}





void mostrarOcorrenciasPorMatricula(const char *matricula) {
    printf("Ocorrências do aluno com matrícula %s:\n", matricula);
    for (int i = 0; i < tamanhoOcorrencias; i++) {
        if (strcmp(listaOcorrencias[i].matricula, matricula) == 0) {
            printf("Tipo de ocorrência: %s, Data: %s\n", listaOcorrencias[i].tipoOcorrencia);
        }
    }
}


void adicionarOcorrencia(const char *matricula, const char *tipoOcorrencia, const char *data) {
    if (tamanhoOcorrencias < MAX_OCORRENCIAS) {
        // Adiciona na chamada
        Aluno alunoEncontrado;
        if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
            adicionarNaChamada(&alunoEncontrado);
            // Adiciona na lista de ocorrências
            registrarOcorrencia(matricula, tipoOcorrencia, data);
        } else {
            printf("Aluno com matrícula %s não encontrado.\n", matricula);
        }


    } else {
        printf("A lista de ocorrências está cheia. Não é possível adicionar mais ocorrências.\n");
    }
}


void chamadaGeral(const char *data) {
    if (tamanhoLista == 0) {
        printf("Você não possui alunos cadastrados.\n");
        return;
    }

    char tipoOcorrencia[10];
    for (int i = 0; i < tamanhoLista; i++) {
        printf("Matrícula: %s, Nome: %s, Período: %s\n", listaAlunos[i].matricula, listaAlunos[i].nome, listaAlunos[i].periodo);
        printf("Gostaria de adicionar uma ocorrência para este aluno? (1 para Sim, 0 para Não): ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha == 1) {
            obterTipoOcorrencia(tipoOcorrencia);
            adicionarOcorrencia(listaAlunos[i].matricula, tipoOcorrencia, data);
        }
    }
}

int main() {
    int escolha;
    int app = 1;
    char matricula[20];
    char nome[50];
    char tipoOcorrencia[10];
    char data[20];
    char periodo[20];

    Aluno alunoEncontrado;

    while (app == 1) {
        printf("\nMenu:\n");
        printf("1. Chamada\n");
        printf("2. Buscar Aluno\n");
        printf("3. Cadastrar Novo Aluno\n");
        printf("4. Inserir Ocorrência\n");
        printf("5. Mostrar Número de Alunos Cadastrados\n");
        printf("6. Editar/Remover Aluno\n");
        printf("7. Mostrar Ocorrências\n");
        printf("8. Reiniciar Ocorrências\n");
        printf("9. Reiniciar Programa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    obterData(data);
                    chamadaGeral(matricula);
                    mostrarChamada(data);
                }
                break;
            case 2:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    printf("Digite a matrícula do aluno a ser buscado: ");
                    scanf("%s", matricula);

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        printf("Aluno encontrado!\n Matrícula: %s, Nome: %s, Período: %s\n", alunoEncontrado.matricula, alunoEncontrado.nome, alunoEncontrado.periodo);
                    } else {
                        printf("Aluno com matrícula %s não encontrado.\n", matricula);
                    }
                }
                break;
            case 3:
                if (tamanhoLista < MAX_ALUNOS) {
                    obterInformacaoAluno(matricula, nome, periodo);
                    cadastrarAluno(matricula, nome, periodo);
                } else {
                    printf("A lista de alunos está cheia. Não é possível cadastrar mais alunos.\n");
                }
                break;
            case 4:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    printf("Digite a matrícula do aluno: ");
                    scanf("%s", matricula);
                    printf("Digite o tipo de ocorrência: ");
                    scanf("%s", tipoOcorrencia);
                    registrarOcorrencia(matricula, tipoOcorrencia, data);
                }
                break;
            case 5:
                printf("Número de alunos cadastrados: %d\n", contarAlunos(listaAlunos, tamanhoLista));
                break;
            case 6:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                }  else {
                    char matricula[20];
                    printf("Digite a matrícula do aluno a ser editado: ");
                    scanf("%s", matricula);

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        printf("Aluno encontrado: Matrícula: %s, Nome: %s, Período: %s\n", alunoEncontrado.matricula, alunoEncontrado.nome, alunoEncontrado.periodo);
                        editarOuRemoverAluno(listaAlunos, tamanhoLista);
                    } else {
                        printf("Aluno com matrícula %s não encontrado.\n", matricula);
                    }
                }

                break;
            case 7:
                if (tamanhoLista == 0) {
                    printf("Você não possui alunos cadastrados.\n");
                } else {
                    mostrarListaAlunos();
                    char matricula[20];
                    printf("Digite a matrícula do aluno para mostrar as ocorrências: ");
                    scanf("%s", matricula);

                    if (buscarAlunoPorMatricula(matricula, &alunoEncontrado)) {
                        mostrarOcorrenciasPorMatricula(matricula);
                    } else {
                        printf("Aluno com matrícula %s não encontrado.\n", matricula);
                    }
                }
                break;
            case 8:
                reiniciarOcorrencias();
                break;
            case 9:
                reiniciarPrograma();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                app = 0;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
