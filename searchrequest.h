#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

#include <cstddef>
#include <bitset>

class SearchRequest
{
public:
    SearchRequest();
private:
    //HP
    size_t hpMin_ {};
    size_t hpMax_ {};
    size_t hp_ {};
    //Cost
    size_t costMin_ {};
    size_t costMax_ {};
    size_t cost_ {};
    //Atack
    size_t atackMin_ {};
    size_t atackMax_ {};
    size_t atack_ {};
    //Name
    std::string name {};
    //Rarity
    std::bitset<3> rarity_ {};
    //Type
    std::bitset<3> cardType_ {};
    //Region
    std::bitset<13> region_ {};

};

#endif // SEARCHREQUEST_H
