#include <iostream>
#include <fstream>
#include <cstring>
#include "registro.hpp"

using namespace std;

class arquivoCSV
{
private:
    dadosFuncionario *funcionario;
    int qtdFuncionarios;
    ifstream arquivoEntrada;
    ofstream arquivoConvertido;
    void verificar_se_string_eh_numero(string &palavra);
    bool verificar_se_string_esta_vazia(const char *palavra);

public:
    arquivoCSV();
    ~arquivoCSV();
    int quantidade_de_funcionarios();
    string ler_palavra(ifstream &arquivoEntrada);
    void ler_os_tipos_do_registro_em_cada_linha();
    void gravar_no_arquivo_binario(ofstream &arquivoConvertido);
};

void arquivoCSV::verificar_se_string_eh_numero(string &palavra)
{
    for (unsigned i = 0; i < (palavra.length()); ++i)
    {
        if (isdigit(palavra[i]) == 0)
            palavra = '0';
    }
}

bool arquivoCSV::verificar_se_string_esta_vazia(const char *palavra)
{
    return strlen(palavra) == 0;
}

arquivoCSV::arquivoCSV()
{
    funcionario = new dadosFuncionario;
}
arquivoCSV::~arquivoCSV()
{
    delete funcionario;
}

int arquivoCSV::quantidade_de_funcionarios()
{
    return qtdFuncionarios;
}

string arquivoCSV::ler_palavra(ifstream &arquivoEntrada)
{
    string palavra;
    char caracterParaFormarAPalavra;
    arquivoEntrada.read(&caracterParaFormarAPalavra, 1);

    if (caracterParaFormarAPalavra == '"')
    {
        do
        {
            palavra += caracterParaFormarAPalavra;
            arquivoEntrada.read(&caracterParaFormarAPalavra, 1);
        } while (caracterParaFormarAPalavra != '"');

        arquivoEntrada.read(&caracterParaFormarAPalavra, 1);

        palavra += '"';
    }
    else
    {
        do
        {
            palavra += caracterParaFormarAPalavra;
            arquivoEntrada.read(&caracterParaFormarAPalavra, 1);

        } while (caracterParaFormarAPalavra != ',' and caracterParaFormarAPalavra != '\n' and !arquivoEntrada.eof());
    }

    return palavra;
}

void arquivoCSV::ler_os_tipos_do_registro_em_cada_linha()
{

    arquivoEntrada.open("san_francisco_payroll_dataset.csv");
    arquivoConvertido.open("binario.bin", ios::binary);

    string palavra;

    if (!arquivoEntrada.good())
    {
        cout << "ERRO!! Nao foi possivel abrir o arquivo csv";
    }
    else
    {

        for (int i = 0; i < 10; i++)
        {
            ler_palavra(arquivoEntrada); // elimina a primeira linha(cabeçalho)
        }

        while (!arquivoEntrada.eof())
        {
            palavra = ler_palavra(arquivoEntrada);
            if (verificar_se_string_esta_vazia(palavra.data()))
            {
                break;
            }
            funcionario->id = stoi(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            strcpy(funcionario->nomeFuncionario, palavra.c_str());
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            strcpy(funcionario->cargo, palavra.c_str());
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            verificar_se_string_eh_numero(palavra);
            funcionario->pagamentoBase = stof(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            verificar_se_string_eh_numero(palavra);
            funcionario->pagamentoHoraExtra = stof(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            verificar_se_string_eh_numero(palavra);
            funcionario->outroPagamento = stof(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            verificar_se_string_eh_numero(palavra);
            funcionario->beneficios = stof(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            verificar_se_string_eh_numero(palavra);
            funcionario->pagamentoTotal = stof(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            verificar_se_string_eh_numero(palavra);
            funcionario->pagamentoTotalVezesBeneficios = stof(palavra);
            palavra.clear();

            palavra = ler_palavra(arquivoEntrada);
            funcionario->ano = stoi(palavra);
            palavra.clear();

            gravar_no_arquivo_binario(arquivoConvertido);
        }
        cout << "terminado";
        arquivoConvertido.close();
        arquivoEntrada.close();
    }
}

void arquivoCSV::gravar_no_arquivo_binario(ofstream &arquivoConvertido)
{
    arquivoConvertido.write((const char *)(funcionario), sizeof(dadosFuncionario));

    qtdFuncionarios++;
}
