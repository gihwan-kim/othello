#include "UpdateBoardState.h"
#include "Viewer.h"


/*
    8 방향 이동 {dx(row), dy(col)}
    아래, 위, 왼쪽, 오른쪽, 왼위 대, 윈아 대, 오위 대, 오아 대
*/
std::array<std::array<int, 2>, 8> UpdateBoardState::mover_ = {
    {{1, 0}, {-1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}}};

UpdateBoardState::UpdateBoardState(Context *context)
    : State(context, kStateUserInput) {}

UpdateBoardState::~UpdateBoardState() {}

UpdateBoardState &UpdateBoardState::GetInstace(Context *context) {
    static UpdateBoardState instance(context);
    return (instance);
}

// UserInputState 에서 결정된 좌표에서 뒤집을 수 있는 돌 뒤집기,
// 갱신된 board 출력
// context 의 toupdate_coordinate 에 기록된 좌표와 현재 입력된
// 좌표 사이의 돌을 뒤집어줍니다.
void UpdateBoardState::Action() {
    // context 가져오기
    Context *context = UpdateBoardState::GetInstace(nullptr).context_;

    // 오델로 보드
    // 보드 내용을 수정해야 하기 때문에 reference
    auto &board = context->vec_board();

    // 기준 좌표 (유저가 입력한 좌표)
    const auto &coordinate_data = context->coordinate();

    // 뒤집기 작업
    // 담긴 벡터 개수 만큼 반복
    for (const auto &toupdate : coordinate_data.toupdate_coord_) {
        // 방향 (mover_ 배열의 인덱스)
        const int direction = toupdate.first;

        // 어디까지 뒤집을지 : pair <x, y>
        const auto &destination = toupdate.second;

        int cur_row = coordinate_data.x_;
        int cur_col = coordinate_data.y_;

        // 현재 설정된 방향(direction) 으로 이동하며 뒤집기 진행
        while (cur_row != destination.first || cur_col != destination.second) {
            board[cur_row][cur_col]->owner(context->cur_user());
            cur_row += mover_[direction][0];
            cur_col += mover_[direction][1];
        }
    }
    // 승자 확인
    context->state(kStateWinnercheck);
}
