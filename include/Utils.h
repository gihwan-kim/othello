#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_UTILS_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_UTILS_H_

#include <string>
#include <cstring>
#include <vector>
#include <utility>

const int kMinBoardSize = 3;

// 자주 사용는 함수, 필요한 enum type 들이 선언된 헤더파일

//  현재 게임 상태
enum StateType {
    kStateUserInput,
    kStateCoordCheck,
    kStateUpdateBoard,
    kStateWinnercheck,
    kStateFinal,
    kStateGameEnd
};

// 각 유저별 입력 상태
enum UserInputType {
    kUserInputValid,    // 입력 O, (돌을 둘 곳이 있음)
    kUserInputInvalid,  // 입력 O, (돌을 둘 곳이 없음)
    kUserInputNotYet    // 아직 돌을 두지 않음
};

// 유저 유형
enum UserType {
                kUserO,     // 백
                kUserX,     // 흑
                kUserNone,  // 소유주 없음
                kUserTie    // 무승부
            };

// 입력 가능한 좌표 데이터
struct ValidCoord {
    int x_, y_;

    // 현재 (x, y) 를 기준으로
    // 뒤집을 좌표 범위를 담은 벡터 : <mover_idx, <x, y>>
    //     (x, y) ~ (?, ?) 까지 mover_idx 방향으로 뒤집기
    std::vector<std::pair<int, std::pair<int, int>>> toupdate_coord_;
    ValidCoord() {}
    ValidCoord(int x, int y) : x_(x), y_(y) {}
};

// split 함수
std::vector<std::string> UtilsSplit(std::string str, std::string del);

// 문자열이 숫자로만 이루어져 있는지 검사
bool UtilsStringIsNumber(const std::string &str);

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_UTILS_H_
