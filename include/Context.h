#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_CONTEXT_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_CONTEXT_H_

#include <vector>

#include "CoordCheckState.h"
#include "FinalState.h"
#include "GameEndState.h"
#include "State.h"
#include "StoneFactory.h"
#include "UpdateBoardState.h"
#include "UserInputState.h"
#include "Viewer.h"
#include "WinnerCheckState.h"

/*
** 현재 상태를 저장
** Controller 의 기능을 담당
** 각 상태에 맞게 기능을 하도록 action 을 호출
*/

class Context {
 public:
    explicit Context(int);
    ~Context();

    /*
    **  setter, getter START
    */
    void state(StateType);
    StateType state();

    void coordinate(ValidCoord);
    ValidCoord coordinate();

    void board_size(int);
    int board_size();

    UserType cur_user();
    void cur_user(UserType);

    std::vector<std::vector<Stone *>> &vec_board();

    std::vector<ValidCoord> vec_valid_coordinate();
    void vec_valid_coordinate(std::vector<ValidCoord>);

    UserInputType user_o_state();
    void user_o_state(UserInputType);

    UserInputType user_x_state();
    void user_x_state(UserInputType);

    UserType winner();
    void winner(UserType);

    int turn();
    void turn(int);
    /*
    **  setter, getter END
    */

    // 상태별 동작을 진행시키는 함수
    void Action();

    // dervied class 에서도 setter, getter 를 통해서만 데이터에 접근할 수 있도록
 private:
    /* data */
    std::vector<std::vector<Stone *>> vec_board_;  // 오델로 보드
    int board_size_;                               // 오델로 보드 크기

    StateType state_;    // 현재 게임 상태
    UserType cur_user_;  // 현재 입력 차례

    ValidCoord coordinate_;  // 현재 입력된 좌표, 뒤집기할 목록

    // 유저가 해당 턴에 뒤집을 수 있는 수를 두었는지
    UserInputType user_o_state_;
    UserInputType user_x_state_;

    int turn_;         // 몇번 째 턴인지
    UserType winner_;  // 우승자 확인 (default = kUserNone)

    std::vector<ValidCoord>
        vec_valid_coordinate_;  // 현재 유저가 선택 가능한 좌표 목록
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_CONTEXT_H_
