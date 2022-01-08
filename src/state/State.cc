#include "State.h"

#include <iostream>

State::State(Context *context, StateType type)
    : context_(context), type_(type) {}

State::~State() {}
