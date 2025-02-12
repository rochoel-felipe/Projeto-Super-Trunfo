#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

int gerarNumeroAleatorio(int min, int max) {
     return min + (rand() % (max - min + 1));
}//funcao gera numero aleatorio.






//Função que tranfere carta de um jogador a outro 
//Ela diminui uma carta do jogador1 e aumenta uma carta no jogador2
void transferir_carta(Carta **cartas_jogador1, int *qtd_jogador1, Carta **cartas_jogador2, int *qtd_jogador2, int indice) {

    // Realocar espaço para o jogador 2
    *cartas_jogador2 = realloc(*cartas_jogador2, (*qtd_jogador2 + 1) * sizeof(Carta));
    (*cartas_jogador2)[*qtd_jogador2] = (*cartas_jogador1)[indice]; // Adiciona a carta ao jogador 2
    (*qtd_jogador2)++;

    // Alocar um espaco a mais 
    *cartas_jogador2 = realloc(*cartas_jogador2, (*qtd_jogador2 + 1) * sizeof(Carta));
    (*cartas_jogador2)[*qtd_jogador2] = (*cartas_jogador2)[indice]; // Adiciona a primeira carta do jogador ao final do baralho
    (*qtd_jogador2)++;

    // Remover a carta do jogador 2 e reorganizar o array
    for (int i = indice; i < *qtd_jogador2 - 1; i++) {
        (*cartas_jogador2)[i] = (*cartas_jogador2)[i + 1]; // Move as cartas para a esquerda
    }//for
    


    // Reduzir o tamanho do baralho do jogador 2
    *cartas_jogador2 = realloc(*cartas_jogador2, (*qtd_jogador2 - 1) * sizeof(Carta));
    (*qtd_jogador2)--;


    // Remover a carta do jogador 1 e reorganizar o array
    for (int i = indice; i < *qtd_jogador1 - 1; i++) {
        (*cartas_jogador1)[i] = (*cartas_jogador1)[i + 1]; // Move as cartas para a esquerda
    }//for 
    


    // Reduzir o tamanho do baralho do jogador 1
    *cartas_jogador1 = realloc(*cartas_jogador1, (*qtd_jogador1 - 1) * sizeof(Carta));
    (*qtd_jogador1)--;
}//transferir_carta

