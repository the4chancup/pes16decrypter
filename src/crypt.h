/*
    This is free and unencumbered software released into the public domain.

    Anyone is free to copy, modify, publish, use, compile, sell, or
    distribute this software, either in source code form or as a compiled
    binary, for any purpose, commercial or non-commercial, and by any
    means.

    In jurisdictions that recognize copyright laws, the author or authors
    of this software dedicate any and all copyright interest in the
    software to the public domain. We make this dedication for the benefit
    of the public at large and to the detriment of our heirs and
    successors. We intend this dedication to be an overt act of
    relinquishment in perpetuity of all present and future rights to this
    software under copyright law.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

    For more information, please refer to <http://unlicense.org>
 */

#ifndef _CRYPT_H
#define _CRYPT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32

#ifdef BUILDING_LIBRARY
#define CRYPTER_EXPORT __declspec(dllexport)
#else
#define CRYPTER_EXPORT __declspec(dllimport)
#endif

#else

#ifdef BUILDING_LIBRARY
#define CRYPTER_EXPORT __attribute__ ((visibility ("protected")))
#else
#define CRYPTER_EXPORT __attribute__ ((visibility ("default")))
#endif

#endif /* _WIN32 */

struct FileHeader
{
    uint8_t mysteryData[64];
    uint32_t dataSize;
    uint32_t logoSize;
    uint32_t descSize;
    uint32_t serialLength;
    uint8_t hash[64];
    uint8_t fileTypeString[32];
};

struct FileDescriptor
{
    uint8_t *encryptionHeader;
    struct FileHeader *fileHeader;
    
    uint8_t *description;
    uint8_t *logo;
    uint8_t *data;
    uint8_t *serial;
};

struct FileDescriptor CRYPTER_EXPORT *createFileDescriptor();
void CRYPTER_EXPORT destroyFileDescriptor(struct FileDescriptor *desc);

void CRYPTER_EXPORT decrypt(struct FileDescriptor *descriptor, const uint8_t *input);
uint8_t CRYPTER_EXPORT *encrypt(const struct FileDescriptor *descriptor, int *size);

void CRYPTER_EXPORT decrypt_ex(const char *pathIn, const char *pathOut);
void CRYPTER_EXPORT encrypt_ex(const char *pathIn, const char *pathOut);


#ifdef __cplusplus
}
#endif

#endif /* _CRYPT_H */