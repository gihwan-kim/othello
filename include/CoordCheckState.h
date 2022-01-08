#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_COORDCHECKSTATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_COORDCHECKSTATE_H_

#include <array>
#include <iostream>

#include "Context.h"
#include "State.h"
#include "Utils.h"

/*
** singleton pattern
*/

class CoordCheckState : public State {
 public:
    static CoordCheckState &GetInstace(Context *);

    // 가능한 좌표와 그 좌표에서 바꿀수 있는 볌위들을 모두 계산하고
    // context 에 저장
    void Action() override;

 private:
    static std::array<std::array<int, 2>, 8> mover_;
    ~CoordCheckState();
    explicit CoordCheckState(Context *);
    struct ValidCoord  CalculateValidCoord(int, int);
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_COORDCHECKSTATE_H_
