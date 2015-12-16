#include <ucos_ii.h>

#if OS_APP_HOOKS_EN > 0u
void  App_TaskCreateHook (OS_TCB *ptcb)
{
	(void)ptcb;
}
#endif

#if OS_APP_HOOKS_EN > 0u
void  App_TaskDelHook (OS_TCB *ptcb)
{
	(void)ptcb;
}
#endif

#if (OS_APP_HOOKS_EN > 0u) && (OS_TASK_SW_HOOK_EN > 0u)
void  App_TaskSwHook (void) {}
#endif

#if OS_APP_HOOKS_EN > 0u
void  App_TaskIdleHook (void) {}
#endif

#if OS_APP_HOOKS_EN > 0u
void  App_TaskStatHook (void) {}
#endif

#if (OS_APP_HOOKS_EN > 0u) && (OS_TIME_TICK_HOOK_EN > 0u)
void  App_TimeTickHook (void) {}
#endif

#if OS_APP_HOOKS_EN > 0u
void  App_TCBInitHook (OS_TCB *ptcb)
{
	(void)ptcb;
}
#endif

#if OS_APP_HOOKS_EN > 0u
void  App_TaskReturnHook (OS_TCB  *ptcb)
{
	(void)ptcb;
}
#endif