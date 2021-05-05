#include "DeckBuilder/Include/DeckBuilder.hpp"
#include "DeckBuilder/Include/Card.hpp"

DeckBuilder& makeDeckBuilder()
{
    DeckBuilder deckBuilder{};
    Card c1{};
    c1.setCardCode("abc");
    c1.setAttack(24);
    c1.setHealth(42);
    c1.setName("Abc Xyz");
    c1.setRarity("Champion");
    c1.setRegion("BANDLE CITY");
    c1.setLevelupDescriptionRaw("jjejnejdnedjej eeidene de");
    c1.setSet("JDndjwn");
    c1.setSpellSpeed("JCEJNejne");
    c1.setSupertype("WJDWNJDNW");
    c1.setType("UXWNJWNJWw");
    c1.setAssociatedCards({"abc", "xyz"});
    c1.setCardAssets({{"abc", "xyz"}, {"xyz", "abc"}});
    c1.setCardKeywords({"cwcscw", "wwwcw", "ccw"});
    c1.setCardSubtypes({"cce", "cece", "gtrf"});
    c1.setCollectible(true);
    c1.setDescriptionRaw("ejncwecwecnwej cwejcwec wcwe wejc wejwe wew eejwejwe ejw");
    c1.setFlavorText("ewwejwjemdwe wewd wedwe dwe dwed");
    deckBuilder.addCard(c1);
    Card c2{};
    c2.setCardCode("foo");
    c2.setAttack(100);
    c2.setHealth(200);
    c2.setName("njcdjwjwjncjnjcnejncjncjecjnejnc");
    c2.setRarity("ccnwcnwjnjwndjjdjejejje");
    c2.setRegion("DlkwdwdnwdwkdDKKDMJW");
    c2.setLevelupDescriptionRaw("eJCJEJenejnj n encjenjcejnc en");
    c2.setSet("CECh");
    c2.setSpellSpeed("cSSJn");
    c2.setSupertype("NJNW");
    c2.setType("NCENW");
    c2.setAssociatedCards({"wwuh", "DWD"});
    c2.setCardAssets({{"Axdsd", "ada"}, {"Dwdws", "cscws"}});
    c2.setCardKeywords({"cwcw", "cwcwc", "vrvr", "veve"});
    c2.setCardSubtypes({"vfgfb", "vfvr", "vvv"});
    c2.setCollectible(true);
    c2.setDescriptionRaw("cen c vd vv fujef  fjre rejif e wuf wew fref  fre");
    c2.setFlavorText("cenjcnjj wefjwe fjwe fe wf wef wef we");
    deckBuilder.addCard(c2);
    Card c3{};
    c3.setCardCode("zxc");
    c3.setAttack(2238498);
    c3.setHealth(345);
    c3.setName("qwe");
    c3.setRarity("Legend of legends");
    c3.setRegion("BSUSHUIIDJWDIJDIOWio");
    c3.setLevelupDescriptionRaw("Hdwwdudjwu jwjdjd djwd w d wid");
    c3.setSet("NEJn");
    c3.setSpellSpeed("JNDH");
    c3.setSupertype("CNJNJJNJWNJ");
    c3.setType("SJXWW");
    c3.setAssociatedCards({"DWD", "WDWD"});
    c3.setCardAssets({{"addsd", "feffe"}, {"scecw", "ccwscw"}});
    c3.setCardKeywords({"cwwwcw", "cece", "ecece", "rgtt", "efvrge"});
    c3.setCardSubtypes({"sceee", "eeeeeeeeeeeeee", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"});
    c3.setCollectible(false);
    c3.setDescriptionRaw("cnwejncewf cef ef wej f wef weuwe he diwe");
    c3.setFlavorText("cdcwdjjcwejcjwec cwewjwe we cwecwe cecwe");
    deckBuilder.addCard(c3);
    return deckBuilder;
}