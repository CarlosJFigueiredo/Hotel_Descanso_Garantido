#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "util.h"

void formatar_data(char* data) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    strptime(data, "%d/%m/%Y", &tm);
    strftime(data, 11, "%d/%m/%Y", &tm);
}

int calcular_dias_entre_datas(const char* data_inicio, const char* data_fim) {
    struct tm tm_inicio, tm_fim;
    time_t t_inicio, t_fim;

    memset(&tm_inicio, 0, sizeof(struct tm));
    strptime(data_inicio, "%d/%m/%Y", &tm_inicio);
    t_inicio = mktime(&tm_inicio);

    memset(&tm_fim, 0, sizeof(struct tm));
    strptime(data_fim, "%d/%m/%Y", &tm_fim);
    t_fim = mktime(&tm_fim);

    return (int)difftime(t_fim, t_inicio) / (60 * 60 * 24);
}
