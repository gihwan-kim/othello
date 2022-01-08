#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_WINNERCHECKSTATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_WINNERCHECKSTATE_H_

#include <iostream>
#include <array>

#include "State.h"
#include "Utils.h"
#include "Context.h"

/*
** singleton pattern
*/

/*
** 	아래와 같은 조건에 의해 양쪽 모두 더 이상 돌을 놓을 수 없게 되면 게임이
**  끝나게 된다.
**     N x M 개의 돌 모두가 판에 가득 찬 경우 (가장 일반적)
**     어느 한 쪽이 돌을 모두 뒤집은 경우
**     한 차례에 양 쪽 모두 서로 차례를 넘겨야 하는 경우
** 	게임이 끝났을 때 돌이 많이 있는 플레이어가 승자가 된다.
**  만일 돌의 개수가 같을 경우는 무승부가 된다.
**
*/

class WinnerCheckState : public State {
 public:
    static WinnerCheckState &GetInstace(Context *);

    // 승자 확인 함수
    // 게임이 종료되었다면 종료상태로 변경 : kStateGameEnd
    // 게임이 종료되지 않았다면 현재 턴 종료 : kStateFinal
    void Action() override;

 private:
    ~WinnerCheckState();
    explicit WinnerCheckState(Context *);
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_WINNERCHECKSTATE_H_
