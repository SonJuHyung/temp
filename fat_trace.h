#undef TRACE_SYSTEM
#define TRACE_SYSTEM fat_log_lecture

#if !defined(_TRACE_FAT_LOG_LECTURE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_FAT_LOG_LECTURE_H

#include <linux/tracepoint.h>
#include <linux/types.h>
#include "fat.h"

#define FAT_YEAR_CRITERIA   0x7BC

#define FAT_YEAR_MASK       0xFE00
#define FAT_YEAR_SHIFT      0x9
#define FAT_MONTH_MASK      0x1E0
#define FAT_MONTH_SHIFT     0x5
#define FAT_DATE_MASK       0x1F
#define FAT_DATE_SHIFT      0

#define FAT_HOUR_MASK       0xF800
#define FAT_HOUR_SHIFT      0xB
#define FAT_MINUTE_MASK     0x7E0
#define FAT_MINUTE_SHIFT    FAT_MONTH_SHIFT
#define FAT_SECOND_MASK     FAT_DATE_MASK
#define FAT_SECOND_SHIFT    FAT_DATE_SHIFT

#define CALC_DT(raw, value) ((raw & FAT_##value##_MASK)>>FAT_##value##_SHIFT)

TRACE_EVENT(fat_ent_new_write,
	TP_PROTO(struct inode *inode, int new_cls, int wait),

	TP_ARGS(inode, new_cls, wait),

	TP_STRUCT__entry(
		__field(	unsigned long   , t_ino		    )
		__field(	int             , t_new		    )
		__field(	int             , t_wait		)
	),

	TP_fast_assign(
		__entry->t_ino	= inode->i_ino;
		__entry->t_new	= new_cls;
        __entry->t_wait = wait;
	),

	TP_printk("ino %lu , cluster : %d , wait : %d ", __entry->t_ino, __entry->t_new ,__entry->t_wait)
);

TRACE_EVENT(fat_log_check,
	TP_PROTO(struct inode *inode, struct fat_log_entry *log, sector_t blocknr, sector_t log_sectornr),

	TP_ARGS(inode, log, blocknr, log_sectornr),

	TP_STRUCT__entry(
		__field(	unsigned long   , t_ino		                )
        __array(    unsigned char   , t_log_name,   MSDOS_NAME  )         
        __field(    unsigned short  , t_log_year                )
        __field(    unsigned short  , t_log_month               )
        __field(    unsigned short  , t_log_date                )
        __field(    unsigned short  , t_log_hour                )
        __field(    unsigned short  , t_log_minute              )
        __field(    unsigned short  , t_log_seconds             )
		__field(	sector_t        , t_blocknr		            )
		__field(	sector_t        , t_sectornr	            )
	),

	TP_fast_assign(
		__entry->t_ino	= inode->i_ino;
        memcpy(__entry->t_log_name, log->name, MSDOS_NAME);
		__entry->t_log_year	= CALC_DT(log->date, YEAR) + FAT_YEAR_CRITERIA;
        __entry->t_log_month = CALC_DT(log->date, MONTH);
        __entry->t_log_date = CALC_DT(log->date, DATE);
        __entry->t_log_hour = CALC_DT(log->time, HOUR);
        __entry->t_log_minute = CALC_DT(log->time, MINUTE);
        __entry->t_log_seconds = CALC_DT(log->time, SECOND) * 2;
        __entry->t_blocknr = blocknr;
        __entry->t_sectornr = log_sectornr;
	),

	TP_printk("logged content[file name : %s, ino : %lu, date : %hu.%hu.%hu, time : %hu:%hu:%hu, blocknr : %lu, sectornr : %lu ", \
            __entry->t_log_name, __entry->t_ino, \
            __entry->t_log_year, __entry->t_log_month, __entry->t_log_date, \
            __entry->t_log_hour, __entry->t_log_minute, __entry->t_log_seconds, \
            __entry->t_blocknr, __entry->t_sectornr)
);

#endif /* _TRACE_FAT_LECTURE_H  */


#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE fat_trace
#include <trace/define_trace.h>



