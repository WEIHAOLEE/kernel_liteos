/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "It_vfs_jffs.h"

static UINT32 Testcase(VOID)
{
    INT32 ret, len;
    INT32 fd = -1;
    CHAR pathname1[JFFS_STANDARD_NAME_LENGTH] = { JFFS_PATH_NAME0 };
    CHAR pathname2[JFFS_STANDARD_NAME_LENGTH] = "/jffs111";
    CHAR pathname3[JFFS_STANDARD_NAME_LENGTH] = "/jffs222";
    struct stat buf1 = { 0 };

    ret = umount(JFFS_MAIN_DIR0);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    ret = mount(JFFS_DEV_PATH0, JFFS_MAIN_DIR0, JFFS_FILESYS_TYPE, 0, NULL);
    ICUNIT_GOTO_EQUAL(ret, 0, ret, EXIT);

    ret = mount(JFFS_DEV_PATH0, pathname2, JFFS_FILESYS_TYPE, 0, NULL);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT2);

    ret = mount(JFFS_DEV_PATH0, pathname3, JFFS_FILESYS_TYPE, 0, NULL);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT1);

    ret = umount(pathname2);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT2);

    ret = umount(pathname3);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT1);

    ret = stat(pathname2, &buf1);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT);

    ret = stat(pathname3, &buf1);
    ICUNIT_GOTO_EQUAL(ret, -1, ret, EXIT);

    return JFFS_NO_ERROR;
EXIT2:
    umount(pathname2);
    goto EXIT;
EXIT1:
    remove(pathname3);
EXIT:
    mount(JFFS_DEV_PATH0, JFFS_MAIN_DIR0, JFFS_FILESYS_TYPE, 0, NULL);
    return LOS_NOK;
}

VOID ItFsJffs086(VOID)
{
    TEST_ADD_CASE("IT_FS_JFFS_086", Testcase, TEST_VFS, TEST_JFFS, TEST_LEVEL2, TEST_FUNCTION);
}
