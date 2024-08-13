#include "colliders.hpp"
using namespace bn;
namespace colliders{
    arena::arena(int stage){
        this->cStage = stage;
    }
    bool arena::pointIn(fixed x, fixed y){
        switch(this->cStage){  
            case 0:
                if(x>-44 && y>39 && x<66 && y<50)return true;
                if(x<-55 && y>-3 && x>-150 && y<10)return true;
                if(x>80 && y>20 && y<30)return true;
                break;
            case 1:
                if(y>10 && x<65 && x>-65 && y<20)return true;
                if(y<-15 && x<45 && x>-45 && y>-25)return true;
                break;
            case 2:
                if(y>37 && x<40 && x>-65 && y<50)return true;
                if(y<-35 && y>-58 && x<15 && x>-35)return true;
                if(y<-10 && y>-20 && x>35 && x<70)return true;
                if(y<-10 && y>-20 && x<-57 && x>-90)return true;
                break;
            case 3:
                if(y>21 && x>-45 && x<30 && y<31)return true;
                if(y<-21 && x>-70 && x<-20 && y>-31)return true;
                if(y<8 && x<105 && x>55 && y>-2)return true;
                break;
            default:
                return false;
        }
        return false;
    }
}