#pragma once

#include "types.h"

namespace sead {

template <typename T>
class BitFlag
{
public:
    BitFlag()
        : mBits(0)
    {
    }

    explicit BitFlag(T t)
        : mBits(t)
    {
    }

    operator T() const { return mBits; }

    void makeAllZero() { mBits = 0; }
    void makeAllOne() { mBits = T(-1); }

    void setDirect(T bits) { mBits = bits; }
    T getDirect() const { return mBits; }
    T* getPtr() { return &mBits; }
    const T* getPtr() const { return &mBits; }
    size_t getByteSize() const { return sizeof(T); }

    void set(T mask) { mBits |= mask; }
    void reset(T mask) { mBits &= ~mask; }
    void toggle(T mask) { mBits ^= mask; }
    void change(T mask, bool b) { b ? set(mask) : reset(mask); }

    bool isZero() const { return mBits == 0; }
    bool isOn(T mask) const { return (mBits & mask) != 0; }
    bool isOnAll(T mask) const { return (mBits & mask) == mask; }
    bool isOff(T mask) const { return !isOn(mask); }

    T getMask(T mask) const { return mBits & mask; }

    static T makeMask(s32 bit)
    {
        return T(1) << bit;
    }

    void setBit(s32 bit) { set(makeMask(bit)); }
    void resetBit(s32 bit) { reset(makeMask(bit)); }
    void changeBit(s32 bit, bool b) { change(makeMask(bit), b); }
    void toggleBit(s32 bit) { toggle(makeMask(bit)); }

    bool isOnBit(s32 bit) const { return isOn(makeMask(bit)); }
    bool isOffBit(s32 bit) const { return isOff(makeMask(bit)); }

    // s32 countOnBit() const;
    // inline s32 countContinuousOffBitFromRight() const;
    // s32 countRightOnBit(s32) const;
    // s32 findOnBitFromRight(s32) const;

protected:
    T mBits;
};

typedef BitFlag<u8> BitFlag8;
typedef BitFlag<u16> BitFlag16;
typedef BitFlag<u32> BitFlag32;

}
