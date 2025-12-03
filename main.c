/*
    C.R.U.D. - Agenda telefonica (nome+contato)

    Trabalho em grupos de 5 pessoas
    Professor Manfred Heil Junior

    Alunos: Sarah Enaile Braga da Silva; Vitor Hugo Wille; TODO: Adicionar restante.

*/

/*
    TODO: - "Embelezar" o modulo de cadastro (atualmente ta bem feio)
          - Implementar funçao de edicao
          - Implementar funçao de exclusao
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_CONTATOS 100
#define MAX_CARACTERES 40
#define ARQUIVO_DADOS "dadosAgenda.vhw"

int escolhaMenu;
char tabelaDados[100][2][40]; // 100 linhas, 2 colunas (nome e telefone), 40 caracteres cada campo
int totalContatos = 0;

void carregaDados()
{
    // eh minha primeira vez lidando com salvamento/carregamento de arquivo - desculpe se tiver meio zuado, professor =)
    FILE *dadosAgenda = fopen(ARQUIVO_DADOS, "r"); // define variavel e abre pra read-only

    if (dadosAgenda == NULL)
    {
        totalContatos = 0;
        printf("\n[DEBUG] Arquivo de dados nao encontrado. Iniciando agenda vazia.\n"); //atencao: pra essa mensagem aparecer, nao pode ter limpatela no main!
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
        fprintf(dadosAgenda, "%s %s\n", tabelaDados[i][0], tabelaDados[i][1]); // coloca todos os dados no arquivo e separa os campos por espaço
    }

    fclose(dadosAgenda);
}

void limparTela()
{
#ifdef _WIN32
    system("cls"); // limpa cmd com tls se vc estiver usando windows
#else
    system("clear"); // limpa terminal do linux/mac
#endif
};

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // limpa o buffer direito - esse eu tive que pesquisar no stackoverflow, minha nossa senhora, fflush tava dando cada b.o que me fez repensar minha existencia
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
            printf("\n/!\\ OPCAO INVALIDA. Insira uma opcao novamente.\n\n");
        };
    } while (escolhaMenu < 1 || escolhaMenu > 5);
};

void consultarLista()
{
    limparTela();

    // impressao da tabela bonitinha
    printf("+-------------------------------------------------------------------------------------+");
    printf("\n|                                   CONSULTA DADOS                                    |");
    printf("\n|                                                                                     |");
    printf("\n| %-40s   %-40s |", "                  NOME", "                TELEFONE");
    printf("\n|-------------------------------------------------------------------------------------|");
    if (totalContatos == 0)
    {
        printf("\n\n", "A agenda esta vazia.");
    }

    for (int i = 0; i < totalContatos; i++)
    {
        printf("\n| %-40s | %-40s |", tabelaDados[i][0], tabelaDados[i][1]);
    };
    printf("\n+-------------------------------------------------------------------------------------+\n");

    printf("\n\nPressione ENTER para voltar ao menu.");
    getchar(); // depois de bilhoes de horas gastas, eu aprendi a limpar buffer sem usar o fflush (ele tava bugando tudo
};

void cadastraContato()
{
    limparTela();

    int numContato = totalContatos;
    printf("/!\\ Atencao: Nao utilize espacos ao digitar nome ou telefone!\nUtilize hifen ('-') ou underline ('_') como alternativa.\n\nO maximo de letras/numero por campo e de 40 digitos.\n\n");
    printf("+-------------------------------------------------------------------------------------+");
    printf("\n|                                  CADASTRO DE CONTATO                                |");
    printf("\n+-------------------------------------------------------------------------------------+");
    printf("\n\nDigite o NOME do contato (nao utilize espacos!): ");
    scanf("%39s", tabelaDados[numContato][0]); // nome (ignora tudo que vier apos o 40o digito)
    limparBuffer();
    int somenteNumero;
    do
    {
        somenteNumero = 1;
        printf("\n\nDigite o TELEFONE do contato (somente numeros): ");
        scanf("%39s", tabelaDados[numContato][1]);
        limparBuffer();
        int i = 0;
        while (tabelaDados[numContato][1][i] != '\0') // ve se o campo nao ta vazio
        {
            if (tabelaDados[numContato][1][i] < '0' || tabelaDados[numContato][1][i] > '9') // se nao conter numero...
            {
                somenteNumero = 0;
                break;
            }
            i++;
        }
    } while (somenteNumero == 0);
    limparTela();
    printf("[OK] Cadastro realizado com sucesso!\n\n");
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
    printf("+-------------------------------------------------------------------------------------+");
    printf("\n|                            CONSULTA DADOS (POS CADASTRO)                            |");
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
    getchar();
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

int main(void)
{
    carregaDados();
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
            limparTela();
            printf("\n\nOpcao escolhida: sair da lista telefonica\nEncerrando programa...\n\n");
            printf("----------------------------------\n\n");
            return 0;
        }
    }
};