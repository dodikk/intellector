
#ifndef _OPTIMIZEDALPHABETABOT_HPP
#define _OPTIMIZEDALPHABETABOT_HPP

#include "Bot.hpp"
#include "FunctionSet.hpp"
#include "FigureKeeper.hpp"
// #pragma once

class OptimizedAlphaBetaBot : Bot
{
public:
    OptimizedAlphaBetaBot() = delete;
    OptimizedAlphaBetaBot(int depth, int set_number) : 
                 depth_(depth),  
                 functions_(set_number) {};

    Move makeMove(const Game &g) override;

   private:
    std::pair<int, Move> make_virtual_move(Game &game,
                                           PlayerColour colour,
                                           bool max,
                                           int alpha,
                                           int beta,
                                           int depth, 
                                           int prev_value);

    int depth_;
    // evaluate_function_t evaluation_function_;
    FunctionSet functions_;
    FigureKeeper figures_;
};

#endif  //_OPTIMIZEDALPHABETABOT_HPP