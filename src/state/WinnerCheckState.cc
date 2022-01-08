#include "WinnerCheckState.h"

WinnerCheckState::WinnerCheckState(Context *context)
    : State(context, kStateUserInput) {}

WinnerCheckState::~WinnerCheckState() {
}

WinnerCheckState &WinnerCheckState::GetInstace(Context *context) {
    static WinnerCheckState instance(context);
    return (instance);
}


// 승자 확인, 게임이 종료되었다면 종료상태로 변경
// 종료되지 않았다면 현재 턴 종료
void WinnerCheckState::Action() {
    // context 가져오기
    Context *context = WinnerCheckState::GetInstace(nullptr).context_;

    // 오델로 보드
    // 보드 내용을 수정할 필요 없음
    const auto &board = context->vec_board();

    int board_size = context->board_size();

    // 유저별 돌의 개수
    int user_o_size = 0;
    int user_x_size = 0;
    int user_none_size = 0;

    // 현재 보드에서 유저가 소요한 돌의 개수 확인
    for (int row = 0; row < board_size; ++row) {
        for (int col = 0; col < board_size; ++col) {
            switch (board[row][col]->owner()) {
                case kUserO:
                    user_o_size++;
                    break;
                case kUserX:
                    user_x_size++;
                    break;
                default:
                    user_none_size++;
                    break;
            }
        }
    }
    // 아래 조건에 의해 더이상 돌을 놓을 수 없게 되면 게임이 끝납니다.
    //      1. 양 쪽 모두 서로 차례를 넘겨야하는 경우
    //      2. 어느 한쪽이 돌을 모두 뒤집은 경우
    //      3. 돌이 가득찬 경우
    if ((context->user_o_state() == kUserInputInvalid &&
         context->user_x_state() == kUserInputInvalid) ||
        (user_o_size * user_x_size == 0) ||
        (user_o_size + user_x_size == board_size * board_size)) {
        // 돌의 개수를 비교해서 누가 이겼는지 확인
        if (user_o_size > user_x_size) {
            context->winner(kUserO);
        } else if (user_o_size < user_x_size) {
            context->winner(kUserX);
        } else {
            // 돌의 개수가 같으면 무승부
            context->winner(kUserTie);
        }
        // 게임 종료 상태로 변경
        context->state(kStateGameEnd);
        return;
    }

    // 현재 턴 종료
    context->state(kStateFinal);
}
