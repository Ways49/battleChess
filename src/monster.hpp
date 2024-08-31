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
    explicit gunner(int pos = 0) : baseMonster(3,1,1,pos){
        //pass
    }
    void nextRound(){
        shoot.nextRound();
    }
protected:
    shootSkill shoot;
};

//园区警犬
class policeDog : public baseMonster{
public:
    explicit policeDog(int pos = 0) : baseMonster(3,1,2,pos){
        //pass
    }
    void nextRound(){
        accelerateAndMoveAgain.nextRound(*this);
    }
protected:
    accelerateAndMoveAgainSkill accelerateAndMoveAgain;
};

//园区武装直升机
class gunship : public baseMonster{
public:
    explicit gunship(int pos = 0) : baseMonster(5,2,2,pos){
        //pass
    }
    void nextRound(){
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
    explicit swordMan(int pos = 0) : baseMonster(7,2,1,pos){
        //pass
    }
    void nextRound(){
        thump.nextRound();
        circle.nextRound();
    }
protected:
    thumpSkill thump{};
    circleAttackSkill circle;
};

//园区尖端战将
class warrier : public baseMonster{
public:
    explicit warrier(int pos = 0) : baseMonster(8,2,2,pos){
        //pass
    }
    void nextRound(){
        cure.nextRound();
        crossSlash.nextRound();
        proBarrier.nextRound(*this);
    }
protected:
    cureSkill cure;
    crossSlashSkill crossSlash;
    proBarrierSkill proBarrier;
};

//园区无人车
class driverlessCar : public baseMonster{
public:
    explicit driverlessCar(int pos) : baseMonster(3,1,2,pos){
        //pass
    }
    void nextRound(baseMonster & actor){
        justAccelerateSelf.nextRound(actor);
        justAccelerateOther.nextRound(actor);
    }
protected:
    justAccelerateSelfSkill justAccelerateSelf;
    justAccelerateOtherSkill justAccelerateOther;
};
