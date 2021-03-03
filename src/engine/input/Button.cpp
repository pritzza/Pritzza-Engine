#include "Button.h"

#include <SFML/Graphics.hpp>

void Button::update(const bool isPressed)
{
    if      (isIdle()   && isPressed)  state = BUTTON_STATE::TAPPED;
    else if (isTapped() && isPressed)  state = BUTTON_STATE::HELD;
    else if (isTapped() && !isPressed) state = BUTTON_STATE::RELEASED;
    else if (isHeld()   && !isPressed) state = BUTTON_STATE::RELEASED;
    else if (isReleased()            ) state = BUTTON_STATE::IDLE;
}

const bool Button::isTapped() const     { return state == BUTTON_STATE::TAPPED;     }
const bool Button::isHeld() const       { return state == BUTTON_STATE::HELD;       }
const bool Button::isReleased() const   { return state == BUTTON_STATE::RELEASED;   }
const bool Button::isIdle() const       { return state == BUTTON_STATE::IDLE;       }
