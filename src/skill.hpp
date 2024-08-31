#pragma once
#include "baseMonster.hpp"
#include <vector>

enum parkAreaSkill{
    shoot = 1,              //射击
    accelerate = 2,         //额外和加速移动（仅第一次免费）
    remove = 3,             //拆迁
    thump = 4,              //重击
    circleAttack = 5,       //环击
};

//射击
class shootSkill{
public:
    shootSkill(){
        used = true;
    }
    bool canUseSkill() const{
        return !used;
    }
    void useSkill(baseMonster& actor,baseMonster& other){
        assert(!used);
        actor.ATK++;
        actor.attack(other);
        actor.ATK--;
        used = true;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//额外和加速移动
class accelerateSkill{
public:
    accelerateSkill(){
        limit = false;
        roundCnt = 0;
    }
    bool canUseSkill(king& actorSideKing) const{
        if(!limit){
            return true;
        }
        return (roundCnt <= 1 && actorSideKing.ENE >= 1);
    }
    void useSkill(baseMonster& actor,king& actorSideKing,int toPos){
        assert(getSlideMoveType(actor.POS,toPos) <= actor.MOB + (roundCnt > 0));
        assert(roundCnt <= 1);
        if(limit){
            assert(actorSideKing.ENE >= 1);
            actorSideKing.payEnergy(1);
        }else{
            limit = true;
        }
        roundCnt++;
        actor.POS = toPos;
    }
    void nextRound(){
        roundCnt = 0;
    }
protected:
    bool limit;
    int roundCnt;
};

//拆迁
class removeSkill{
public:
    removeSkill(){
        used = false;
    }
    bool canUseSkill() const{
        return !used;
    }
    void useSkill(baseMonster& actor,king& other){
        assert(!used);
        actor.ATK *= 3;
        actor.attack(other);
        actor.ATK /= 3;
        used = true;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//重击
class thumpSkill{
public:
    bool canUseSkill() const{
        return !used;
    }
    void useSkill(baseMonster& actor,king& other){
        assert(!used);
        actor.ATK *= 2;
        actor.attack(other);
        actor.ATK /= 2;
        used = true;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//环击
class circleAttackSkill{
public:
    circleAttackSkill(){
        used = false;
    }
    bool canUseSkill() const{
        return !used;
    }
    void useSkill(baseMonster& actor,const vector<baseMonster*>& others){
        assert(!used);
        for(baseMonster* pOther : others){
            actor.attack(*pOther);
        }
        used = true;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

