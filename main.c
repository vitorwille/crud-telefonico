/*
    CRUD - Agenda telefonica (nome+contato)

    Trabalho em grupos de 5 pessoas
    Professor Manfred Heil Junior

    Alunos: Sarah Enaile Braga da Silva; Vitor Hugo Wille; TODO: Adicionar restante.

*/

#include <stdio.h>
#include <string.h>

#define MAX_CONTATOS 100
#define MAX_CARACTERES 40
#define ARQUIVO_DADOS "dadosAgenda.txt"

int escolhaMenu;
char tabelaDados[100][2][40]; // 100 linhas, 2 colunas (nome e telefone), 40 caracteres cada campo
int totalContatos = 0;

int main(void)
{
    carregaDados();
    while (1)
    {
        // limparTela();
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
};

void carregaDados()
{
    // eh minha primeira vez lidando com salvamento/carregamento de arquivo - desculpe se tiver meio zuado, professor =)
    FILE *dadosAgenda = fopen(ARQUIVO_DADOS, "r"); // define variavel e abre pra read-only

    if (dadosAgenda == NULL)
    {
        // Se o arquivo não existe, a agenda começa vazia.
        totalContatos = 0;
        printf("\n/!\\ Arquivo de dados nao encontrado. Iniciando agenda vazia.\n");
        // Não precisa fechar, pois ele não foi aberto
        return; 
    }

    totalContatos = 0; 
    
    // Loop para ler dados do arquivo
    // fscanf() retorna o número de itens lidos com sucesso (esperamos 2: Nome e Telefone)
    while (fscanf(dadosAgenda, "%s %s", tabelaDados[totalContatos][0], tabelaDados[totalContatos][1]) == 2)
    { 
        totalContatos++;
        if (totalContatos >= MAX_CONTATOS){
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
            printf("\n/!\\ Erro: Nao foi possivel salvar o arquivo de dados. Verifique as permissoes de acesso ao arquivo.\n");
            return;
        }
        for (int i = 0; i < totalContatos; i++)
        {
            fprintf(dadosAgenda, "%s %s\n", tabelaDados[i][0], tabelaDados[i][1]); // coloca todos os dados no arquivo e separa os campos por , (vira csv)
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

    void irMenu()
    {
        do
        {
            printf("CRUD SIMPLES - AGENDA TELEFONICA\n");
            printf("/!\\ Atencao: para visualizacao ideal, por favor, maximize a janela do seu terminal!\n\n");
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
        getchar(); // eu tive que usar 2x, se nao ele simplesmente ignora a solicitaçao de input. honestamente, nao sei o que aconteceu kkkkkk
        getchar(); // se vc usar uma vez so, ele fica em loop eterno.                     "Não é bug, é feature." -Alan Turing
    };

    void cadastraContato()
    {
        limparTela();
        printf("eles estao de olho em nois da silva (cadastro)");

        if (totalContatos >= MAX_CONTATOS)
        {
            printf("\n/!\\ Voce atingiu o maximo de contatos. Exclua algum contato para realizar um novo cadastro.\n");
            printf("\nPressione ENTER para voltar ao menu.");
            getchar(); // socorro.com.br
            getchar();
            return 0;
        }

        int numContato = totalContatos;

        scanf("%s", tabelaDados[numContato][0]); // nome
        scanf("%s", tabelaDados[numContato][1]); // telefone

        totalContatos++;
        salvaDados();

        /*
        scanf(" %s[^\n]", tabelaDados[linha][0]); //nome - permite espaço
        scanf(" %s[^\n]", tabelaDados[linha][1]); //telefone - permite espaço

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
        printf("\n+-----------------------------------------------------// lê até a vírgula e até o fim da linha--------------------------------+");
        printf("\n\nPressione ENTER para voltar ao menu.");
        getchar();
        getchar(); // socorro 2.0
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