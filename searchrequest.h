#ifndef SEARCHREQUEST_H
#define SEARCHREQUEST_H

#include <cstddef>
#include <vector>
#include <QList>
#include <QCheckBox>

class SearchRequest
{
public:
    SearchRequest();
    SearchRequest(int hpMin,
                  int hpMax,
                  int costMin,
                  int costMax,
                  int attackMin,
                  int attackMax,
                  std::string name,
                  QList<QCheckBox*>& rarity,
                  QList<QCheckBox*>& cardType,
                  QList<QCheckBox*>& region);
    //Devfunc
    void ShowRequest();
private:
    //HP
    std::optional<size_t> hpMin_ {};
    std::optional<size_t> hpMax_ {};
    //Cost
    std::optional<size_t> costMin_ {};
    std::optional<size_t> costMax_ {};
    //Atack
    std::optional<size_t> attackMin_ {};
    std::optional<size_t> attackMax_ {};
    //Name
    std::string name_ {};
    //Rarity
    std::vector<std::string> rarity_ {};
    //Type
    std::vector<std::string> cardType_ {};
    //Region
    std::vector<std::string> region_ {};
};

#endif // SEARCHREQUEST_H
