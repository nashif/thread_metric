/**************************************************************************/
/*                                                                        */
/*            Copyright (c) 1996-2016 by Express Logic Inc.               */
/*                                                                        */
/*  This Original Work may be modified, distributed, or otherwise used in */
/*  any manner with no obligations other than the following:              */
/*                                                                        */
/*    1. This legend must be retained in its entirety in any source code  */
/*       copies of this Work.                                             */
/*                                                                        */
/*    2. This software may not be used in the development of an operating */
/*       system product.                                                  */
/*                                                                        */
/*  This Original Work is hereby provided on an "AS IS" BASIS and WITHOUT */
/*  WARRANTY, either express or implied, including, without limitation,   */
/*  the warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A  */
/*  PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY OF this         */
/*  ORIGINAL WORK IS WITH the user.                                       */
/*                                                                        */
/*  Express Logic, Inc. reserves the right to modify this software        */
/*  without notice.                                                       */
/*                                                                        */
/*  Express Logic, Inc.                     info@expresslogic.com         */
/*  11423 West Bernardo Court               http://www.expresslogic.com   */
/*  San Diego, CA  92127                                                  */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** Thread-Metric Component                                               */
/**                                                                       */
/**   Porting Layer (Must be completed with RTOS specifics)               */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary files.  */

#include <zephyr.h>
#include "tm_api.h"

/* Thread has not yet started */
#define _THREAD_PRESTART (BIT(2))

#define N_THREADS 10
#define STACK_SIZE 512
#define TM_MAX_SEMAPHORES       1

static K_THREAD_STACK_ARRAY_DEFINE(stacks, N_THREADS, STACK_SIZE);
static struct k_thread threads[N_THREADS];
static struct k_sem semaphores[TM_MAX_SEMAPHORES];

/* This function called from main performs basic RTOS initialization,
   calls the test initialization function, and then starts the RTOS function.  */
void  tm_initialize(void (*test_initialization_function)(void))
{
  (test_initialization_function)();
}


/* This function takes a thread ID and priority and attempts to create the
   file in the underlying RTOS.  Valid priorities range from 1 through 31,
   where 1 is the highest priority and 31 is the lowest. If successful,
   the function should return TM_SUCCESS. Otherwise, TM_ERROR should be returned.   */
int  tm_thread_create(int thread_id, int priority, void (*entry_function)(void))
{
  k_thread_create(&threads[thread_id], stacks[thread_id], STACK_SIZE,
                (k_thread_entry_t)entry_function, NULL, NULL, NULL,
                K_PRIO_PREEMPT(priority), 0, K_FOREVER);

  return TM_SUCCESS;
}


/* This function resumes the specified thread.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_thread_resume(int thread_id)
{
  struct k_thread *thread;

  thread = &threads[thread_id];

  if (thread->base.thread_state & _THREAD_PRESTART)
  {
    k_thread_start(&threads[thread_id]);
  } else {
    k_thread_resume(&threads[thread_id]);
  }
  return TM_SUCCESS;
}


/* This function suspends the specified thread.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_thread_suspend(int thread_id)
{
  k_thread_suspend(&threads[thread_id]);
  return TM_SUCCESS;
}


/* This function relinquishes to other ready threads at the same
   priority.  */
void tm_thread_relinquish(void)
{
  k_yield();
}


/* This function suspends the specified thread for the specified number
   of seconds.  If successful, the function should return TM_SUCCESS.
   Otherwise, TM_ERROR should be returned.  */
void tm_thread_sleep(int seconds)
{
  k_sleep(K_SECONDS(seconds));
}


/* This function creates the specified queue.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_queue_create(int queue_id)
{
  return TM_SUCCESS;
}


/* This function sends a 16-byte message to the specified queue.  If successful,
   the function should return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_queue_send(int queue_id, unsigned long *message_ptr)
{
  return TM_SUCCESS;
}


/* This function receives a 16-byte message from the specified queue.  If successful,
   the function should return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_queue_receive(int queue_id, unsigned long *message_ptr)
{
  return TM_SUCCESS;
}


/* This function creates the specified semaphore.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_semaphore_create(int semaphore_id)
{
  k_sem_init(&semaphores[semaphore_id], 1, 1);
  return TM_SUCCESS;
}


/* This function gets the specified semaphore.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_semaphore_get(int semaphore_id)
{
  k_sem_take(&semaphores[semaphore_id], K_NO_WAIT);
  return TM_SUCCESS;
}


/* This function puts the specified semaphore.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_semaphore_put(int semaphore_id)
{
  k_sem_give(&semaphores[semaphore_id]);
  return TM_SUCCESS;
}


/* This function creates the specified memory pool that can support one or more
   allocations of 128 bytes.  If successful, the function should
   return TM_SUCCESS. Otherwise, TM_ERROR should be returned.  */
int  tm_memory_pool_create(int pool_id)
{
  return TM_SUCCESS;
}


/* This function allocates a 128 byte block from the specified memory pool.
   If successful, the function should return TM_SUCCESS. Otherwise, TM_ERROR
   should be returned.  */
int  tm_memory_pool_allocate(int pool_id, unsigned char **memory_ptr)
{
  return TM_SUCCESS;
}


/* This function releases a previously allocated 128 byte block from the specified
   memory pool. If successful, the function should return TM_SUCCESS. Otherwise, TM_ERROR
   should be returned.  */
int  tm_memory_pool_deallocate(int pool_id, unsigned char *memory_ptr)
{
  return TM_SUCCESS;
}
