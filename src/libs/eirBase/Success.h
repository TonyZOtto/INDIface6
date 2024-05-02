#pragma once

#include "Boolean.h"

/* Use Case
 *
 *  bool doThings()
 *  {
 *      Success success;
 *      if (success.test())     success.expect(doThing1());
 *      if (success.test())     success.expect(doThing2());
 *      if (success.test())     success.expect(doThing3());
 *      return success;
 *  }
 *
 */

class Success : public Boolean
{
public: // ctors
    Success();  // invalid

public: // const
    bool test() const;


public: // non-const
    bool expect(const bool is);
};
