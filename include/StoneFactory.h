#ifndef LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STONEFACTORY_H_
#define LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STONEFACTORY_H_

#include "Stone.h"

/*
** Factory pattern
** Singleton pattern
*/

// stone 을 생산해주는 Factory class
class StoneFactory {
 public:
    static StoneFactory &GetInstance();

    // stone 동적할당
    Stone *CreateStone();

 private:
    /* data */
    ~StoneFactory();
    StoneFactory();
};

#endif  // LEC_2_OOP_TERMPROJECTVER01_INCLUDE_STONEFACTORY_H_
