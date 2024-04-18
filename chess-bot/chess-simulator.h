#pragma once
#include <string>
#include "chess.hpp"

struct EvaluatedMove
{
	std::string move;
	float evaluation;
};

namespace ChessSimulator {
/**
 * @brief Move a piece on the board
 *
 * @param fen The board as FEN
 * @return std::string The move as UCI
 */
std::string Move(std::string fen);
EvaluatedMove BestOneDeep(chess::Movelist moves, chess::Board, chess::Color turn, int depth);
} // namespace ChessSimulator