#include <stdio.h>
#include <string.h>

void menu_inicial(){
    printf("\n================================\n");
    printf("   Controle de Estoque\n");
    printf("================================\n");
    printf("Selecione uma opcao:\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item\n");
    printf("3. Listar Estoque\n");
    printf("4. Sair\n");
    printf("Opcao: ");
}

int operacao_do_estoque (){
    int opcao_do_estoque;

    scanf("%d", &opcao_do_estoque);
    printf("\n");

    while (opcao_do_estoque < 1 || opcao_do_estoque > 4) {
        printf("Opcao invalida! Tente novamente: ");
        scanf("%d", &opcao_do_estoque);
        printf("\n");
    }
    
    return opcao_do_estoque;
}

void adicionar_item(){
    char item[100]; 
    int quantidade;

    FILE *arquivo;
    arquivo = fopen("estoque.txt","a"); 

    printf("Digite o nome do item: "); 
    scanf("%s", item);
    printf("Digite a quantidade: "); 
    scanf("%d", &quantidade);
    printf("\nItem adicionado com sucesso!\n"); 

    fprintf(arquivo, "%s\n", item);
    fprintf(arquivo, "%d\n", quantidade);
    fclose(arquivo);
}

void remover_item(){
    char item[100]; 
    int quantidade;
    int quantidade_lida;
    int encontrou_item = 0;
    char buffer_nome[100]; 
    char buffer_quantidade[50];

    FILE *arquivo;
    arquivo = fopen("estoque.txt","r"); 
    FILE *arquivo_temporario;
    arquivo_temporario = fopen("estoque_temporario.txt", "w");

    if (arquivo == NULL || arquivo_temporario == NULL) {
        printf("Erro ao abrir os arquivos de estoque.\n");
        return;
    }

    printf("Digite o nome do item: "); 
    scanf("%s", item);
    printf("Digite a quantidade a ser removida: "); 
    scanf("%d", &quantidade);
    printf("\n");

    while (fgets(buffer_nome, sizeof(buffer_nome), arquivo)) {
        if (fgets(buffer_quantidade, sizeof(buffer_quantidade), arquivo)) {
            
            buffer_nome[strcspn(buffer_nome, "\n")] = 0;
            quantidade_lida = atoi(buffer_quantidade); 

            if (strcmp(buffer_nome, item) == 0) {
                encontrou_item = 1;

                if (quantidade > quantidade_lida) {
                    printf("Estoque insuficiente. Quantidade disponivel: %d\n", quantidade_lida);
                    fprintf(arquivo_temporario, "%s\n%d\n", buffer_nome, quantidade_lida);
                } 
                else if (quantidade_lida - quantidade == 0) {
                    printf("Item removido do estoque!\n");
                    continue; 
                } 
                else {
                    quantidade_lida -= quantidade;
                    fprintf(arquivo_temporario, "%s\n%d\n", buffer_nome, quantidade_lida);
                    printf("Quantidade atualizada com sucesso!\n");
                }
            } else {
                fprintf(arquivo_temporario, "%s\n%d\n", buffer_nome, quantidade_lida);
            }
        }
    }

    if (!encontrou_item) {
        printf("Item nao encontrado.\n");
    }

    fclose(arquivo);
    fclose(arquivo_temporario);

    remove("estoque.txt");
    rename("estoque_temporario.txt", "estoque.txt");
}

void listar_estoque(){
    char item[100];
    int quantidade;
    int linhas_lidas = 0;

    FILE *arquivo;
    arquivo = fopen("estoque.txt","r"); 

    while (fscanf(arquivo, "%s %d", item, &quantidade) == 2) {
        if (linhas_lidas == 0) {
            printf("=============================\n");
            printf("        Estoque Atual\n");       
            printf("=============================\n");
        }
        printf("\nNome: %s\n", item);
        printf("Quantidade: %d\n", quantidade);
        linhas_lidas++;
    }

    if (linhas_lidas == 0) {
        printf("O estoque esta vazio\n");
    }
}

int questionamento(){
    char afirmacao;

    printf("\nDeseja realizar outra operacao? (s/n): ");
    scanf(" %c", &afirmacao);

    if (afirmacao == 's'){
        return 1;
    } else if (afirmacao == 'n'){
        printf ("\nObrigado por usar o Controle de Estoques! Ate a proxima.");
        return 0;
    }
    return 0;
}

void estrutura_switch(int escolha_do_usuario) {
    switch (escolha_do_usuario) {
        case 1:
            adicionar_item();
            break;
        case 2:
            remover_item();
            break;
        case 3:
            listar_estoque();
            break;
        case 4:
            break;
    }
}

int main() {
    int escolha_do_usuario;
    int loop;

    do {
        menu_inicial();
        escolha_do_usuario = operacao_do_estoque();

        if (escolha_do_usuario == 4){
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.");
            break;
        }

        estrutura_switch(escolha_do_usuario);

        loop = questionamento();

    } while (loop == 1);
    return 0;
}