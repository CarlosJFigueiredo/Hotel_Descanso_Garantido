#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"

int proximo_codigo_funcionario = 1;

void cadastrar_funcionario() {
    FILE *file;
    Funcionario funcionario;

    file = fopen("funcionarios.bin", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    funcionario.codigo = proximo_codigo_funcionario++;
    printf("Digite o nome do funcionário: ");
    scanf(" %49[^\n]", funcionario.nome);
    printf("Digite o telefone do funcionário: ");
    scanf(" %19[^\n]", funcionario.telefone);
    printf("Digite o cargo do funcionário: ");
    scanf(" %49[^\n]", funcionario.cargo);
    printf("Digite o salário do funcionário: ");
    scanf("%f", &funcionario.salario);

    fwrite(&funcionario, sizeof(Funcionario), 1, file);

    fclose(file);
    printf("Funcionário cadastrado com sucesso. Código: %d\n", funcionario.codigo);
}

void pesquisar_funcionario() {
    FILE *file;
    Funcionario funcionario;
    char busca[50];

    printf("Digite o nome ou código do funcionário: ");
    scanf(" %49[^\n]", busca);

    file = fopen("funcionarios.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (strcmp(funcionario.nome, busca) == 0 || atoi(busca) == funcionario.codigo) {
            printf("Código: %d\n", funcionario.codigo);
            printf("Nome: %s\n", funcionario.nome);
            printf("Telefone: %s\n", funcionario.telefone);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("Salário: %.2f\n", funcionario.salario);
            fclose(file);
            return;
        }
    }

    printf("Funcionário não encontrado.\n");
    fclose(file);
}
