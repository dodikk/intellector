#include "AlphaBetaBot.hpp"

#include <cassert>

#include "Evaluate.hpp"
#include "Game.hpp"
#include <iostream>
#include <thread>         
#include <chrono>
#include <random>

std::mt19937 randoms(std::time(0));

using std::cout;
using std::endl;

const int DEPTH = 5;
PlayerColour Colour;

std::pair<int, std::shared_ptr<Move>> AlphaBetaBot::make_virtual_move(const Game &game,
                                                                      PlayerColour colour,
                                                                      bool max,
                                                                      int alpha,
                                                                      int beta,
                                                                      int depth) {
    int value = evaluation_function_(game, Colour);

    if (abs(value) > 1e5) {
        return {value, nullptr};
    }

    if (depth == 0) {
        return std::pair<int, std::shared_ptr<Move>>{evaluation_function_(game, Colour), nullptr};
    }

    std::vector<std::pair<std::shared_ptr<Move>, int>> all_moves;


    Board board = Board(game.getBoard());

    for (auto &row : board.data_)
        for (auto &cell : row) {
            std::vector<std::shared_ptr<Move>> moves = game.allFigureMoves(cell.pos_);
            for (auto &move : moves) 
            	all_moves.emplace_back(move, evaluate::figure_value.at(cell.figure_.value().type_));
        }

    std::sort(all_moves.begin(), all_moves.end(), [&](auto a, auto b)
    {
        return a.second > b.second;
    });


    if (max) {
        std::pair<int, std::shared_ptr<Move>> res = {-1e9, nullptr};
        for (const auto &[move, _] : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);

			copy.makeMove(*move);
            auto mvm = make_virtual_move(copy, other_colour(colour), !max, alpha, beta, depth - 1);

            if (res.first < mvm.first) {
                res.first = mvm.first;
                res.second = move;
            }

            alpha = std::max(alpha, mvm.first);
        }
        return res;
    } else {
        std::pair<int, std::shared_ptr<Move>> res = {1e9, nullptr};
        for (auto &[move, _] : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);
            copy.makeMove(*move);
            auto mvm = make_virtual_move(copy, other_colour(colour), !max, alpha, beta, depth - 1);

            if (res.first > mvm.first) {
                res.first = mvm.first;
                res.second = move;
            }
            beta = std::min(beta, mvm.first);
        }
        return res;
    }
}

std::shared_ptr<Move> AlphaBetaBot::makeMove(const Game &game) {
    Game gamecopy(game);
    auto colour = game.getColourCurrentPlayer();
    Colour = colour;
    auto res = make_virtual_move(gamecopy, colour, true, -1000, 1000, DEPTH);
	return res.second;
}
