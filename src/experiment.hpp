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
    static void testGunnerRound(){
        gunner first = gunner(red);
        gunner second = gunner(black);
        cout<<first.HP<<" "<<second.HP<<endl;
        first.shootOther(second);
        cout<<first.HP<<" "<<second.HP<<endl;
        first.shootOther(second);
        cout<<first.HP<<" "<<second.HP<<endl;
        first.nextRound();
        first.shootOther(second);
        cout<<first.HP<<" "<<second.HP<<endl;
    }
    static void testPoliceDogRound(){
        king firstKing = king(30,0,5,5);
        policeDog first = policeDog(red);
        first.nextRound();
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
        first.accelerateAndMoveAgainSelf(firstKing);
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
        first.nextRound();
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
        first.accelerateAndMoveAgainSelf(firstKing);
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
        first.accelerateAndMoveAgainSelf(firstKing);
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
        first.nextRound();
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
        first.accelerateAndMoveAgainSelf(firstKing);
        cout<<first.MOB<<" "<<first.BUFFSUM<<" "<<first.roundMoveSum<<" "<<firstKing.ENE<<endl;
    }
    static void testGunshipRound(){
        king firstKing = king(30,0,5,5);
        king secondKing = king(30,0,5,5);
        gunship first = gunship(red);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
        first.removeOtherKing(firstKing,secondKing);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
        first.removeOtherKing(firstKing,secondKing);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
        first.nextRound();
        first.removeOtherKing(firstKing,secondKing);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
        first.nextRound();
        first.removeOtherKing(firstKing,secondKing);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
        first.shootOther(firstKing,secondKing);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
        first.shootOther(firstKing,secondKing);
        cout<<firstKing.ENE<<" "<<secondKing.HP<<endl;
    }
    static void testSwordManRound(){
        king firstKing = king(30,0,5,5);
        swordMan first = swordMan(red);
        swordMan second = swordMan(black);
        vector<baseMonster*> v;
        v.push_back(&second);
        cout<<firstKing.ENE<<" "<<second.HP<<endl;
        first.thumpOther(firstKing,second);
        cout<<firstKing.ENE<<" "<<second.HP<<endl;
        first.circleOthers(firstKing,v);
        cout<<firstKing.ENE<<" "<<second.HP<<endl;
        first.circleOthers(firstKing,v);
        cout<<firstKing.ENE<<" "<<second.HP<<endl;
        first.nextRound();
        first.circleOthers(firstKing,v);
        cout<<firstKing.ENE<<" "<<second.HP<<endl;
    }
    static void testWarrierRound(){
        king secondKing = king(30,0,5,5);
        warrier first = warrier(red);
        warrier second = warrier(black);
        vector<baseMonster*> v;
        v.push_back(&first);
        cout<<secondKing.ENE<<" "<<first.HP<<endl;
        second.crossSlashOthers(secondKing,v);
        cout<<secondKing.ENE<<" "<<first.HP<<endl;
        second.cureSidePiece(first);
        cout<<secondKing.ENE<<" "<<first.HP<<endl;
        second.cureSidePiece(first);
        cout<<secondKing.ENE<<" "<<first.HP<<endl;
        second.nextRound();
        second.cureSidePiece(first);
        cout<<secondKing.ENE<<" "<<first.HP<<endl;
        cout<<"-------------------------------"<<endl;
        secondKing.ENE = 30;
        cout<<secondKing.ENE<<" "<<second.MAXDEHP<<endl;
        second.proBarrierSelf(secondKing);
        cout<<second.HP<<endl;
        first.attack(second);
        cout<<second.HP<<endl;
        cout<<secondKing.ENE<<" "<<second.MAXDEHP<<endl;
        second.proBarrierSelf(secondKing);
        cout<<secondKing.ENE<<" "<<second.MAXDEHP<<endl;
        second.nextRound();
        cout<<secondKing.ENE<<" "<<second.MAXDEHP<<endl;
        second.nextRound();
        cout<<secondKing.ENE<<" "<<second.MAXDEHP<<endl;
        second.nextRound();
        cout<<secondKing.ENE<<" "<<second.MAXDEHP<<endl;
    }
    static void testdriverlessCarRound(){
        king firstKing = king(30,0,5,5);
        king secondKing = king(30,0,5,5);
        driverlessCar first = driverlessCar(red);
        driverlessCar second = driverlessCar(black);
        driverlessCar second_2 = driverlessCar(black);
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.accelerateSelf(firstKing);
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.accelerateSelf(firstKing);
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.nextRound();
        first.accelerateSelf(firstKing);
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.nextRound();
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.nextRound();
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.nextRound();
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        first.nextRound();
        cout<<firstKing.ENE<<" "<<first.MOB<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<firstKing.ENE<<endl;
        firstKing.ENE = 30;
        cout<<second.MOB<<endl;
        first.accelerateOther(second,firstKing);
        cout<<second.MOB<<endl;
        first.nextRound();
        first.accelerateOther(second,firstKing);
        first.accelerateOther(second_2,firstKing);
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
        first.nextRound();
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
        first.nextRound();
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
        first.nextRound();
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
        first.nextRound();
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
        first.nextRound();
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
        first.nextRound();
        cout<<second.MOB<<" "<<second_2.MOB<<endl;
    }
};