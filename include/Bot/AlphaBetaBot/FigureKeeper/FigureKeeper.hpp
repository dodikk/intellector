#ifndef _FIGUREKEEPER_HPP
#define _FIGUREKEEPER_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Bot/AlphaBetaBot/Evaluate/Evaluate.hpp"
#include "Model/ModelImpl/Board.hpp"
#include "Model/ModelImpl/Figure.hpp"
#include "Model/ModelImpl/MoveTypes.hpp"
#include "Model/ModelImpl/Position.hpp"

class FigureKeeper
{
public:
	FigureKeeper() = default;
	FigureKeeper(const Board &board);

    FigureKeeper(const std::vector<std::pair<Position, Figure>> &v);


	std::vector<Position> &get_figures(const PlayerColour colour);

	void makeMove(Move &move);
	void cancelMove(Move &move);

    size_t get_hash() const;

    friend bool operator==(const FigureKeeper &a, const FigureKeeper &b);
	void insertFigure(Position &pos, Figure &fig);
	void eraseFigure(Position &pos, Figure &fig);
private:

    size_t hash = 0;
	std::vector<Position> white_figures_;
	std::vector<Position> black_figures_;

};

namespace std
{
    template<>
    struct hash<FigureKeeper>
    {
        size_t operator()(const FigureKeeper &fig_keep) const
        {
            return fig_keep.get_hash();
        }
    };
};

bool operator==(const FigureKeeper &a, const FigureKeeper &b);

#endif // _FIGUREKEEPER_HPP
