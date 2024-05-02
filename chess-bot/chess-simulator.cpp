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


  chess::Board board(fen);
  chess::Movelist moves;
  chess::movegen::legalmoves(moves, board);
  if(moves.size() == 0)
    return move;

  move = BestOneDeep(moves, board, board.sideToMove(), 3).move;

  return move;
}

EvaluatedMove ChessSimulator::BestOneDeep(chess::Movelist moves, chess::Board board, chess::Color turn, int depth) 
{
	EvaluatedMove evalMove;
	evalMove.move = "";
	if (moves.size() < 1)
		return evalMove;

	chess::Board tmpBoard;
	tmpBoard = board;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, moves.size() - 1);
	int ranNum = dist(gen);
	tmpBoard.makeMove(moves[ranNum]);
	float tmpScore = Evaluate(tmpBoard, turn);
	if (depth > 0) {
		chess::Movelist tmpEnemyValidMoves;
		chess::movegen::legalmoves(tmpEnemyValidMoves, tmpBoard);
		EvaluatedMove min = BestOneDeep(tmpEnemyValidMoves, tmpBoard, ~turn, depth - 1);
		tmpScore -= Evaluate(tmpBoard, ~turn);
	}
	int bestScoreIndex = ranNum;
	float bestScore = tmpScore;


	for(int i = 0; i < moves.size(); i++)
	{
		tmpBoard = board;
		tmpBoard.makeMove(moves[i]);
		tmpScore = Evaluate(tmpBoard, turn);

		if (depth > 0) 
		{
			chess::Movelist tmpEnemyValidMoves;
			chess::movegen::legalmoves(tmpEnemyValidMoves, tmpBoard);
			EvaluatedMove min = BestOneDeep(tmpEnemyValidMoves, tmpBoard, ~turn, depth-1);
			if (min.move == "")
			{
				if (turn == board.sideToMove())
				{
					tmpScore = 1000;
				}
				else 
				{
					tmpScore = -1000;
				}
			}
			else {
				tmpScore = Evaluate(tmpBoard, ~turn);
			}
		}


		if (tmpScore > bestScore) {
			bestScore = tmpScore;
			bestScoreIndex = i;
		}
	}
	evalMove.move = chess::uci::moveToUci(moves[bestScoreIndex]);

	return evalMove;
}


