/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"


/*======================================================================*
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq)
{
	disp_str("#");

	u32 code_base=(u32)task_table[p_proc_ready->pid].initial_eip;
	u32 code_limit=(u32)CS_SIZE;
	u32 data_base=(u32)p_proc_ready->p_task_stack;
	u32 data_limit=(u32)task_table[p_proc_ready->pid].stacksize;

	u32 code_segment_checksum = calculate_checksum(code_base, code_limit);
	u32 data_segment_checksum = calculate_checksum(data_base, data_limit);

	if (code_segment_checksum != p_proc_ready->code_segment_checksum)
	{
		disp_str("CS!\n");
	}
	if (data_segment_checksum != p_proc_ready->data_segment_checksum)
	{
		disp_str("DS!\n");
	}

	p_proc_ready++;
	if (p_proc_ready >= proc_table + NR_TASKS)
		p_proc_ready = proc_table;
}
