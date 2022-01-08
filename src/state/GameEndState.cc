#include "GameEndState.h"

GameEndState::GameEndState(Context *context)
    : State(context, kStateUserInput) {}

GameEndState &GameEndState::GetInstace(Context *context) {
    static GameEndState instance(context);
    return (instance);
}
GameEndState::~GameEndState() {}

/*
** 오델로 게임 하나가 끝났을 때 진행되는 Action
**     우승자 발표
**     board 출력
**     동적할당한 메모리 해제
*/
void GameEndState::Action() {
    // context 가져오기
    Context *context = GameEndState::GetInstace(nullptr).context_;

    // board 출력
    DisplayBoard(context->vec_board());

    // 우승자 발표
    std::cout << "\n";
    switch (context->winner()) {
        case kUserO:
            std::cout << "!!!!! WINNER [USER O] !!!!!\n\n";
            break;
        case kUserX:
            std::cout << "!!!!! WINNER [USER X] !!!!!\n\n";
            break;
        default:
            std::cout << "!!!!! WINNER [TIE] !!!!!\n\n";
            break;
    }
    std::cout << "GAME OVER... Thank you.\n";
}
