#include "Success.h"

Success::Success()
{
    invalidate();
}

bool Success::test() const
{
    return isInvalid() || isTrue();
}

bool Success::expect(const bool is)
{
    if (is) Boolean::set(is);
    return test();
}
