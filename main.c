/*
    C.R.U.D. - Agenda telefonica (nome+contato)

    Trabalho em grupos de ate 5 pessoas
    Professor Manfred Heil Junior

    Alunos: Sarah Enaile Braga da Silva; Vitor Hugo Wille; Gabriel Nardes.

*/

// /!\ Perdao pelo excesso de comentarios. Criamos eles para ajudar a organizar o pensamento, facilitar a compreensao pelos colegas
// e pelo professor, alem de servir como guia para que eu ache rapidamente as partes do codigo que mais passam por alteracao.

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //tive que usar pra reorganizar os ids na hora da exclusao :( nao queria, mas precisei

#define MAX_CONTATOS 100
#define MAX_CARACTERES 40
#define ARQUIVO_DADOS "dadosAgenda.vhw"

int escolhaMenu;
char tabelaDados[100][2][40]; // 100 linhas, 2 colunas (nome e telefone), 40 caracteres cada campo
int totalContatos = 0;
int idContato, idEscolhido;

void carregaDados()
{
    // eh minha primeira vez lidando com salvamento/carregamento de arquivo - desculpe se tiver meio zuado, professor =)
    FILE *dadosAgenda = fopen(ARQUIVO_DADOS, "r"); // define variavel e abre pra leitura

    if (dadosAgenda == NULL)
    {
        totalContatos = 0;
        printf("\n[DEBUG] Arquivo de dados nao encontrado. Iniciando agenda vazia.\n"); // atencao: pra essa mensagem aparecer, nao pode ter limparTela(); na func. main!
        return 0;
    }

    totalContatos = 0;

    while (fscanf(dadosAgenda, "%s %s", tabelaDados[totalContatos][0], tabelaDados[totalContatos][1]) == 2)
    {
        totalContatos++;
        if (totalContatos >= MAX_CONTATOS)
        {
            break;
        };
    };

    fclose(dadosAgenda);
}

void salvaDados()
{
    FILE *dadosAgenda = fopen(ARQUIVO_DADOS, "w"); // abre o arquivo em write
    if (dadosAgenda == NULL)
    {
        printf("\n/!\\ ERRO: Nao foi possivel salvar o arquivo de dados. Verifique as permissoes de acesso ao arquivo.\n");
        return 0;
    }
    for (int i = 0; i < totalContatos; i++)
    {
        fprintf(dadosAgenda, "%s %s\n", tabelaDados[i][0], tabelaDados[i][1]); // coloca todos os dados no arquivo e separa os campos por espaco
    }

    fclose(dadosAgenda);
}

void limparTela()
{
#ifdef _WIN32
    system("cls"); // limpa cmd com cls se vc estiver usando windows
#else
    system("clear"); // limpa terminal do linux/mac
#endif
};

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // limpa o buffer direito - esse eu tive que pesquisar no stackoverflow, minha nossa senhora, fflush tava dando tanta dor de cabeca que me fez repensar sobre minha existencia
};

void irMenu()
{
    do
    {
        printf("C.R.U.D. SIMPLES - AGENDA TELEFONICA\n\n");
        printf("/!\\ Atencao: para visualizacao ideal, por favor, maximize a janela do seu terminal!\n\n");
        printf("+--------------------------------+\n");
        printf("                                 |\n[ 1 ] - Consultar lista          |\n[ 2 ] - Cadastrar contato        |\n[ 3 ] - Editar contato           |\n[ 4 ] - Excluir contato          |\n[ 5 ] - Sair da lista telefonica |\n                                 |\n");
        printf("+--------------------------------+\n");
        printf(("\nEscolha a opcao desejada: "));
        scanf("%i", &escolhaMenu);
        limparBuffer();
        if (escolhaMenu < 1 || escolhaMenu > 5)
        {
            limparTela();
            printf("\n/!\\ OPCAO INVALIDA. Insira uma opcao novamente.\n\n");
        };
    } while (escolhaMenu < 1 || escolhaMenu > 5);
};

