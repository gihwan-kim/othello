#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STONE_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STONE_H_

#include <string>

#include "Utils.h"

// 오델로 돌
class Stone {
 public:
    Stone();
    explicit Stone(UserType);
    void owner(UserType);
    UserType owner();
    ~Stone();

 private:
    /* data */
    UserType owner_;  // 해당 돌의 소유주
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STONE_H_
