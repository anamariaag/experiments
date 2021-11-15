#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

#define valorInicial 5

typedef struct node Node;
typedef struct list List;
typedef struct bloque Bloque;

Bloque* getBloque(List* list,int index);
Color getColor(List* gusano, int index);
float getRadio(List* gusano,int index);
Vector2 getPosicion(List* gusano,int index);
void setPosicion(List* gusano, int index, Vector2 pos);
Bloque* newBloque(Color color,int n);
void updateListaP(List* posiciones, Vector2 mouse);
void updateGusano(List *gusano,List* posiciones);
void copyData(List *list, Vector2 mouse);

List *newList();
void addElement(List *list,void* value);
void removeLastElement(List *list);
void* getElement(List* list,int index);

struct node{
    void* value;
    struct node *next;
};

struct list{
    Node* head;
    int size;
};

struct bloque{
    Color color;
    Vector2 posicion;
    float alpha;
    float radio;
};

    int main() {
        printf("Hello, World!\n");
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

        Vector2 pInicial = { 100.0f, 100.0f };
        void *ptrPosicionInicial=&pInicial;

        SetTargetFPS(1);               // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------
        List *posiciones = newList();
        List *gusano = newList();

        Color random1=(Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
        for(int i = 0; i<valorInicial;i++){//inicializar bloque
            addElement(gusano, newBloque(random1,i));
        }

        for(int i = 0; i<valorInicial;i++){//inicializar posiciones
            addElement(posiciones, ptrPosicionInicial);
        }

        Vector2 pMouse;
        // Main game loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update
            //----------------------------------------------------------------------------------
            // TODO: Update your variables here
            updateListaP(posiciones, GetMousePosition());//agrega nueva posicion mouse y quita ultima
            updateGusano(gusano,posiciones);//copia lista de posiciones a posiciones de los bloques
            //----------------------------------------------------------------------------------
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

            for(int i=0;i<valorInicial;i++){
                DrawCircleV(getPosicion(gusano,i), getRadio(gusano,i), getColor(gusano,i));
                printf("(%f,%f)\n", getPosicion(gusano,i).x,getPosicion(gusano,i).y);
            }
            printf("\n");
            EndDrawing();
            //----------------------------------------------------------------------------------
        }
        // De-Initialization
        //--------------------------------------------------------------------------------------
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        return 0;
    }

List *newList(){//regresa el primer nodo de una lista
    List *newHead= malloc(sizeof(List));
    newHead->size=0;
    newHead->head=NULL;
    return newHead;
}

void* getElement(List* list, int index){
        Node *focusNode=list->head;
        for(int i=1;i<index;i++){
            focusNode=focusNode->next;
        }
        return focusNode->value;
    }

void addElement(List *list,void* value){
    Node *new =malloc(sizeof(Node));
    new->value=value;
    new->next=list->head;
    list->head=new;
    list->size++;
}

void removeLastElement(List *list){
    Node *focusNode = list->head;
    while (focusNode->next->next!= NULL) {
        focusNode = focusNode->next;
    }
    Node *elementDelete = focusNode->next;
    focusNode->next = NULL;
    free(elementDelete);
    list->size--;
}

Bloque* getBloque(List* list,int index){
    Node *focusNode = list->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr;
}

Color getColor(List* gusano, int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->color;
}

float getRadio(List* gusano,int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->radio;
}

Vector2 getPosicion(List* gusano,int index){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    return ptr->posicion;
}

void setPosicion(List* gusano, int index,Vector2 pos){
    Node *focusNode = gusano->head;//index 0
    for (int i = 0; i < index; i++) {
        focusNode = focusNode->next;
    }
    Bloque *ptr = focusNode->value;
    ptr->posicion=pos;
    }

Bloque* newBloque(Color color,int n){
    Bloque* new=malloc(sizeof(Bloque));
    new->color=color;
    new->alpha=1;
    new->posicion=(Vector2){ 100+5*n, 100 +5*n};
    new->radio=10;
    return new;
}

void updateListaP(List* posiciones,Vector2 mouse){
    Node* focus=posiciones->head;
    Vector2 *vec=focus->value;
    Vector2 tmp1=*vec;
    Vector2 tmp2;
    *vec=mouse;
    for(int i =1; i<posiciones->size;i++){
        focus=focus->next;
        vec=focus->value;
        tmp2=*vec;
        *vec=tmp1;

        i++;
        focus=focus->next;
        vec=focus->value;
        tmp1=*vec;
        *vec=tmp2;
    }
}

void updateGusano(List *gusano,List *posiciones){
    /*for(int i =0; i<gusano->size;i++){
        setPosicion(gusano,i, *(Vector2*)getElement(posiciones,i));
    }*/
    for(int i =0; i<gusano->size;i++){
        setPosicion(gusano,i,*(Vector2*)getElement(posiciones,i));
    }


}