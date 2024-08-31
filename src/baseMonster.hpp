#pragma once
#include "base.hpp"
#include <cassert>
#include <algorithm>
using namespace std;
#define inf 10000;

enum mobilityType{
    quickSlide = 2,     //双格快速滑行
    slowSlide = 1,      //单格滑行
    quiet = 0,          //瘫痪
    moment = -1         //瞬移
};

class baseMonster{
public:
    explicit baseMonster(int HP = 0,int ATK = 0,int MOB = 0,int POS = 0){
        this->MAXHP = HP;
        this->MAXDEHP = inf;
        this->INIMOB = MOB;
        this->HP = HP;
        this->ATK = ATK;
        this->MOB = MOB;
        this->PRO = 0;
        this->POS = POS;
        this->roundMoveSum = 1;
        this->BUFFSUM = 0;
    }
    void attack(baseMonster& other){
        assert(HP > 0 && other.HP > 0);
        //护盾
        if(other.PRO >= ATK){
            return;
        }
        const int DEHP = min(ATK - other.PRO,other.MAXDEHP);
        //受伤
        other.HP = max(0,other.HP - DEHP);
        //存活反击
        if(other.HP > 0){
            if(PRO >= other.ATK){
                return;
            }
            const int RE_DEHP = min(other.ATK - PRO,MAXDEHP);
            HP = max(0,HP - RE_DEHP);
        }
    }
    bool move(int toPos){
        if(roundMoveSum > 0){
            POS = toPos;
            roundMoveSum--;
            return true;
        }
        return false;
    }
protected:
    int HP;         //生命值
    int ATK;        //攻击力
    int MOB;        //机动性
    int PRO;        //护盾值
    int POS;        //位置
protected:
    int MAXHP;              //最大生命值
    int MAXDEHP;            //最大受损生命值
    int INIMOB;             //初始机动性
    int BUFFSUM;            //接受的buff总数，不能超过两个
    int roundMoveSum;     //回合内可以移动的剩余次数
private:
    friend class experiment;
    friend class shootSkill;
    friend class accelerateAndMoveAgainSkill;
    friend class removeSkill;
    friend class thumpSkill;
    friend class circleAttackSkill;
    friend class cureSkill;
    friend class proBarrierSkill;
    friend class justAccelerateSelfSkill;
    friend class justAccelerateOtherSkill;
};

class king : public baseMonster{
public:
    king(int HP,int POS,int ENE,int MON) : baseMonster(HP,0,0,POS){
        this->ENE = ENE;
        this->MON = MON;
    }
    bool payMoney(int paySum){
        if(MON >= paySum){
            MON = paySum;
            return true;
        }
        return false;
    }
    bool payEnergy(int paySum){
        if(ENE >= paySum){
            ENE -= paySum;
            return true;
        }
        return false;
    }
    bool charge(){
        if(HP > 2){
            HP -= 2;
            ENE += 3;
            return true;
        }
        return false;
    }
protected:
    int ENE;        //能量值
    int MON;        //金钱数
private:
    friend class accelerateAndMoveAgainSkill;
    friend class justAccelerateSelfSkill;
    friend class justAccelerateOtherSkill;
    friend class thumpSkill;
    friend class circleAttackSkill;
    friend class crossSlashSkill;
    friend class proBarrierSkill;
};