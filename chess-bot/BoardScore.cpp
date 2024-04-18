#include "BoardScore.h"
#include "chess.hpp"

enum PieceScore {
	PAWN = 1,
	KNIGHT = 3,
	BISHOP = 3,
	ROOK = 5,
	QUEEN = 10,
	KING = 1000
};

static float Evaluate(chess::Board& board, chess::Color turn) {

	float score = 0;
	for (size_t row = 0; row < 8; row++) {
		for (size_t col = 0; col < 8; col++) {
			auto piece = board.at(chess::Square(chess::Rank(row), chess::File(col)));
			int scoreMod = 1, value = 0;

			if (piece.color().internal() != turn) 
				scoreMod = -1;

			switch (piece.type())
			{
			case (uint8_t)chess::PieceType::PAWN:
				value = PieceScore::PAWN;
				break;
			case (uint8_t)chess::PieceType::KNIGHT:
				value = PieceScore::KNIGHT;
				break;
			case (uint8_t)chess::PieceType::BISHOP:
				value = PieceScore::BISHOP;
				break;
			case (uint8_t)chess::PieceType::ROOK:
				value = PieceScore::ROOK;
				break;
			case (uint8_t)chess::PieceType::QUEEN:
				value = PieceScore::QUEEN;
				break;
			case (uint8_t)chess::PieceType::KING:
				value = PieceScore::KING;
				break;
			default:
				//debug
				break;
			}
			score += value * scoreMod;
		}
	}

	return score;
}