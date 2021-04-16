#pragma once
#include <optional>
#include <string>
#include <vector>


struct searchFlags
{
    struct intmember    //notice: unset member means no filter
    {                   //but member = 0 will give no results
        std::optional<int> value;
        std::optional<int> min;
        std::optional<int> max;
        
        intmember();
        intmember(int, int, int);
        //intmember operator=(intmember);
    };
    
    intmember hp;
    intmember cost;
    intmember attack;
    
    std::string name;
    
    std::vector<std::string> rarities;
    std::vector<std::string> regions;
    std::vector<std::string> types;
    //and maybe those?
    //std::vector<std::string> spellSpeeds;
    //std::vector<std::string> sets;
    
    int pageNr;  //starting from 1
    
    searchFlags();
};
