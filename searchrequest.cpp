#include "searchrequest.h"
#include<iostream>

SearchRequest::SearchRequest(
                             std::string hpMin,
                             std::string hpMax,
                             std::string costMin,
                             std::string costMax,
                             std::string attackMin,
                             std::string attackMax,
                             std::string name,
                             std::vector<std::string> rarity,
                             std::vector<std::string> cardType,
                             std::vector<std::string> region) :
    rarity_(rarity),
    cardType_(cardType),
    region_(region)
{

    hpMin != "" ? hpMin_=std::stoi(hpMin) : false;
    hpMax != "" ? hpMax_=std::stoi(hpMax) : false;
    costMin != "" ? costMin_=std::stoi(costMin) : false;
    costMax != "" ? costMax_=std::stoi(costMax) : false;
    attackMin != "" ? attackMin_=std::stoi(attackMin) : false;
    attackMax != "" ? attackMax_=std::stoi(attackMax) : false;

    name_=name;

}

//Devfunc
void SearchRequest::ShowRequest(){

        std::cerr<<"HP from " << hpMin_.value_or(1) << " to " << hpMax_.value_or(999) <<'\n';

        std::cerr<<"cost from " << costMin_.value_or(1) << " to " << costMax_.value_or(999) <<'\n';

        std::cerr<<"Attack from " << attackMin_.value_or(1) << " to " << attackMax_.value_or(999) <<'\n';


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
