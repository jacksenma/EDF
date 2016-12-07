/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          APPLICATION CODE
*
*                                          Microsoft Windows
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JJL
*                 FGK
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/
//Õ»¿Õ¼ä
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK  TASK1[APP_TASK_START_STK_SIZE];
static  OS_STK  TASK2[APP_TASK_START_STK_SIZE];
static  OS_STK  TASK3[APP_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart(void  *p_arg);
static  void  task1(void  *p_arg);
static  void  task2(void  *p_arg);
static  void  task3(void  *p_arg);


/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main (void)
{
    OSInit();                                                   /* Init uC/OS-II.                                       */

	OSTaskCreate((void(*)(void *))task1,              /* Create the start task                                */
		(void          *)0,
		(OS_STK        *)&TASK1[APP_TASK_START_STK_SIZE - 1],
		(INT8U)1,
		(INT32U)1,
		(INT32U)3
		);

	OSTaskCreate((void(*)(void *))task2,              /* Create the start task                                */
		(void          *)0,
		(OS_STK        *)&TASK2[APP_TASK_START_STK_SIZE - 1],
		(INT8U)2,
		(INT32U)3,
		(INT32U)5
		);
//	OSTaskCreate((void(*)(void *))task3,              /* Create the start task                                */
//		(void          *)0,
//		(OS_STK        *)&TASK3[APP_TASK_START_STK_SIZE - 1],
//		(INT8U)3,
//		(INT32U)2,
//		(INT32U)10
//		);
		

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg       is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    OS_ERR  err;


   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();                                                 /* Initialize uC/CPU services                           */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    APP_TRACE_DBG(("uCOS-II is Running...\n\r"));

    while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0, 0, 1, 0);

        APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet(&err)));
    }
}


static  void  task1(void *p_arg)
{
	INT32U start;
	INT32U end;
	INT32U toDelay;
	INT32U cValue = 1;
	INT32U pValue = 3;
	start = 0;
	while (1) {
		while (OSTCBCur->compTime>0)
		{
			//do nothing
		}
		;
		
		end = OSTimeGet();
		toDelay = pValue - (end - start);
		start += pValue;
		OSTCBCur->compTime = cValue;
		OSTCBCur->ddl += pValue;	
		OSTimeDly(toDelay);
	}
}

static  void  task2(void *p_arg)
{
	INT32U start;
	INT32U end;
	INT32U toDelay;
	INT32U cValue = 3;
	INT32U pValue = 5;
	start = 0;
	//OSTCBCur->compTime =3;
	while (1) {
		//printf("t2ddl");
		//printf("%d", OSTCBCur->ddl);
		while (OSTCBCur->compTime>0)
		{
			//do nothing
			//APP_TRACE("T2: %d\n\r", &OSTCBCur->compTime);
			//printf("T2: %d\n\r", OSTCBCur->compTime);
		}
		//APP_TRACE_DBG(("task2##########################\n\r"));
		end = OSTimeGet();
		toDelay = pValue - (end - start);
		start += pValue;
		OSTCBCur->compTime = cValue;
		//printf("t2:%d", OSTCBCur->ddl);
		OSTCBCur->ddl += pValue;
		
		OSTimeDly(toDelay);
		

	}
}
/*
static  void  task3(void *p_arg)
{
	INT32U start;
	INT32U end;
	INT32U toDelay;
	INT32U cValue = 2;
	INT32U pValue = 10;
	start = 0;
	//OSTCBCur->compTime =3;
	while (1) {
		//printf("t2ddl");
		//printf("%d", OSTCBCur->ddl);
		while (OSTCBCur->compTime>0)
		{
			//do nothing
			//APP_TRACE("T2: %d\n\r", &OSTCBCur->compTime);
			//printf("T2: %d\n\r", OSTCBCur->compTime);
		}
		//APP_TRACE_DBG(("task2##########################\n\r"));
		end = OSTimeGet();
		toDelay = pValue - (end - start);
		start += pValue;
		OSTCBCur->compTime = cValue;
		//printf("t2:%d", OSTCBCur->ddl);
		OSTCBCur->ddl += pValue;

		OSTimeDly(toDelay);


	}
	
}
*/