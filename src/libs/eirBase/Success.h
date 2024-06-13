//!file {Eclipse6}/root/src/libs/eirBase6/AText.h ASCII Text
#pragma once
#include "eirBase.h"

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

class EIRBASE_EXPORT Success : public Boolean
{
public: // ctors
    Success();  // invalid

public: // const
    bool test() const;


public: // non-const
    bool expect(const bool is);
};
