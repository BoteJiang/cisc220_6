#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//Bote Jiang 10126930
//Jingyuan Chen 10152291
//Guanlin Lu 10199220

int dis1=1;
int dis2=1;
int dis3=1;
int dis4=1;
int dis5=1;
int win=0;
int winner=0;

void printline(int ply,int pos){
  if (pos==10){
    winner=ply;
    win=1;
    return;
  }
  char line[60]="|";
  int i=0;
  for (i=0;i<pos;i++){
    strcat(line,"~");
  }
  strcat(line,">");
  char*ptr=line;
  printf("Player %d%s\n",ply,line);

}

void callPrint(){
  printline(1,dis1);
  printline(2,dis2);
  printline(3,dis3);
  printline(4,dis4);
  printline(5,dis5);
}



void read(){
  int result=0;
  system("clear");

  callPrint();
  scanf("%d", &result);
}

void init(){

  while (dis1!=10){
    read();
    dis1++;
  }
  printf("Player %d wins!\n",winner);

}

int main(){
  init();
}
