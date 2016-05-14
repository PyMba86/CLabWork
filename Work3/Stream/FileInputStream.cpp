
#include "FileInputStream.h"

namespace lab
{
    namespace stream
    {
        FileInputStream::FileInputStream(const vaca::String &path)
        {
            open(path,Mode::Disposition::OpenExisting,Mode::Access::Read);
        }

        bool FileInputStream::readByte(types::byte_t &bValue) {
            unsigned long dwNumRead = 0;
            size_t sizeByte = sizeof(types::byte_t);
            ReadFile(m_handle, &bValue, sizeByte, &dwNumRead, nullptr);
            return dwNumRead == sizeByte;
        }

        size_t FileInputStream::readBytes(types::byte_t *arrBytes, size_t count) {
            size_t numRead = 0;
            while (numRead < count) {
                if (!readByte(arrBytes[numRead]))
                    break;
                ++numRead;
            }
            return numRead;
        }
    }
}


