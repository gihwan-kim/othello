#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_GAMEENDSTATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_GAMEENDSTATE_H_

#include <iostream>

#include "Context.h"
#include "State.h"
#include "Viewer.h"

/*
** singleton pattern
*/

/*
** 오델로 게임 하나가 끝났을 때 진행되는 상태
**     우승자 발표
**     board 출력
**     동적할당한 메모리 해제
*/
class GameEndState : public State {
 public:
    static GameEndState &GetInstace(Context *);
    void Action() override;

 private:
    ~GameEndState();
    explicit GameEndState(Context *);
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_GAMEENDSTATE_H_
