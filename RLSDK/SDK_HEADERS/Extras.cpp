#include "Extras.hpp"

namespace TArrayUtils
{
    bool extendCapacity(void* inOldTArray, int32_t newCapacity, void* outNewTArray, int32_t elementSize)
    {
        if (inOldTArray == outNewTArray)
            throw std::logic_error("extendCapacity: input and output TArray pointers must not alias");

        auto*        oldArray    = reinterpret_cast<FArray_Mirror*>(inOldTArray);
        auto*        newArray    = reinterpret_cast<FArray_Mirror*>(outNewTArray);
        const size_t newByteSize = static_cast<size_t>(newCapacity) * elementSize;

        if (!oldArray || !newArray || elementSize == 0 || newCapacity <= 0 || newCapacity <= oldArray->ArrayMax)
            return false;


        const size_t requiredWChars = (newByteSize + 1) / sizeof(wchar_t);
        FString fstr = UObject::RepeatString(L"A", static_cast<int32_t>(requiredWChars));



        const size_t allocatedBytes = fstr.size() * sizeof(wchar_t);
        if (allocatedBytes < newByteSize)
            return false;


        void* newData = *reinterpret_cast<void**>(&fstr);
        ZeroMemory(newData, allocatedBytes);
        std::memcpy(newData,& oldArray->Data.Dummy, oldArray-> ArrayNum* elementSize);


        newArray->Data.Dummy     = *(uintptr_t*)newData;
        newArray->ArrayNum     = oldArray->ArrayNum;
        newArray->ArrayMax = newCapacity;


        *reinterpret_cast<void**>(&fstr) = nullptr;
        return true;
    }
}

