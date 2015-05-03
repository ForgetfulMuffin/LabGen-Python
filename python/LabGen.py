#!/usr/bin/python
import random
map=[]
path=[]
visited=0
i=0
j=0

#===============================
# INITIALISATION
#===============================

def generate(): # Fonction principale du module
    global i,j,visited,size
    createEmpty()
    visiting = random.randint(0,size - 1),random.randint(0,size - 1)
    i = visiting[0]
    j = visiting[1]
    path.append(visiting)
    visited = 1

    while visited < size*size :
        createMaze()
    addExits()

def createEmpty(): # Cree une carte vide caree de size*size cases.
    global size
    for i in range (size):
        map.append([])
        for j in range (size):
            map[i].append({'north':0,'south':0,'east':0,'west':0,'visited' : 0})

    
def createMaze(): # Cree un labyrinthe parfait (bas de boucles, pas de zones innaccessibles)
    global size
    global visited,i,j
    chosen = 0
    n = 0
    s = 0
    e = 0
    w = 0
    dir = 0

    if i>0 :
        if map[i-1][j]['north']== 0 and map[i-1][j]['south']== 0 and map[i-1][j]['east']== 0 and map[i-1][j]['west']== 0 :
            n = 1
    if i<size - 1 :
        if map[i+1][j]['north']== 0 and map[i+1][j]['south']== 0 and map[i+1][j]['east']== 0 and map[i+1][j]['west']== 0 :
            s = 1
    if j>0 :
        if map[i][j-1]['north']== 0 and map[i][j-1]['south']== 0 and map[i][j-1]['east']== 0 and map[i][j-1]['west']== 0 :
            w = 1
    if j<size - 1 :
        if map[i][j+1]['north']== 0 and map[i][j+1]['south']== 0 and map[i][j+1]['east']== 0 and map[i][j+1]['west']== 0 :
            e = 1
    if n+s+e+w > 0:
        while chosen == 0:
            dir = random.randint(0,3)
            if dir == 0 and w == 1:
                chosen = 1
                map[i][j]['west'] = 1
                map[i][j-1]['east'] = 1
                j = j - 1
                visiting = i,j
                path.append(visiting)
                visited = visited + 1
                printMap()
                print 'west'
            elif dir == 1 and e == 1:
                chosen = 1
                map[i][j]['east'] = 1
                map[i][j+1]['west'] = 1
                j = j + 1
                visiting = i,j
                path.append(visiting)
                visited = visited + 1
                printMap()
                print 'east'
            elif dir == 2 and s == 1:
                chosen = 1
                map[i][j]['south'] = 1
                map[i+1][j]['north'] = 1
                i = i + 1
                visiting = i,j
                path.append(visiting)
                visited = visited + 1
                printMap()
                print 'south'
            elif dir == 3 and n == 1:
                chosen = 1
                map[i][j]['north'] = 1
                map[i-1][j]['south'] = 1
                i = i - 1
                visiting = i,j
                path.append(visiting)
                visited = visited + 1
                printMap()
                print 'north'
    else:
         print 'BACK'
         path.pop(len(path)-1)
         i = path[len(path) - 1][0]
         j = path[len(path) - 1][1]
    map[0][0]['visited'] = 1

def printMap(): # Affiche un visuel de la carte. Destine aux developpeurs. (^ signifie un mur au nord, _ au sud, = les deux and | a l'est ou a l'ouest en fonction du cote.)
    global size
    line=[]
    for i in range (size): 
        line.append('')
        for j in range (size):
            if map[i][j]['west']== 0:
                line[i]=line[i]+'|'
            else:
                line[i]=line[i]+' '
            if map[i][j]['north']== 0 and map [i][j]['south']== 0:
                line[i]=line[i]+'='
            elif map[i][j]['north']== 0:
                line[i]=line[i]+'^'
            elif map[i][j]['south']== 0:
                line[i]=line[i]+'_'
            else:
                line[i]=line[i]+' '
            if map[i][j]['east']== 0:
                line[i]=line[i]+'|'
            else:
                line[i]=line[i]+' '
        print line[i]

def addExits(): # Ajoute des sorties (condition de victoire) au labyrinthe au sud and/ou a l'est
    global size
    quantum = random.randint(2,4)
    for exit in range(quantum):
        side = random.randint(0,1)
        if side == 0:
            map[size - 1][random.randint(0,size - 1)]['south'] = 2
        else:
            map[random.randint(0,size - 1)][size - 1]['east'] = 2

def setVisited(position):
	map[position[0]][position[1]]["visited"] = 1

#========================================
# ACCESSEURS
#========================================

def check(position, direction): # Verifie la presence d'un mur dans la direction demandee and renvoie la reponse.
    answer = map[position[0]][position[1]][direction]
    return answer

def getDescript(position): # Genere la description de la zone dans laquelle se trouve le joueur and la renvoie.
    n = check(position,'north')
    s = check(position,'south')
    e = check(position,'east')
    w = check(position,'west')
    descript = 'The area you are in has'
    if n>0 and s+e+w>0 :
        descript = descript + " an exit heading north"
        if s > 0 and e+w>0:
            descript = descript + ", an exit heading south"
            if e>0 and w>0:
                descript = descript + ", an exit heading east and an exit heading west."
            elif e>0 and w==0:
                descript = descript + " and an exit heading east."
            else :
                descript = descript + " and an exit heading west."
        elif s>0 :
            descript = descript + " and an exit heading south."
        elif e>0 and w>0:
            descript = descript + ", an exit heading east and an exit heading west."
        elif e>0 and w==0:
            descript = descript + " and an exit heading east."
        else:
            descript = descript + " and an exit heading west."
    elif n>0:
        descript = descript + " an exit heading north."
    elif s > 0 and e+w>0:
        descript = descript + " an exit heading  south"
        if e>0 and w>0:
            descript = descript + ", an exit heading east and an exit heading west."
        elif e>0 and w==0:
            descript = descript + " an exit heading east."
        else:
            descript = descript + " and an exit heading west."
    elif s>0:
        descript = descript + " an exit heading south."
    elif e>0 and w>0:
        descript = descript + " an exit heading east and an exit heading west."
    elif e>0 and w==0:
        descript = descript + " an exit heading east."
    else:
        descript = descript + " an exit heading west."
    return descript

def getAltDescript(position): # Ajoute quelques informations a la description de base
    descript = getDescript(position)
    s = check(position,'south')
    e = check(position,'east')
    if s == 2:
        descript += " ~~~~~~~~~~~~~~~~~~~~~~~~~ The suthern exit is particularly bright."
    if e == 2:
        descript += " ~~~~~~~~~~~~~~~~~~~~~~~~~ The eastern exit is particularly bright."
    return descript

def getVisited(position): # Renvoie si la zone a deja ande visitee
    return map[position[0]][position[1]]["visited"]


#================
# Lancement
#================

size = input("Veuillez entrer un nombre entier s'il vous plait : ")
generate()
