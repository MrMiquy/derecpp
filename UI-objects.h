#include "Widget.h"

//std::vector<std::string> strTags = {"hololive"};

class UIObjects {
public:
    ArtClass* art;
    ArtClass* logo;

    Plate* sidebar;
    Plate* bgPl;
    EditBox* input;

    Button* bSettings;
    Button* bHide;

    Text* title_Tags;

    // Yandere STUFF
    Plate* tTip;
    std::vector<Button*> tBtnTags;

    // ANIMATIONS
    intAnimation* input_Width;
    intAnimation* tTip_Width;
    intAnimation* tTip_Height;

    intAnimation* sidebar_xPos;
};
