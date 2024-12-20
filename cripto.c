#include "cripto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[50];
    char letra;
    int numero;
    bool superTrunfo;
    int vida;  //em corações 
    float dano; //em corações 
    float altura; //em blocos
    float velocidade; //blocos/tique
}Carta;//Cartas

void inicializarCartas(Carta* carta, char* nome, char letra, int numero, bool superTrunfo, int vida, float dano, float altura, float velocidade){
    strcpy(carta->nome, nome);
    carta->letra = letra; 
    carta->numero = numero;
    carta->superTrunfo = superTrunfo;
    carta->vida = vida;
    carta->dano = dano;
    carta->altura = altura;
    carta->velocidade = velocidade;

}//inicializarCartas


void gera_csv(){

    FILE * fp = fopen("cartas.csv","w+");// cria o arquivo csv

    if (fp == NULL) {
         printf("Erro ao abrir o arquivo!\n");
         exit(1);// 1 significa erro arquivo
    }//if

    Carta cartas[36];

        
    //Chama função que faz alocação dinamica 
    inicializarCartas(&cartas[0],"Zumbi",'A', 1, false, 10, 1.5, 1.95, 0.23);
    inicializarCartas(&cartas[1],"Baby Zombie",'A', 2, false, 10, 2.25, 0.975, 0.46);
    inicializarCartas(&cartas[2],"Drowned", 'A', 3, false, 10, 6.5, 1.95, 0.23);
    inicializarCartas(&cartas[3],"Esqueleto", 'A', 4, false, 10, 1.5, 1.99, 0.25);
    inicializarCartas(&cartas[4],"Stray", 'A', 5, false, 10, 2, 1.99, 0.25);
    inicializarCartas(&cartas[5],"Skeleton Horseman", 'A', 6, false, 35, 3, 2.55, 0.24);
    inicializarCartas(&cartas[6],"Creeper", 'A', 7, false, 10, 21.5, 1.7, 0.25);
    inicializarCartas(&cartas[7],"Aranha", 'A', 8, false, 8, 1, 0.9, 0.3);
    inicializarCartas(&cartas[8],"Cave Spider", 'A', 9, false, 6, 3.5, 0.5, 0.35);
    inicializarCartas(&cartas[9],"Bruxa", 'B', 1, false, 13, 14, 1.95, 0.25);
    inicializarCartas(&cartas[10],"Enderman", 'B', 2, false, 20, 5, 2.9, 0.28);
    inicializarCartas(&cartas[11],"Endermite", 'B', 3, false, 8, 1.5, 0.3, 0.35);
    inicializarCartas(&cartas[12],"Slime", 'B', 4, false, 32, 1, 2.04, 0.2);
    inicializarCartas(&cartas[13],"Magma Cube", 'B', 5, false, 32, 1, 1.3, 0.2);
    inicializarCartas(&cartas[14],"Ghast", 'B', 6, false, 50, 4.5, 4, 0.2);
    inicializarCartas(&cartas[15],"Blaze", 'B', 7, false, 10, 4.5, 1.7, 0.23);
    inicializarCartas(&cartas[16],"Zumbi Piglin", 'B', 8, false, 10, 3.5, 1.9, 0.25);
    inicializarCartas(&cartas[17],"Piglin Brute", 'B', 9, false, 25, 13, 1.95, 0.35);
    inicializarCartas(&cartas[18],"Piglin", 'C', 1, false, 8, 8, 1.95, 0.35);
    inicializarCartas(&cartas[19],"Hoglin", 'C', 2, false, 15, 4, 1.7, 0.35);
    inicializarCartas(&cartas[20],"Zoglin", 'C', 3, false, 25, 4, 1.4, 0.35);
    inicializarCartas(&cartas[21],"Pillager", 'C', 4, false, 12, 2.5, 1.9, 0.25);
    inicializarCartas(&cartas[22],"Evoker", 'C', 5, false, 12, 9, 1.9, 0.25);
    inicializarCartas(&cartas[23],"Vindicator", 'C', 6, false, 24, 4.5, 1.9, 0.25);
    inicializarCartas(&cartas[24],"Ravager", 'C', 7, false, 50, 30, 2.7, 0.35);
    inicializarCartas(&cartas[25],"Guardian", 'C', 8, false, 15, 2.5, 0.85, 0.3);
    inicializarCartas(&cartas[26],"Elder Guardian", 'C', 9, false, 40, 5, 1.9, 0.3);
    inicializarCartas(&cartas[27],"Shulker", 'D', 1, false, 15, 2, 0.5, 0.25);
    inicializarCartas(&cartas[28],"Phantom", 'D', 2, false, 10, 2, 0.9, 0.4);
    inicializarCartas(&cartas[29],"Silverfish", 'D', 3, false, 4, 1.5, 0.3, 0.25);
    inicializarCartas(&cartas[30],"Wither Skeleton", 'D', 4, false, 10, 3.5, 2.4, 0.3);
    inicializarCartas(&cartas[31],"Wither", 'D', 5, false, 150, 30, 3, 0.5);
    inicializarCartas(&cartas[32],"Ender Dragon", 'D', 6, false, 100, 12.5, 12, 0.5);
    inicializarCartas(&cartas[33],"Warden", 'D', 7, false, 250, 17.5, 3, 0.3);
    inicializarCartas(&cartas[34],"Strider", 'D', 8, false, 10, 3.5, 1.4, 0.25);
    inicializarCartas(&cartas[35],"Herobrine", 'D', 9, true, 300, 35, 1.95, 0.5);
    
    for(int i = 0 ; i < 35 ; i++){

        fprintf(fp,"%s,%c,%d,false,%d,%.2f,%.2f,%.2f\n",
                cartas[i].nome,
                cartas[i].letra,
                cartas[i].numero,
                cartas[i].vida,
                cartas[i].dano,
                cartas[i].altura,
                cartas[i].velocidade);
        
    }//for

    fprintf(fp,"%s,%c,%d,true,%d,%.2f,%.2f,%.2f",
            cartas[35].nome,
            cartas[35].letra,
            cartas[35].numero,
            cartas[35].vida,
            cartas[35].dano,
            cartas[35].altura,
            cartas[35].velocidade);

    printf("Dentro da funcao gera csv!\n");
    
    fclose(fp);
}//gera_csv
