#include "AlphaBetaBot.hpp"

#include "Game.hpp"

#include <cassert>

std::pair<int, std::shared_ptr<SimpleMove>> AlphaBetaBot::make_virtual_move(const Game &game,
                                                                            PlayerColour colour,
                                                                            bool max,
                                                                            int alpha,
                                                                            int beta,
                                                                            int depth) {
    if (depth == 0) {
        return std::pair<int, std::shared_ptr<SimpleMove>>{
            evaluation_function_(game.getBoard(), colour),
            nullptr};
    }

    std::vector<std::shared_ptr<SimpleMove>> all_moves;

    Board board = Board(game.getBoard());

    for (auto &row : board.data_)
        for (auto &cell : row) {
            std::vector<std::shared_ptr<SimpleMove>> moves = game.allFigureMoves(cell.pos_);
            for (auto &move : moves) 
            	all_moves.push_back(move);
        }

    if (max) {
        std::pair<int, std::shared_ptr<SimpleMove>> res = {-1000, nullptr};
        for (const auto &move : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);
            if(!move)
            {
            	assert(0);
            }
			copy.makeMove(*move);
            auto mvm = make_virtual_move(game, colour, !max, alpha, beta, depth - 1);

            if(res.first < mvm.first)
            {
            	res.first = mvm.first;
            	res.second = move;
            }

            alpha = std::max(alpha, mvm.first);
        }
        return res;
    } else {
        std::pair<int, std::shared_ptr<SimpleMove>> res = {1000, nullptr};
        for (auto &move : all_moves) {
            if (alpha > beta)
                break;
            Game copy(game);
			copy.makeMove(*move);
            auto mvm = make_virtual_move(game, colour, !max, alpha, beta, depth - 1);

            if(res.first > mvm.first)
            {
            	res.first = mvm.first;
            	res.second = move;
            }
            beta = std::min(beta, mvm.first);
        }
        return res;
    }
}

std::shared_ptr<SimpleMove> AlphaBetaBot::makeMove(const Game &game) {
	Game gamecopy(game);
    auto colour = game.getColourCurrentPlayer();
	return make_virtual_move(gamecopy, colour, true, -1000, 1000, 6).second;
}