void consultarLista()
{
    limparTela();

    // impressao da tabela bonitinha
    printf("+---------------------------------------------------------------------------------------------+");
    printf("\n|                                        CONSULTA DADOS                                       |");
    printf("\n|                                                                                             |");
    printf("\n| %-5s %-40s %-40s |", " ID ", "                  NOME", "                   TELEFONE                 ");
    printf("\n|---------------------------------------------------------------------------------------------|");
    if (totalContatos == 0)
    {
        printf("\n\n", "/!\\ A agenda esta vazia.");
    }

    for (int i = 0; i < totalContatos; i++)
    {
        idContato = i + 1;
        printf("\n| %-3i | %-40s | %-40s   |", idContato, tabelaDados[i][0], tabelaDados[i][1]);
    };
    printf("\n+---------------------------------------------------------------------------------------------+\n");

    printf("\nPressione ENTER para voltar ao menu.");
    getchar(); // espera o enter
};

void cadastraContato()
{
    limparTela();

    int numContato = totalContatos;
    printf("/!\\ Atencao: Nao utilize espacos ao digitar nome ou telefone!\nUtilize hifen ('-') ou underline ('_') como alternativa.\n\nO maximo de letras/numero por campo e de 40 digitos.\n\n");
    printf("+---------------------------------------------------------------------------------------------+");
    printf("\n|                                     CADASTRO DE CONTATO                                     |");
    printf("\n+---------------------------------------------------------------------------------------------+");
    printf("\n\nDigite o NOME do contato (nao utilize espacos!): ");
    scanf("%39s", tabelaDados[numContato][0]); // nome (ignora tudo que vier apos o 39o digito)
    limparBuffer();
    int somenteNumero;
    do
    {
        somenteNumero = 1;
        printf("\n\nDigite o TELEFONE do contato (somente numeros): ");
        scanf("%39s", tabelaDados[numContato][1]); // telefone (ignora tudo que vier apos o 39o digito)
        limparBuffer();
        int i = 0;
        while (tabelaDados[numContato][1][i] != '\0') // ve se o campo nao ta vazio
        {
            if (tabelaDados[numContato][1][i] < '0' || tabelaDados[numContato][1][i] > '9') // gambiarra nao, adaptacao tecnica!
            {
                somenteNumero = 0;
                break;
            }
            i++;
        }
    } while (somenteNumero == 0);
    limparTela();
    if (totalContatos >= MAX_CONTATOS)
    {
        printf("\n/!\\ Voce atingiu o maximo de contatos. Exclua algum contato para realizar um novo cadastro.\n");
        printf("\nPressione ENTER para voltar ao menu.");
        getchar();
        return 0;
    }
    totalContatos++;
    salvaDados();

    // impressao da tabela bonitinha
    printf("+---------------------------------------------------------------------------------------------+");
    printf("\n|                                CONSULTA DADOS (POS CADASTRO)                                |");
    printf("\n|                                                                                             |");
    printf("\n| %-5s %-40s %-40s |", " ID ", "                  NOME", "                   TELEFONE                 ");
    printf("\n|---------------------------------------------------------------------------------------------|");
    for (int i = 0; i < 100; i++)
    {
        if (tabelaDados[i][0][0] == '\0') // \0 eh "vazio", se a matriz estiver vazia ele vai printar so o cabecalho e rodape
        {
            break;
        }

        idContato = i + 1;
        printf("\n| %-3i | %-40s | %-40s   |", idContato, tabelaDados[i][0], tabelaDados[i][1]);
    };
    printf("\n+---------------------------------------------------------------------------------------------+");
    printf("\n\n[OK] Cadastro realizado com sucesso!");
    printf("\nPressione ENTER para voltar ao menu.");
    getchar();
};

