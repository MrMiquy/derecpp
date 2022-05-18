#include "../headers/Parent.h"

Parent::Parent() {
}

Parent::~Parent() {
}

void Parent::addChild(Widget* child) {
    children.push_back(child);
}
