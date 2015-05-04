#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "labGen.h"

#define SIZE 6

//======main()======//
int main(){
  srand(time(NULL));
  printf("====Program Start===\n");
  map * test = generate();
  printMap(test);
  return 0;
}

//===definitions====//
map * generate(){
  printf("======Generate======\n");
  map * gameMap = NULL;
  createEmpty(&gameMap);
  printf("=Exited createEmpty=\n");
  coord * path = (coord *)malloc((SIZE)*(SIZE)*sizeof(coord));
  printf("=Created empty path=\n");
  int pathNum = 0;
  coord visiting;
  visiting.x = (int)(rand()%SIZE);
  visiting.y = (int)(rand()%SIZE);
  printf("=Created rand start=\n");
  int visited = 1;
  path[pathNum] = visiting;
  for (int k = visited; k < SIZE*SIZE; k ++){
    path[k].x = 0;
    path[k].y = 0;
  }
  printf("===Set path start===\n");
  while (visited < SIZE*SIZE){
    createMaze(gameMap, &visiting, &visited, path, &pathNum);
  }
  printf("===Maze generated===\n");
  printf("=====Path is Free===\n");
  return gameMap;
}

void createEmpty(map ** emptyMap){
  printf("=====createEmpty====\n");
  * emptyMap = (map *)malloc(SIZE*sizeof(area *));
  printf("===Map allocated====\n");
  for (int k = 0; k < SIZE; k++){
   (* emptyMap)[k] = (area *)malloc(SIZE*sizeof(area));
  }
  printf("===Areas allocated==\n");
  for (int i = 0; i < SIZE; i++){
    printf("======Column %d======\n",i);
    for (int j = 0; j < SIZE; j++){
      ((*emptyMap)[i][j]).north = 0;
      ((*emptyMap)[i][j]).south = 0;
      ((*emptyMap)[i][j]).east = 0;
      ((*emptyMap)[i][j]).west = 0;
    }
    printf("Walls Placed in %d, y\n",i);
  }
  printf("===Empty finished===\n");
}

void createMaze(map * gameMap, coord * visiting, int * visited , coord * path, int * pathNum){

  for (int t = *visited; t < SIZE*SIZE; t ++){
    printf("path.x = %d || ",path[t].x);
    printf("path.y = %d\n",path[t].y);
  }
  printf("======createMaze====\n");
  int chosen = 0;
  int n = 0;
  int s = 0; 
  int e = 0; 
  int w = 0; 
  int dir = 0;
  printf("===Set variables====\n");
  printf(">>>>>>>Coords (%d, %d)\n",visiting->x,visiting->y);

  if(visiting->x > 0){
    if ((gameMap[visiting->x-1][visiting->y]).north == 0 && (gameMap[visiting->x-1][visiting->y]).south == 0 && (gameMap[visiting->x-1][visiting->y]).east == 0 && (gameMap[visiting->x-1][visiting->y]).west == 0){
      n = 1;
    }
  }
  if(visiting->x < SIZE-1){
    if ((gameMap[visiting->x+1][visiting->y]).north == 0 && (gameMap[visiting->x+1][visiting->y]).south == 0 && (gameMap[visiting->x+1][visiting->y]).east == 0 && (gameMap[visiting->x+1][visiting->y]).west == 0){
      s = 1;
    }
  }
  if(visiting->y > 0){
    if ((gameMap[visiting->x][visiting->y-1]).north == 0 && (gameMap[visiting->x][visiting->y-1]).south == 0 && (gameMap[visiting->x][visiting->y-1]).east == 0 && (gameMap[visiting->x][visiting->y-1]).west == 0){
      w = 1;
    }
  }
  if(visiting->y < SIZE-1){
    if ((gameMap[visiting->x][visiting->y+1]).north == 0 && (gameMap[visiting->x][visiting->y+1]).south == 0 && (gameMap[visiting->x][visiting->y+1]).east == 0 && (gameMap[visiting->x][visiting->y+1]).west == 0){
      e = 1;
    }
  }

  printf("-n=%d, s=%d, e=%d, w=%d\n",n,s,e,w);
  printf("=Checked Directions=\n");
  if (n+s+e+w > 0){
    while (chosen == 0){
      dir = (int)(rand()%4);
      if (dir == 0 && w == 1){
        //        printf(">>>>>WEST\n");
        chosen = 1;
        (gameMap[visiting->x][visiting->y]).west = 1;
        (gameMap[visiting->x][visiting->y-1]).east = 1;
        //        printf("<><><>Added door\n");
        visiting->y -= 1;
        *pathNum += 1;
        path[*pathNum].x = visiting->x;
        path[*pathNum].y = visiting->y;
        //        printf("[][][]Changed path\n");
        (*visited) += 1;
      }

      else if (dir == 1 && e == 1){
        //        printf(">>>>>EAST\n");
        chosen = 1;
        (gameMap[visiting->x][visiting->y]).east = 1;
        (gameMap[visiting->x][visiting->y+1]).west = 1;
        //        printf("<><><>Added door\n");
        visiting->y += 1;
        *pathNum += 1;
        path[*pathNum].x = visiting->x;
        path[*pathNum].y = visiting->y;
        //        printf("[][][]Changed path\n");
        (*visited) += 1;
      }

      else if (dir == 2 && s == 1){
        //        printf(">>>>>SOUTH\n");
        chosen = 1;
        (gameMap[visiting->x][visiting->y]).south = 1;
        (gameMap[visiting->x+1][visiting->y]).north = 1;
        //        printf("<><><>Added door\n");
        visiting->x += 1;
        *pathNum += 1;
        path[*pathNum].x = visiting->x;
        path[*pathNum].y = visiting->y;
        //        printf("[][][]Changed path\n");
        (*visited) += 1;
      }

      else if (dir == 3 && n == 1){
        //        printf(">>>>>NORTH\n");
        chosen = 1;
        (gameMap[visiting->x][visiting->y]).north = 1;
        (gameMap[visiting->x-1][visiting->y]).south = 1;
        //        printf("<><><>Added door\n");
        visiting->x -= 1;
        *pathNum += 1;
        path[*pathNum].x = visiting->x;
        path[*pathNum].y = visiting->y;
        //        printf("[][][]Changed path\n");
        (*visited) += 1;
      }
    }
  }
  else {
    //    printf(">>>>>BACK\n");
    *pathNum -=1;
    visiting->x = path[*pathNum].x;
    visiting->y = path[*pathNum].y;
    //    printf("[][][]Changed path\n");
  }
}

void printMap(map * gameMap){
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      if (gameMap[i][j].west == 0){
        printf("|");
      }
      else {
        printf(" ");
      }
      if (gameMap[i][j].north == 0 && gameMap[i][j].south == 0){
        printf("=");
      }
      else if (gameMap[i][j].north == 0){
        printf("^");
      }
      else if (gameMap[i][j].south == 0){
        printf("_");
      }
      else {
        printf(" ");
      }
      if (gameMap[i][j].east == 0){
        printf("|");
      }
      else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

