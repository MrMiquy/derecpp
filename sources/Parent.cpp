#include "../headers/Parent.h"

void Parent::addChild(Widget* child) {
    children.push_back(child);
}

void Parent::fixChildrenPos(bool value) {
    isFixed = value;
}
