#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct {
    int codigo;
    char nome[50];
    char telefone[20];
    char cargo[50];
    float salario;
} Funcionario;

void cadastrar_funcionario();
void pesquisar_funcionario();

#endif 
