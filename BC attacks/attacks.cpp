#include "connectDoS.h"

int main(int argc, char *argv[]){

  arg arg = argParse(argc, argv);
  switch (PROGRAM) {
    case DOS:
      dos_attack dos_attack;
      dos_attack.Flood(arg);
      break;
    case MAP:
      mapping map;
      map.openCon(arg);
      break;
    case DOSC:
      connectDoS dosC;
      dosC.openCon(arg);
      break;
    default:
      break;
  }

  //free(arg);
  return 0;
}
