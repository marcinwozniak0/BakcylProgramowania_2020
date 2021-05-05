#pragma once

#include <cstddef>
#include <vector>
#include <QList>
#include <QCheckBox>

class SearchRequest
{
public:
    void setPage(int page);
    //Devfunc
    void ShowRequest();

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

private:
    int page_ {};

};
