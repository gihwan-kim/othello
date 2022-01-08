#include "Stone.h"

Stone::Stone() : owner_(kUserNone) {}
Stone::Stone(UserType owner) : owner_(owner) {}

void Stone::owner(UserType owner) { this->owner_ = owner; }
UserType Stone::owner() { return (this->owner_); }

Stone::~Stone() {}
