#ifndef _VIEW_MODEL_CURSES_HPP
#define _VIEW_MODEL_CURSES_HPP

#include "Board.hpp"
#include "Game.hpp"
#include "ViewModelBase.hpp"

namespace viewCurses {

struct ViewModelCurses : public ViewModelBase {
    typedef std::vector<Move> MovesTable;

    ViewModelCurses(const Board&, PlayerColour);
    ViewModelCurses(const Board&, PlayerColour, MovesTable&);

    struct ViewCellCurses {
        enum class ViewCellCursesStatus {
            ACTIVE,         // possible move
            INACTIVE,       // nothing special
            CURRENT,        // current pointer position
            SELECTED,       // selected to make move
            PREVIOUS_FROM,  // previous cell of moved figure
            PREVIOUS_TO     // current cell of moved figure
        };

        ViewCellCurses(Cell, ViewCellCursesStatus = ViewCellCursesStatus::INACTIVE);

        Cell cell_;
        std::vector<Move> inMoves_;
        ViewCellCursesStatus status_;
    };

    ViewCellCurses& get(const Position& pos);
    const ViewCellCurses& get(const Position& pos) const;

    const int cols_, rows_;
    std::vector<std::vector<ViewCellCurses>> viewBoard_;
    PlayerColour turn_;
};


using CellStatus = ViewModelCurses::ViewCellCurses::ViewCellCursesStatus;
using ViewCellCurses = ViewModelCurses::ViewCellCurses;

}  // namespace viewCurses

#endif
