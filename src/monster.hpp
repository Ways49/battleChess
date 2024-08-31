#pragma once
#include "skill.hpp"
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

//园区枪手
class gunner : public baseMonster{
public:
    gunner(int pos = 0) : baseMonster(3,1,1,pos){
        //pass
    }
    void nextRound() override{
        shoot.nextRound();
    }
protected:
    shootSkill shoot;
};

//园区警犬
class policeDog : public baseMonster{
public:
    policeDog(int pos = 0) : baseMonster(3,1,2,pos){
        //pass
    }
    void nextRound() override{
        accelerate.nextRound();
    }
protected:
    accelerateSkill accelerate;
};

//园区武装直升机
class gunship : public baseMonster{
public:
    gunship(int pos = 0) : baseMonster(5,2,2,pos){
        //pass
    }
    void nextRound() override{
        shoot.nextRound();
        remove.nextRound();
    }
protected:
    shootSkill shoot;
    removeSkill remove;
};

//园区科技剑士
class swordMan : public baseMonster{
public:
    swordMan(int pos = 0) : baseMonster(7,2,1,pos){
        //pass
    }
    void nextRound(){
        thump.nextRound();
        circle.nextRound();
    }
protected:
    thumpSkill thump;
    circleAttackSkill circle;
};

//园区尖端战将
class warrier : public baseMonster{
public:
    warrier(int pos = 0) : baseMonster(6,2,2,pos){
        //pass
    }
    void nextRound(){
        //todo
    }
protected:
    //todo
};