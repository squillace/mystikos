// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include <errno.h>
#include <string.h>

#include <myst/eraise.h>
#include <myst/strings.h>
#include <myst/syscall.h>

int myst_path_absolute_cwd(
    const char* cwd,
    const char* path,
    char* buf,
    size_t size)
{
    int ret = 0;

    if (buf)
        *buf = '\0';

    if (!path || !buf || !size)
        ERAISE(-EINVAL);

    if (path[0] == '/')
    {
        if (myst_strlcpy(buf, path, size) >= size)
            ERAISE(-ENAMETOOLONG);
    }
    else
    {
        size_t cwd_len;

        if (myst_strlcpy(buf, cwd, size) >= size)
            ERAISE(-ENAMETOOLONG);

        if ((cwd_len = strlen(cwd)) == 0)
            ERAISE(-EINVAL);

        if (cwd[cwd_len - 1] != '/')
        {
            if (myst_strlcat(buf, "/", size) >= size)
                ERAISE(-ENAMETOOLONG);
        }

        if (myst_strlcat(buf, path, size) >= size)
            ERAISE(-ENAMETOOLONG);
    }

done:
    return ret;
}

int myst_path_absolute(const char* path, char* buf, size_t size)
{
    int ret = 0;

    if (buf)
        *buf = '\0';

    if (!path || !buf || !size)
        ERAISE(-EINVAL);

    if (path[0] == '/')
    {
        if (myst_strlcpy(buf, path, size) >= size)
            ERAISE(-ENAMETOOLONG);
    }
    else
    {
        long r;
        char cwd[PATH_MAX];

        if ((r = myst_syscall_getcwd(cwd, sizeof(cwd))) < 0)
            ERAISE((int)r);

        ERAISE(myst_path_absolute_cwd(cwd, path, buf, size));
    }

done:
    return ret;
}
