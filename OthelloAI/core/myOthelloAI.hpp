#ifndef MYOTHELLOAI_HPP
#define MYOTHELLOAI_HPP

#include "OthelloAI.hpp"

namespace jordanby
{
    class warGamesAI: public OthelloAI
    {
    public:
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;

    private:
        std::vector<std::pair<int, int>> findPossibleMoves(const OthelloGameState& state);
        int eval(const OthelloGameState& state, std::string turn);
        int search(const OthelloGameState& state, int depth, std::string turn);
        

        // 1 is black
        // -1 is white
        // will need a search function, pass this whose turn it is as well 
    };
}

#endif