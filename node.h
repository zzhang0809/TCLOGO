#ifndef _NODE_H
#define _NODE_H

#define INST_FORWARD 0
#define INST_LEFT 1
#define INST_RIGHT 2
#define INST_REPEAT 3
#define INST_CIRCLE 4
#define PI 3.14159265

struct elem_inst {
  int categorie;
  int parametre;
  struct elem_inst *programme;
  struct elem_inst *suivant;
};
typedef struct elem_inst ELEMINST;
typedef ELEMINST *inst;

double cor_x;
double cor_y;
int direction;

FILE* flogo;
static inst pinst;
ELEMINST *creationInstruction(int categorie, int parametre, ELEMINST* programme, ELEMINST* suivant);
void affiche(ELEMINST* pinst);
ELEMINST *ajoutInstruction(ELEMINST* prog, ELEMINST* inst);
void svg_begin();
void svg(ELEMINST *pinst, char* color);
void svg_end();
void supprimer(ELEMINST* pinst);

#endif
