#include "Context.h"

void Context::coordinate(ValidCoord coord) {
    this->coordinate_ = coord;
}

ValidCoord Context::coordinate() { return (this->coordinate_); }

void Context::Action() {
    State *cur_state = nullptr;
    switch (this->state_) {
        case kStateUserInput:
            // 유저 입력 상태
            cur_state = &UserInputState::GetInstace(this);
            break;
        case kStateCoordCheck:
            // 초기 상태
            cur_state = &CoordCheckState::GetInstace(this);
            break;
        case kStateUpdateBoard:
            // 뒤집기 상태
            cur_state = &UpdateBoardState::GetInstace(this);
            break;
        case kStateWinnercheck:
            // 승패 규칙 검사 상태
            cur_state = &WinnerCheckState::GetInstace(this);
            break;
        case kStateFinal:
            // 현재 사용자 차례 종료 상태
            cur_state = &FinalState::GetInstace(this);
            break;
        case kStateGameEnd:
            // 게임 종료 상태
            cur_state = &GameEndState::GetInstace(this);
            break;
        default:
            cur_state = nullptr;
            break;
    }
    // 각 상태의 Action 실행
    if (cur_state != nullptr) {
        cur_state->Action();
    }
}

// USR_X(흑) 부터 시작, kStateCoordCheck 부터 시작하도록
Context::Context(int board_size)
    : board_size_(board_size),
      state_(kStateCoordCheck),
      cur_user_(kUserX),
      turn_(1),
      winner_(kUserNone),
      user_o_state_(kUserInputNotYet),
      user_x_state_(kUserInputNotYet) {
    // create Board
    for (int row = 0; row < board_size; ++row) {
        vec_board_.push_back(std::vector<Stone *>(board_size));
        for (int col = 0; col < board_size; ++col) {
            vec_board_[row][col] = StoneFactory::GetInstance().CreateStone();
        }
    }
    // 2 x 2 넣기
    int start_col = (this->board_size_ - 1) / 2;
    int start_row = start_col;
    if (this->board_size_ % 2 == 1) {
        start_row--;
    }
    vec_board_[start_row][start_col]->owner(kUserO);
    vec_board_[start_row][start_col + 1]->owner(kUserX);
    vec_board_[start_row + 1][start_col]->owner(kUserX);
    vec_board_[start_row + 1][start_col + 1]->owner(kUserO);
}

/*
** getter, setter START
*/

void Context::state(StateType state) { this->state_ = state; }
StateType Context::state() { return (this->state_); }

void Context::board_size(int board_size) { this->board_size_ = board_size; }
int Context::board_size() { return (this->board_size_); }

void Context::cur_user(UserType user_type) { this->cur_user_ = user_type; }
UserType Context::cur_user() { return (this->cur_user_); }

std::vector<std::vector<Stone *>> &Context::vec_board() {
    return (this->vec_board_);
}

void Context::vec_valid_coordinate(
    std::vector<ValidCoord> toupdate_coordinate) {
    this->vec_valid_coordinate_ = toupdate_coordinate;
}

std::vector<ValidCoord>
Context::vec_valid_coordinate() {
    return (this->vec_valid_coordinate_);
}

UserInputType Context::user_o_state() { return (this->user_o_state_); }
void Context::user_o_state(UserInputType user_state_type) {
    this->user_o_state_ = user_state_type;
}

UserInputType Context::user_x_state() { return (this->user_x_state_); }
void Context::user_x_state(UserInputType user_state_type) {
    this->user_x_state_ = user_state_type;
}

UserType Context::winner() { return (this->winner_); }
void Context::winner(UserType user_type) { this->winner_ = user_type; }

int Context::turn() { return (this->turn_); }
void Context::turn(int turn) { this->turn_ = turn; }
/*
** getter, setter END
*/

/*
** 동적할당한 vec_board 벡터의 element 메모리들을 해제
*/
Context::~Context() {
    // 동적할당한 board 삭제
    for (int row = 0; row < this->board_size_; ++row) {
        for (int col = 0; col < this->board_size_; ++col) {
            delete vec_board_[row][col];
            vec_board_[row][col] = nullptr;
        }
    }
}
