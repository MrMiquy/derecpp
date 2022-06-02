#include <SDL2/SDL.h>
#include <vector>
#include "Widget.h"
#include "Parent.h"
#include "Animation.h"
#include "Scrollbar.h"

class Grid : public Widget, public Parent {
public:
    //intAnimation yOffset;
    //Scrollbar xScroll, yScroll;

    void setTable(Uint8 rows, Uint8 collumns);
    void setCellSize(SDL_Point cellSize);
    void setPadding(SDL_Rect padding);
    void setColor(SDL_Color color);
    void setOffset(SDL_Point offset);
    //void setRow(Uint8 rows);
    //void setCol(Uint8 collumns);

    SDL_Point getTable();
    SDL_Point getOffset();
    SDL_Point getCellSize();
    int* yOffsetReference();
    int* xOffsetReference();
    Uint8 getRow();
    Uint8 getCol();

    //void addWidget(Widget* widget, SDL_Point toCell);
    //void addWidget(Widget* widget, Uint8 row, Uint8 col);
    void addChild(Widget* child) override;
    void print();
    void render();

protected:
    SDL_Point offset = {0, 0};
    SDL_Color color = {0, 0, 0, 0};
    SDL_Point cell = {100, 100};
    SDL_Point table = {1, 1};
    Alignment alignment = Horizontal;
    std::vector<std::vector<Widget*>> grid;

    void setChildPos(SDL_Point point, Widget* child);
};
