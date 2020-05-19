#ifndef _GREEDYBOT_HPP
#define _GREEDYBOT_HPP

#include "Bot.hpp"
#include "MoveTypes.hpp"
#include "Evaluate.hpp"

#include <functional>

class GreedyBot : Bot
{
public:
    GreedyBot() = delete;
    GreedyBot(evaluate_function_t eval_function) : evaluation_finction_(eval_function) {};
    Move makeMove(const Game &game) override;
    std::pair<int, Move> test_makeMove(const Game &g) override;


   private:
    evaluate_function_t evaluation_finction_;
};

#endif
