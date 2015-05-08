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

map * generate(const int);
void createEmpty(map **,const int);
void createMaze(map *, coord*, int *, coord *, int *, const int);
void printMap(map *, const int);

#endif
