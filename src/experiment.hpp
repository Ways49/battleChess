#pragma once
#include "monster.hpp"


class experiment{
public:
    static void testMonster(){
        baseMonster first = baseMonster(3,2,1);
        baseMonster second = baseMonster(7,1,2);
        first.attack(second);
        cout<<first.HP<<endl;
        cout<<second.HP<<endl;
        first.PRO = 1;
        first.attack(second);
        cout<<first.HP<<endl;
        cout<<second.HP<<endl;
        first.PRO = 2;
        first.attack(second);
        cout<<first.HP<<endl;
        cout<<second.HP<<endl;
        first.PRO = 0;
        first.attack(second);
        cout<<first.HP<<endl;
        cout<<second.HP<<endl;
    }
};