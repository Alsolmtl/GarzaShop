/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alsolmtl
 *
 * Created on 7 de octubre de 2021, 19:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
/*
 * 
 */
struct articulos{
    int clave;
    char NomArticulo[30];
    int cantidad;
    float precio;
};

void alta(){
    int i,n;
    struct articulos garza;
    FILE *ap;
    printf("Cuántos artículos vas a registrar: ");
    scanf("%d",&n);
    ap=fopen("garza.txt","w");
    if(ap!=NULL){
        for(i=0;i<n;i++){
            printf("Clave del artículo %d: ",i+1);
            scanf("%d",&garza.clave);
            printf("Nombre del artículo %d: ",i+1);
            __fpurge(stdin);
            gets(garza.NomArticulo);
            printf("Unidades del artículo %d: ",i+1);
            scanf("%d",&garza.cantidad);
            printf("Precio del artículo %d: ",i+1);
            scanf("%f",&garza.precio);
            fwrite(&garza,sizeof(struct articulos),1,ap);
        }
    fclose(ap);
    }
    else
        printf("Error en la apertura del archivo.");
}

int muestraRegistros(struct articulos *p){
    FILE *ap;
    int i=0,n;
    ap=fopen("garza.txt","r");
    if(ap!=NULL){
        while(!feof(ap)){
            fread(&(*p),sizeof(struct articulos),1,ap);
            p++;
            i++;
        }
        p-=i;
        n=i-1;
        fclose(ap);
        /*printf("\n\nLos articulos disponibles son: \n");
        for(i=0;i<n;i++,p++)
            printf("%d: %d %s $%.2f En almacen: %d\n",i+1,p->clave,p->NomArticulo,p->precio,p->cantidad);*/
    }
    else
        printf("Error en la apertura del archivo para la venta.");
    return n;
}

void muestraMemoria(struct articulos *p, int n){
    int i=0;      
    printf("\n\nLos articulos disponibles son: \n");
    for(i=0;i<n;i++,p++)
        printf("%d: %d %s $%.2f En almacen: %d\n",i+1,p->clave,p->NomArticulo,p->precio,p->cantidad);    
}

void venta(){
    FILE *ap;
    struct articulos garza[100];
    int i=0,n,clave,op;
    float total;
    total=0;
    n=muestraRegistros(&garza);
    do{      
        muestraMemoria(&garza,n);  
        printf("Clave del artículo a vender: ");
        scanf("%d",&clave);
        for(i=0;i<n;i++){
            if(garza[i].clave==clave){
                garza[i].cantidad--;
                total+=garza[i].precio;
                break;
            }
        }
        printf("Artículo %d, vendido.\n¿Deseas otra venta 1=Sí 0=No? ",garza[i].clave);
        scanf("%d",&op);
        if(garza[i].cantidad<=5)
            printf("\nAlerta!!!! El artículo %d %s tiene %d unidades. Se requiere la compra para tener en stock.",garza[i].clave,garza[i].NomArticulo,garza[i].cantidad);
    }while(op==1);
    printf("El monto a pagar es de: %.2f\n\nLo que hay en existencia es:\n",total);
    muestraMemoria(&garza,n);
    ap=fopen("garza.txt","w");
    if(ap!=NULL)
        for(i=0;i<n;i++){
            fwrite(&garza[i],sizeof(struct articulos),1,ap);
        }
    else
        printf("Error en la apertura del archivo depués de las ventas.");
}

void verAlmacen(){
    int i,n;
    struct articulos garza[100];
    n=muestraRegistros(&garza);
    muestraMemoria(&garza,n);
    for(i=0;i<n;i++)
        if(garza[i].cantidad<=5)
            printf("\nAlerta!!!! El artículo %d %s tiene %d unidades. Se requiere la compra para tener en stock.",garza[i].clave,garza[i].NomArticulo,garza[i].cantidad);
}

int main(int argc, char** argv) {
    int op;
    printf("¿Que tarea deseas realizar? \n1:Dar de alta artículos \n2:Venta de articulos\n3:Consulta de almacen\n-> ");
    scanf("%d",&op);
    if(op==1)
        alta();
    else{
        if(op==2)
            venta();    
        else
            verAlmacen();
    }
    return (EXIT_SUCCESS);
}

