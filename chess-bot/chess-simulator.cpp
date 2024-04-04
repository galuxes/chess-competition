#include "chess-simulator.h"
// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
#include "BoardScore.cpp"
#include <random>
using namespace ChessSimulator;

std::string ChessSimulator::Move(std::string fen) {
  // create your board based on the board string following the FEN notation
  // search for the best move using minimax / monte carlo tree search /
  // alpha-beta pruning / ... try to use nice heuristics to speed up the search
  // and have better results return the best move in UCI notation you will gain
  // extra points if you create your own board/move representation instead of
  // using the one provided by the library

    std::string move = "";


  // here goes a random movement
  chess::Board board(fen);
  chess::Movelist moves;
  chess::movegen::legalmoves(moves, board);
  if(moves.size() == 0)
    return move;

  return BestOneDeep(moves, board);

  //// get random move
  //std::random_device rd;
  //std::mt19937 gen(rd());
  //std::uniform_int_distribution<> dist(0, moves.size() - 1);
  //chess::Move move = moves[dist(gen)];
  //return chess::uci::moveToUci(move);
}

std::string ChessSimulator::BestOneDeep(chess::Movelist moves, chess::Board board) 
{
	chess::Board tmpBoard;
	tmpBoard = board;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, moves.size() - 1);
	int ranNum = dist(gen);
	tmpBoard.makeMove(moves[ranNum]);
	float bestScore = Evaluate(tmpBoard), tmpScore = 0;
	int bestScoreIndex = ranNum;

	for(int i = 0; i < moves.size(); i++)
	{
		tmpBoard = board;
		tmpBoard.makeMove(moves[i]);
		tmpScore = Evaluate(tmpBoard);
		if (tmpScore > bestScore) {
			bestScore = tmpScore;
			bestScoreIndex = i;
		}
	}
	std::cout << moves.size();
	return chess::uci::moveToUci(moves[bestScoreIndex]);
}


