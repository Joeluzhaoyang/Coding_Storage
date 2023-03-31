#include "wolf.h"
#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 4
 * 
 * Place a copy of this Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putSelf().
*/
void Wolf::putSelf(Grid* nextGrid, const int x, const int y) {
    Wolf* copyWolf = new Wolf(*this);
    bool tof = putAnimal(copyWolf,nextGrid,x,y);
    if(tof)
    {setNextSelf(copyWolf);}
}

/**
 * TODO: TASK 4
 * 
 * Place a brand new Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putClone().
*/
void Wolf::putClone(Grid* nextGrid, const int x, const int y) const {
    Wolf* newWolf = new Wolf(this->getBoard());
    bool tof = putAnimal(newWolf,nextGrid,x,y);
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::eat().
 * The only difference is that Wolf eats Sheep instead of Grass.
*/
void Wolf::eat(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
        if(adjEntity->toChar() == 'S')
        {
            adjEntity->removeSelf(nextGrid);
            this->setHungerCounter(WOLF_HUNGER_COOLDOWN);
            break;
        }
    }
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::breed().
 * The only difference is that Wolf breeds by finding a Wolf instead of Sheep.
*/
void Wolf::breed(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
        if(adjEntity->toChar() == 'W'){
            int nextPos = getRandomMovementIndex(nextGrid);
            if(nextPos != -1){
                int newX = getX() + getAdjX(nextPos);
                int newY = getY() + getAdjY(nextPos);
                Wolf* smallWOlf = new Wolf(this->getBoard());

                //smallSheep->putSelf(nextGrid,newX,newY);
                putAnimal(smallWOlf, nextGrid,newX,newY);
                this->setBreedCounter(WOLF_BREED_COOLDOWN);
            }
        }
    }
}

/**
 * TODO: TASK 4
 * 
 * If there is at least one Sheep on the board, Wolf tries to move towards it.
 * 
 * You should loop over the board in the same order as Board calling update(), 
 * calculate Euclidean distance to each cell containing a Sheep, and keep track of the shortest distance found.
 * Ignore sheeps that have been eaten (removed).
 * No need to keep track of Sheeps with the same distance as shortest one found so far.
 * 
 * If a Sheep is found, move to the adjacent cell closest to that Sheep. If that cell is occupied with another Animal,
 * the Wolf stays at its position.
 * 
 * If no Sheep is found, the Wolf moves randomly like a Sheep.
 * 
 * You may follow the structure below to implement the function.
*/
void Wolf::move(Grid* nextGrid) {
    // First, find a sheep to target
    
    // ?
    Entity* closeSheep = nullptr;
    int closeDistance = 114514;
    
    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {

            // ?
            if(getBoard()->getGrid()->getCell(x,y) != nullptr){
                if(getBoard()->getGrid()->getCell(x,y)->toChar() == 'S' && getBoard()->getGrid()->getCell(x,y)->isRemoved() == false)
                {
                    Entity* tempSheep = getBoard()->getGrid()->getCell(x,y);
                    int tempX = tempSheep->getX() - this->getX();
                    int tempY = tempSheep->getY() - this->getY();
                    int tempDistance = tempX*tempX + tempY*tempY;
                    if(tempDistance < 0)
                        tempDistance = -tempDistance;
                    if(tempDistance < closeDistance){
                        closeSheep = tempSheep;
                        closeDistance = tempDistance;
                    }
                }
            }

        }
    }

    if (closeSheep != nullptr) { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it
        
        // ?
        int moveIndex = 114514;
        int moveDistance = 114514;
        for(int i = 0;i<9;++i){
            if (i == 4) continue;
            int adjX = closeSheep->getX() - (getX() + getAdjX(i));
            int adjY = closeSheep->getY() - (getY() + getAdjY(i));
            int tempDistance = adjX*adjX + adjY*adjY;
            
            if(tempDistance < moveDistance){
                moveDistance = tempDistance;
                moveIndex = i;
            }
        }
        int moveX = getX() + getAdjX(moveIndex);
        int moveY = getY() + getAdjY(moveIndex);

            if(this->getBoard()->getGrid()->getCell(moveX,moveY) == nullptr){//is empty
                putSelf(nextGrid,moveX,moveY);
            }
            else if(this->getBoard()->getGrid()->getCell(moveX,moveY)->toChar() == 'S' ||
            this->getBoard()->getGrid()->getCell(moveX,moveY)->toChar() == 'W'){//is animal
                putSelf(nextGrid,getX(),getY());
            }
            else{
                putSelf(nextGrid,moveX,moveY);//is grass
            }
    }
    else {
        // No sheep found, move randomly
        
        // ?
        bool ismoved = false;
        int i = getRandomMovementIndex(nextGrid);
 
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if(adjEntity == nullptr || adjEntity->toChar() == '.'){
            this->putSelf(nextGrid,adjX,adjY);
            ismoved = true;
        }
    
        if(ismoved == false){
        putSelf(nextGrid,this->getX(),this->getY());}    
    }
}