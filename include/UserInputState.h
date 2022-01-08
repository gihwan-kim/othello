#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_USERINPUTSTATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_USERINPUTSTATE_H_

#include <iostream>
#include <utility>

#include "Context.h"
#include "State.h"
#include "Utils.h"

/*
** singleton pattern
*/

class UserInputState : public State {
 public:
    static UserInputState &GetInstace(Context *);

    // 좌표를 입력받고 유효성을 검사해 올바른 경우
    // context에 좌표 저장 및 다음 상태로 이동
    void Action() override;

 private:
    /* data */
    explicit UserInputState(Context *);
    ~UserInputState();
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_USERINPUTSTATE_H_
