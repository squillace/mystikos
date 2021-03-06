// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include <openenclave/host.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "run_u.h"

int main(int argc, const char* argv[])
{
    oe_result_t r;
    oe_enclave_t* enclave = NULL;
    const oe_enclave_type_t type = OE_ENCLAVE_TYPE_SGX;
    const uint32_t flags = OE_ENCLAVE_FLAG_DEBUG;
    int retval;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s ENCLAVE_PATH\n", argv[0]);
        return 1;
    }

    r = oe_create_run_enclave(argv[1], type, flags, NULL, 0, &enclave);
    if (r != OE_OK)
    {
        fprintf(stderr, "%s: oe_create_echo_enclave(): %u\n", argv[0], r);
        exit(1);
    }

    r = run_ecall(enclave, &retval);
    if (r != OE_OK)
    {
        fprintf(stderr, "%s: echo_ecall(): %u\n", argv[0], r);
        exit(1);
    }

    if (retval != 0)
    {
        fprintf(stderr, "%s: bad retval=%d\n", argv[0], retval);
        exit(1);
    }

    r = oe_terminate_enclave(enclave);
    if (r != OE_OK)
    {
        fprintf(stderr, "%s: oe_terminate_enclave(): %u\n", argv[0], r);
        exit(1);
    }

    printf("=== passed test (%s)\n", argv[1]);

    return 0;
}
