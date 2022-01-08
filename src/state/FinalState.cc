#include "FinalState.h"

FinalState::FinalState(Context *context) : State(context, kStateUserInput) {}

FinalState &FinalState::GetInstace(Context *context) {
    static FinalState instance(context);
    return (instance);
}

FinalState::~FinalState() {}

/*
** 유저 둘다 입력을 완료 O          :  다음 턴
** 유저 둘중 하나라도 입력 완료 X   :  차례 변경
*/
void FinalState::Action() {
    // context 가져오기
    Context *context = FinalState::GetInstace(nullptr).context_;

    // 유저 둘다 입력을 완료 O :  다음 턴
    if (context->user_o_state() != kUserInputNotYet &&
        context->user_x_state() != kUserInputNotYet) {
        // std::cout << " 둘다 입력 완료 O\n" ;
        // 각 유저의 상태를 "입력하지 않음" 으로 변경
        context->user_o_state(kUserInputNotYet);
        context->user_x_state(kUserInputNotYet);

        // 다음 턴
        context->turn(context->turn() + 1);
        // 순서 : (kUserO, kUserX) => (kUserO, kUserX) ...
        context->cur_user(kUserX);
    } else {
        // 유저 둘다 입력을 완료 X :  차례 변경
        // std::cout << " 둘다 입력 완료 X\n" ;
        (context->user_o_state() == kUserInputNotYet)
            ? context->cur_user(kUserO)
            : context->cur_user(kUserX);
    }

    // 초기상태로 변경
    context->state(kStateCoordCheck);
}
