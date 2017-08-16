#include<iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

int comparaString(char *cadena1, char *cadena2);
int coutTokens(char *ins);
void guardarInst(char *inst);
void compararInts(string  set[],string ins []);
char* ObtenerOperador(char *inst);
void imprimirIns(char *inst);

struct compilado{
string num;
char *numOP;
char *inst;
char *operador;
char *operando;
};


string itoa(int num)
{
  stringstream s;
  s<<num;
  return s.str();
}
void imprimirIns(char *inst){
  cout<<"RESULTADOS"<<endl;
  cout<<inst<<endl;
}


char* compararINST(char *inst){
  char *retorno;
  if(comparaString(inst,"STAA")==0){
    retorno="C9";
  }else if(comparaString(inst,"STAB")==0){
    retorno="C7";
  }else if(comparaString(inst,"LDAB")==0){
    retorno="D6";
  }else if(comparaString(inst,"LDAA")==0){
    retorno="D5";
  }else if(comparaString(inst,"SWI")==0){
    retorno="F5";
  }else{
    if (inst!=NULL){
    char *num = ObtenerOperador(inst);
    retorno=num;
   }
  }
  return retorno;

}

int coutTokens(char *ins){
  int count =0,i;
  char *str = ins;

  while(*str){
      cout<<" "<<*str;
      if(*str == ' '){
          count++;
       }
       str++;
  }
  cout<<"NUMERO DE TROZOS: "<<count<<endl;
  return count;
}
void menu(char *arg){
    int op=0;
      cout<<"\n ****USTED HA FINALIZADO QUE DESEA HACER****";
      cout<<"\n ****   1. GUARDAR Y SALIR        **********";
      cout<<"\n ****   2. VER Y GUARDAR          **********";
      cout<<"\n ****   3. SALIR                  **********";
    do{
      cout<<"\n SU OPCION: ";
      cin>>op;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(),'\n');
      switch(op){
        case 1:
            guardarInst(arg);
        break;
        case 2:
            imprimirIns(arg);
        break;
        case 3:
            exit(0);
        break;

      }
    }while(op>3);

}

int main()
{
    int fin=1;
    int i=0;
    compilado assem[50];
    int n=0;
    char aux='0';
    char cadena[14];
    char tex[200];
    cout<<"Escriba las instrucciones:\n";
    do{
     cin.getline(cadena,10);
     cin.clear();
     if (comparaString(cadena,"FIN")==0){
        break;
     }
     if (comparaString(cadena,"SWI")==0){
         n=i;
         assem[i].num=itoa(n);
         assem[i].inst=cadena;
         assem[i].operador=compararINST(cadena);
         assem[i].operando=" ";
         assem[i].numOP=" ";
     }else{
       char *aux=strtok(cadena," ");
       char *ins=aux;
       char *cod1=compararINST(aux);
       aux=strtok(NULL," ");
       char *cod2=compararINST(aux);
       char *numOP=aux;
     //}
       n=i+2;
       assem[i].num=itoa(n);
       assem[i].inst=ins;
       assem[i].operador=cod1;
       assem[i].operando=cod2;
       assem[i].numOP=numOP;
   }
    cout<<assem[i].num<<" "<<assem[i].operador<<" "<<assem[i].operando<<" "<<assem[i].inst<<" "<<assem[i].numOP<<endl;
     strcat(tex,assem[i].operador);
     strcat(tex," ");
     strcat(tex,assem[i].operando);
     strcat(tex," ");
     strcat(tex,assem[i].inst);
     strcat(tex," ");
     strcat(tex,assem[i].numOP);
     strcat(tex,"\n");
     memset(cadena,0,strlen(cadena));
     i++;
    }while(fin==1);
    menu(tex);
    return 0;
}

void guardarInst(char *inst){
    FILE *arch;
    int i=0;
    char nombre[20];
    char tex[200];

    cout<<"Escriba el nombre de su archivo: ";
    cin>>nombre;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    strcat(nombre,".txt");
    arch=fopen(nombre,"w+");

    while(*inst){
     tex[i]=*inst;
     inst++;
     i++;
    }
    tex[i-1]='\0';

    fputs(tex,arch);
    printf("\nEL ARCHIVO SE HA GUARDADRO EXITOSAMENTE!!!!");
    fclose(arch);
}

int comparaString(char *cadena1, char *cadena2){
     int valor=0;
    if (!strcmp(cadena1,cadena2)){
    while(*cadena1){
        if (*cadena1!=*cadena2){
            valor++;
            break;
        }
            cadena1++;
            cadena2++;
        }
    if (valor==strlen(cadena1)){
       return 0;
    }
    }else{
      return 1;
    }
}

char* ObtenerOperador(char *inst){
  char *aux=strtok(inst,"$");
  aux=strtok(inst,"$");
  return aux;
}
