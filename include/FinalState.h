#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_FINALSTATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_FINALSTATE_H_

#include <iostream>

#include "Context.h"
#include "State.h"
#include "Utils.h"

/*
** singleton pattern
*/

/*
** 유저 둘다 입력을 완료 O          :  다음 턴
** 유저 둘중 하나라도 입력 완료 X   :  차례 변경
*/
class FinalState : public State {
 public:
    static FinalState &GetInstace(Context *);
    void Action() override;

 private:
    ~FinalState();
    explicit FinalState(Context *);
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_FINALSTATE_H_
