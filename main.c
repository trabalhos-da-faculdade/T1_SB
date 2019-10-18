//Bibliotecas Básicas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>

//Biblioteca de Leitura das Imagens
#include "SOIL.h"

//Biblioteca do GLUT para Linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

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
float dist(RGB* a, RGB* b);
void init(); // PRA OPENGL
void draw(); // PRA OPENGL
void keyboard(unsigned char key, int x, int y); // PRA OPENGL

// Vetores
Img pic[3];
GLuint tex[3];

// Largura e Altura
int width, height;
int pos;
int sel;
unsigned char* novaImagem;
clock_t start;

// =================================================
// FUNÇÃO LOAD PARA CARREGAR A IMAGEM NO COMPUTADOR
// =================================================

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

// ==========================================
// FUNÇÃO DE VALIDADE(SE O BYTE JA FOI USADO)
// ==========================================

int testeVal(int* vet, int pos){
    if(sizeof(vet) != 0){
        return 1;
    }
    for(int i = 0 ; i < sizeof(vet) ; i++){
        if(vet[i] == pos){
            return 0;
        }
    }
}

// ====================================
// FUNÇÃO DE DESENHAR NA TELA A IMAGEM
// ====================================

void draw(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Preto
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3ub(255, 255, 255); // Branco
    glBindTexture(GL_TEXTURE_2D, tex[sel]);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(pic[sel].width,0);
    glTexCoord2f(1,1);
    glVertex2f(pic[sel].width, pic[sel].height);
    glTexCoord2f(0,1);
    glVertex2f(0,pic[sel].height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //Exibe a imagem
    glutSwapBuffers();
}

// ============================ 
// FUNÇÃO DE SELEÇÃO NO TECLADO
// ============================

void keyboard(unsigned char key, int x, int y){
    if(key==27){
        free(pic[0].pixels);
        free(pic[1].pixels);
        free(pic[2].pixels);
        exit(1);
    }
    if(key >= '1' && key <= '3'){
        sel = key - '1';
    }
    glutPostRedisplay();
}

// ===============================
// FUNCAO DE CALCULO DA DISTANCIA
// ===============================
float dist(RGB* a, RGB* b) {
    float d = pow(a->r - b->r,2);
    d += pow(a->g - b->g,2);
    d += pow(a->b - b->b,2);
    return d;
}



int main(int argc, char* argv[]){
   //argv significa que é a imagem que entra no sistema
   //Deve se passar um nome da imagem e que ela esteja no mesmo diretorio que este arquivo

    // CARREGANDO A PRIMEIRA IMAGEM
   load(argv[1], &pic[0]);
   printf("Largura da Imagem: %d \n", pic[0].width);
   printf("Altura da Imagem: %d \n", pic[0].height);
   printf("Nome da Imagem: %s \n", argv[1]);

    printf("\n");

   // CARREGANDO A SEGUNDA IMAGEM
   load(argv[2], &pic[1]);
   printf("Largura da Imagem: %d \n", pic[1].width);
   printf("Altura da Imagem: %d \n", pic[1].height);
   printf("Nome da Imagem: %s \n", argv[2]);

   printf("\n");

   // CARREGANDO A TERCEIRA IMAGEM
   load(argv[3], &pic[2]); 
   printf("Largura da Imagem: %d \n", pic[2].width);
   printf("Altura da Imagem: %d \n", pic[2].height);
   printf("Nome da Imagem: %s \n", argv[3]);


  // INICIANDO AS VARIAVEIS
  int width = pic[1].width;
  int height = pic[1].height;

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

    // ===========================================
    // ALGORITMO DO PROFESSOR PARA FAZER FUNCIONAR
    // ===========================================

    #define PAL 0
    #define SRC 1
    #define DST 2

    memcpy(pic[DST].pixels, pic[PAL].pixels, pic[1].width*pic[1].height*3);
    printf("Processando....");

    long int tot = 0;
    int tent = 0;
    start = clock();
    int tam = pic[0].width + pic[0].height;

    while(1){
        int pos1 = rand()%tam;
        int pos2 = rand()%tam;

        RGB* s1 = &pic[SRC].pixels[pos1];
        RGB* s2 = &pic[SRC].pixels[pos2];
        RGB* d1 = &pic[DST].pixels[pos1];
        RGB* d2 = &pic[DST].pixels[pos2];

        if(dist(s1,d1) + dist(s2,d2) > dist(s1,d2) + dist(s2,d1)){
            RGB aux = *d1;
            pic[DST].pixels[pos1] = *d2;
            pic[DST].pixels[pos2] = aux;
            tent = 0;
            tot++;
        }
        else tent++;
        if(tent > 5000){
            break;
        }
    }

    // INICIANDO O GLUT
    glutInit(&argc,argv);

    // DEFINIÇÃO DO MODO DE OPERAÇÃO DO GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Iniciando o tamanho da Tela
    glutInitWindowSize(pic[2].width,pic[2].height);

    // Cria uma Janela e o nome da Janela
    glutCreateWindow("Resultado do T1");

    // Registra a função Callback de redesenho
    glutDisplayFunc(draw);

    // Registra a função Callback do Teclado
    glutKeyboardFunc(keyboard);

    //verificacao do tamanho da pic[2]
    pic[2].pixels = malloc(pic[1].width * pic[1].height * 3); // W x H x 3 bytes (RGB)

    //Cria o Vetor do tex para o OPENGL
    tex[0] = SOIL_create_OGL_texture((unsigned char*) pic[0].pixels, pic[0].width, pic[0].height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    tex[1] = SOIL_create_OGL_texture((unsigned char*) pic[1].pixels, pic[1].width, pic[1].height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
    tex[2] = SOIL_create_OGL_texture((unsigned char*) pic[2].pixels, pic[2].width, pic[2].height, SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

    // Define a Janela de visualização 2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,width,height,0.0);
    glMatrixMode(GL_MODELVIEW);

    // Entra no Loop de eventos
    glutMainLoop();


}