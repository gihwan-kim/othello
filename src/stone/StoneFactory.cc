#include "StoneFactory.h"

#include <iostream>

StoneFactory::StoneFactory() {}

StoneFactory::~StoneFactory() {}

StoneFactory &StoneFactory::GetInstance() {
    static StoneFactory instance;
    return (instance);
}

Stone *StoneFactory::CreateStone() { return (new Stone()); }
