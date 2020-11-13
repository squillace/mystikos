// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#ifndef _JSONSAMPLE_STRUCTS_H
#define _JSONSAMPLE_STRUCTS_H

#include <stdint.h>

#define TYPE_SIZE 32
#define SALT_SIZE 128
#define HASH_SIZE 32
#define ENCRYPTION_SIZE 128
#define NUM_KEYSLOTS 32
#define NUM_SEGMENTS 8
#define NUM_DIGESTS 8
#define NUM_CONFIGS 1
#define DIGEST_SIZE 128
#define MAX_NESTING 64

typedef struct luks2_keyslot
{
    char type[TYPE_SIZE];
    uint64_t key_size;
    struct
    {
        char type[TYPE_SIZE];
        char salt[SALT_SIZE];

        /* For type 'pbkdf2' */
        char hash[HASH_SIZE];
        uint64_t iterations;

        /* For type 'argon2i' or 'argon2id' */
        uint64_t time;
        uint64_t memory;
        uint64_t cpus;
    } kdf;
    struct
    {
        char type[TYPE_SIZE];
        char hash[HASH_SIZE];
        uint64_t stripes;
    } af;
    struct
    {
        char type[TYPE_SIZE];
        char encryption[ENCRYPTION_SIZE];
        uint64_t key_size;
        uint64_t offset;
        uint64_t size;
    } area;
} luks2_keyslot_t;

typedef struct luks2_segment
{
    /* only "crypt" supported */
    char type[TYPE_SIZE];

    /* offset in bytes */
    uint64_t offset;

    /* starting offset for the initialization vector */
    uint64_t iv_tweak;

    /* (uint64_t)-1 indicates dynamic */
    uint64_t size;

    /* example: "aes-xts-plain64" */
    char encryption[ENCRYPTION_SIZE];

    /* 512, 1024, 2048, 4096 */
    uint64_t sector_size;

    /* Data integrity type */
    struct
    {
        char type[TYPE_SIZE];
        char journal_encryption[ENCRYPTION_SIZE];
        char journal_integrity[TYPE_SIZE];
    } integrity;
} luks2_segment_t;

typedef struct luks2_digest
{
    /* Example: "pbkdf2" */
    char type[TYPE_SIZE];

    /* Keyslots that are used are non-zero in this array */
    uint8_t keyslots[NUM_KEYSLOTS];

    /* Segments that are used are non-zero in this array */
    uint8_t segments[NUM_SEGMENTS];

    /* Example: "sha256" */
    char hash[HASH_SIZE];

    uint64_t iterations;

    char salt[SALT_SIZE];

    uint8_t digest[DIGEST_SIZE];
} luks2_digest_t;

typedef struct luks2_config
{
    uint64_t json_size;
    uint64_t keyslots_size;
} luks2_config_t;

typedef struct _header
{
    luks2_keyslot_t keyslots[NUM_KEYSLOTS];
    luks2_segment_t segments[NUM_SEGMENTS];
    luks2_digest_t digests[NUM_DIGESTS];
    luks2_config_t config;
} header_t;

#endif /* _JSONSAMPLE_STRUCTS_H */
