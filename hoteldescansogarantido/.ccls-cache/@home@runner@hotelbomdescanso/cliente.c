#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

int proximo_codigo_cliente = 1;

void inicializar_codigos() {
    FILE *file;
    Cliente cliente;

    // Inicializa o código do cliente
    file = fopen("clientes.bin", "rb");
    if (file != NULL) {
        while (fread(&cliente, sizeof(Cliente), 1, file)) {
            if (cliente.codigo >= proximo_codigo_cliente) {
                proximo_codigo_cliente = cliente.codigo + 1;
            }
        }
        fclose(file);
    }
}

void cadastrar_cliente() {
    FILE *file;
    Cliente cliente;

    file = fopen("clientes.bin", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    cliente.codigo = proximo_codigo_cliente++;
    printf("Digite o nome do cliente: ");
    scanf(" %49[^\n]", cliente.nome);
    printf("Digite o endereço do cliente: ");
    scanf(" %99[^\n]", cliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf(" %19[^\n]", cliente.telefone);

    fwrite(&cliente, sizeof(Cliente), 1, file);

    fclose(file);
    printf("Cliente cadastrado com sucesso. Código: %d\n", cliente.codigo);
}

void pesquisar_cliente() {
    FILE *file;
    Cliente cliente;
    char busca[50];

    printf("Digite o nome ou código do cliente: ");
    scanf(" %49[^\n]", busca);

    file = fopen("clientes.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (strcmp(cliente.nome, busca) == 0 || atoi(busca) == cliente.codigo) {
            printf("Código: %d\n", cliente.codigo);
            printf("Nome: %s\n", cliente.nome);
            printf("Endereço: %s\n", cliente.endereco);
            printf("Telefone: %s\n", cliente.telefone);
            fclose(file);
            return;
        }
    }

    printf("Cliente não encontrado.\n");
    fclose(file);
}
