//
//  Copyright (C) 2019 Microsoft.  All rights reserved.
//  See LICENSE file in the project root for full license information.
//
#pragma once

#include "Exceptions.hpp"
#include "StreamBase.hpp"
#include "Crypto.hpp"

namespace MSIX {
    // Hashes the data written to it; out stream only.
    class SHA256HashStream final : public StreamBase
    {
    public:
        SHA256HashStream() = default;

        HRESULT STDMETHODCALLTYPE Write(const void* buffer, ULONG countBytes, ULONG* bytesWritten) noexcept override try
        {
            m_hasher.Add(reinterpret_cast<const uint8_t*>(buffer), countBytes);
            if (bytesWritten)
            {
                *bytesWritten = countBytes;
            }
            return static_cast<HRESULT>(Error::OK);
        } CATCH_RETURN();

        SHA256::HashBuffer GetHash()
        {
            return m_hasher.Get();
        }

    private:
        SHA256 m_hasher;
    };
}