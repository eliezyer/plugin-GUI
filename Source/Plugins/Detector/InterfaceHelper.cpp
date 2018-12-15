#include "InterfaceHelper.h"

int getNext_X(Component* reference) {
	int next_X = reference->getX() + reference->getWidth() + SPACING;
	return next_X;
}

int getNext_Y(Component* reference) {
	int next_Y = reference->getY() + reference->getHeight() + SPACING;
	return next_Y;
}