void editarContato()
{
    limparTela();
    if (totalContatos == 0)
    {
        printf("\n\n/!\\ Nao ha contatos para editar. Voce deve efetuar um cadastro primeiro.");
        printf("\nPressione ENTER para voltar ao menu.");
        getchar();
        return;
    }

    // impressao da tabela bonitinha
    do
    {
        limparTela();
        printf("+---------------------------------------------------------------------------------------------+");
        printf("\n|                                       EDITAR CONTATO                                         |");
        printf("\n+---------------------------------------------------------------------------------------------+");
        printf("\n|                                                                                             |");
        printf("\n| %-5s %-40s %-40s |", " ID ", "                  NOME", "                   TELEFONE                 ");
        printf("\n|---------------------------------------------------------------------------------------------|");

        for (int i = 0; i < totalContatos; i++)
        {
            printf("\n| %-3i | %-40s | %-40s   |", i + 1, tabelaDados[i][0], tabelaDados[i][1]);
        }

        printf("\n+---------------------------------------------------------------------------------------------+");
        printf("\n\nDigite o ID do contato que deseja editar: ");
        scanf("%i", &idEscolhido);
        limparBuffer();

    } while (idEscolhido <= 0 || idEscolhido > totalContatos);
    limparTela();

    int idParaEdit = idEscolhido-1;
    printf("+---------------------------------------------------------------------------------------------+");
    printf("\n|                                       EDITAR CONTATO                                       |");
    printf("\n+---------------------------------------------------------------------------------------------+");

    printf("\n\nNome atual: %s", tabelaDados[idParaEdit][0]);
    printf("\nDigite o novo NOME (sem espacos): ");
    scanf("%39s", tabelaDados[idParaEdit][0]);
    limparBuffer();

    int somenteNumero; // reciclagem de codigo
    do
    {
        somenteNumero = 1;
        printf("\nTelefone atual: %s", tabelaDados[idParaEdit][1]);
        printf("\nDigite o novo TELEFONE (somente numeros): ");
        scanf("%39s", tabelaDados[idParaEdit][1]);
        limparBuffer();

        int i = 0;
        while (tabelaDados[idParaEdit][1][i] != '\0')
        {
            if (tabelaDados[idParaEdit][1][i] < '0' || tabelaDados[idParaEdit][1][i] > '9')
            {
                somenteNumero = 0;
                break;
            }
            i++;
        }

    } while (somenteNumero == 0);

    salvaDados();

    printf("\n\n[OK] Contato editado com sucesso!");
    printf("\nPressione ENTER para voltar ao menu.");
    getchar();

};

void excluirContato()
{
    limparTela();
    if (totalContatos == 0)
    {
        printf("\n/!\\ Nao ha contatos para excluir. Voce deve efetuar um cadastro primeiro.");
        printf("\nPressione ENTER para voltar ao menu.");
        getchar();
        return;
    }

    do
    {
        limparTela();
        // impressao da tabela bonitinha
        printf("+---------------------------------------------------------------------------------------------+");
        printf("\n|                                     EXCLUSAO DE CONTATO                                     |");
        printf("\n+---------------------------------------------------------------------------------------------+");
        printf("\n|                                                                                             |");
        printf("\n| %-5s %-40s %-40s |", " ID ", "                  NOME", "                   TELEFONE                 ");
        printf("\n|---------------------------------------------------------------------------------------------|");
        for (int i = 0; i < totalContatos; i++)
        {
            if (tabelaDados[i][0][0] == '\0') // \0 eh "vazio", se a matriz estiver vazia ele vai printar so o cabecalho e rodape
            {
                break;
            }

            idContato = i + 1;
            printf("\n| %-3i | %-40s | %-40s   |", idContato, tabelaDados[i][0], tabelaDados[i][1]);
        };
        printf("\n+---------------------------------------------------------------------------------------------+");
        printf("\n\n/!\\ ATENCAO: A exclusao de um contato NAO E REVERSIVEL! Certifique-se de inserir o ID correto!\nDigite o ID do contato a excluir: ");
        scanf("%i", &idEscolhido);
        limparBuffer();
    } while (idEscolhido <= 0 || idEscolhido > totalContatos);

    for (int i = idEscolhido - 1; i < totalContatos - 1; i++) // desloca todos os ids um numero pra tras, assim nao tem ordem bizarra (tipo 1,2,4,7)
    {                                                         // se nao usar o -1 ele deleta o da frentekkkkkkkkkkkk descobri do pior jeito (perdi meia hora nisso
        strcpy(tabelaDados[i][0], tabelaDados[i + 1][0]);
        strcpy(tabelaDados[i][1], tabelaDados[i + 1][1]);
    }
    totalContatos--;

    salvaDados();

    printf("\n\n[OK] Contato excluido com sucesso!\n");
    printf("\nPressione ENTER para voltar ao menu.");
    getchar();
};

int main(void)
{
    carregaDados();
    while (1)
    {
        limparTela(); // comente pra visualizar a mensagem de debug sobre o carregamento dos dados
        irMenu();

        switch (escolhaMenu)
        {
        case 1:
            consultarLista();
            break;
        case 2:
            cadastraContato();
            break;
        case 3:
            editarContato();
            break;
        case 4:
            excluirContato();
            break;
        case 5:
            limparTela();
            printf("\n\nOpcao escolhida: sair da lista telefonica\nEncerrando programa...\n\n");
            printf("----------------------------------\n\n");
            return 0;
        }
    }
};