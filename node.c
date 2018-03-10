#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "node.h"

ELEMINST *creationInstruction(int categorie, int parametre, ELEMINST* programme, ELEMINST* suivant){
  ELEMINST *newElem = (ELEMINST*)malloc(sizeof(ELEMINST));
  newElem->categorie = categorie;
  newElem->parametre = parametre;
  newElem->programme = programme;
  newElem->suivant = suivant;
  return newElem;
}

// see the commands on the screen
void affiche(ELEMINST* pinst){
  if (pinst != NULL){
    if (pinst->categorie==INST_REPEAT){
      printf("REPEAT %d [\n", pinst->parametre);
      affiche(pinst->programme);
      printf("]\n");
    }else{
      if (pinst->categorie==INST_FORWARD)
        printf("FORWARD %d\n", pinst->parametre);
      if (pinst->categorie==INST_LEFT)
        printf("LEFT %d\n", pinst->parametre);
      if (pinst->categorie==INST_RIGHT)
        printf("RIGHT %d\n", pinst->parametre);
      if (pinst->categorie==INST_CIRCLE)
        printf("CIRCLE %d\n", pinst->parametre);
    }
    affiche(pinst->suivant);
  }
}

ELEMINST *ajoutInstruction(ELEMINST* prog, ELEMINST* inst){
  inst->suivant = prog;
  return inst;
}

// the header of svg
void svg_begin(){
  flogo = fopen("logo.svg","w");
  fprintf(flogo,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
  fprintf(flogo,"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.0\" width=\"600\" height=\"300\">\n");
  fprintf(flogo,"<title>Projet TC-LOGO</title>\n");
  fprintf(flogo,"<desc>LOGO de ZHANG Zhiyi</desc>\n");
}

// the ending of svg
void svg_end(){
  fprintf(flogo,"</svg>\n");
}

// write svg in the file
void svg(ELEMINST* pinst, char* color){
  int i;
  if (pinst != NULL){
      switch(pinst->categorie){
        case INST_FORWARD:
          fprintf(flogo,"<line x1=\"%f\" y1=\"%f\" ",cor_x,cor_y);
	  cor_x = cor_x + pinst->parametre * cos(PI*direction/180);
	  cor_y = cor_y + pinst->parametre * sin(PI*direction/180);
	  fprintf(flogo,"x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n",cor_x,cor_y,color);
	  break;

	case INST_LEFT:
	  direction = direction - pinst->parametre;
	  break;

	case INST_RIGHT:
	  direction = direction + pinst->parametre;
	  break;

        case INST_CIRCLE:
          fprintf(flogo,"<circle cx=\"%f\" cy=\"%f\" r=\"%d\" stroke=\"%s\" fill=\"%s\"/>\n",cor_x,cor_y,pinst->parametre,color,color);
          break;

	case INST_REPEAT:
	  for (i=1;i<=pinst->parametre;i++){
	    svg(pinst->programme,color);
	  }
	  break;
      }	
	svg(pinst->suivant,color);  
  }
}

// release the memories used
void supprimer(ELEMINST* pinst){
  if (pinst != NULL){
    supprimer(pinst->programme);
    supprimer(pinst->suivant);
    free(pinst);
  }
}
