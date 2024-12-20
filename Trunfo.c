#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char nome[50];
    char letra;
    int numero;
    char superTrunfo[6];
    int vida;         // em corações
    float dano;       // em corações
    float altura;     // em blocos
    float velocidade; // blocos/tique
} Carta;              // Cartas

int funcao_tamanho(FILE *fp)
{ 
    int quantidade_linhas = 1;
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
        { // Cada nova linha é identificada por '\n'
            quantidade_linhas++;
        } // if
    } // while

    fseek(fp, 0, SEEK_SET); // reinicia o cursor para o começo do codigo

    return quantidade_linhas;
}//funcao_tamanho

void inserir_carta(Carta cartas[], int tamanho)
{
    FILE *fp = fopen("../cartas.csv", "a");
  
    char nome[50];
    char letra;
    int numero;
    int vida;         // em corações
    float dano;       // em corações
    float altura;     // em blocos
    float velocidade; // blocos/tique
    int salvo = 0;

    setbuf(stdin, NULL);
    printf("Digite o nome da carta:\n");
    fgets(nome, 50, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    do
    {
        printf("Digite qual letra que adicionar(de A a D):\n");
        scanf("%c", &letra);
    } while (letra < 'A' || letra > 'D');

    for (int i = 0; i < tamanho; i++)
    {
        if (cartas[i].letra == letra)
        {
            if (cartas[i].numero > salvo)
            {
                salvo = cartas[i].numero;
            } // if
        } // if
    } // if

    do
    {
        printf("Digite qual numero quer adicionar(maior que 9):\n");
        scanf("%d", &numero);
    } while (numero < salvo);

    printf("Digite qual vida:\n");
    scanf("%d", &vida);

    printf("Digite qual Dano:\n");
    scanf("%f", &dano);

    printf("Digite qual altura:\n");
    scanf("%f", &altura);

    printf("Digite qual velocidade:\n");
    scanf("%f", &velocidade);

    fprintf(fp, "\n%s,%c,%d,false,%d,%.2f,%.2f,%.2f",
            nome,
            letra,
            numero,
            vida,
            dano,
            altura,
            velocidade);

    fclose(fp);

} // inserirCarta

void listar_as_cartas(Carta cartas[], int tamanho)
{
    printf("listas das cartas:\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
               cartas[i].nome,
               cartas[i].letra,
               cartas[i].numero,
               cartas[i].superTrunfo,
               cartas[i].vida,
               cartas[i].dano,
               cartas[i].altura,
               cartas[i].velocidade);
    } // listar cartas
}

