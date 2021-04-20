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
                  QList<QCheckBox*>& region);
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
