// quarto.h
#ifndef QUARTO_H
#define QUARTO_H

typedef struct {
    int numero;
    int quantidade_hospedes;
    float valor_diaria; // Valor da diária do quarto
    char status[20];    // Status do quarto
} Quarto;

void cadastrar_quarto();
void atualizar_status_quarto(int numero_quarto, const char* novo_status);
char* obter_status_quarto(int numero_quarto);
double obter_valor_diaria_quarto(int numero_quarto);

#endif // QUARTO_H
