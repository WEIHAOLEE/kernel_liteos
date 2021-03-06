/*
 * Copyright (c) 2013-2019 Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
#include "It_posix_pthread.h"

static VOID *pthread_f01(VOID *data)
{
    pthread_t self;
    struct sched_param schedparam;
    struct params *paramTest = (struct params *)data;
    INT32 policy;
    INT32 ret;

    self = pthread_self();
    ret = pthread_getschedparam(self, &policy, &schedparam);
    ICUNIT_TRACK_EQUAL(ret, PTHREAD_NO_ERROR, ret);
    ICUNIT_TRACK_EQUAL(policy, SCHED_FIFO, policy);
    ICUNIT_TRACK_EQUAL(paramTest->priority, PRIORITY_FIFO, paramTest->priority);
    ICUNIT_TRACK_EQUAL(schedparam.sched_priority, paramTest->priority, schedparam.sched_priority);

    return NULL;
}

static UINT32 Testcase(VOID)
{
    INT32 ret;
    struct params paramTest;
    pthread_t thread;
    pthread_attr_t attr;
    VOID *status;
    struct sched_param schedparam;

    paramTest.policy = SCHED_FIFO;
    paramTest.priority = PRIORITY_FIFO;
    paramTest.policy_label = "SCHED_FIFO";
    paramTest.status = LOS_NOK;

    ret = pthread_attr_init(&attr);
    ICUNIT_ASSERT_EQUAL(ret, PTHREAD_NO_ERROR, ret);

    g_pthreadSchedPolicy = SCHED_FIFO;
    ret = pthread_attr_setschedpolicy(&attr, g_pthreadSchedPolicy);
    ICUNIT_ASSERT_EQUAL(ret, 0, ret);

    g_pthreadSchedInherit = PTHREAD_EXPLICIT_SCHED;
    ret = pthread_attr_setinheritsched(&attr, g_pthreadSchedInherit);
    ICUNIT_ASSERT_EQUAL(ret, PTHREAD_NO_ERROR, ret);

    schedparam.sched_priority = paramTest.priority;
    ret = pthread_attr_setschedparam(&attr, &schedparam);
    ICUNIT_ASSERT_EQUAL(ret, PTHREAD_NO_ERROR, ret);

    ret = pthread_create(&thread, &attr, pthread_f01, &paramTest);
    ICUNIT_ASSERT_EQUAL(ret, PTHREAD_NO_ERROR, ret);

    ret = pthread_join(thread, &status);
    ICUNIT_ASSERT_EQUAL(ret, PTHREAD_NO_ERROR, ret);

    ret = pthread_attr_destroy(&attr);
    ICUNIT_ASSERT_EQUAL(ret, PTHREAD_NO_ERROR, ret);

    return PTHREAD_NO_ERROR;
}


VOID ItPosixPthread187(VOID)
{
    TEST_ADD_CASE("IT_POSIX_PTHREAD_187", Testcase, TEST_POSIX, TEST_PTHREAD, TEST_LEVEL2, TEST_FUNCTION);
}
