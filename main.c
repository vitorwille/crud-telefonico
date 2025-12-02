/*
    CRUD - Agenda telefônica (nome+contato)

    Trabalho em grupos de 5
    Professor Manfred Heil Junior

    Alunos: Sarah Enaile Braga da Silva; Vitor Hugo Wille; TODO: Adicionar restante.

*/

#include <stdio.h>

int escolhaMenu;
char tabelaDados[100][2];

int main(void){

    for(int i=0; i<50; i++){
            printf("\n"); //limpar tela
    };

    do{

        printf("CRUD SIMPLES - AGENDA TELEFONICA\n\n");
        printf("+--------------------------------+\n");
        printf("                                 |\n[ 1 ] - Consultar lista          |\n[ 2 ] - Cadastrar contato        |\n[ 3 ] - Editar contato           |\n[ 4 ] - Excluir contato          |\n[ 5 ] - Sair da lista telefonica |\n                                 |\n");
        printf("+--------------------------------+\n");
        printf(("\nEscolha a opcao desejada: "));
        scanf("%i",&escolhaMenu);
        fflush(stdin);
        if(escolhaMenu < 1 ||  escolhaMenu > 5){
            printf("\n/!\\ OPCAO INVALIDA. Insira uma opcao novamente.\n\n");
        };
    }while(escolhaMenu < 1 ||  escolhaMenu > 5);

    void consultarLista(){
        for(int i=0; i<50; i++){
            printf("\n");   //limpa tela
        };
        printf("teste da silva (consulta)");
    };

    void cadastraContato(){
        for(int i=0; i<50; i++){
            printf("\n");   //limpa tela
        };
        printf("eles estao de olho em nois da silva (cadastro)");
    };

    void editarContato(){
        for(int i=0; i<50; i++){
            printf("\n");   //limpa tela
        };
        printf("catapimbas! (edicao)");
    };

    void excluirContato(){
        for(int i=0; i<50; i++){
            printf("\n");   //limpa tela
        };
        printf("vish (exclusao)");
    };

    switch(escolhaMenu){
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
            break;
    }

    return 0;
}