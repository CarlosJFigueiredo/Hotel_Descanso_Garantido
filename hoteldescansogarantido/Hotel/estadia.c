#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "estadia.h"
#include "util.h"
#include "quarto.h"

int proximo_codigo_estadia = 1;

void cadastrar_estadia() {
    FILE *file;
    Estadia estadia;
    char* status_quarto;
    struct tm tm_entrada = {0}, tm_saida = {0};
    time_t time_entrada, time_saida;
    double diff_seconds;
    int diff_days;

    printf("Digite o código do cliente: ");
    scanf("%d", &estadia.codigo_cliente);
    printf("Digite o número do quarto: ");
    scanf("%d", &estadia.numero_quarto);

    // Verificar o status do quarto
    status_quarto = obter_status_quarto(estadia.numero_quarto);
    if (status_quarto == NULL) {
        printf("Quarto não encontrado.\n");
        return;
    }
    if (strcmp(status_quarto, "desocupado") != 0) {
        printf("O quarto está ocupado ou em manutenção. Escolha outro quarto.\n");
        return;
    }

    printf("Digite a data de entrada (dd/mm/aaaa): ");
    scanf(" %10[^\n]", estadia.data_entrada);
    sscanf(estadia.data_entrada, "%d/%d/%d", &tm_entrada.tm_mday, &tm_entrada.tm_mon, &tm_entrada.tm_year);
    tm_entrada.tm_mon -= 1;
    tm_entrada.tm_year -= 1900;
    time_entrada = mktime(&tm_entrada);

    printf("Digite a data de saída (dd/mm/aaaa): ");
    scanf(" %10[^\n]", estadia.data_saida);
    sscanf(estadia.data_saida, "%d/%d/%d", &tm_saida.tm_mday, &tm_saida.tm_mon, &tm_saida.tm_year);
    tm_saida.tm_mon -= 1;
    tm_saida.tm_year -= 1900;
    time_saida = mktime(&tm_saida);

    // Calcula a diferença de dias
    diff_seconds = difftime(time_saida, time_entrada);
    diff_days = (int)(diff_seconds / (60 * 60 * 24));
    estadia.dias_estadia = diff_days;

    strcpy(estadia.status, "ativa");
    estadia.codigo = proximo_codigo_estadia++;

    file = fopen("estadias.bin", "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&estadia, sizeof(Estadia), 1, file);
    atualizar_status_quarto(estadia.numero_quarto, "ocupado");

    fclose(file);
    printf("Estadia cadastrada com sucesso. Código: %d\n", estadia.codigo);
}

void mostrar_estadias_cliente() {
    FILE *file;
    Estadia estadia;
    int codigo_cliente;

    printf("Digite o código do cliente: ");
    scanf("%d", &codigo_cliente);

    file = fopen("estadias.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&estadia, sizeof(Estadia), 1, file)) {
        if (estadia.codigo_cliente == codigo_cliente) {
            printf("Código da estadia: %d\n", estadia.codigo);
            printf("Número do quarto: %d\n", estadia.numero_quarto);
            printf("Data de entrada: %s\n", estadia.data_entrada);
            printf("Data de saída: %s\n", estadia.data_saida);
            printf("Dias de estadia: %d\n", estadia.dias_estadia);
            printf("Status: %s\n\n", estadia.status);
        }
    }

    fclose(file);
}

void dar_baixa_estadia() {
    FILE *file;
    Estadia estadia;
    int codigo_estadia;
    double valor_diaria, valor_total;

    printf("Digite o código da estadia: ");
    scanf("%d", &codigo_estadia);

    file = fopen("estadias.bin", "r+b");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fread(&estadia, sizeof(Estadia), 1, file)) {
        if (estadia.codigo == codigo_estadia) {
            fseek(file, -sizeof(Estadia), SEEK_CUR);
            strcpy(estadia.status, "finalizada");
            fwrite(&estadia, sizeof(Estadia), 1, file);
            atualizar_status_quarto(estadia.numero_quarto, "desocupado");

            // Obter o valor da diária do quarto
            valor_diaria = obter_valor_diaria_quarto(estadia.numero_quarto);
            if (valor_diaria < 0) {
                printf("Erro ao obter o valor da diária do quarto.\n");
                fclose(file);
                return;
            }

            // Calcular o valor total da estadia
            valor_total = valor_diaria * estadia.dias_estadia;

            printf("Estadia finalizada com sucesso. Código: %d\n", estadia.codigo);
            printf("Valor a pagar: R$ %.2f\n", valor_total);

            fclose(file);
            return;
        }
    }

    printf("Estadia não encontrada.\n");
    fclose(file);
}

int calcular_pontos_fidelidade(int codigo_cliente) {
    FILE *file;
    Estadia estadia;
    int pontos = 0;

    file = fopen("estadias.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    while (fread(&estadia, sizeof(Estadia), 1, file)) {
        if (estadia.codigo_cliente == codigo_cliente) {
            pontos += estadia.dias_estadia * 10; // 10 pontos por dia
        }
    }

    fclose(file);
    return pontos;
}
