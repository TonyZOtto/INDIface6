//!file {Eclipse6}/root/src/libs/eirBase6/Boolean.h Tri-value bool
#pragma once
#include "eirBase.h"

class EIRBASE_EXPORT Boolean
{
/*
 *      Result:     mValue  mValid
 *                  false   false       null
 *                  true    false       invalid
 *                  false   true        false
 *                  true    true        true
 */
public:
    Boolean() { nullify(); }
    Boolean(const bool is) { set(is); }

public: // const
    bool value() const;
    bool valid() const;
    bool is(const bool b) const;
    bool isTrue() const;
    bool notTrue() const;
    bool isNull() const;
    bool notNull() const;
    bool isInvalid() const;
    bool notInvalid() const;


public: // non-const
    void value(const bool vue);
    void valid(const bool vid);
    void set(const bool is=true);
    void reset();
    void nullify();
    void invalidate();

private:
    bool mValue=false;
    bool mValid=false;
};

inline bool Boolean::value() const
{
    return mValue;
}

inline bool Boolean::valid() const
{
    return mValid;
}

inline void Boolean::value(const bool vue)
{
    mValue = vue;
}

inline void Boolean::valid(const bool vid)
{
    mValid = vid;
}
