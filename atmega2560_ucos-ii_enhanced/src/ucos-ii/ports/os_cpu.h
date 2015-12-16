#ifndef  OS_CPU_H
#define  OS_CPU_H

#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

#ifdef __cplusplus
extern  "C" {
#endif

/*******************************************************************************************************/

typedef unsigned char	BOOLEAN;
typedef unsigned char	INT8U;
typedef signed char		INT8S;
typedef unsigned int	INT16U;
typedef signed int		INT16S;
typedef unsigned long	INT32U;
typedef signed long		INT32S;
typedef float			FP32;
typedef double			FP64;

typedef INT8U			OS_STK;
typedef INT8U			OS_CPU_SR;

/*******************************************************************************************************/

#define OS_CRITICAL_METHOD	3

#define OS_ENTER_CRITICAL()	cpu_sr = CPUGetSR()
#define OS_EXIT_CRITICAL()	CPUSetSR(cpu_sr)

OS_CPU_SR CPUGetSR(void);
void CPUSetSR(OS_CPU_SR  cpu_sr);

/*******************************************************************************************************/

#define OS_STK_GROWTH	1

/*******************************************************************************************************/

#define OS_TASK_SW()	OSCtxSw()
#define OSIntCtxSw()	OSCtxSw()

/*******************************************************************************************************/

void OSStartHighRdy(void);
void OSCtxSw(void);

/*******************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
