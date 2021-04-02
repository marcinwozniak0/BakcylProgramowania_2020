#include "searchrequest.h"
#include<iostream>

SearchRequest::SearchRequest(
                             size_t hpMin,
                             size_t hpMax,
                             size_t hp,
                             size_t costMin,
                             size_t costMax,
                             size_t cost,
                             size_t atackMin,
                             size_t atackMax,
                             size_t atack,
                             std::string name,
                             QList<QCheckBox*>& rarity,
                             QList<QCheckBox*>& cardType,
                             QList<QCheckBox*>& region)
{
    hpMin_=hpMin;
    hpMax_=hpMax;
    hp_=hp;
    costMin_=costMin;
    costMax_=costMax;
    cost_=cost;
    atackMin_=atackMin;
    atackMax_=atackMax;
    atack_=atack;
    name_=name;

    for(int i = 0; i < 3; i++){
        if(rarity[i]->isChecked()){
            rarity_.set(i,true);
        }
    }

    for(int i = 0; i < 4; i++){
        if(cardType[i]->isChecked()){
            cardType_.set(i,true);
        }
    }

    for(int i = 0; i < 13; i++){
        if(region[i]->isChecked()){
            region_.set(i,true);
        }
    }
}

//Devfunc
void SearchRequest::ShowRequest(){
    if(hp_ == 0){
        if(hpMin_ != 0 || hpMax_ != 0)
        std::cerr<<"HP od " << hpMin_ << " Do " << hpMax_ <<'\n';
    }else{
        std::cerr<<"HP "<< hp_ <<'\n';
    }

    if(cost_ == 0){
        if(costMin_ != 0 || costMax_ != 0)
        std::cerr<<"koszt od " << costMin_ << " Do " << costMax_ <<'\n';
    }else{
        std::cerr<<"koszt "<< cost_ <<'\n';
    }

    if(atack_ == 0){
        if(atackMin_ != 0 || atackMax_ != 0)
        std::cerr<<"atak od " << atackMin_ << " Do " << atackMax_ <<'\n';
    }else{
        std::cerr<<"atak "<< atack_ <<'\n';
    }

    if(name_ != ""){
        std::cerr<<"Nazwa zawiera w sobie: "<<name_ <<'\n';
    }

    if(rarity_ != 000){
        std::cerr<<"Bitset rzadkości: " <<rarity_ << '\n';
    }
    if(cardType_ != 0000){
        std::cerr<<"Bitset typu kart:  " <<cardType_ << '\n';
    }
    if(region_ != 000'000'000'000'0){
        std::cerr<<"Bitset typu kart:  " <<region_ << '\n';
    }
}
