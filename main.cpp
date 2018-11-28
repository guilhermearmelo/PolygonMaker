#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>
#include <stdio.h>

/* ESTADOS DO SISTEMA
    0 - ESTADO INICIAL
    1 - CRIAR POLIGONO
    2 - SELECIONAR POLIGONO
    3 - TRANSLADAR
    4 - ROTACIONAR + 90 GRAUS
    5 - ROTACIONAR - 90 GRAUS
    6 - CALCULAR AREA
    7 - DETERMINAR ORIENTACAO
    8 - ELIMINAR
    9 - LIMPAR TUDO
    10 - SAIR
*/


#define LARGURA 800
#define ALTURA  600

using namespace std;

////////////////////////////////////////////////////

class Ponto{
public:
    int x, y;
};

class Cor{
public:
    float R, G, B;
};

class Poligono{
public:
    list<Ponto> vert;
    bool preenchido;
    int cor;
};

//typedef struct ponto{
//    int x, y;
//}Ponto;

//typedef struct cor{
//    float R, G, B;
//}Cor;

//typedef struct poligono{
//    list<Ponto> vert;
//    bool preenchido;
//    int cor;
//}Polig;

////////////////////////////////////////////////////
// VARIAVEIS GLOBAIS

int larg = LARGURA;
int altu = ALTURA;
vector<Cor> paleta;
bool preencher = false;
vector<Poligono> Poligonos;
int corUsada = 0;
int estado = 0;
bool NOVO_POLIGONO = true;

////////////////////////////////////////////////////

void IniciarPaleta(){
    Cor c();

    // azul bebe
    c.R = 84/ 255.0;
    c.G = 174/ 255.0;
    c.B = 232/ 255.0;
    paleta.push_back(c);
    // roxo
    c.R = 128/ 255.0;
    c.G = 0/ 255.0;
    c.B = 128/ 255.0;
    paleta.push_back(c);
    // amarelo
    c.R = 255/ 255.0; c.G = 255/ 255.0; c.B = 0/ 255.0; paleta.push_back(c);
    // bordo
    c.R = 128/ 255.0; c.G = 0/ 255.0; c.B = 0/ 255.0; paleta.push_back(c);
    // verde claro
    c.R = 144/ 255.0; c.G = 238/ 255.0; c.B = 144/ 255.0; paleta.push_back(c);
    // marsala
    c.R = 150/ 255.0; c.G = 79/ 255.0; c.B = 76/ 255.0; paleta.push_back(c);
    // vermelho
    c.R = 255/ 255.0; c.G = 0/ 255.0; c.B = 0/ 255.0; paleta.push_back(c);
    // azul meia noite
    c.R = 25/ 255.0; c.G = 25/ 255.0; c.B = 112/ 255.0; paleta.push_back(c);
    // rosa claro
    c.R = 255/ 255.0; c.G = 182/ 255.0; c.B = 193 / 255.0; paleta.push_back(c);
    // verde escuro
    c.R = 0 / 255.0; c.G = 100 / 255.0; c.B = 0 / 255.0; paleta.push_back(c);
}

void init(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 800.0, 600.0, 0.0, 0.0, 1000.0); // tamanho dos eixos
}

int selecionaCor(int y){
    int cor = 9;
    while(y<=600){
        y = y + 60;
        cor --;
    }
    return cor+1;
}

void DesenharPaleta(){

    Ponto p1, p2, p3, p4;

    p1.x = 0; p1.y = 0;
    p2.x = 0; p2.y = 60;
    p3.x = 100; p3.y = 60;
    p4.x = 100; p4.y = 0;

    //cout << paleta[1].R << endl;

    for(int i=0; i<10; i++){

        glColor3f(paleta.at(i).R , paleta.at(i).G , paleta.at(i).B )

        glBegin(GL_POLYGON);
            glVertex3f(p1.x, p1.y, 0.0);
            glVertex3f(p2.x, p2.y, 0.0);
            glVertex3f(p3.x, p3.y, 0.0);
            glVertex3f(p4.x, p4.y, 0.0);
        glEnd();

        p1.x = p2.x;
        p1.y = p2.y;

        p4.x = p3.x;
        p4.y = p3.y;

        p2.x = p2.x;
        p2.y = p2.y + 60;

        p3.x = p3.x;
        p3.y = p3.y + 60;
    }
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    DesenharPaleta();



    glFlush();
}

