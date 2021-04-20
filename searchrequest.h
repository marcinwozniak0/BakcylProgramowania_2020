#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

#include <cstddef>
#include <bitset>
#include <QList>
#include <QCheckBox>

class SearchRequest
{
public:
    SearchRequest();
    SearchRequest(size_t hpMin,
                  size_t hpMax,
                  size_t costMin,
                  size_t costMax,
                  size_t attackMin,
                  size_t attackMax,
                  std::string name,
                  QList<QCheckBox*>& rarity,
                  QList<QCheckBox*>& cardType,
                  QList<QCheckBox*>& region);
    //Devfunc
    void ShowRequest();
private:
    //HP
    size_t hpMin_ {};
    size_t hpMax_ {};
    //Cost
    size_t costMin_ {};
    size_t costMax_ {};
    //Atack
    size_t attackMin_ {};
    size_t attackMax_ {};
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
