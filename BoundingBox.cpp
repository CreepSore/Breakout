#include "BoundingBox.hpp"

BoundingBox::BoundingBox()
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

BoundingBox::BoundingBox(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}
