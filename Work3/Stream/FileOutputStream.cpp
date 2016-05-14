#include "FileOutputStream.h"

namespace lab
{
    namespace stream
    {
        FileOutputStream::FileOutputStream(const vaca::String &path)
        {
            open(path,Mode::Disposition::CreateAlways,Mode::Access::Write);
        }

        // ------------------------------------------------------------------
       bool FileOutputStream::writeByte( const types::byte_t&  bValue)
        {
            unsigned long dwNumRead = 0;
            size_t sizeByte = sizeof(types::byte_t);
            WriteFile(m_handle, &bValue, sizeByte, &dwNumRead, nullptr);
            return dwNumRead == sizeByte;
        };

        // ------------------------------------------------------------------
       size_t FileOutputStream::writeByte(const types::byte_t& bValue, size_t nCount)
        {
            size_t nNumWritten = 0;
            while (nNumWritten < nCount)
            {
                if (!writeByte(bValue))
                    break;
                ++nNumWritten;
            }
            return nNumWritten;
        };

        // ------------------------------------------------------------------
        size_t FileOutputStream::writeBytes(const types::byte_t* arrBytes, size_t nCount)
        {
            size_t nNumWritten = 0;
            while (nNumWritten < nCount)
            {
                if (! writeByte(arrBytes[nNumWritten]))
                    break;
                ++nNumWritten;
            }
            return nNumWritten;
        };
    }
}

