#pragma once
#include "base.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

enum mobilityType{
    quickSlide = 2,     //双格快速滑行
    slowSlide = 1,      //单格滑行
    quiet = 0,          //瘫痪
    moment = -1         //瞬移
};

class baseMonster{
public:
    baseMonster(){
        HP = 0;
        ATK = 0;
        MOB = 0;
        PRO = 0;
    }
    baseMonster(int HP,int ATK,int MOB){
        this->HP = HP;
        this->ATK = ATK;
        this->MOB = MOB;
        this->PRO = 0;
    }
    void attack(baseMonster& other){
        //护盾
        if(other.PRO >= ATK){
            return;
        }
        const int DEHP = ATK - other.PRO;
        //受伤
        other.HP = max(0,other.HP - DEHP);
        //存活反击
        if(other.HP){
            if(PRO >= other.ATK){
                return;
            }
            const int RE_DEHP = other.ATK - PRO;
            HP = max(0,HP - RE_DEHP);
        }
    }
protected:
    int HP;         //生命值
    int PRO;        //护盾值
    int ATK;        //攻击力
    int MOB;        //机动性
private:
    friend class experiment;
};