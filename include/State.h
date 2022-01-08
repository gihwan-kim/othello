
#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STATE_H_

#include "Utils.h"

class Context;

/*
** Abstract class
*/

/*
** State : 현재 상태를 나타내는 interface
**   State 를 상속받는 class
**     배치 규칙 검사       CoordCheckState     : 현재 유저가 돌을 둘 수 있는 상황인지 확인하고 둘 수 있는 돌을 미리 계산
**     유저 입력 상태       UserInputState      : 보드 출력, 좌표 입력, 입력한 좌표문자열 검사
**     뒤집기              UpdateBoardState    : 뒤집기
**     승패 규칙 검사       WinnerCheckState    : 승패 확인
**     종료 상태           FinalState           : 유저 변경, 현재 턴 확인후 갱신(유저 둘다 입력을 완료했다면)
**     게임종료 상태        GameEndState        : 게임이 끝났을때, 우승자 발표, board 출력
*/

class State {
 public:
    explicit State(Context *, StateType);

/*
**     각 상태 별로 해야하는 작업들, derived class 에서 각각의 Action 함수를 override
**     Context 의 Action 기능을 호출 했을 때 State 들에 맞게 Action 이 호출 됩니다.
*/
    virtual void Action() = 0;
    ~State();

 protected:
    Context *context_;
    StateType type_;

 private:
    /* data */
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STATE_H_