int main(){
    
    int numero_bot= 0;
    int contadora = 0;
      SetTargetFPS(60);
      
    InitAudioDevice(); // Ativa o sistema de som
    Sound efeito = LoadSound("efeito.wav");     
    Music musica = LoadMusicStream("musica.mp3");
    PlayMusicStream(musica); // Começa a tocar a música
    
    
    InitWindow(1280, 720, "JOGAR");
    
    FILE *fp = fopen("cartas.csv", "r+");
    if (fp == NULL) {
        printf("Erro ao abrir o csv.\n");
        return 1;
    }//if

    int quantidade_linhas = funcao_tamanho(fp);

    Carta cartas[quantidade_linhas];

    for (int i = 0; i < quantidade_linhas; i++) {
        fscanf(fp, " %[^,],", cartas[i].nome);        // Lê nome até a vírgula
        fscanf(fp, "%c,", &cartas[i].letra);          // Lê letra
        fscanf(fp, "%d,", &cartas[i].numero);         // Lê número
        fscanf(fp, " %[^,],", cartas[i].superTrunfo); // Lê superTrunfo até a vírgula
        fscanf(fp, "%d,", &cartas[i].vida);           // Lê vida
        fscanf(fp, "%f,", &cartas[i].dano);           // Lê dano
        fscanf(fp, "%f,", &cartas[i].altura);         // Lê altura
        fscanf(fp, "%f", &cartas[i].velocidade);      // Lê velocidade
    }//for

    fclose(fp);// fecha o arquivo 
  
    srand(time(NULL));
    

    int numero ;
    bool numeros_usados[quantidade_linhas + 1]; // Vetor para marcar números usados

    //Inicializa o vetor de números usados como falso
    for (int i = 0; i < (quantidade_linhas + 1); i++)
    {
       numeros_usados[i] = false;
    }
    
    //Declarando as cartas do jogadores 1
    Carta *cartas_jogadores_1 = malloc(quantidade_linhas+ (1 * sizeof(Carta)));

    if(quantidade_linhas % 2 == 0){ //Confere se o número de cartas é par
    
        //redefinindo a quantidade de cartas do jogador 1 as cartas do jogadores 1
        cartas_jogadores_1 = realloc(cartas_jogadores_1, (quantidade_linhas/2) * sizeof(Carta));

        
        for (int i = 0; i < (quantidade_linhas/2)  ; i++) {
            do {
                numero = gerarNumeroAleatorio(0, quantidade_linhas-1); // Gera número
            } while (numeros_usados[numero]); // Repete até encontrar um número não usado

            numeros_usados[numero] = true; // Marca o número como usado

                
                //numero = gerarNumeroAleatorio(1,quantidade_linhas);
                strcpy(cartas_jogadores_1[i].nome, cartas[numero].nome);
                cartas_jogadores_1[i].letra = cartas[numero].letra;
                cartas_jogadores_1[i].numero= cartas[numero].numero;
                strcpy(cartas_jogadores_1[i].superTrunfo, cartas[numero].superTrunfo);
                cartas_jogadores_1[i].vida = cartas[numero].vida;
                cartas_jogadores_1[i].dano = cartas[numero].dano;
                cartas_jogadores_1[i].altura = cartas[numero].altura;
                cartas_jogadores_1[i].velocidade = cartas[numero].velocidade;

            }//for


    }else{
            //redefinindo a quantidade de cartas do jogador 1 as cartas do jogadores 1
            cartas_jogadores_1 = realloc(cartas_jogadores_1, ((quantidade_linhas-1)/2) * sizeof(Carta));

            //CUIDADO POIS A CARTA TIRADA SE FOR HEROBRINE VAI SER UMA ANTERIOR
            int numero_excluido;
            numero_excluido =  gerarNumeroAleatorio(0,quantidade_linhas-1);

        for (int i = 0; i < (quantidade_linhas/2)  ; i++) {
            do {
                numero = gerarNumeroAleatorio(0, quantidade_linhas); // Gera número
            } while (numeros_usados[numero]); // Repete até encontrar um número não usado

            if(i != numero_excluido){

                numeros_usados[numero] = true; // Marca o número como usado

                    
                    //numero = gerarNumeroAleatorio(1,quantidade_linhas);
                    printf("numero aleatorio %d\n",numero);    
                    strcpy(cartas_jogadores_1[i].nome, cartas[numero].nome);
                    cartas_jogadores_1[i].letra = cartas[numero].letra;
                    cartas_jogadores_1[i].numero= cartas[numero].numero;
                    strcpy(cartas_jogadores_1[i].superTrunfo, cartas[numero].superTrunfo);
                    cartas_jogadores_1[i].vida = cartas[numero].vida;
                    cartas_jogadores_1[i].dano = cartas[numero].dano;
                    cartas_jogadores_1[i].altura = cartas[numero].altura;
                    cartas_jogadores_1[i].velocidade = cartas[numero].velocidade;
            }//if

        }//for

    }//else

    //Declarando as cartas do jogadores 2
    Carta *cartas_jogadores_2 = malloc((quantidade_linhas / 2) * sizeof(Carta));

    // Distribuir as cartas restantes para o jogador 2
    int index = 0;
    int vetor_de_indice[quantidade_linhas/2];

    for (int i = 0; i < quantidade_linhas; i++) {
        if (!numeros_usados[i]) {
            //Salva no vetor quais numero nao foram dados ao jogador 1 
            vetor_de_indice[index++] = i;
        }//if
    }//for

    //Salva as cartas do jogador 2
    for (int i = 0; i < quantidade_linhas/2; i++)
    {
        strcpy(cartas_jogadores_2[i].nome, cartas[vetor_de_indice[i]].nome);
        cartas_jogadores_2[i].letra = cartas[vetor_de_indice[i]].letra;
        cartas_jogadores_2[i].numero= cartas[vetor_de_indice[i]].numero;
        strcpy(cartas_jogadores_2[i].superTrunfo, cartas[vetor_de_indice[i]].superTrunfo);
        cartas_jogadores_2[i].vida = cartas[vetor_de_indice[i]].vida;
        cartas_jogadores_2[i].dano = cartas[vetor_de_indice[i]].dano;
        cartas_jogadores_2[i].altura = cartas[vetor_de_indice[i]].altura;
        cartas_jogadores_2[i].velocidade = cartas[vetor_de_indice[i]].velocidade;

    }//for
    
    
    
    
    for (int i = 0; i < quantidade_linhas/2; i++)
    {
        printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas_jogadores_1[i].nome,
                       cartas_jogadores_1[i].letra,
                       cartas_jogadores_1[i].numero,
                       cartas_jogadores_1[i].superTrunfo,
                       cartas_jogadores_1[i].vida,
                       cartas_jogadores_1[i].dano,
                       cartas_jogadores_1[i].altura,
                       cartas_jogadores_1[i].velocidade);
    }//for
     printf("baralho 1 cabo\n");

    for (int i = 0; i < quantidade_linhas/2; i++)
    {
        printf("%s,%c,%d,%s,%d,%.2f,%.2f,%.2f\n",
                       cartas_jogadores_2[i].nome,
                       cartas_jogadores_2[i].letra,
                       cartas_jogadores_2[i].numero,
                       cartas_jogadores_2[i].superTrunfo,
                       cartas_jogadores_2[i].vida,
                       cartas_jogadores_2[i].dano,
                       cartas_jogadores_2[i].altura,
                       cartas_jogadores_2[i].velocidade);
    }//for
    printf("baralho 2 cabo\n");


    

                
                
         
        

    Rectangle botao1 = { (GetScreenWidth() - 598) /2,328 , 598, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao11 = { 10, 10 , 100, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao2 = { (GetScreenWidth() - 598) /2,400, 598, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao21 = { 10, 10 , 100, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao22 = { 232.5, (GetScreenHeight() - 50)/2  , 100, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao23 = { 1047.5, (GetScreenHeight() - 50)/2  , 100, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao3 = { (GetScreenWidth() - 598) /2,472 , 598, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle botao31 = { 10, 10 , 100, 50 }; // Posição X, Y e dimensões Largura, Altura
    Rectangle carta = { (GetScreenWidth() - 350) /2,(GetScreenHeight() - 525)/2 , 350, 525 }; // Posição X, Y e dimensões Largura, Altura
    
    Texture2D capa = LoadTexture("capa.jpg");
    Texture2D fundo_game = LoadTexture("fundo_game.jpg");
    Texture2D versocarta = LoadTexture("versocarta.png");
    Texture2D placa = LoadTexture("placa.jpg");

    Color corbotao1 = GRAY;
    Color corbotao11 = GRAY;
    Color corbotao2 = GREEN;
    Color corbotao21 = GRAY;
    Color corbotao22 = GRAY;
    Color corbotao23 = GRAY;
    Color corbotao3 = RED;
    Color corbotao31 = GRAY;
    Color corcarta = GRAY;


 
    bool verificabotao1 = false;
    bool verificabotao11 = false;
    bool verificabotao2 = false;
    bool verificabotao21 = false;
    bool verificabotao3 = false;
    bool verificabotao31 = false;
    bool gameplay = false;
    bool verificabotaovida = false;
    bool verificabotaodano = false;
    bool verificabotaoaltura = false;
    bool verificabotaovelocidade = false;
 

    bool menu = true;
    int i = 0;
    
    int qtd_cartas_do_jogador1 = quantidade_linhas/2;
    int qtd_cartas_do_jogador2= quantidade_linhas/2;


    
    while (!WindowShouldClose()){
        
    UpdateMusicStream(musica); // Mantém a música tocando corretamente   
        
        // Obter a posição do mouse
        Vector2 posicaomouse = GetMousePosition();
        
        
        //Verifica se o mouse está sobre o botão1
        if (CheckCollisionPointRec(posicaomouse, botao1) && !verificabotao2 && !verificabotao3) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                verificabotao1 = true; // Registra que o botão foi clicado
                menu = false;
                contadora ++ ;
                PlaySound(efeito);
            }//if
        }//if
        
        if(verificabotao1 && !verificabotao2 && !verificabotao3){
        DrawTexture(fundo_game, 0, 0, WHITE);
        DrawTexture(placa, 10, 10, WHITE);
        
        
            if(!gameplay){
            //DrawText("Você apertou o botão 1!",(1280 - (MeasureText("Você apertou o botão 1!", 60)))/2,50, 60,BLACK); 
            DrawRectangleRec(botao11, corbotao11); // Desenhar o botão
            DrawTexture(placa, 10, 10, WHITE);
            DrawText("Voltar",23,23, 23,BLACK);      
            
                
////////////////////////////////////////////////////////////////////////////////////////////

        
        DrawText("Clique com o botao direito para sortear quem começa!", 50, 100, 40, BLACK);
      
        
     
    }//if gameplay
    
        
            
            
            //AQUI COMEÇA A GAMEPLAY IHUUHHUHUHUHUHUHUHUHU
            gameplay = true;
            DrawTexture(fundo_game, 0, 0, WHITE);

            
            Color corbotaoesc = GRAY;
            
                
            Rectangle botaoesc = { 10, 10 , 100, 50 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(botaoesc, corbotaoesc); // Desenhar o botão
            DrawTexture(placa, 10, 10, WHITE);
            DrawText("Voltar",23,23, 23,BLACK); 
            
            

            //Exibe a primeira carta do jogador da vez para escolher uma carcteristica
            DrawText("Escolha uma caracteristica da carta:",(1280 - (MeasureText("Escolha uma caracteristica da carta:", 40)))/2,100, 40,BLACK);

            
            char buffer[50]; // Buffer para converter números em string
            
            // Converte os valores numéricos em string antes de desenhar
            Rectangle carta = { 290, 155 , 350, 525 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(carta, corcarta); // Desenhar a carta
            
            Rectangle nome = { 290 ,155 , 350, 120 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(nome, BLACK); // Desenhar a carta
            Rectangle vida = { 290 ,300 , 350, 60 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(vida, BLACK); // Desenhar a carta
            Rectangle dano = { 290 ,400 , 350, 60 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(dano, BLACK); // Desenhar a carta
            Rectangle altura = { 290 ,500 , 350, 60 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(altura, BLACK); // Desenhar a carta
            Rectangle velocidade = { 290 ,600 , 350, 80 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(velocidade, BLACK); // Desenhar a carta
            
            
            Rectangle nome2 = { 290 ,190 , 350, 55 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(nome2, GRAY); // Desenhar a carta
            Rectangle vida2 = { 290 ,300 , 350, 55 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(vida2, GRAY); // Desenhar a carta
            Rectangle dano2 = { 290 ,400 , 350, 55 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(dano2, GRAY); // Desenhar a carta
            Rectangle altura2 = { 290 ,500 , 350, 55 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(altura2, GRAY); // Desenhar a carta
            Rectangle velocidade2 = { 290 ,600 , 350, 55 }; // Posição X, Y e dimensões Largura, Altura
            DrawRectangleRec(velocidade2, GRAY); // Desenhar a carta
            
            
            
            
            
            
            sprintf(buffer, "%s", cartas_jogadores_1[0].nome);
            DrawText(buffer, 300, 200, 40, BLACK);
            
            sprintf(buffer, "Vida: %d", cartas_jogadores_1[0].vida);
            DrawText(buffer, 320, 300, 40, BLACK);

            sprintf(buffer, "Dano: %.2f", cartas_jogadores_1[0].dano);
            DrawText(buffer, 320, 400, 40, BLACK);

            sprintf(buffer, "Altura: %.2f", cartas_jogadores_1[0].altura);
            DrawText(buffer, 320, 500, 40, BLACK);

            sprintf(buffer, "Velocidade: %.2f", cartas_jogadores_1[0].velocidade);
            DrawText(buffer, 305, 600, 40, BLACK);
            

            Rectangle botaovida = { 290 ,300 , 350, 50 }; // Posição X, Y e dimensões Largura, Altura
            //bool verificabotaovida = false;
            //DrawRectangleRec(botaovida, RED); // Desenhar a carta
            Rectangle botaodano = { 290 ,400 , 350, 50 }; // Posição X, Y e dimensões Largura, Altura
            //bool verificabotaodano = false;
            //DrawRectangleRec(botaodano, RED); // Desenhar a carta
            Rectangle botaoaltura = { 290 ,500 , 350, 50 }; // Posição X, Y e dimensões Largura, Altura
            //bool verificabotaoaltura = false;
            //DrawRectangleRec(botaoaltura, RED); // Desenhar a carta
            Rectangle botaovelocidade = { 290 ,600 , 350, 50 }; // Posição X, Y e dimensões Largura, Altura
            //bool verificabotaovelocidade = false;
            //DrawRectangleRec(botaovelocidade, RED); // Desenhar a carta
            
                static double tempoInicio = 0;  // Armazena o momento do clique
                static bool ocultando = false;  // Se a carta está oculta

                // Detecta o clique no botão para iniciar a ocultação
                if (CheckCollisionPointRec(posicaomouse, botaovida)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        ocultando = true;        // Ativa o modo ocultar
                        tempoInicio = GetTime(); // Registra o momento do clique
                        verificabotaovida = true;
                         PlaySound(efeito);
                    }
                }
                
                
                // Detecta o clique no botão para iniciar a ocultação
                if (CheckCollisionPointRec(posicaomouse, botaodano)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        ocultando = true;        // Ativa o modo ocultar
                        tempoInicio = GetTime(); // Registra o momento do clique
                        verificabotaodano = true;
                         PlaySound(efeito);
                    }
                }
                
                // Detecta o clique no botão para iniciar a ocultação
                if (CheckCollisionPointRec(posicaomouse, botaoaltura)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        ocultando = true;        // Ativa o modo ocultar
                        tempoInicio = GetTime(); // Registra o momento do clique
                        verificabotaoaltura = true;
                         PlaySound(efeito);
                    }
                }
                
                // Detecta o clique no botão para iniciar a ocultação
                if (CheckCollisionPointRec(posicaomouse, botaovelocidade)) {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        ocultando = true;        // Ativa o modo ocultar
                        tempoInicio = GetTime(); // Registra o momento do clique
                        verificabotaovelocidade = true;
                         PlaySound(efeito);
                    }
                }
                
                

                // Se já passou 2 segundos, a carta reaparece
                if (ocultando && GetTime() - tempoInicio > 4.0) {
                    ocultando = false;
                }//if
                

                // Se **não** estiver ocultando, desenha a carta
                if (!ocultando) {        
                    
                    Rectangle carta2 = { 790, 155 , 350, 525 };
                    DrawRectangleRec(carta2, GRAY);
                }//if
    
                
                Rectangle carta2 = { 790, 155 , 350, 525 };
                DrawRectangleRec(carta2, GRAY);
                sprintf(buffer, "%s", cartas_jogadores_2[1].nome);
                DrawText(buffer, 800, 200, 40, BLACK);
                
                sprintf(buffer, "Vida: %d", cartas_jogadores_2[1].vida);
                DrawText(buffer, 820, 300, 40, BLACK);

                sprintf(buffer, "Dano: %.2f", cartas_jogadores_2[1].dano);
                DrawText(buffer, 820, 400, 40, BLACK);

                sprintf(buffer, "Altura: %.2f", cartas_jogadores_2[1].altura);
                DrawText(buffer, 820, 500, 40, BLACK);

                sprintf(buffer, "Velocidade: %.2f", cartas_jogadores_2[1].velocidade);
                DrawText(buffer, 805, 600, 40, BLACK);                


    // Se está ocultando, verifica se já passou o tempo de espera (ex: 2 segundos)
    if (ocultando && GetTime() - tempoInicio > 4.0) {   
        ocultando = false; // Volta a mostrar a carta
    }
    
    // Se **não** estiver ocultando, desenha a carta normalmente
    if (!ocultando) {        

        Rectangle carta2 = { 790, 155 , 350, 525 };
        DrawRectangleRec(carta2, GRAY);
        DrawTexture(versocarta, 790, 155, WHITE);
    }
            

        
        if(verificabotaovida || numero_bot == 1){
            
            if(cartas_jogadores_1[0].vida > cartas_jogadores_2[0].vida){
                numero_bot = 0 ;
                printf("\nJogador 1 ganhou!\n");
                fflush(stdout);
                transferir_carta(&cartas_jogadores_2, &qtd_cartas_do_jogador2, &cartas_jogadores_1, &qtd_cartas_do_jogador1, 0);
                
                
            }else{
                //O outro jogador passa a ser o da vez  
                printf("Jogador 2 ganhou!\n");
                fflush(stdout); 
                transferir_carta(&cartas_jogadores_1, &qtd_cartas_do_jogador1, &cartas_jogadores_2, &qtd_cartas_do_jogador2, 0);//o zero é o indice da carta que desejo transferir
              
              
               numero_bot = gerarNumeroAleatorio(1,4);
                printf("Bot escolheu vida como atributo\n");
                fflush(stdout); 

             
            }//else
            
            verificabotaovida = false;

        }//if verifica botao vida

        
        
        if(verificabotaodano || numero_bot == 2){
            
            
            if(cartas_jogadores_1[0].dano > cartas_jogadores_2[0].dano){
                numero_bot = 0 ;
                printf("\nJogador 1 ganhou!\n");
                fflush(stdout);
                transferir_carta(&cartas_jogadores_2, &qtd_cartas_do_jogador2, &cartas_jogadores_1, &qtd_cartas_do_jogador1, 0);
            }else{
                //O outro jogador passa a ser o da vez  
                printf("Jogador 2 ganhou!\n");
                fflush(stdout); 
                transferir_carta(&cartas_jogadores_1, &qtd_cartas_do_jogador1, &cartas_jogadores_2, &qtd_cartas_do_jogador2, 0);//o zero é o indice da carta que desejo transferir
              
               numero_bot = gerarNumeroAleatorio(1,4);
                printf("Bot escolheu Dano como atributo\n");
                fflush(stdout); 
            }//else
                
            verificabotaodano = false;
            
        }//if verifica botao dano
        
        if(verificabotaoaltura || numero_bot == 3 ){
            
            
            if(cartas_jogadores_1[0].altura > cartas_jogadores_2[0].altura){
               
               numero_bot = 0 ;
               printf("\nJogador 1 ganhou!\n");
               fflush(stdout);
               transferir_carta(&cartas_jogadores_2, &qtd_cartas_do_jogador2, &cartas_jogadores_1, &qtd_cartas_do_jogador1, 0);
               
            }else{
            
            printf("Jogador 2 ganhou!\n");
            fflush(stdout); 
            transferir_carta(&cartas_jogadores_1, &qtd_cartas_do_jogador1, &cartas_jogadores_2, &qtd_cartas_do_jogador2, 0);//o zero é o indice da carta que desejo transferir
            numero_bot = gerarNumeroAleatorio(1,4);
            printf("Bot escolheu Altura como atributo\n");
            fflush(stdout);
             
            }//else
                verificabotaoaltura = false;
            
        }//if verifica botao altura
        
        if(verificabotaovelocidade || numero_bot == 4){
            
            
            if(cartas_jogadores_1[0].velocidade > cartas_jogadores_2[0].velocidade){
                
               numero_bot = 0 ;
               printf("\nJogador 1 ganhou!\n");
               fflush(stdout);
               transferir_carta(&cartas_jogadores_2, &qtd_cartas_do_jogador2, &cartas_jogadores_1, &qtd_cartas_do_jogador1, 0);
               
            }else{
            
            printf("Jogador 2 ganhou!\n");
            fflush(stdout); 
            transferir_carta(&cartas_jogadores_1, &qtd_cartas_do_jogador1, &cartas_jogadores_2, &qtd_cartas_do_jogador2, 0);//o zero é o indice da carta que desejo transferir
            numero_bot = gerarNumeroAleatorio(1,4);
            printf("Bot escolheu Velocidade como atributo\n");
            fflush(stdout);
             
            }//else
                verificabotaovelocidade = false;
            
        }//if verifica botao velocidade

        if(qtd_cartas_do_jogador2 == 0){
            printf("Jogador 1 é o vencedor!!!!!!!!!!!!!!!!!! \n ");
        }
        if(qtd_cartas_do_jogador1 == 0) { 
            printf("Jogador 2 é o vencedor!!!!!!!!!!!!!!!!!! \n ");
        }
        
    

//////////////////////////////////////////////////////////////////////////////


            
                if (CheckCollisionPointRec(posicaomouse, botao11)) {            
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        verificabotao11 = true; // Registra que o botão foi clicado
                         PlaySound(efeito);
                         contadora -- ;
                    }//if 
                }//if
                
                
                if(verificabotao11){
                    menu = true;
                    verificabotao1 = false;
                    verificabotao11 = false;
                }//if
                
        }//if botao 1

        
            
        
        //Verifica se o mouse está sobre o botão2
        if (CheckCollisionPointRec(posicaomouse, botao2)&& !verificabotao1 && !verificabotao3) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                verificabotao2 = true; // Registra que o botão foi clicado
                menu = false;
                 PlaySound(efeito);
            }//if
        }//if
        if(verificabotao2 && !verificabotao1 && !verificabotao3){
            
            if (CheckCollisionPointRec(posicaomouse, botao22)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                      PlaySound(efeito);
                    if(i != 0){
                        i --;
                    }else{
                        i = quantidade_linhas - 1 ;
                    }//else
                }//if
            }//if
            
            if (CheckCollisionPointRec(posicaomouse, botao23)) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                      PlaySound(efeito);
                    if(i == quantidade_linhas - 1 ){
                        i = 0;
                    }else{
                        i++;
                    }//else
                }//if
            }//if
            
            char buffer[50];
            DrawText("Você apertou o botão 2!",(1280 - (MeasureText("Você apertou o botão 2!", 60)))/2,30, 60,BLACK); 
            
            
            
            DrawRectangleRec(carta, corcarta); // Desenhar a carta
            
            sprintf(buffer, "%s", cartas[i].nome);
            DrawText(buffer, 490, 120, 50, BLACK);
            
            sprintf(buffer, "Vida: %d", cartas[i].vida);
            DrawText(buffer, 490, 200, 35, BLACK);
            
            sprintf(buffer, "Dano: %.2f", cartas[i].dano);
            DrawText(buffer, 490, 280, 35, BLACK);

            sprintf(buffer, "Altura: %.2f", cartas[i].altura);
            DrawText(buffer, 490, 360, 35, BLACK);

            sprintf(buffer, "Velocidade: %.2f", cartas[i].velocidade);
            DrawText(buffer, 490, 440, 35, BLACK);
         
            DrawRectangleRec(botao23, corbotao23); // Desenhar o botão de volta
            DrawRectangleRec(botao22, corbotao22); // Desenhar o botão de volta
            DrawRectangleRec(botao21, corbotao21); // Desenhar o botão de volta
            DrawText("Voltar",20,20, 20,BLACK);

              
            if (CheckCollisionPointRec(posicaomouse, botao21)) {            
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    verificabotao21 = true; // Registra que o botão foi clicado
                     PlaySound(efeito);
                }//if 
            }//if
            
            if(verificabotao21){
                menu = true;
                verificabotao2 = false;
                verificabotao21 = false;
            }//if
        }//if
        
        
        //Verifica se o mouse está sobre o botão3
        
        if (CheckCollisionPointRec(posicaomouse, botao3) && !verificabotao1 && !verificabotao2) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                verificabotao3 = true; // Registra que o botão foi clicado
                menu = false;
                 PlaySound(efeito);
            }//if
        }//if
        
        if(verificabotao3 && !verificabotao1 && !verificabotao2){
            DrawText("coom soon!",(1280 - (MeasureText("coom soon!", 60)))/2,(720 - 100)/2, 60,BLACK);  
            DrawRectangleRec(botao31, corbotao31); // Desenhar o botão
            DrawText("Voltar",20,20, 20,BLACK);            
            
            if (CheckCollisionPointRec(posicaomouse, botao31)) {                    
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    verificabotao31 = true;// Registra que o botão foi clicado 
                     PlaySound(efeito);
                }//if 
            }//if
            if(verificabotao31){
                menu = true;
                verificabotao3 = false;
                verificabotao31 = false;
            }//if
        }//if
        


        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(menu){
        
            
            DrawRectangleRec(botao1, corbotao1); // Desenhar o botão
            DrawRectangleRec(botao2, corbotao2); // Desenhar o botão
            DrawRectangleRec(botao3, corbotao3); // Desenhar o botão
            DrawTexture(capa, 0, 0, WHITE);
            DrawText("JOGAR!",(1280 - (MeasureText("JOGAR!", 40)))/2,334, 40,BLACK);
            DrawText("BARALHO!",(1280 - (MeasureText("BARALHO!", 40)))/2,406, 40,BLACK);
            DrawText("JOGAR EM LAN!",(1280 - (MeasureText("JOGAR EM LAN!", 40)))/2,478, 40,BLACK);
            

           
        }//if
        
        

        EndDrawing();
        
    }//while
    
    
    UnloadMusicStream(musica); // Libera a memória da música
    CloseAudioDevice(); // Fecha o sistema de áudio

 
    CloseWindow();       

    return 0;
}//main
