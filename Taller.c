#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *archivo;
void mandarArchivo (const char nombre[30][20], const int cantidad[10], const float precio[10], const int filas);
void modificarArchivo(char nombre[30][20], int cantidad[10], float precio[10], int filas);
void mostrarDatosArchivo(const char []);
void eliminarProductoArchivo(const char []);
void datos (char nombre[30][20], int cantidad[10], float precio[10],int *filas);
int leerEntero(char* );
int leerEnteroPositivo(char* );
int leerEnteroEntre(char*,int,int);

float leerFlotante(char* );
float leerFlotantePositivo(char* );
float leerFlotanteEntre(char*, float, float);

char leerCaracter(char*);

int menu();

int main(void) {
  char nombre [30][20];
  int opcion;
  int filas=50;
  float precio[10];
  int cantidad[10];
  do {
    opcion = menu();
    switch(opcion){
      case 1:
      printf("Cuantos productos va a ingresar: ");
      scanf("%d",&filas);
      datos(nombre, cantidad, precio, &filas);
      mandarArchivo (nombre, cantidad, precio, filas);
      break;

      case 2:
      modificarArchivo(nombre, cantidad, precio, filas);
      break;

      case 3:
      eliminarProductoArchivo("datos.txt");
      break;

      case 4:
      mostrarDatosArchivo("datos.txt");
      break;

      case 5:
      printf("Saliendo del programa");
      break;
    }
  }while(opcion!=5);

  return 0;
}

void mandarArchivo (const char nombre[30][20], const int cantidad[10], const float precio[10], const int filas){
  if ((archivo = fopen("datos.txt", "w+")) != NULL) {
  for (int i = 0; i < filas; i++) {
  fputs(nombre[i], archivo);
  fputs("\n", archivo);
  fprintf(archivo, "%d", cantidad[i]);
  fputs("\n", archivo);
  fprintf(archivo, "%f", precio[i]);
  fputs("\n", archivo);
  fprintf(archivo, "%s", "\n\n");
    fclose(archivo);
}
}
}

void modificarArchivo(char nombre[30][20], int cantidad[10], float precio[10], int filas) {
      if (filas == 50) {
          printf("No hay productos ingresados para mostrar.\n");
          return;
      }

      FILE *archivo;
      archivo = fopen("datos.txt", "r+");

      if (archivo == NULL) {
          perror("Error al abrir el archivo");
          return;
      }

      printf("Que producto desea editar?\n");
      int productoAEditar = leerEnteroEntre("Numero: ", 1, filas);

      
      fseek(archivo, 0, SEEK_SET);

    
      for (int i = 0; i < filas; i++) {
          fscanf(archivo, "%s %d %f", nombre[i], &cantidad[i], &precio[i]);
      }

      
      printf("Que desea editar sobre el producto?\n");
      printf("1. Nombre\n");
      printf("2. Cantidad\n");
      printf("3. Precio\n");
      int opcion = leerEnteroEntre("Opcion: ", 1, 3);

      if (opcion == 1) {
          printf("Ingrese el nuevo nombre del producto: ");
          scanf(" %s", nombre[productoAEditar - 1]);
      } else if (opcion == 2) {
          printf("Ingrese la nueva cantidad de productos: ");
          scanf("%d", &cantidad[productoAEditar - 1]);
      } else if (opcion == 3) {
          printf("Ingrese el nuevo precio: ");
          scanf("%f", &precio[productoAEditar - 1]);
      }

     
      fseek(archivo, 0, SEEK_SET);

      
      for (int i = 0; i < filas; i++) {
          fprintf(archivo, "%s %d %.2f\n", nombre[i], cantidad[i], precio[i]);
      }

      fclose(archivo);
      printf("Producto editado\n");
}


