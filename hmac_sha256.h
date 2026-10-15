

#ifndef _HMAC_SHA256_H_
#define _HMAC_SHA256_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "sha256.h"

size_t
hmac_sha256(


    const void* key,
    const size_t keylen,


    const void* data,
    const size_t datalen,




    void* out,
    const size_t outlen);

#ifdef __cplusplus
}
#endif

#endif