void GerenciaMouse(int button, int state, int x, int y){

    if(x < 100){ // SE
        if (button == GLUT_LEFT_BUTTON){ // SE CLICOU NA PALETA -> SELECIONA COR
            corUsada = selecionaCor(y);
            cout << "PALETA -> cor: " << corUsada << endl;
        }
    }

    if(button == GLUT_RIGHT_BUTTON){
        NOVO_POLIGONO = true; // FECHAR POLIGONO
    }

    if(x >= 100){ // SE CLICOU NO QUADRO BRANCO
        switch(estado){
        case 0:
            cout << "Estado 0" << endl;
            break;
        case 1: // CRIAR POLIGONO
            cout << "Estado 1" << endl;
            if(NOVO_POLIGONO){
                // CRIAR UM POLIGONO
                Polig pol;
                pol.preenchido = preencher;
                pol.cor = corUsada;
                Poligonos.insert(pol);
                cout << "Criado novo poligono" << endl;
                NOVO_POLIGONO = false;
            }
            // CRIAR O PONTO
            // INSERIR NO ULTIMO POLIGONO
            Ponto p;
            p.x = x; p.y = y;

            //Poligonos.back()->vert.insert(p);
            //Poligonos.at(Poligonos.size()-1).vert.insert(p); // INSERE PONTO NOS VERTICES DO ULTIMO POLIGONO
            break;
        }

    }

    glutPostRedisplay();
}

void GerenciaTeclado(unsigned char tecla, GLint x, GLint y){
    switch(tecla){
    case 'f':
        preencher = !preencher;
        cout << preencher << endl;
        break;
    case 'F':
        preencher = !preencher;
        cout << preencher << endl;
        break;
    }
}

void GoMenu(int value){
    switch( value ){
    case 1: // ROTACIONAR + 90 GRAUS
        break;
    case 2: // ROTACIONAR - 90 GRAUS
        break;
    case 3: // CRIAR POLIGONO
        estado = 1;
        break;
    case 4: // SELECIONAR POLIGONO
        break;
    case 5: // TRANSLADAR
        break;
    case 6: // CALCULAR AREA
        break;
    case 7: // DETERMINAR ORIENTACAO
        break;
    case 8: // ELIMINAR
        break;
    case 9: // LIMPAR TUDO
        break;
    case 10: // SAIR
        break;
    }
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (LARGURA , ALTURA);
    glutInitWindowPosition (10 , 10);
    glutCreateWindow ("Trabalho 2 de Computacao Grafica");
    IniciarPaleta();



    int sub1 = glutCreateMenu(GoMenu);

    glutAddMenuEntry("+ 90º", 1);
    glutAddMenuEntry("- 90º", 2);
    glutCreateMenu(GoMenu);

    glutAddSubMenu("Rotacionar", sub1);

    glutAddMenuEntry("Criar Poligono", 3);
    glutAddMenuEntry("Selecionar Poligono", 4);
    glutAddMenuEntry("Transladar", 5);
    glutAddMenuEntry("Calcular Area", 6);
    glutAddMenuEntry("Determinar Orientacao", 7);
    glutAddMenuEntry("Eliminar", 8);
    glutAddMenuEntry("Limpar Tudo", 9);
    glutAddMenuEntry("Sair", 10);

    glutAttachMenu(GLUT_RIGHT_BUTTON);


    init();
    glutMouseFunc(GerenciaMouse);
    glutKeyboardFunc(GerenciaTeclado);
    glutDisplayFunc ( display ) ;



    glutMainLoop( );
    return 0;
}
