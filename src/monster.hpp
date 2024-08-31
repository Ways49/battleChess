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
    explicit gunner(int side,int pos = 0) : baseMonster(3,1,1,pos){
        pieceType = side * levelOne;
    }
    void nextRound(){
        shoot.nextRound();
    }
    bool shootOther(baseMonster& other){
        return shoot.useSkill(*this,other);
    }
protected:
    shootSkill shoot;
    int pieceType;
private:
    friend class experiment;
};

//园区警犬
class policeDog : public baseMonster{
public:
    explicit policeDog(int side,int pos = 0) : baseMonster(3,1,2,pos){
        pieceType = side * levelTwo;
    }
    void nextRound(){
        accelerateAndMoveAgain.nextRound(*this);
    }
    bool accelerateAndMoveAgainSelf(king& actorSideKing){
        return accelerateAndMoveAgain.useSkill(*this,actorSideKing);
    }
protected:
    accelerateAndMoveAgainSkill accelerateAndMoveAgain;
    int pieceType;
};

//园区武装直升机
class gunship : public baseMonster{
public:
    explicit gunship(int side,int pos = 0) : baseMonster(5,2,2,pos){
        pieceType = side * levelThree;
    }
    void nextRound(){
        shoot.nextRound();
        remove.nextRound();
    }
    bool shootOther(king& actorSideKing,baseMonster& other){
        return shoot.useSkill(*this,other,&actorSideKing,2);
    }
    bool removeOtherKing(king& actorSideKing,king& otherSideKing){
        return remove.useSkill(*this,actorSideKing,otherSideKing);
    }
protected:
    shootSkill shoot;
    removeSkill remove;
    int pieceType;
};

//园区科技剑士
class swordMan : public baseMonster{
public:
    explicit swordMan(int side,int pos = 0) : baseMonster(7,2,1,pos){
        pieceType = side * levelFour;
    }
    void nextRound(){
        thump.nextRound();
        circle.nextRound();
    }
    bool circleOthers(king& actorSideKing,const vector<baseMonster*>& others){
        return circle.useSkill(*this,actorSideKing,others);
    }
    bool thumpOther(king& actorSideKing,baseMonster& other){
        return thump.useSkill(*this,actorSideKing,other);
    }
protected:
    thumpSkill thump{};
    circleAttackSkill circle;
    int pieceType;
};

//园区尖端战将
class warrier : public baseMonster{
public:
    explicit warrier(int side,int pos = 0) : baseMonster(8,2,2,pos){
        pieceType = side * levelFive;
    }
    void nextRound(){
        cure.nextRound();
        crossSlash.nextRound();
        proBarrier.nextRound(*this);
    }
    bool cureSidePiece(baseMonster& other){
        return cure.useSkill(*this,other);
    }
    bool crossSlashOthers(king& actorSideKing,const vector<baseMonster*>& others){
        return crossSlash.useSkill(*this,actorSideKing,others);
    }
    bool proBarrierSelf(king& actorSideKing){
        return proBarrier.useSkill(*this,actorSideKing);
    }
protected:
    cureSkill cure;
    crossSlashSkill crossSlash;
    proBarrierSkill proBarrier;
    int pieceType;
};

//园区无人车
class driverlessCar : public baseMonster{
public:
    explicit driverlessCar(int side,int pos = 0) : baseMonster(3,1,2,pos){
        pieceType = side * levelHelper;
    }
    void nextRound(){
        justAccelerateSelf.nextRound(*this);
        assert(pAcceleratedOtherPool.size() == justAccelerateOtherPool.size());
        for(int i = 0;i < pAcceleratedOtherPool.size();i++){
            assert(pAcceleratedOtherPool[i]);
            justAccelerateOtherPool[i].nextRound(*pAcceleratedOtherPool[i]);
        }
        for(int i = 0;i < justAccelerateOtherPool.size();i++){
            if(justAccelerateOtherPool[i].remainingRound <= 0){
                pAcceleratedOtherPool[i] = pAcceleratedOtherPool.back();
                justAccelerateOtherPool[i] = justAccelerateOtherPool.back();
                pAcceleratedOtherPool.pop_back();
                justAccelerateOtherPool.pop_back();
            }
        }
    }
    bool accelerateSelf(king& actorSideKing){
        return justAccelerateSelf.useSkill(*this,actorSideKing);
    }
    bool accelerateOther(baseMonster& other,king& actorSideKing){
        pAcceleratedOtherPool.emplace_back(&other);
        justAccelerateOtherPool.emplace_back();
        return justAccelerateOtherPool.back().useSkill(other,actorSideKing);
    }
protected:
    vector<baseMonster*> pAcceleratedOtherPool;
    justAccelerateSelfSkill justAccelerateSelf;
    vector<justAccelerateOtherSkill> justAccelerateOtherPool;
    int pieceType;
};
