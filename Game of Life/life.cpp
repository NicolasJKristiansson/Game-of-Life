#include "life.h"

Life::Life() : dim(6), wrap(false){
    for(int k = 0; k < dim; k++){
        std::vector<bool> row;
        for(int j = 0; j < dim; j++){
            if(j/(k+1) == k/(j+1)){
                row.push_back(true);
            }
            else{
                row.push_back(false);
            }
        }
        world.push_back(row);
    }
}

Life::Life(int d, bool w) : dim(d), wrap(w){
    for(int k = 0; k < dim; k++){
        std::vector<bool> row;
        for(int j = 0; j < dim; j++){
            row.push_back(false);
        }
        world.push_back(row);
    }
}

/// TODO: find way to consolidate both constructors elegantly

int Life::getDim(){
    return dim;
}

bool Life::getCell(int x, int y){
    return world[x][y];
}

void Life::modCell(int x, int y, bool live){
    world[x][y] = live;
}

bool Life::getRefreshedCell(int x, int y){
    int no_adj = 0;
    int status;
    for(int k = 1; k <= 8; k++){
        if(getAdjCell(x,y,k)){
            no_adj++;
        }
    }
    if(no_adj < 2){
        status = false;
    } else if(no_adj == 2){
        status = world[x][y];
    } else if(no_adj == 3){
        status = true;
    } else{
        status = false;
    }
    return status;
}

void Life::refreshWorld(){
    std::vector<std::vector<bool> > snapshot;
    for(int k = 0; k < dim; k++){
        std::vector<bool> row;
        for(int j = 0; j < dim; j++){
            row.push_back(getRefreshedCell(k,j));
        }
        snapshot.push_back(row);
    }
    world = snapshot;
}

void Life::clearWorld(){
    for(int k = 0; k < dim; k++){
        for(int j = 0; j < dim; j++){
            world[k][j] = false;
        }
    }
}

void Life::simWorld(int n){
    for(int k = 0; k < n; k++){
        refreshWorld();
    }
}

bool Life::getAdjCell(int x, int y, int dir){
    bool adj = false;
    switch(dir){
    /** Moves counter-clockwise starting from the right (think unit circle)
        4 3 2
        5 O 1
        6 7 8
    **/
    case 1 :
        if(x+1 <= dim-1){
            adj = getCell(x+1,y);
        }
        else if(wrap){
            adj = getCell(0,y);
        }
        break;
    case 2 :
        if(x+1 <= dim-1 && y-1 >= 0){
            adj = getCell(x+1,y-1);
        }
        else if(wrap){
            if(x == dim-1 && y == 0){
                adj = getCell(0,dim-1);
            } else if(x == dim-1){
                adj = getCell(0,y-1);
            } else if(y == 0){
                adj = getCell(x+1,dim-1);
            }
        }
        break;
    case 3 :
        if(y-1 >= 0){
            adj = getCell(x,y-1);
        }
        else if(wrap){
            adj = getCell(x,dim-1);
        }
        break;
    case 4 :
        if(x-1 >= 0 && y-1 >= 0){
            adj = getCell(x-1,y-1);
        }
        else if(wrap){
            if(x == 0 && y == 0){
                adj = getCell(dim-1,dim-1);
            } else if(x == 0){
                adj = getCell(dim-1,y-1);
            } else if(y == 0){
                adj = getCell(x-1,dim-1);
            }
        }
        break;
    case 5 :
        if(x-1 >= 0){
            adj = getCell(x-1,y);
        }
        else if(wrap){
            adj = getCell(dim-1,y);
        }
        break;
    case 6 :
        if(x-1 >= 0 && y+1 <= dim-1){
            adj = getCell(x-1,y+1);
        }
        else if(wrap){
            if(x == 0 && y == dim-1){
                adj = getCell(dim-1,0);
            } else if(x == 0){
                adj = getCell(dim-1,y+1);
            } else if(y == dim-1){
                adj = getCell(x-1,0);
            }
        }
        break;
    case 7 :
        if(y+1 <= dim-1){
            adj = getCell(x,y+1);
        }
        else if(wrap){
            adj = getCell(x,0);
        }
        break;
    case 8 :
        if(x+1 <= dim-1 && y+1 <= dim-1){
            adj = getCell(x+1,y+1);
        }
        else if(wrap){
            if(x == dim-1 && y == dim-1){
                adj = getCell(0,0);
            } else if(x == dim-1){
                adj = getCell(0,y+1);
            } else if(y == dim-1){
                adj = getCell(x+1,0);
            }
        }
        break;
    default :
        return false;
    }
    return adj;
}
