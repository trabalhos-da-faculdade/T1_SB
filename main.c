//Bibliotecas Básicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Biblioteca de Leitura das Imagens
#include "SOIL.h"

// Um pixel RGB (24 bits) = R = RED , G = GREEN , B = BLUE
typedef struct {
    unsigned char r,g,b;
} RGB;

// Uma Imagem RGB = Width = Largura , Height = Altura
typedef struct {
    int width , height;
    int pixels_lenght;
    RGB* pixels;
} Img;

// Protótipos das Funções
void load(char* name, Img* pic); //Carrega a Imagem RGB
void valida();

// Variáveis
Img pic[0];


// Carregando uma Imagem com a Biblioteca SOIL

 void load(char* name, Img* pic){
     int channel; //Channel é o local da imagem que será lida

     //Agora iremos pegar a imagem e definir ela como RGB(SOIL_LOAD_RGB)
     pic->pixels = (RGB*) SOIL_load_image(name, &pic->width, &pic->height, &channel, SOIL_LOAD_RGB);
     if(!pic->pixels){
         printf("SOIL Loading Error: '%s' \n", SOIL_last_result());
         exit(1);
     }
     printf("Imagem Carregada: %d x %d x %d\n", pic->width, pic->height, channel);
 }

int main(int argc, char* argv[]){
   //argv significa que é a imagem que entra no sistema
   //para funcionar se deve rodar o programa e colocar o nome da imagem do lado
   // Exemplo ./run nome_imagem.png


    //Carregando uma imagem de teste
   load(argv[1], &pic[0]);
   printf("Largura da Imagem: %d \n", pic[0].width);
   printf("Largura da Imagem: %d \n", pic[0].height);
   printf("Nome da Imagem: %s \n", argv[1]);
   printf("");




    
}