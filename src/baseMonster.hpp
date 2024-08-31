#pragma once
#include "base.hpp"
#include <cassert>
#include <algorithm>
using namespace std;

enum mobilityType{
    quickSlide = 2,     //双格快速滑行
    slowSlide = 1,      //单格滑行
    quiet = 0,          //瘫痪
    moment = -1         //瞬移
};

class baseMonster{
public:
    baseMonster(int HP = 0,int ATK = 0,int MOB = 0,int POS = 0){
        this->HP = HP;
        this->ATK = ATK;
        this->MOB = MOB;
        this->PRO = 0;
        this->POS = 0;
    }
    void attack(baseMonster& other){
        assert(HP > 0 && other.HP > 0);
        //护盾
        if(other.PRO >= ATK){
            return;
        }
        const int DEHP = ATK - other.PRO;
        //受伤
        other.HP = max(0,other.HP - DEHP);
        //存活反击
        if(other.HP > 0){
            if(PRO >= other.ATK){
                return;
            }
            const int RE_DEHP = other.ATK - PRO;
            HP = max(0,HP - RE_DEHP);
        }
    }
    void move(int toPos){
        assert(roundMoveCnt <= 1);
        POS = toPos;
        roundMoveCnt++;
    }

    virtual void nextRound(){
        roundMoveCnt = 0;
    }
protected:
    int HP;         //生命值
    int ATK;        //攻击力
    int MOB;        //机动性
    int PRO;        //护盾值
    int POS;        //位置
protected:
    int roundMoveCnt;   //回合内已经移动过的次数
private:
    friend class experiment;
    friend class shootSkill;
    friend class accelerateSkill;
    friend class removeSkill;
    friend class thumpSkill;
    friend class circleAttackSkill;
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
    friend class accelerateSkill;
};