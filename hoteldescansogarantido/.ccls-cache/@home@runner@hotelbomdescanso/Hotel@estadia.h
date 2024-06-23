#ifndef ESTADIA_H
#define ESTADIA_H

typedef struct {
    int codigo;
    int codigo_cliente;
    int numero_quarto;
    char data_entrada[11];
    char data_saida[11];
    int dias_estadia;
    char status[10];
} Estadia;

void cadastrar_estadia();
void mostrar_estadias_cliente();
void dar_baixa_estadia();
int calcular_pontos_fidelidade(int codigo_cliente);

#endif // ESTADIA_H
