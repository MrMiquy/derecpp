#include <curl/curl.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>

enum tagType {
    General,
    Artist,
    Other,
    Copyright,
    Character,
    Circle,
    Warning
};

class Tag {
public:
    ~Tag() { delete this; }

    std::string operator ()(unsigned int index) { return name[index]; }

    void addTag(std::string name, std::string type, std::string amount);

    std::string typeStr(unsigned int index);
    SDL_Color typeColor(unsigned int index);

    int size() { return name.size(); }
    int getAmount(unsigned int index) { return amount[index]; }

    void clear();


    std::vector<int> amount;
    std::vector<std::string> name;
    std::vector<tagType> type;
};


class Parser {
public:
    bool setToOutput = false;
    bool internetConnection = false;
    int cer = 0;

    std::string inputMarkup;
    std::string outputMarkup;
    Tag tag;

    bool request(std::string type = "tag", std::string name = "");

    std::string findP(std::string tag, int match = 0);
    std::string findS(std::string tag, int match = 0);
    std::vector<std::string> findAllS(std::string tag, int matches = -1);
    std::string byAttribute(std::string attribute, std::string markup = "");
    std::string byContent(std::string attributeContent);
    std::string unfold();

};