void mostrarDatosArchivo(const char datos[]) {
    FILE *archivo;
    archivo = fopen("datos.txt", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char nombre[50][20];
    int cantidad[50];
    float precio[50];
    int filas = 0;
    float total, acumulador = 0;

    while (fscanf(archivo, "%s %d %f", nombre[filas], &cantidad[filas], &precio[filas]) == 3 && filas < 50) {
        filas++;
    }

    fclose(archivo);

    if (filas == 0) {
        printf("No hay productos ingresados para mostrar.\n");
        return;
    }

    printf("Producto\t\t  Cantidad\t\tPrecio\t\tTotal\n");

    for (int i = 0; i < filas; i++) {
        total = cantidad[i] * precio[i];
        acumulador += total;
        printf("%d.%s\t\t\t\t %d \t\t\t%.2f\t\t%.2f\n", i + 1, nombre[i], cantidad[i], precio[i], total);
    }

    printf("\t\t\t\t\t\t\t\t\t\t\tTotal %.2f\n", acumulador);
}

void eliminarProductoArchivo(const char datos[]) {
    FILE *archivo;
    archivo = fopen("datos.txt", "r+");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char nombre[50][20];
    int cantidad[50];
    float precio[50];
    int filas = 0;

    while (fscanf(archivo, "%s %d %f", nombre[filas], &cantidad[filas], &precio[filas]) == 3 && filas < 50) {
        filas++;
    }

    fclose(archivo);

    if (filas == 0) {
        printf("No hay productos ingresados para mostrar.\n");
        return;
    }

    int productoAEliminar;
    printf("Ingrese el numero del producto que desea eliminar: ");
    scanf("%d", &productoAEliminar);

    if (productoAEliminar < 1 || productoAEliminar > filas) {
        printf("Número de producto inválido. No se realizará ninguna eliminación.\n");
        return;
    }


    archivo = fopen("datos.txt", "w");


    for (int i = 0; i < filas; i++) {
        if (i != productoAEliminar - 1) {
            fprintf(archivo, "%s %d %.2f\n", nombre[i], cantidad[i], precio[i]);
        }
    }

    fclose(archivo);

    printf("Producto eliminado.\n");
}

int leerEntero(char* mensaje){
  int valor;

    printf("%s",mensaje);
    scanf("%d",&valor);

  return valor;

}
int leerEnteroPositivo(char* mensaje){
  int valor;
  do{
     printf("%s",mensaje);
      scanf("%d",&valor);

  }while(valor<=0);
  return valor;

}

int leerEnteroEntre (char* mensaje, int min, int max){
  int valor;
  do {
    printf("%s",mensaje);
    scanf("%d",&valor);
  }while(valor<min || valor>max);
  return valor;
}


float leerFlotantePositivo(char* mensaje){
  float valor;
  do{
    printf("%s",mensaje);
    scanf("%f",&valor);

  }while(valor<=0);
  return valor;
}

float leerFlotante(char* mensaje){
  float valor;

  printf("%s",mensaje);
  scanf("%f",&valor);
  return valor;

}

float leerFlotanteEntre (char* mensaje, float min, float max){
  float valor;
  do {
    printf("%s",mensaje);
    scanf("%f",&valor);
  }while(valor<min || valor>max);
  return valor;
}

int menu (){
  int opcion=0;
  printf ("Menu\n");
  printf ("1. Ingresar productos\n");
  printf("2. Editar productos\n");
  printf("3. Eliminar productos\n");
  printf("4. Lista de productos ingresados\n");
  printf("5. Salir\n");
  return leerEnteroEntre("Ingrese un numero: ",1,5);
}

void datos(char nombre[][20], int cantidad[], float precio[], int *filas) {
    int i;
    for (i = 0; i < *filas; i++) {
        printf("Ingrese el nombre del producto %d: ", i + 1);
        scanf(" %s", nombre[i]);
        cantidad[i] = leerEnteroPositivo("Ingrese la cantidad de productos: ");
        precio[i] = leerFlotantePositivo("Ingrese el precio de los productos: ");
    }
}