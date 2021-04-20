#include "searchrequest.h"
#include<iostream>

SearchRequest::SearchRequest(
                             int hpMin,
                             int hpMax,
                             int costMin,
                             int costMax,
                             int attackMin,
                             int attackMax,
                             std::string name,
                             QList<QCheckBox*>& rarity,
                             QList<QCheckBox*>& cardType,
                             QList<QCheckBox*>& region)
{
    hpMin > 0 ? hpMin_=hpMin : false;
    hpMax > 0 ? hpMax_=hpMax : false;
    costMin > 0 ? costMin_=costMin : false;
    costMax > 0 ? costMax_=costMax : false;
    attackMin > 0 ? attackMin_=attackMin : false;
    attackMax > 0 ? attackMax_=attackMax : false;



    name_=name;

    for(int i = 0; i < 3; i++){
        if(rarity[i]->isChecked()){
                rarity_.push_back(rarity[i]->text().toUtf8().constData());
        }
    }

    for(int i = 0; i < 4; i++){
        if(cardType[i]->isChecked()){
            cardType_.push_back(cardType[i]->text().toUtf8().constData());
        }
    }

    for(int i = 0; i < 13; i++){
        if(region[i]->isChecked()){
            region_.push_back(region[i]->text().toUtf8().constData());
        }
    }
}

//Devfunc
void SearchRequest::ShowRequest(){

        std::cerr<<"HP from " << hpMin_.value_or(0) << " to " << hpMax_.value_or(999) <<'\n';

        std::cerr<<"cost from " << costMin_.value_or(0) << " to " << costMax_.value_or(999) <<'\n';

        std::cerr<<"Attack from " << attackMin_.value_or(0) << " to " << attackMax_.value_or(999) <<'\n';


    if(name_ != ""){
        std::cerr<<"The name includes: "<<name_ <<'\n';
    }

    if(!rarity_.empty()){
        std::cerr<<"Rarity: ";
        for(auto& it : rarity_){
            std::cerr<<it<<" ";
        }
        std::cerr<<"\n";
    }
    if(!cardType_.empty()){
        std::cerr<<"CardType: ";
        for(auto& it : cardType_){
            std::cerr<<it<<" ";
        }
        std::cerr<<"\n";
    }
    if(!region_.empty()){
        std::cerr<<"Regions: ";
        for(auto& it : region_){
            std::cerr<<it<<" ";
        }
        std::cerr<<"\n";
    }
}
