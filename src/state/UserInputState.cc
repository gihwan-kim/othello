#include "UserInputState.h"

#include "Viewer.h"

UserInputState::UserInputState(Context *context)
    : State(context, kStateUserInput) {}

UserInputState::~UserInputState() {}

UserInputState &UserInputState::GetInstace(Context *context) {
    static UserInputState instance(context);
    return (instance);
}

// validation 항목
//     1. 입력한 좌표개수 : 2
//     2. 입력한 문자열이 숫자로만
//     3. 입력한 좌표의 범위는 0 ~ board_size-1
//     4. 가능한 목록과 일치하는게 있는 지 확인

// 좌표를 입력받고 유효성을 검사해 올바른 경우
// context에 좌표 저장 및 다음 상태로 이동
void UserInputState::Action() {
    Context *context = UserInputState::GetInstace(nullptr).context_;
    // prompt message
    const auto &valid_coord_list = context->vec_valid_coordinate();

    std::cout << "\nYou can choose one of theese Coordinate list.\n";
    for (int j = 0; j < valid_coord_list.size(); ++j) {
        std ::cout << "(" << valid_coord_list[j].x_ << ", "
                   << valid_coord_list[j].y_ << ")\n";
    }
    std::cout << "\n";
    std::cout << "TURN [" << context->turn() << "]  : ";
    std::cout << "Place your disk!!\tEx. \"(x, y)\" or \"x y\" or \"x, y\"\n";
    if (context->cur_user() == kUserO) {
        std::cout << "USER_O >> ";
    } else if (context->cur_user() == kUserX) {
        std::cout << "USER_X >> ";
    } else {
        // error
        return;
    }

    // 좌표 입력
    std::string command;
    getline(std::cin, command);
    std::vector<std::string> vec_cmd = UtilsSplit(command, "( ,)");

    /*
    **     [validation : 좌표 두개 입력 확인]
    */
    if (vec_cmd.size() != 2) {
        // error message
        std::cout << "[Invalid input] : wrong coordinate number!!\n";
        context->state(kStateUserInput);
        return;
    }

    /*
    **     [validation : 입력한 문자열은 숫자만]
    */
    for (auto &str : vec_cmd) {
        if (!UtilsStringIsNumber(str)) {
            // error message
            std::cout << "[Invalid input] : wrong coordinate format!!\n";
            context->state(kStateUserInput);
            return;
        }
    }

    // 유저가 입력한 좌표
    int coord_x = std::stoi(vec_cmd[0]);
    int coord_y = std::stoi(vec_cmd[1]);
    /*
    **     [validation : 유효한 좌표 범위( 0 ~ board_size-1) 확인]
    */
    if (0 > coord_x || context->board_size() <= coord_x || 0 > coord_y ||
        context->board_size() <= coord_y) {
        // error message
        std::cout << "[Invalid input] : wrong coordinate range!!\n";
        context->state(kStateUserInput);
        return;
    }

    /*
    **     [validation : 입력 가능한 좌표 목록 확인]
    */
    // 입력 가능한 좌표가 없다면 다음 상태로
    if (valid_coord_list.size() == 0) {
        std::cout << "[Change User] : No coordinate to input!!\n";
        // 현재 유저가 현재 턴에 아직 입력을 완료하지 않았다고 표시
        // 이후 WinerCheckState 에서 게임 종료상황인지 확인하기 위해 사용
        (context->cur_user() == kUserO)
            ? context->user_o_state(kUserInputInvalid)
            : context->user_x_state(kUserInputInvalid);
        context->state(kStateWinnercheck);
        return;
    }
    // 유저가 입력한 좌표가 가능한 목록에 있는지 확인
    bool is_valid = false;
    int idx = 0;
    for (; idx < valid_coord_list.size(); ++idx) {
        if (coord_x == valid_coord_list[idx].x_ &&
            coord_y == valid_coord_list[idx].y_) {
            is_valid = true;
            break;
        }
    }
    if (is_valid) {
        // context 에 현재 입력된 좌표 설정 및 다음 상태(뒤집기) 이동
        // 현재 유저가 입력을 완료했다고 표시
        (context->cur_user() == kUserO)
            ? context->user_o_state(kUserInputValid)
            : context->user_x_state(kUserInputValid);

        // 좌표 기록, 상태 변경
        context->coordinate(valid_coord_list[idx]);
        context->state(kStateUpdateBoard);
    } else {
        // 유저가 입력한 좌표가 입력 가능한 목록에 없음 : 다시 입력
        // error message
        std::cout << "[Invalid input] : Invalid coordinate!!\n";
        context->state(kStateUserInput);
    }
}
