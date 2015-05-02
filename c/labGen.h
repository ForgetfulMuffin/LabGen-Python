
#ifndef LABGEN
#define LABGEN 1

struct _coord {
  int x,y;
};

typedef struct _coord coord;

struct _area {
  char north, south, east, west;
};

typedef struct _area area;

typedef area * map;

map * generate();
map * createEmpty();
void createMaze(map *, coord*, int *, coord *, int *);
void printMap(map *);

#endif
