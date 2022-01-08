#include <iostream>
#include "gtest/gtest.h"
#include "Utils.h"
#include "Context.h"

Context context(4);

TEST(TestForStart, CheckBoardSize) {
    /* 보드 사이즈 맞게 할당 되었는지 확인 */
    EXPECT_EQ(context.board_size(), 4);
}
TEST(TestForStart, kStateCoordCheck) {
    /* 초기 상태는 StateCoordCheck 부터 시작*/
    EXPECT_EQ(context.state(), kStateCoordCheck);
}
TEST(TestForStart, CheckStateChange) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    context.state(kStateCoordCheck);
    /*현재 상태가 kStateCoordCheck로 정확하게 바뀌었는지 확인 */
    EXPECT_EQ(context.state(), kStateCoordCheck);
    context.Action();
    /* kStateCoordCheck에서 Action 동작 이후에는 kStateUserInput으로 돌아간다.*/
    EXPECT_EQ(context.state(), kStateUserInput);
    std::cout.rdbuf(rbuf);
}

TEST(TestForUserInput, CheckBeforeUserInput) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    /* 첫 번째는 UserX(흑) 부터 시작하게 세팅되어있음 */
    EXPECT_EQ(context.cur_user(), kUserX);
    /* 아직 입력하지 않은 상태이므로 user state는 not yet*/
    EXPECT_EQ(context.user_x_state(), kUserInputNotYet);
    /* 현재 선택할 수 있는 곳이 0이 아니므로 */
    EXPECT_EQ((context.vec_valid_coordinate().size() == 0) , false);
    std::cout.rdbuf(rbuf);
}

TEST(TestForUserInput, CkeckInputCountValidation) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    /* 입력 처리용 코드*/
    std::stringstream buffer;
    buffer << "0";
    std::streambuf *sbuf = std::cin.rdbuf();
    std::cin.rdbuf(buffer.rdbuf());
    context.Action();
    /* 숫자 하나만 입력됐으므로 다시 input 받는 상태로 돌아간다. */
    EXPECT_EQ(context.state(), kStateUserInput);
    std::cin.rdbuf(sbuf);
    std::cout.rdbuf(rbuf);
}

TEST(TestForUserInput, CkeckInputIntegerValidation) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    std::stringstream buffer;
    buffer << "abce efg";
    std::streambuf *sbuf = std::cin.rdbuf();
    std::cin.rdbuf(buffer.rdbuf());
    context.Action();
    /* 문자열이 입력됐으므로 다시 input 받는 상태로 돌아간다. */
    EXPECT_EQ(context.state(), kStateUserInput);
    std::cin.rdbuf(sbuf);
    std::cout.rdbuf(rbuf);
}

TEST(TestForUserInput, CkeckInputRangeValidation) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    std::stringstream buffer;
    buffer << "5 5";
    std::streambuf *sbuf = std::cin.rdbuf();
    std::cin.rdbuf(buffer.rdbuf());
    context.Action();
    /* 보드의 범위를 넘어가는 입력을 받았으므로 다시 input으로 돌아간다. */
    EXPECT_EQ(context.state(), kStateUserInput);
    std::cin.rdbuf(sbuf);
    std::cout.rdbuf(rbuf);
}

TEST(TestForUserInput, CkeckMoveToUpdate) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    std::stringstream buffer;
    buffer << "1 0";
    std::streambuf *sbuf = std::cin.rdbuf();
    std::cin.rdbuf(buffer.rdbuf());
    context.Action();
    /* 정상 좌표 입력 이후에는 돌을 뒤집고 보드를 업데이트 하는 상태로 간다. */
    EXPECT_EQ(context.state(), kStateUpdateBoard);
    std::cin.rdbuf(sbuf);
    std::cout.rdbuf(rbuf);
}

TEST(TestForAfterInput, CheckStatesChange) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    context.Action();
    /* 보드 상태 업데이트 이후 Action을 호출하면 승자 체크 상태로 간다 */
    EXPECT_EQ(context.state(), kStateWinnercheck);

    context.Action();
    /* 승패 체크 이후에 final state로 간다. */
    EXPECT_EQ(context.state(), kStateFinal);

    context.Action();
		/* final state에서 확인했을 때 두 유저 중 User O(백)가 입력을
		*  아직 하지 않았으므로 차례를 변경하고(cur_user를 kUserX로)
		*  초기상태(kStateCoordCheck)로 돌아간다.
		*/
    EXPECT_EQ(context.state(), kStateCoordCheck);
    std::cout.rdbuf(rbuf);
}

TEST(TestForCoordState, CheckChangeAndUserChange) {
    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    context.Action();
    /* user가 kUserX에서 kUserO로 바뀌었는지 확인 */
    EXPECT_EQ(context.state(), kStateUserInput);
    EXPECT_EQ(context.cur_user(), kUserO);
    EXPECT_EQ(context.user_o_state(), kUserInputNotYet);
    EXPECT_EQ(context.vec_valid_coordinate().size() , 3);
    std::cout.rdbuf(rbuf);
}

TEST(TestContinue, TestUntilGameEnd) {
    /* 사용자 입력을 대체하는 코드 */
    std::stringstream buffer;
    buffer << "2 0\n3 3\n0 0\n3 0\n2 3\n3 2\n0 3\n1 3\n0 2";
    std::streambuf *sbuf = std::cin.rdbuf();
    std::cin.rdbuf(buffer.rdbuf());

    std::stringstream tmp;
    std::streambuf *rbuf = std::cout.rdbuf();
    std::cout.rdbuf(tmp.rdbuf());
    /* main문의 코드와 일치 => 게임을 마지막까지 진행시킨다. */
    context.Action();
    EXPECT_EQ(context.state(), kStateUpdateBoard);

    while (context.state() != kStateGameEnd) {
        context.Action();
    }
    /* 게임을 종료할 때의 상태는 kStateGameEnd */
    EXPECT_EQ(context.state(), kStateGameEnd);
    std::cin.rdbuf(sbuf);
    context.Action();
    /* Test에서 사용한 입력을 기준으로 결과는 TIE임을 확인한다. */
    EXPECT_EQ(context.winner(), kUserTie);
    std::cout.rdbuf(rbuf);
}