void pesquisar_cartas(Carta cartas[], int tamanho)
{
    int numero;

    // força o usuario a digitar certo
    do
    {
        printf("Digite um numero de 1 a 7: \n");
        printf("1-Nome\n2-Letra\n3-Numero\n4-Vida\n5-Dano\n6-Altura\n7-Velocidade\n");
        scanf("%d", &numero);
        setbuf(stdin, NULL);
    } while (numero < 1 || numero > 7);

    switch (numero)
    {
    case 1:
    {
        char texto[51];
        printf("Digite o nome da Carta:");
        fgets(texto, 51, stdin);
        texto[strcspn(texto, "\n")] = '\0'; // Remove a quebra de linha

        for (int i = 0; i < tamanho; i++)
        {
            if (strcasecmp(texto, cartas[i].nome) == 0)
            {

                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 1
    case 2:
    {
        char c;
        printf("Digite uma letra entre A e D :");
        scanf("%c", &c);
        for (int i = 0; i < tamanho; i++)
        {
            if (c == cartas[i].letra)
            {
                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 2
    case 3:
    {
        int numero;
        printf("digite o numero da carta :");
        scanf("%d", &numero);
        for (int i = 0; i < tamanho; i++)
        {
            if (numero == cartas[i].numero)
            {
                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 3
    case 4:
    {
        float vida;
        printf("digite a vida: ");
        scanf("%f", &vida);
        for (int i = 0; i < tamanho; i++)
        {
            if (vida == cartas[i].vida)
            {
                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 4
    case 5:
    {
        float dano;
        printf("digite o dano:");
        scanf("%f", &dano);
        for (int i = 0; i < tamanho; i++)
        {
            if (dano == cartas[i].dano)
            {
                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 5
    case 6:
    {
        float altura;
        printf("digite o altura:");
        scanf("%f", &altura);
        for (int i = 0; i < tamanho; i++)
        {
            if (altura == cartas[i].altura)
            {
                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 6
    case 7:
    {
        float velocidade;
        printf("digite o velocidade:");
        scanf("%f", &velocidade);
        for (int i = 0; i < tamanho; i++)
        {
            if (velocidade == cartas[i].velocidade)
            {
                printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas[i].nome,
                       cartas[i].letra,
                       cartas[i].numero,
                       cartas[i].superTrunfo,
                       cartas[i].vida,
                       cartas[i].dano,
                       cartas[i].altura,
                       cartas[i].velocidade);
            } // if
        } // for
        break;
    } // case 7
    default:
        printf("erro na digitação do numero tente novamente");
        break;
    } // swith

} // listar as cartas

void salvar_cartas_no_arquivo(Carta cartas[], int tamanho)
{
    FILE *fp = fopen("../cartas.csv", "w");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    } // if

    for (int i = 0; i < tamanho; i++)
    {
            //Confere se é o último indice 
            if(i == tamanho - 1){
                //Confere se é o Super Trunfo para salvar == true
                if(strcasecmp("Herobrine",cartas[i].nome)== 0){
                    fprintf(fp, "%s,%c,%d,true,%d,%.2f,%.2f,%.2f",
                            cartas[i].nome,
                            cartas[i].letra,
                            cartas[i].numero,
                            cartas[i].vida,
                            cartas[i].dano,
                            cartas[i].altura,
                            cartas[i].velocidade);  
                    }else{
                        fprintf(fp, "%s,%c,%d,false,%d,%.2f,%.2f,%.2f",
                                cartas[i].nome,
                                cartas[i].letra,
                                cartas[i].numero,
                                cartas[i].vida,
                                cartas[i].dano,
                                cartas[i].altura,
                                cartas[i].velocidade);
                    }//else
            }else{
           
            fprintf(fp, "%s,%c,%d,false,%d,%.2f,%.2f,%.2f\n",
                    cartas[i].nome,
                    cartas[i].letra,
                    cartas[i].numero,
                    cartas[i].vida,
                    cartas[i].dano,
                    cartas[i].altura,
                    cartas[i].velocidade);
            }
    } // for
   
    fclose(fp);
} // salvar_cartas_no_arquivo

void alterar_carta(Carta cartas[], int tamanho)
{

    char nome_procurado[50];
    int numero;
    int indice_carta_alterar = -1;

    printf("Digite qual carta deseja alterar:\n");
    fgets(nome_procurado, 49, stdin);
    nome_procurado[strcspn(nome_procurado, "\n")] = '\0';

    // Confere se a carta que deseja alterar não é o super trunfo
    if (strcasecmp(nome_procurado, "Herobrine") == 0)
    {
        printf("Essa carta não pode ser alterada!\n");
        return;
    } // if

    // Procura carta
    for (int i = 0; i < tamanho; i++)
    {
        if (strcasecmp(nome_procurado, cartas[i].nome) == 0)
        {
            indice_carta_alterar = i;
        } // if
    } // for

    // Confere se o que foi digitado existe nas cartas
    if (indice_carta_alterar == -1)
    {
        printf("Carta não encontrada.\n");
        return;
    } // if

    printf("Digite qual atributo deseja modificar:\n1-Nome\n2-Vida\n3-Dano\n4-Altura\n5-Velocidade\n");
    scanf("%d", &numero);
    setbuf(stdin, NULL);

    switch (numero)
    {
    case 1:
    {
        char novo_nome[50];

        printf("Digite o nome para qual deseja alterar:\n");
        fgets(novo_nome, 51, stdin);
        novo_nome[strcspn(novo_nome, "\n")] = '\0';
        setbuf(stdin, NULL);

        strcpy(cartas[indice_carta_alterar].nome, novo_nome);

        salvar_cartas_no_arquivo(cartas, tamanho);
        printf("Alteração salva com sucesso.\n");

        break;
    } // case 1
    case 2:
    {
        int nova_vida;
        // Pede ao usuário um valor válido(maior que zero e menor que o do super trunfo)
        do
        {
            printf("Digite a quantidade de vida que deseja alterar:\n");
            scanf("%d", &nova_vida);
            setbuf(stdin, NULL);

        } while (nova_vida > 300 || nova_vida < 0);

        cartas[indice_carta_alterar].vida = nova_vida;

        salvar_cartas_no_arquivo(cartas, tamanho);
        printf("Alteração salva com sucesso.\n");

        break;
    } // case 2
    case 3:
    {
        float novo_dano;
        printf("Digite a quantidade de dano que deseja alterar:\n");
        scanf("%f", &novo_dano);
        setbuf(stdin, NULL);

        cartas[indice_carta_alterar].dano = novo_dano;

        salvar_cartas_no_arquivo(cartas, tamanho);
        printf("Alteração salva com sucesso.\n");

        break;
    } // case 3
    case 4:
    {
        float nova_altura;
        printf("Digite a quantidade de dano que deseja alterar:\n");
        scanf("%f", &nova_altura);
        setbuf(stdin, NULL);

        cartas[indice_carta_alterar].altura = nova_altura;

        salvar_cartas_no_arquivo(cartas, tamanho);
        printf("Alteração salva com sucesso.\n");

        break;
    } // case 4
    case 5:
    {
        float nova_velocidade;
        printf("Digite a quantidade de dano que deseja alterar:\n");
        scanf("%f", &nova_velocidade);
        setbuf(stdin, NULL);

        cartas[indice_carta_alterar].altura = nova_velocidade;

        salvar_cartas_no_arquivo(cartas, tamanho);
        printf("Alteração salva com sucesso.\n");

        break;
    } // case 5
    default:
        printf("Erro na digitação do numero tente novamente!\n");
        break;
    } // switch

} // alterar_cartas

void excluir_carta(Carta cartas[], int tamanho)
{

    char nome_procurado[50];
    int indice_carta_excluir = -1;

    printf("Digite qual carta deseja excluir:\n");
    fgets(nome_procurado, 49, stdin);
    nome_procurado[strcspn(nome_procurado, "\n")] = '\0';

    // Confere se a carta que deseja alterar não é o super trunfo
    if (strcasecmp(nome_procurado, "Herobrine") == 0)
    {
        printf("Essa carta não pode ser excluída!\n");
        return;
    } // if

    // Procura carta
    for (int i = 0; i < tamanho; i++)
    {
        if (strcasecmp(nome_procurado, cartas[i].nome) == 0)
        {
            indice_carta_excluir = i;
        } // if
    } // for

    // Confere se o que foi digitado existe nas cartas
    if (indice_carta_excluir == -1){
        printf("Carta não encontrada.\n");
        return;
    }//if

    FILE * fp = fopen("../cartas.csv", "w+");

    if (fp == NULL){
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    } // if

    for (int i = 0; i < tamanho; i++) {
        if (i != indice_carta_excluir) {
            if(strcasecmp("Herobrine",cartas[i].nome)==0){
            fprintf(fp, "%s,%c,%d,%s,%d,%.2f,%.2f,%.2f",
                cartas[i].nome,
                cartas[i].letra,
                cartas[i].numero,
                cartas[i].superTrunfo,
                cartas[i].vida,
                cartas[i].dano,
                cartas[i].altura,
                cartas[i].velocidade);
                }else{
                fprintf(fp, "%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                cartas[i].nome,
                cartas[i].letra,
                cartas[i].numero,
                cartas[i].superTrunfo,
                cartas[i].vida,
                cartas[i].dano,
                cartas[i].altura,
                cartas[i].velocidade);
                }//else
        }//if
    }//for

    fclose(fp);
    

} // excluir_carta

int main(){
    
    
    int num_digitado;

    FILE *fp = fopen("../cartas.csv", "r+");

    int tamanho = 0;
    tamanho = funcao_tamanho(fp);

    Carta *cartas = (Carta *)malloc(tamanho * sizeof(Carta));

    if (cartas == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    } // if

    for (int i = 0; i < tamanho; i++)
    {
        fscanf(fp, " %[^,],", cartas[i].nome);        // Lê nome até a vírgula
        fscanf(fp, "%c,", &cartas[i].letra);          // Lê letra
        fscanf(fp, "%d,", &cartas[i].numero);         // Lê número
        fscanf(fp, " %[^,],", cartas[i].superTrunfo); // Lê superTrunfo até a vírgula
        fscanf(fp, "%d,", &cartas[i].vida);           // Lê vida
        fscanf(fp, "%f,", &cartas[i].dano);           // Lê dano
        fscanf(fp, "%f,", &cartas[i].altura);         // Lê altura
        fscanf(fp, "%f", &cartas[i].velocidade);      // Lê velocidade
    } // for

    printf("MENU: Escolha uma das opções abaixo:\n");
    printf("1 - Inserir uma carta.\n");
    printf("2 - Listar as carta.\n");
    printf("3 - Pesquisar uma carta.\n");
    printf("4 - Alterar uma carta.\n");
    printf("5 - Excluir uma carta.\n");
    scanf("%d", &num_digitado);
    setbuf(stdin, NULL);

    fclose(fp);

    switch (num_digitado)
    {
    case 1:
        inserir_carta(cartas, tamanho);
        fp = fopen("../cartas.csv", "r+");
        tamanho = funcao_tamanho(fp);
        realloc(cartas,tamanho*sizeof(Carta));
        fclose(fp);
        break;

    case 2:
        listar_as_cartas(cartas, tamanho);
        break;

    case 3:
        pesquisar_cartas(cartas, tamanho);
        break;

    case 4:
        alterar_carta(cartas, tamanho);
        break;

    case 5:
        excluir_carta(cartas,tamanho);
        fp = fopen("../cartas.csv", "r+");
        tamanho = funcao_tamanho(fp);
        realloc(cartas,tamanho * sizeof(Carta));
        fclose(fp);

        break;

    default:
        break;
    } // switch

    return 0;
} // main
