#include "CoordCheckState.h"

/*
    8 방향 이동 {dx(row), dy(col)} 배열
    아래, 위, 왼쪽, 오른쪽, 왼위 대, 윈아 대, 오위 대, 오아 대
*/
std::array<std::array<int, 2>, 8> CoordCheckState::mover_ = {
    {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}}};

CoordCheckState::~CoordCheckState() {}

CoordCheckState::CoordCheckState(Context *context)
    : State(context, kStateUserInput) {}

CoordCheckState &CoordCheckState::GetInstace(Context *context) {
    static CoordCheckState instance(context);
    return (instance);
}

// 각 좌표가 입력 가능한 좌표인지 확인하고 구조체를 리턴
// 입력 불가능한 좌표인 경우 : 구조체의 toupdate_coord_ 멤버의 size() = 0
struct ValidCoord CoordCheckState::CalculateValidCoord(int x, int y) {
    // context 가져오기
    // Context *context = instance_->context_;
    Context *context = CoordCheckState::GetInstace(nullptr).context_;

    // 오델로 보드 가져오기 : 수정하면 안됨 (const)
    const auto &board = context->vec_board();

    // 갱신할 좌표 범위를 담은 벡터 : <mover_idx, <x, y>>
    struct ValidCoord cur_coord(x, y);

    // 좌표를 기준으로 8 방향으로 확인
    for (int mover_idx = 0; mover_idx < mover_.size(); ++mover_idx) {
        int cur_row = x;
        int cur_col = y;
        bool is_valid = false;  // 뒤집을 돌이 있는지 판단

        cur_row += mover_[mover_idx][0];
        cur_col += mover_[mover_idx][1];

        // 올바른 인덱스 범위이고 사용자의 돌과 동일한 돌을 만날 때까지 반복

        // 돌과 돌사이를 만나야함
        while (0 <= cur_row && cur_row < context->board_size() &&
               0 <= cur_col && cur_col < context->board_size() &&
               context->cur_user() != board[cur_row][cur_col]->owner()) {
            // 현재 위치의 돌의 주인
            auto cur_stone_owner = board[cur_row][cur_col]->owner();

            // 중간에 소유주 없는 돌 만날 경우 해당 방향은 유효하지 않음
            if (cur_stone_owner == kUserNone) {
                is_valid = false;
                break;
            }
            // 현재 유저와 다른 돌일때만
            if (cur_stone_owner != context->cur_user()) {
                is_valid = true;
            }
            cur_row += mover_[mover_idx][0];
            cur_col += mover_[mover_idx][1];
        }
        // 어디까지 뒤집을지 기록
        // 현재 위치, 뒤집을 범위의 끝이 소유주가 같아야한다.

        // 맨 끝에 올경우 안됨
        if (is_valid && 0 <= cur_row && cur_row < context->board_size() &&
            0 <= cur_col && cur_col < context->board_size() &&
            context->cur_user() == board[cur_row][cur_col]->owner()) {
            cur_coord.toupdate_coord_.push_back(
                std::make_pair(mover_idx, std::make_pair(cur_row, cur_col)));
        }
    }
    return (cur_coord);
}

// 현재 보드에서 유저가 뒤집을 곳이 있는지 확인
// 유저가 둘 수 있는 모든 좌표들을 계산
void CoordCheckState::Action() {
    // context 가져오기
    Context *context = CoordCheckState::GetInstace(nullptr).context_;

    // 시작전 보드 출력
    DisplayBoard(context->vec_board());
    // 오델로 보드 가져오기 : 수정하면 안됨 (const)
    const auto &board = context->vec_board();

    // 갱신할 좌표 범위를 담은 벡터 : <mover_idx, <x, y>>
    std::vector<ValidCoord> toupdate_coord(0);

    // 완전탐색으로 현재 유저가 입력가능한 좌표를 모두 계산
    // vec_possible_coord : 입력 가능한 좌표의 목록
    for (int x = 0; x < context->board_size(); ++x) {
        for (int y = 0; y < context->board_size(); ++y) {
            // 주인이 없는 돌만 확인
            if (board[x][y]->owner() == kUserNone) {
                struct ValidCoord cur_coord = CalculateValidCoord(x, y);
                if (cur_coord.toupdate_coord_.size() > 0) {
                    toupdate_coord.push_back(cur_coord);
                }
            }
        }
    }

    // 뒤집을 목록이 없다면 => kStateWinnercheck (승패 검사),
    // 현재 유저 상태 = 유효하지 않은 입력
    if (toupdate_coord.size() == 0) {
        std::cout << "[Change user] : there's no place to flip the stone!!\n";
        (context->cur_user() == kUserO)
            ? context->user_o_state(kUserInputInvalid)
            : context->user_x_state(kUserInputInvalid);
        context->state(kStateWinnercheck);
        return;
    } else {
        // 뒤집을 수 있는 돌이 있다면 => kStateWinnercheck (유저 입력)
        // 목록 교체
        context->vec_valid_coordinate(toupdate_coord);
        context->state(kStateUserInput);
        return;
    }
}
