#include "ErrorCode.h"

BaseErrorCode::BaseErrorCode() : mUCode(0) {}
BaseErrorCode::BaseErrorCode(const unsigned int u) : mUCode(u) {;}
BaseErrorCode::BaseErrorCode(const Key key) : mKey(key) {;}
