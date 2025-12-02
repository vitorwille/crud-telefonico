/*
    CRUD - Agenda telefonica (nome+contato)

    Trabalho em grupos de 5 pessoas
    Professor Manfred Heil Junior

    Alunos: Sarah Enaile Braga da Silva; Vitor Hugo Wille; TODO: Adicionar restante.

*/

#include <stdio.h>
#include <string.h>

int escolhaMenu;
char tabelaDados[100][2][40]; // 100 linhas, 2 colunas (nome e telefone), 40 caracteres cada campo

int main(void)
{
    while (1)
    {
        limparTela();
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
            printf("\n\nOpcao escolhida: sair da lista telefonica\nEncerrando programa...\n\n");
            return 0;
        }
    }
}

void limparTela()
{
    for (int i = 0; i < 50; i++)
    {
        printf("\n"); // limpar tela
    };
};

void irMenu()
{
    do
    {
        printf("CRUD SIMPLES - AGENDA TELEFONICA\n\n");
        printf("+--------------------------------+\n");
        printf("                                 |\n[ 1 ] - Consultar lista          |\n[ 2 ] - Cadastrar contato        |\n[ 3 ] - Editar contato           |\n[ 4 ] - Excluir contato          |\n[ 5 ] - Sair da lista telefonica |\n                                 |\n");
        printf("+--------------------------------+\n");
        printf(("\nEscolha a opcao desejada: "));
        scanf("%i", &escolhaMenu);
        fflush(stdin);
        if (escolhaMenu < 1 || escolhaMenu > 5)
        {
            printf("\n/!\\ OPCAO INVALIDA. Insira uma opcao novamente.\n\n");
        };
    } while (escolhaMenu < 1 || escolhaMenu > 5);
};

void consultarLista()
{
    limparTela();
    strcpy(tabelaDados[0][0], "SarahEnaileBragaDaSilva");
    strcpy(tabelaDados[0][1], "11987654321");
    strcpy(tabelaDados[1][0], "VitorHugoWille");
    strcpy(tabelaDados[1][1], "11912345678");

    // impressao da tabela bonitinha
    printf("+-------------------------------------------------------------------------------------+");
    printf("\n|                                   CONSULTA DADOS                                    |");
    printf("\n|                                                                                     |");
    printf("\n| %-40s   %-40s |", "                  NOME", "                TELEFONE");
    printf("\n|-------------------------------------------------------------------------------------|");
    for (int i = 0; i < 100; i++)
    {
        if (tabelaDados[i][0][0] == '\0') // \0 eh "vazio", se a matriz estiver vazia ele vai printar so o cabecalho e rodape
        {
            break;
        }

        printf("\n| %-40s | %-40s |", tabelaDados[i][0], tabelaDados[i][1]);
    };
    printf("\n+-------------------------------------------------------------------------------------+");
    printf("\n\nPressione ENTER para voltar ao menu.");
    getchar(); // eu tive que usar 2x, se nao ele simplesmente ignora a solicitaçao de input. honestamente, nao sei o que aconteceu kkkkkk
    getchar(); // se vc usar uma vez so, ele fica em loop eterno.                     "Não é bug, é feature." -Alan Turing
};

void cadastraContato()
{
    limparTela();
    printf("eles estao de olho em nois da silva (cadastro)");

    /*
    scanf(" %s[^\n]", tabelaDados[linha][0]); //nome - permite espaço
    scanf(" %39[^\n]", tabelaDados[linha][1]); //telefone - permite espaço

    scanf("%s", &tabelaDados[0][1]);
    fflush(stdin);
    scanf("%s", &tabelaDados[1][2]);
    fflush(stdin);
    scanf("%s", &tabelaDados[1][1]);
    fflush(stdin);
    scanf("%s", &tabelaDados[2][2]);
    fflush(stdin);
    */

    // impressao da tabela bonitinha
    printf("\n+-------------------------------------------------------------------------------------+");
    printf("\n| %-40s | %-40s |", "NOME", "TELEFONE");
    printf("\n|-------------------------------------------------------------------------------------|");
    for (int i = 0; i < 100; i++)
    {
        if (tabelaDados[i][0][0] == '\0') // \0 eh "vazio", se a matriz estiver vazia ele vai printar so o cabecalho e rodape
        {
            break;
        }

        printf("\n| %-40s | %-40s |", tabelaDados[i][0], tabelaDados[i][1]);
    };
    printf("\n+-------------------------------------------------------------------------------------+");
    printf("\n\nPressione ENTER para voltar ao menu.");
    getchar();
    getchar(); // socorro...
};

void editarContato()
{
    limparTela();
    printf("catapimbas! (edicao)");
};

void excluirContato()
{
    limparTela();
    printf("vish (exclusao)");
};