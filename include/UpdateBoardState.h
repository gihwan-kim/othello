#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_UPDATEBOARDSTATE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_UPDATEBOARDSTATE_H_

#include <array>
#include <iostream>

#include "Context.h"
#include "State.h"
#include "Utils.h"

/*
** singleton pattern
*/

/*
** 유효한 좌표를 입력 했을 때 실행되는 상태
**     돌 뒤집기
*/

class UpdateBoardState : public State {
 public:
    static UpdateBoardState &GetInstace(Context *);

    // UserInputState 에서 결정된 좌표에서 뒤집을 수 있는 돌 뒤집기,
    // 갱신된 board 출력
    // context 의 toupdate_coordinate 에 기록된 좌표와 현재 입력된
    // 좌표 사이의 돌을 뒤집어줍니다.
    void Action() override;

 private:
    static std::array<std::array<int, 2>, 8> mover_;
    ~UpdateBoardState();
    explicit UpdateBoardState(Context *);
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_UPDATEBOARDSTATE_H_
