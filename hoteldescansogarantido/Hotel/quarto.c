#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quarto.h"

// Função para cadastrar um quarto
void cadastrar_quarto() {
    FILE *file;
    Quarto quarto;

    file = fopen("quartos.bin", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o número do quarto: ");
    scanf("%d", &quarto.numero);
    printf("Digite a quantidade de hóspedes: ");
    scanf("%d", &quarto.quantidade_hospedes);
    printf("Digite o valor da diária: ");
    scanf("%f", &quarto.valor_diaria);

    strcpy(quarto.status, "desocupado"); 

    fwrite(&quarto, sizeof(Quarto), 1, file);

    fclose(file);
    printf("Quarto cadastrado com sucesso. Número: %d\n", quarto.numero);
}

// Função para atualizar o status de um quarto
void atualizar_status_quarto(int numero_quarto, const char* novo_status) {
    FILE *file;
    Quarto quarto;

    file = fopen("quartos.bin", "r+b");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&quarto, sizeof(Quarto), 1, file)) {
        if (quarto.numero == numero_quarto) {
            fseek(file, -sizeof(Quarto), SEEK_CUR);
            strcpy(quarto.status, novo_status);
            fwrite(&quarto, sizeof(Quarto), 1, file);
            printf("Status do quarto atualizado para: %s\n", novo_status);
            fclose(file);
            return;
        }
    }

    printf("Quarto não encontrado.\n");
    fclose(file);
}

// Função para obter o status de um quarto
char* obter_status_quarto(int numero_quarto) {
    FILE *file;
    static char status[20];
    Quarto quarto;

    file = fopen("quartos.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    while (fread(&quarto, sizeof(Quarto), 1, file)) {
        if (quarto.numero == numero_quarto) {
            strcpy(status, quarto.status);
            fclose(file);
            return status;
        }
    }

    fclose(file);
    return NULL;
}

// Função para obter o valor da diária de um quarto
double obter_valor_diaria_quarto(int numero_quarto) {
    FILE *file;
    Quarto quarto;

    file = fopen("quartos.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1.0;
    }

    while (fread(&quarto, sizeof(Quarto), 1, file)) {
        if (quarto.numero == numero_quarto) {
            fclose(file);
            return quarto.valor_diaria;
        }
    }

    fclose(file);
    printf("Quarto não encontrado.\n");
    return -1.0; // Retorna -1.0 para indicar erro
}
