#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int matricula;
    char nome[100];
    char curso[100];
    char endereco[200];
    bool ativo;
} Aluno;

void cadastrarAluno(Aluno **alunos, int *n) {
    Aluno novo;
    printf("Digite a matricula: ");
    scanf("%d", &novo.matricula);
    getchar(); // consumir newline

    printf("Digite o nome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Digite o curso: ");
    fgets(novo.curso, sizeof(novo.curso), stdin);
    novo.curso[strcspn(novo.curso, "\n")] = '\0';

    printf("Digite o endereco: ");
    fgets(novo.endereco, sizeof(novo.endereco), stdin);
    novo.endereco[strcspn(novo.endereco, "\n")] = '\0';

    novo.ativo = true;

    // Alocar novo vetor com espaço para mais 1 aluno
    int novoTamanho = (*n) + 1;
    Aluno *temp = malloc(novoTamanho * sizeof(Aluno));
    if (temp == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }
    // Copiar alunos ja cadastrados
    for (int i = 0; i < (*n); i++) {
        temp[i] = (*alunos)[i];
    }
    // Adicionar novo aluno
    temp[*n] = novo;
    
    // Liberar vetor antigo e atualizar ponteiro e contador
    free(*alunos);
    *alunos = temp;
    (*n)++;
}

void removerAluno(Aluno *alunos, int n) {
    int matricula;
    printf("Digite a matricula do aluno a ser removido: ");
    scanf("%d", &matricula);
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (alunos[i].matricula == matricula && alunos[i].ativo) {
            alunos[i].ativo = false;
            printf("Aluno com matricula %d removido com sucesso!\n", matricula);
            found = true;
            break;
        }
    }
    if (!found)
        printf("Aluno nao encontrado ou ja removido.\n");
}

void alterarCurso(Aluno *alunos, int n) {
    int matricula;
    char novoCurso[100];
    printf("Digite a matricula do aluno para alterar o curso: ");
    scanf("%d", &matricula);
    getchar(); // consumir newline
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (alunos[i].matricula == matricula && alunos[i].ativo) {
            printf("Digite o novo curso: ");
            fgets(novoCurso, sizeof(novoCurso), stdin);
            novoCurso[strcspn(novoCurso, "\n")] = '\0';
            strcpy(alunos[i].curso, novoCurso);
            printf("Curso alterado com sucesso!\n");
            found = true;
            break;
        }
    }
    if (!found)
        printf("Aluno nao encontrado ou inativo.\n");
}

void alterarEndereco(Aluno *alunos, int n) {
    int matricula;
    char novoEndereco[200];
    printf("Digite a matricula do aluno para alterar o endereco: ");
    scanf("%d", &matricula);
    getchar(); 
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (alunos[i].matricula == matricula && alunos[i].ativo) {
            printf("Digite o novo endereco: ");
            fgets(novoEndereco, sizeof(novoEndereco), stdin);
            novoEndereco[strcspn(novoEndereco, "\n")] = '\0';
            strcpy(alunos[i].endereco, novoEndereco);
            printf("Endereco alterado com sucesso!\n");
            found = true;
            break;
        }
    }
    if (!found)
        printf("Aluno nao encontrado ou inativo.\n");
}

void relatorioAlunos(Aluno *alunos, int n) {
    printf("\n===== Relatorio de Alunos Ativos =====\n");
    for (int i = 0; i < n; i++) {
        if (alunos[i].ativo) {
            printf("Matricula: %d\n", alunos[i].matricula);
            printf("Nome: %s\n", alunos[i].nome);
            printf("Curso: %s\n", alunos[i].curso);
            printf("Endereco: %s\n", alunos[i].endereco);
            printf("--------------------------------------\n");
        }
    }
}

int main() {
    Aluno *alunos = NULL;
    int nAlunos = 0;
    int opcao;

    do {
        printf("\n==== Menu ====\n");
        printf("1 - Cadastrar Aluno\n");
        printf("2 - Remover Aluno\n");
        printf("3 - Alterar Curso\n");
        printf("4 - Alterar Endereco\n");
        printf("5 - Relatorio de Alunos\n");
        printf("0 - Sair\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno(&alunos, &nAlunos);
                break;
            case 2:
                if(nAlunos > 0)
                    removerAluno(alunos, nAlunos);
                else
                    printf("Nenhum aluno cadastrado.\n");
                break;
            case 3:
                if(nAlunos > 0)
                    alterarCurso(alunos, nAlunos);
                else
                    printf("Nenhum aluno cadastrado.\n");
                break;
            case 4:
                if(nAlunos > 0)
                    alterarEndereco(alunos, nAlunos);
                else
                    printf("Nenhum aluno cadastrado.\n");
                break;
            case 5:
                if(nAlunos > 0)
                    relatorioAlunos(alunos, nAlunos);
                else
                    printf("Nenhum aluno cadastrado.\n");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao Invalida\n");
        }
    } while (opcao != 0);

    free(alunos);
    return 0;
} 