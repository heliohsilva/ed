#include <iostream>
#ifndef PARSER_H
#define PARSER_H

struct dadosFuncionario
{
    int id;
    char nomeFuncionario[200], cargo[200];
    float pagamentoBase,
        pagamentoHoraExtra,
        outroPagamento;
    float beneficios;
    float pagamentoTotal,
        pagamentoTotalVezesBeneficios;
    int ano;
};

#endif