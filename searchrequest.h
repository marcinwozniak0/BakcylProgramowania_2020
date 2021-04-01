#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

#include <cstddef>
#include <bitset>

class SearchRequest
{
public:
    SearchRequest();
    SearchRequest(size_t hpMin,
                  size_t hpMax,
                  size_t hp,
                  size_t costMin,
                  size_t costMax,
                  size_t cost,
                  size_t atackMin,
                  size_t atackMax,
                  size_t atack,
                  std::string name,
                  std::bitset<3> rarity,
                  std::bitset<4> cardType,
                  std::bitset<13> region);
    //Devfunc
    void ShowRequest();
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
    std::string name_ {};
    //Rarity
    std::bitset<3> rarity_ {};
    //Type
    std::bitset<4> cardType_ {};
    //Region
    std::bitset<13> region_ {};
};

#endif // SEARCHREQUEST_H
