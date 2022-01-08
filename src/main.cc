// #include <cctype>
// #include <iomanip>
#include <iostream>
#include <string>

#include "Context.h"
#include "Utils.h"

// 게임의 첫 입력 명령어가 "quit" 명렁어인지 확인하는 변수
//  main() 함수에서만 사용
static bool kCmdIsQuit = false;

// 입력받은 str(board size)의 유효성 검사
bool BoardSizeValidation(std::string str) {
    if (str == "quit") {
        kCmdIsQuit = true;  // quit 용 flag
        return false;
    } else if (UtilsStringIsNumber(str)) {
        int board_size = std::stoi(str);
        // minimum board size
        if (board_size < kMinBoardSize) {
            std::cout << "[Invalid input] : Wrong baord size (size >= 3)\n";
            return (false);
        }
        return (true);
    }
    return (false);
}

void StartOthello(int board_size) {
    // context : controller
    Context context(board_size);

    system("clear");
    // game loop
    while (true) {
        context.state(kStateCoordCheck);
        // while 문이 한번돌 때마다 유저에게 입력을 요구
        while (context.state() != kStateGameEnd) {
            context.Action();
        }
        // 게임 종료
        if (context.state() == kStateGameEnd) {
            context.Action();
            return;
        }
    }
}

int main() {
    std::cout << "\n\n";
    std::cout
        << "###########################################################\n";
    std::cout
        << "###########################################################\n";
    std::cout
        << "##                                                       ##\n";
    std::cout
        << "##               OOP Term Project : Othello              ##\n";
    std::cout
        << "##                                                       ##\n";
    std::cout
        << "##               Members                                 ##\n";
    std::cout
        << "##                   201701981                           ##\n";
    std::cout
        << "##                   201802120                           ##\n";
    std::cout
        << "##                   201802064                           ##\n";
    std::cout
        << "##                   200000000                           ##\n";
    std::cout
        << "##                                                       ##\n";
    std::cout
        << "###########################################################\n";
    std::cout
        << "###########################################################\n";
    do {
        // prompt message : 게임 종료, 보드 크기 정보 안내
        std::cout << "\n\n";
        std::cout << "Welcome to othello!!\n\n";
        std::cout << "[Information]\n";
        std::cout << "If you want to quit program, please input \"quit\"."
                  << std::endl;
        std::cout << "Or if you want to start Othello, please input Board Size "
                     "N (NxN)"
                  << std::endl;
        std::cout << "\n\n";
        std::cout << "Othello >> ";

        // 보드 입력
        std::string command;
        getline(std::cin, command);

        std::cout << command << "\n";
        if (BoardSizeValidation(command)) {
            // start game loop
            std::cout << "start Othello\n";
            StartOthello(std::stoi(command));
        }
    } while (!kCmdIsQuit);
    std::cout << "Game End!" << std::endl;

    return (0);
}
