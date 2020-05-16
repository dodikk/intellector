#include "ViewStartMenuCurses.hpp"

#include "ViewMenuMultiplexerCurses.hpp"
#include <assert.h>

namespace viewCurses {

StartMenuCurses::StartMenuCurses()
        : MainMenuCurses{{{"resources/newgame.btn", BUTTON_STYLE::RECTANGLE},
                          {"resources/rules.btn", BUTTON_STYLE::RECTANGLE},
                          {"resources/contacts.btn", BUTTON_STYLE::RECTANGLE},
                          {"resources/options.btn", BUTTON_STYLE::RECTANGLE},
                          {"resources/exit.btn", BUTTON_STYLE::RECTANGLE}}} {
}

RET_CODE StartMenuCurses::show(int c) {
    draw();
    RET_CODE rc = RET_CODE::NOTHING;
    switch (c) {
        case 'w':
        case KEY_UP:
            if (buttons_.size() > 0) {
                currentButtonIndex_ = (currentButtonIndex_ - 1 + buttons_.size()) % buttons_.size();
                draw();
            }
            break;
        case 's':
        case KEY_DOWN:
            if (buttons_.size() > 0) {
                currentButtonIndex_ = (currentButtonIndex_ + 1) % buttons_.size();
                draw();
            }
            break;
        case 27:  // ESC
            break;
        case 32:
            // assuming correct buttons order:
            // new game
            // rules
            // contacts
            // options
            // exit
            switch (currentButtonIndex_) {
                case 0:  // new game
                    rc = RET_CODE::START_NEW_GAME;
                    break;
                case 1:  // rules
                    break;
                case 2:  // contacts
                    break;
                case 3:  // options
                    rc = RET_CODE::OPTIONS_MENU;
                    break;
                case 4:  // exit
                    rc = RET_CODE::EXIT;
                    break;
                default:
                    assert(0);
            }
            break;
        default:
            // do nothing
            break;
    }
    return rc;
}

};  // namespace viewCurses
