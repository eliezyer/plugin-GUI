#include "InterfaceHelper.h"

int getNext_X(Component* reference) {
	int next_X = reference->getX() + reference->getWidth();
	return next_X;
}

int getNext_Y(Component* reference) {
	int next_Y = reference->getY() + reference->getHeight();
	return next_Y;
}