#include "Viewer.h"

void DisplayBoard(const std::vector<std::vector<Stone *>> &board) {
    // 보드는 출력전에 항상 콘솔을 비워줌
    system("clear");
    int board_size = board.size();

    // y 위치 정보
    for (int col = 0; col < board_size; ++col) {
        std::cout << "   " << col;
    }
    std::cout << "\n";

    // std::cout << board.size() << board[0].size();
    for (int row = 0; row < board_size; ++row) {
        // 열
        std::cout << "  +";
        for (int col = 0; col < board_size; ++col) {
            std::cout << "---+";
        }
        // x 위치 정보
        std::cout << "\n" << row << " |";

        // 돌 소유주에 맞게 출력
        for (int col = 0; col < board_size; ++col) {
            if (board[row][col]->owner() == kUserO) {
                std::cout << " O |";
            } else if (board[row][col]->owner() == kUserX) {
                std::cout << " X |";
            } else {
                std::cout << "   |";
            }
        }
        std::cout << "\n";
    }

    // footer
    std::cout << "  +";
    for (int col = 0; col < board_size; ++col) {
        std::cout << "---+";
    }
    std::cout << "\n";
}
