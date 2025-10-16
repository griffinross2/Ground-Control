#include "utility.h"

void util::centerItem(float itemWidth) {
    float windowWidth = ImGui::GetWindowSize().x;

    ImGui::SetCursorPosX((windowWidth - itemWidth) / 2.0f);
}
