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

  return BestOneDeep(moves, board, !board.sideToMove(), 1).move;

  //// get random move
  //std::random_device rd;
  //std::mt19937 gen(rd());
  //std::uniform_int_distribution<> dist(0, moves.size() - 1);
  //chess::Move move = moves[dist(gen)];
  //return chess::uci::moveToUci(move);
}

EvaluatedMove ChessSimulator::BestOneDeep(chess::Movelist moves, chess::Board board, chess::Color turn, int depth) 
{
	chess::Board tmpBoard;
	tmpBoard = board;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, moves.size() - 1);
	int ranNum = dist(gen);
	tmpBoard.makeMove(moves[ranNum]);
	float bestScore = Evaluate(tmpBoard, turn), tmpScore = 0;
	int bestScoreIndex = ranNum;

	for(int i = 0; i < moves.size(); i++)
	{
		tmpBoard = board;
		tmpBoard.makeMove(moves[i]);
		tmpScore = Evaluate(tmpBoard, turn);

		if (depth > 0) {
			chess::Movelist tmpEnemyValidMoves;
			chess::movegen::legalmoves(tmpEnemyValidMoves, tmpBoard);
			BestOneDeep(tmpEnemyValidMoves, tmpBoard, ~turn, depth--);
		}


		if (tmpScore > bestScore) {
			bestScore = tmpScore;
			bestScoreIndex = i;
		}
	}
	EvaluatedMove evalMove;
	evalMove.evaluation = bestScore;
	evalMove.move = chess::uci::moveToUci(moves[bestScoreIndex]);

	return evalMove;
}


