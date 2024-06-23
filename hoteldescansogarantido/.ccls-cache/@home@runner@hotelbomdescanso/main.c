#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cliente.h"
#include "funcionario.h"
#include "quarto.h"
#include "estadia.h"
#include "util.h"

int main() {
    srand((unsigned int)time(NULL)); // Inicializar o gerador de números aleatórios
    inicializar_codigos(); // Inicializa os códigos a partir dos arquivos existentes

    int opcao;

    do {
        printf("\n%s - Menu:\n", NOME_HOTEL);
        printf("1. Cadastrar Cliente\n");
        printf("2. Cadastrar Funcionário\n");
        printf("3. Cadastrar Quarto\n");
        printf("4. Cadastrar Estadia\n");
        printf("5. Pesquisar Cliente\n");
        printf("6. Pesquisar Funcionário\n");
        printf("7. Pesquisar Estadias de um Cliente\n");
        printf("8. Relatório dos pontos de fidelidade\n");
        printf("9. Dar baixa em uma estadia\n");
        printf("10. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrar_cliente();
                break;
            case 2:
                cadastrar_funcionario();
                break;
            case 3:
                cadastrar_quarto();
                break;
            case 4:
                cadastrar_estadia();
                break;
            case 5:
                pesquisar_cliente();
                break;
            case 6:
                pesquisar_funcionario();
                break;
            case 7:
                mostrar_estadias_cliente();
                break;
            case 8: {
                int codigo_cliente;
                printf("Digite o código do cliente: ");
                scanf("%d", &codigo_cliente);
                int pontos = calcular_pontos_fidelidade(codigo_cliente);
                printf("Pontos de fidelidade do cliente: %d\n", pontos);
                break;
            }
            case 9:
                dar_baixa_estadia();
                break;
            case 10:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 10);

    return 0;
}
