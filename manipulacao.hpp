#include <iostream>
#include <fstream>
#include "registro.hpp"

using namespace std;

class arquivoBIN
{
private:
    arquivoCSV qtd;
    ifstream arquivo;
    dadosFuncionario *funcionario;
    int posicaoA, posicaoB;
    int diferencaDePosicoes;

public:
    arquivoBIN();
    ~arquivoBIN();
    void lobby();
    void ler_dados();
    void adicionar_elemento_em_uma_posicao_especifica();
    void imprimir_dados_entre_duas_posicoes();
    void alterar_dados_de_uma_posicao();
    void trocar_dois_registros_de_posicao();
    void imprimirDados(ifstream &arquivo);
};

arquivoBIN::arquivoBIN()
{
    funcionario = new dadosFuncionario[200000];
}

arquivoBIN::~arquivoBIN()
{
    delete funcionario;
}

void arquivoBIN::lobby()
{
    arquivo.open("binario.bin", ios::binary);

    if (!arquivo.is_open())
    {
        cout << "arquivo nao aberto";
    }
    else
    {
        imprimirDados(arquivo);
        arquivo.close();
    }
}

void arquivoBIN::adicionar_elemento_em_uma_posicao_especifica()
{
}
void arquivoBIN::imprimir_dados_entre_duas_posicoes()
{
}
void arquivoBIN::alterar_dados_de_uma_posicao()
{
}
void arquivoBIN::trocar_dois_registros_de_posicao()
{
}
void arquivoBIN::imprimirDados(ifstream &arquivo)
{
    int i = 0;

    while (!arquivo.eof())
    {
        arquivo.read((char *)&funcionario[i], sizeof(dadosFuncionario));

        cout << funcionario->id << " "
             << funcionario->nomeFuncionario << " "
             << funcionario->cargo << " "
             << funcionario->pagamentoBase << " "
             << funcionario->pagamentoHoraExtra << " "
             << funcionario->outroPagamento << " "
             << funcionario->beneficios << " "
             << funcionario->pagamentoTotal << " "
             << funcionario->pagamentoTotalVezesBeneficios << " "
             << funcionario->ano << endl;
    }
}