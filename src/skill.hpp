#pragma once
#include "baseMonster.hpp"
#include <vector>
#define MAX_BUFF_SUM 2

//射击
class shootSkill{
public:
    shootSkill(){
        used = false;
    }
    bool canUseSkill(king* pActorSideKing,int payEnergySum) const{
        return !used && (!pActorSideKing || pActorSideKing->ENE >= payEnergySum);
    }
    bool useSkill(baseMonster& actor,baseMonster& other,king* pActorSideKing = nullptr,int payEnergySum = 0){
        if(canUseSkill(pActorSideKing,payEnergySum)){
            if(payEnergySum > 0){
                pActorSideKing->payEnergy(payEnergySum);
            }
            actor.ATK++;
            actor.attack(other);
            actor.ATK--;
            used = true;
        }
        return used;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//额外和加速移动
class accelerateAndMoveAgainSkill{
public:
    accelerateAndMoveAgainSkill(){
        used = false;
        limit = false;
    }
    bool canUseSkill(baseMonster& actor,king& actorSideKing) const{
        return !used && (!limit || actorSideKing.ENE >= 1) && (actor.BUFFSUM < MAX_BUFF_SUM);
    }
    bool useSkill(baseMonster& actor,king& actorSideKing){
        if(canUseSkill(actor,actorSideKing)){
            if(limit){
                actorSideKing.payEnergy(1);
            }
            actor.roundMoveSum++;
            actor.MOB = (actor.roundMoveSum >= 2) ? actor.INIMOB + 1 : actor.INIMOB;
            used = true;
            limit = true;
            actor.BUFFSUM++;
        }
        return used;
    }
    void nextRound(baseMonster& actor){
        if(used){
            used = false;
            actor.roundMoveSum = 1;
            actor.MOB = actor.INIMOB;
            actor.BUFFSUM--;
        }
    }
protected:
    bool limit;
    bool used;
};

//拆迁
class removeSkill{
public:
    removeSkill(){
        used = false;
    }
    bool canUseSkill(king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 1;
    }
    bool useSkill(baseMonster& actor,king& actorSideKing,king& other){
        if(canUseSkill(actorSideKing)){
            actorSideKing.payEnergy(1);
            actor.ATK *= 3;
            actor.attack(other);
            actor.ATK /= 3;
            used = true;
        }
        return used;
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
    bool canUseSkill(king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 2;
    }
    bool useSkill(baseMonster& actor,king& actorSideKing,baseMonster& other){
        if(canUseSkill(actorSideKing)){
            actorSideKing.payEnergy(2);
            actor.ATK <<= 1;
            actor.attack(other);
            actor.ATK >>= 1;
            used = true;
        }
        return false;
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
    bool canUseSkill(king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 1;
    }
    bool useSkill(baseMonster& actor,king& actorSideKing,const vector<baseMonster*>& others){
        if(canUseSkill(actorSideKing)){
            actorSideKing.payEnergy(1);
            for(baseMonster* pOther : others){
                actor.attack(*pOther);
            }
            used = true;
        }
        return used;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//治疗
class cureSkill{
public:
    cureSkill(){
        used = false;
    }
    bool canUseSkill() const{
        return !used;
    }
    bool useSkill(baseMonster& actor,baseMonster& other){
        if(canUseSkill()){
            other.HP = min(other.HP + 1,other.MAXHP);
            used = true;
        }
        return used;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//十字斩
class crossSlashSkill{
public:
    crossSlashSkill(){
        used = false;
    }
    bool canUseSkill(king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 3;
    }
    bool useSkill(baseMonster& actor,king& actorSideKing,const vector<baseMonster*>& others){
        if(canUseSkill(actorSideKing)){
            actorSideKing.payEnergy(3);
            for(baseMonster* pOther : others){
                actor.attack(*pOther);
            }
            used = true;
        }
        return used;
    }
    void nextRound(){
        used = false;
    }
protected:
    bool used;
};

//保护屏障
class proBarrierSkill{
public:
    proBarrierSkill(){
        remainingRound = 0;
        used = false;
    }
    bool canUseSkill(baseMonster& actor,king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 2 && (actor.BUFFSUM < MAX_BUFF_SUM);
    }
    bool useSkill(baseMonster& actor,king& actorSideKing){
        if(canUseSkill(actor,actorSideKing)){
            if(actorSideKing.payEnergy(2)){
                remainingRound = 3;
                actor.MAXDEHP = 1;
                used = true;
                actor.BUFFSUM++;
            }
        }
        return used;
    }
    void nextRound(baseMonster& actor){
        if(remainingRound <= 0){
            remainingRound = 0;
        }else{
            remainingRound--;
            if(remainingRound <= 0){
                actor.MAXDEHP = inf;
                actor.BUFFSUM = (actor.BUFFSUM <= 0) ? 0 : actor.BUFFSUM - 1;
            }
        }
    }
protected:
    bool used;
    int remainingRound;
};

//加速自己
class justAccelerateSelfSkill{
public:
    justAccelerateSelfSkill(){
        remainingRound = 0;
        used = false;
    }
    bool canUseSkill(baseMonster& actor,king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 1 && (actor.BUFFSUM < MAX_BUFF_SUM);
    }
    bool useSkill(baseMonster& actor,king& actorSideKing){
        if(canUseSkill(actor,actorSideKing)){
            if(remainingRound <= 0){
                actor.BUFFSUM++;
            }
            actorSideKing.payEnergy(1);
            actor.MOB += 1;
            remainingRound = 3;
            used = true;
        }
        return used;
    }
    void nextRound(baseMonster& actor){
        if(remainingRound <= 0){
            remainingRound = 0;
        }else{
            remainingRound--;
            if(remainingRound <= 0){
                actor.MOB = actor.INIMOB;
                actor.BUFFSUM = (actor.BUFFSUM <= 0) ? 0 : actor.BUFFSUM - 1;
            }
        }
        used = false;
    }
protected:
    bool used;
    int remainingRound;
private:
    friend class driverlessCar;
};

//加速别人
class justAccelerateOtherSkill{
public:
    justAccelerateOtherSkill(){
        remainingRound = 0;
        used = false;
    }
    bool canUseSkill(baseMonster& actor,king& actorSideKing) const{
        return !used && actorSideKing.ENE >= 1 && (actor.BUFFSUM < MAX_BUFF_SUM);
    }
    bool useSkill(baseMonster& actor,king& actorSideKing){
        if(canUseSkill(actor,actorSideKing)){
            if(remainingRound <= 0){
                actor.BUFFSUM++;
            }
            actorSideKing.payEnergy(1);
            actor.MOB += 1;
            remainingRound = 4;
            used = true;
        }
        return used;
    }
    void nextRound(baseMonster& actor){
        if(remainingRound <= 0){
            remainingRound = 0;
        }else{
            remainingRound--;
            if(remainingRound <= 0){
                actor.MOB = actor.INIMOB;
                actor.BUFFSUM = (actor.BUFFSUM <= 0) ? 0 : actor.BUFFSUM - 1;
            }
        }
        used = false;
    }
protected:
    bool used;
    int remainingRound;
private:
    friend class driverlessCar;
};


