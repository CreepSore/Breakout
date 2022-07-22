#pragma once

struct BoundingBox {
    float x;
    float y;
    float width;
    float height;

    BoundingBox();
    BoundingBox(float x, float y, float width, float height);
};
