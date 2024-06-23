#ifndef CLIENTE_H
#define CLIENTE_H

#define NOME_HOTEL "Hotel Descanso Garantido"

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
} Cliente;

void cadastrar_cliente();
void pesquisar_cliente();
void inicializar_codigos();

#endif // CLIENTE_H
