//Bibliotecas Básicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

// Vetores
Img pic[2];

// Largura e Altura
int width, height;
int pos;



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

// Validação do algoritmo de organização na imagem 3
void valida(){
    int ok = 1;
    int size = width * height;

    //Aloca memoria para os dois vetores RGB
    RGB* aux1 = malloc(size*3);
    RGB* aux2 = malloc(size*3);
}

int testeVal(int* vet, int pos){
    if(sizeof(vet) == 0){
        return 1;
    }
    for(int i = 0 ; i < sizeof(vet) ; i++){
        if(vet[i] == pos){
            return 0;
        }
    }
}


int main(int argc, char* argv[]){
   //argv significa que é a imagem que entra no sistema
   //Deve se passar um nome da imagem e que ela esteja no mesmo diretorio que este arquivo

    //Carregando a primeira imagem(que possui as cores)
   load(argv[1], &pic[0]);
   printf("Largura da Imagem: %d \n", pic[0].width);
   printf("Altura da Imagem: %d \n", pic[0].height);
   printf("Nome da Imagem: %s \n", argv[1]);

    printf("\n");

   //Carregando a segunda imagem
   load(argv[2], &pic[1]);
   printf("Largura da Imagem: %d \n", pic[1].width);
   printf("Altura da Imagem: %d \n", pic[1].height);
   printf("Nome da Imagem: %s \n", argv[2]);

   printf("\n");

   //Carregando a terceira imagem
   load(argv[3], &pic[2]);
   printf("Largura da Imagem: %d \n", pic[2].width);
   printf("Altura da Imagem: %d \n", pic[2].height);
   printf("Nome da Imagem: %s \n", argv[3]);

   printf("\n");


   printf("Pixels: \n");

   //Verificando o Código HEXA das cores
   for(int i = 0 ; i < sizeof(pic[0].pixels) ; i++){
        printf("[%02X%02X%02X] \n", pic[0].pixels[i].r,pic[0].pixels[i].g,pic[0].pixels[i].b);
    }

    printf("\n");

   for(int i = 0 ; i < sizeof(pic[1].pixels) ; i++){
        printf("[%02X%02X%02X] \n", pic[1].pixels[i].r,pic[1].pixels[i].g, pic[1].pixels[i].b);
    }

 
    printf("\n");
    // Aloca memória para a nova imagem
    pic[2].pixels = malloc(pic[1].width * pic[1].height * 3);


    RGB* aux = malloc((width*height)*3);
    float dist;
    float pc = 441.67295593; //Dist do pior caso(preto e branco)
    float mc = 1;
    int vet[sizeof(pic[0].pixels)-1];
    //Cálculo da Distância 
    for(int i = 0 ; i < sizeof(pic[0].pixels); i++){
        for(int j = 0 ; j < sizeof(pic[1].pixels) ; j++){
            unsigned char r1 = pic[0].pixels[i].r;
            unsigned char r2 = pic[1].pixels[j].r;
            unsigned char g1 = pic[0].pixels[i].g;
            unsigned char g2 = pic[1].pixels[j].g;
            unsigned char b1 = pic[0].pixels[i].b;
            unsigned char b2 = pic[1].pixels[j].b;

            unsigned char rs = r1 - r2;
            unsigned char gs = g1 - g2;
            unsigned char bs = b1 - b2;

            unsigned char rp = pow(rs,2);
            unsigned char gp = pow(gs,2);
            unsigned char bp = pow(bs,2);

            dist = (float) sqrt(rp+gp+bp);

            if(dist < pc && dist >= mc && testeVal(vet,i)){
                pos = j;
                pc = dist;
            }
        }
        aux[i].r = pic[0].pixels[pos].r;
        aux[i].g = pic[0].pixels[pos].g;
        aux[i].b = pic[0].pixels[pos].b;

        pic[2].pixels[i].r = pic[0].pixels[pos].r;
        pic[2].pixels[i].g = pic[0].pixels[pos].g;
        pic[2].pixels[i].b = pic[0].pixels[pos].b;

        vet[i] = pos;

    }
    for(int i = 0 ; i < sizeof(pic[2].pixels); i++){
        printf("[%02X%02X%02X] \n", pic[2].pixels[i].r , pic[2].pixels[i].g, pic[2].pixels[i].b);
    }

    int teste = SOIL_save_image("teste.bmp",1,pic[2].width,pic[2].height,3,(unsigned char*) pic[2].pixels);
    printf("%d \n", teste);


    
    

   
   
    





    


}