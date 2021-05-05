#include "SearchRequest.h"
#include<iostream>

void SearchRequest::setPage(int page){
    if(page < 1){
        page_ = 1;
    }else{
        page_ = page;
    }
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
