#include "myOthelloAI.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, jordanby::warGamesAI, "War Games Othello AI (Required)");

std::pair<int, int> jordanby::warGamesAI::chooseMove(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> moveList;
    int optimalX;
    int optimalY;
    std::string turn;
    int bestScore = -9999;

    moveList = findPossibleMoves(state);

    if (state.isWhiteTurn())
        turn = "white";
    else
        turn = "black";

    for (int i = 0; i < moveList.size(); i++)
    {
        int score;
        std::unique_ptr<OthelloGameState> clone = state.clone();
        clone -> makeMove(moveList[i].first, moveList[i].second);
        score = search(*clone, 4, turn);
        if (score > bestScore)
        {
            bestScore = score;
            optimalX = moveList[i].first;
            optimalY = moveList[i].second;
        }
    }

    return std::make_pair(optimalX, optimalY);
}

std::vector<std::pair<int, int>> jordanby::warGamesAI::findPossibleMoves(const OthelloGameState& state)
{
    std::vector<std::pair<int, int>> possible;

    for (int i = 0; i < state.board().width(); i++)
    {
        for (int j = 0; j <state.board().height(); j++)
        {
            if (state.isValidMove(i, j))
            {
                possible.push_back(std::make_pair(i, j));
            }
        }
    }
    
    return possible;
}

int jordanby::warGamesAI::eval(const OthelloGameState& state, std::string turn)
{
    if (turn == "black")
    {
        return state.blackScore() - state.whiteScore();
    }
    else
    {
        return state.whiteScore() - state.blackScore();
    }
}

int jordanby::warGamesAI::search(const OthelloGameState& state, int depth, std::string turn)
{
    int score;
    int myBestScore = -9999;
    int enemyBestScore = 9999;
    std::vector<std::pair<int, int>> moveList;

    // base case
    if (state.isGameOver() || depth == 0)
    {
        return eval(state, turn);
    }
    else
    {
        if ((state.isBlackTurn() && turn == "black") || (state.isWhiteTurn() && turn == "white"))
        {
            moveList = findPossibleMoves(state);
            for (int i = 0; i < moveList.size(); i++)
            {
                std::unique_ptr<OthelloGameState> newClone = state.clone();
                newClone -> makeMove(moveList[i].first, moveList[i].second);
                score = search(*newClone, depth - 1, turn);
                if (score > myBestScore)
                    myBestScore = score;
            }
            return myBestScore;
        }
        else
        {
            moveList = findPossibleMoves(state);
            for (int j = 0; j < moveList.size(); j++)
            {
                std::unique_ptr<OthelloGameState> newClone = state.clone();
                newClone -> makeMove(moveList[j].first, moveList[j].second);
                score = search(*newClone, depth - 1, turn);
                if (score < enemyBestScore)
                    enemyBestScore = score;
            }
            return enemyBestScore;
        }
        
    }
    return 1;
}