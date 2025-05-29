#pragma once
#include "PatternRenderer.h"

class GuiController {
public:
    GuiController(PatternRenderer& renderer);
    void draw();

private:
    PatternRenderer& renderer;
    int selectedPattern = 0;
};