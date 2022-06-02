#include "../headers/Grid.h"

void Grid::render() {
    if (enable) {
        if (children.size() > 0) {
            Widget::render();
            setPadding(padding);
            SDL_Rect temp = {0, 0, geometry.w, geometry.h};
            SDL_Texture* auxtexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, geometry.w, geometry.h);
            SDL_SetTextureBlendMode(auxtexture, SDL_BLENDMODE_BLEND);

            SDL_SetRenderTarget(renderer, auxtexture);

            if (color.a != 0) {
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderFillRect(renderer, &temp);
            }

            for (Uint8 i = 0; i < table.x; i++) {
                for (Uint8 j = 0; j < table.y; j++) {
                    if (grid[i][j] != nullptr) {
                        if (grid[i][j]->getGeometry().w > grid[i][j]->getGeometry().h) {
                            grid[i][j]->proportionalSizeW(cell.x);
                        } else {
                            grid[i][j]->proportionalSizeH(cell.y);
                        }
                        setChildPos({i, j}, grid[i][j]);
                        grid[i][j]->render();
                    }
                }
            }
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, auxtexture, NULL, &geometry);
            SDL_DestroyTexture(auxtexture);
        }
    }
}

void Grid::setTable(Uint8 rows, Uint8 collumns) {
    table = {rows, collumns};
    grid.clear();
    grid.resize(table.x);
    geometry.w = cell.x * table.x;
    geometry.h = cell.y * table.y;

    for (Uint8 i = 0; i < table.x; i++) {
        grid[i].resize(collumns);
    }
}

void Grid::setCellSize(SDL_Point cellSize) {
    geometry.w = cellSize.x * table.x;
    geometry.h = cellSize.y * table.y;
    cell = cellSize;

    for (Uint8 i = 0; i < table.x; i++) {
        for (Uint8 j = 0; j < table.y; j++) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->setSize(cellSize);
            }
        }
    }
}

void Grid::addChild(Widget* widget) {
    Parent::addChild(widget);
    if (alignment == Vertical) {
        for (Uint8 i = 0; i < table.x; i++) {
            for (Uint8 j = 0; j < table.y; j++) {
                if (grid[i][j] == nullptr) {
                    grid[i][j] = widget;
                    return;
                }
            }
        }
    } else {
        for (Uint8 i = 0; i < table.y; i++) {
            for (Uint8 j = 0; j < table.x; j++) {
                if (grid[j][i] == nullptr) {
                    grid[j][i] = widget;
                    return;
                }
            }
        }
    }
}

void Grid::setPadding(SDL_Rect _padding) {
    padding = _padding;
    for (Uint8 i = 0; i < table.x; i++) {
        for (Uint8 j = 0; j < table.y; j++) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->setPadding(_padding);
            }
        }
    }
}

SDL_Point Grid::getTable() {
    return table;
}

void Grid::setColor(SDL_Color _color) {
    color = _color;
}

SDL_Point Grid::getOffset() {
    return offset;
}

SDL_Point Grid::getCellSize() {
    return cell;
}

int* Grid::yOffsetReference() {
    return &offset.y;
}

int* Grid::xOffsetReference() {
    return &offset.x;
}

void Grid::setOffset(SDL_Point _offset) {
    offset = _offset;
}

Uint8 Grid::getRow() {
    return table.x;
}

Uint8 Grid::getCol() {
    return table.y;
}

void Grid::setChildPos(SDL_Point point, Widget* child) {
    child->setPos({(cell.x / 2 - child->getGeometry().w / 2) + (point.x * cell.x) + offset.x, (cell.y / 2 - child->getGeometry().h / 2) + (point.y * cell.y) + offset.y});
}
