#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define STAT_START 0
#define STAT_END 1

typedef struct {
    char name[256];
    long long user; // Time spent in user mode.
    long long nice; // Time spent in user mode with low priority (nice).
    long long system; // Time spent in system mode.
    long long idle; // Time spent in the idle task.
    long long iowait; // Time waiting for I/O to complete.
    long long irq; // Time servicing interrupts.
    long long softirq; // Time servicing softirqs.
    long long steal; // Stolen time, which is the time spent in other operating systems when running in a virtualized environment.
    long long guest; // Time spent running a virtual CPU for guest operating systems under the control of the Linux kernel.
    long long guest_nice; //  Time spent running a niced guest (virtual CPU for guest operating systems under the control of the Linux kernel).
} _stat_t;

typedef struct {
    int pid;
    char comm[16];
    char state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    unsigned int flags;
    unsigned long minflt;
    unsigned long cminflt;
    unsigned long majflt;
    unsigned long cmajflt;
    unsigned long utime;
    unsigned long stime;
    long int cutime;
    long int cstime;
    long int pirority;
    long int nice;
    long int num_threads;
    long int itrealvalue;
    unsigned long long starttime;
    unsigned long vsize;
    long int rss;
    unsigned long rsslim;
    unsigned long startcode;
    unsigned long endcode;
    unsigned long startstack;
    unsigned long kstkesp;
    unsigned long kstkeip;
    unsigned long signal;
    unsigned long blocked;
    unsigned long sigignore;
    unsigned long sigcatch;
    unsigned long wchan;
    unsigned long nswap;
    unsigned long cnswap;
    int exit_signal;
    int processor;
    unsigned int rt_priority;
    unsigned int policy;
    unsigned long long delayacct_blkio_ticks;
    unsigned long guest_time;
    long int cguest_time;
    unsigned long start_data;
    unsigned long end_data;
    unsigned long start_brk;
    unsigned long arg_start;
    unsigned long arg_end;
    unsigned long env_start;
    unsigned long env_end;
    int exit_code;
} _pstat_t;

typedef struct {
    char s_path[256];
    char ps_path[256];
    FILE *s_fp;
    FILE *ps_fp;
    _stat_t s[2];
    _pstat_t ps[2];
} stat_t;

static void load__stat(_stat_t *s, FILE *fp)
{
    fscanf(fp, "%s %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
            s->name, &s->user, &s->nice, &s->system, &s->idle, &s->iowait, &s->irq, &s->softirq, &s->steal, &s->guest, &s->guest_nice);
}

static void load__pstat(_pstat_t *ps, FILE *fp)
{
    fscanf(fp, "%d %s %c %d %d %d %d %d %u %lu"
            "%lu %lu %lu %lu %lu %ld %ld %ld %ld %ld"
            "%ld %llu %lu %ld %lu %lu %lu %lu %lu %lu"
            "%lu %lu %lu %lu %lu %lu %lu %d %d %u"
            "%u %llu %lu %ld %lu %lu %lu %lu %lu %lu"
            "%lu %d",
            &ps->pid, ps->comm, &ps->state, &ps->ppid, &ps->pgrp, &ps->session, &ps->tty_nr, &ps->tpgid, &ps->flags, &ps->minflt, &ps->cminflt,
            &ps->majflt, &ps->cmajflt, &ps->utime, &ps->stime, &ps->cutime, &ps->cstime, &ps->pirority, &ps->nice, &ps->num_threads, &ps->itrealvalue,
            &ps->starttime, &ps->vsize, &ps->rss, &ps->rsslim, &ps->startcode, &ps->endcode, &ps->startstack, &ps->kstkesp, &ps->kstkeip, &ps->signal,
            &ps->blocked, &ps->sigignore, &ps->sigcatch, &ps->wchan, &ps->nswap, &ps->cnswap, &ps->exit_signal, &ps->processor, &ps->rt_priority, &ps->policy,
            &ps->delayacct_blkio_ticks, &ps->guest_time, &ps->cguest_time, &ps->start_data, &ps->end_data, &ps->start_brk, &ps->arg_start, &ps->arg_end,
            &ps->env_start, &ps->env_end, &ps->exit_code);
}

static void print__stat(_stat_t *s)
{
    printf("\n"
           "0.  name       = %s\n"
           "1.  user       = %lld\n"
           "2.  nice       = %lld\n"
           "3.  system     = %lld\n"
           "4.  idle       = %lld\n"
           "5.  iowait     = %lld\n"
           "6.  irq        = %lld\n"
           "7.  softirq    = %lld\n"
           "8.  steal      = %lld\n"
           "9.  guest      = %lld\n"
           "10. guest_nice = %lld\n",
           s->name, s->user, s->nice, s->system, s->idle, s->iowait, s->irq, s->softirq, s->steal, s->guest, s->guest_nice);
}

static void print__pstat(_pstat_t *ps)
{
    printf( "\n"
            "1.  pid                   = %d\n"
            "2.  comm                  = %s\n"
            "3.  state                 = %c\n"
            "4.  ppid                  = %d\n"
            "5.  pgrp                  = %d\n"
            "6.  session               = %d\n"
            "7.  tty_nr                = %d\n"
            "8.  tpgid                 = %d\n"
            "9.  flags                 = %u\n"
            "10. minflt                = %lu\n"
            "11. cminflt               = %lu\n"
            "12. majflt                = %lu\n"
            "13. cmajflt               = %lu\n"
            "14. utime                 = %lu\n"
            "15. stime                 = %lu\n"
            "16. cutime                = %ld\n"
            "17. cstime                = %ld\n"
            "18. pirority              = %ld\n"
            "19. nice                  = %ld\n"
            "20. num_threads           = %ld\n"
            "21. itrealvalue           = %ld\n"
            "22. starttime             = %llu\n"
            "23. vsize                 = %lu\n"
            "24. rss                   = %ld\n"
            "25. rsslim                = %lu\n"
            "26. startcode             = %lu\n"
            "27. endcode               = %lu\n"
            "28. startstack            = %lu\n"
            "29. kstkesp               = %lu\n"
            "30. kstkeip               = %lu\n"
            "31. signal                = %lu\n"
            "32. blocked               = %lu\n"
            "33. sigignore             = %lu\n"
            "34. sigcatch              = %lu\n"
            "35. wchan                 = %lu\n"
            "36. nswap                 = %lu\n"
            "37. cnswap                = %lu\n"
            "38. exit_signal           = %d\n"
            "39. processor             = %d\n"
            "40. rt_priority           = %u\n"
            "41. policy                = %u\n"
            "42. delayacct_blkio_ticks = %llu\n"
            "43. guest_time            = %ld\n"
            "44. cguest_time           = %lu\n"
            "45. start_data            = %lu\n"
            "46. end_data              = %lu\n"
            "47. start_brk             = %lu\n"
            "48. arg_start             = %lu\n"
            "49. arg_end               = %lu\n"
            "50. env_start             = %lu\n"
            "51. env_end               = %lu\n"
            "52. exit_code             = %d\n",
            ps->pid, ps->comm, ps->state, ps->ppid, ps->pgrp, ps->session, ps->tty_nr, ps->tpgid, ps->flags, ps->minflt, ps->cminflt,
            ps->majflt, ps->cmajflt, ps->utime, ps->stime, ps->cutime, ps->cstime, ps->pirority, ps->nice, ps->num_threads, ps->itrealvalue,
            ps->starttime, ps->vsize, ps->rss, ps->rsslim, ps->startcode, ps->endcode, ps->startstack, ps->kstkesp, ps->kstkeip, ps->signal,
            ps->blocked, ps->sigignore, ps->sigcatch, ps->wchan, ps->nswap, ps->cnswap, ps->exit_signal, ps->processor, ps->rt_priority, ps->policy,
            ps->delayacct_blkio_ticks, ps->guest_time, ps->cguest_time, ps->start_data, ps->end_data, ps->start_brk, ps->arg_start, ps->arg_end,
            ps->env_start, ps->env_end, ps->exit_code);

}

static inline long long get_total_cpu_usage(_stat_t *stat)
{
    return stat->user + stat->nice + stat->system + stat->idle;
}

static inline long long get_proc_time(_pstat_t *stat)
{
    return stat->utime + stat->stime;
}

static void print_cpu_stat(stat_t *stat, int cpu)
{
    FILE *s_fp = fopen(stat->s_path, "r");
    cpu++;
    do {
        load__stat(&stat->s[0], s_fp);
    } while (cpu--);
    print__stat(&stat->s[0]);
    fclose(s_fp);
}

static void print_pid_stat(stat_t *stat)
{
    FILE *ps_fp = fopen(stat->ps_path, "r");
    load__pstat(&stat->ps[0], ps_fp);
    print__pstat(&stat->ps[0]);
    fclose(ps_fp);
}

void init_stat(stat_t *stat)
{
    char pfile[256];
    pid_t pid = getpid();
    strcpy(stat->s_path, "/proc/stat");
    sprintf(stat->ps_path, "/proc/%d/stat", pid);
}

void load_stat(stat_t *stat, int offset)
{
    FILE *s_fp = fopen(stat->s_path, "r");
    FILE *ps_fp = fopen(stat->ps_path, "r");
    if (offset < 0 || offset > 1) return;
    load__stat(&stat->s[offset], s_fp);
    load__pstat(&stat->ps[offset], ps_fp);
    fclose(s_fp);
    fclose(ps_fp);
}

// https://newbedev.com/how-to-calculate-the-cpu-usage-of-a-process-by-pid-in-linux-from-c
float cpu_usage(stat_t *stat)
{
    long long total_cpu_usage1 = get_total_cpu_usage(&stat->s[STAT_START]);
    long long total_cpu_usage2 = get_total_cpu_usage(&stat->s[STAT_END]);
    long long proc_times1 = get_proc_time(&stat->ps[STAT_START]);
    long long proc_times2 = get_proc_time(&stat->ps[STAT_END]);
    long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
    printf("cpu_usage: %lld, %lld, %lld, %lld, %ld\n", total_cpu_usage1, total_cpu_usage2, proc_times1, proc_times2, number_of_processors);
    return number_of_processors * (proc_times2 - proc_times1) * 100 / (float) (total_cpu_usage2 - total_cpu_usage1);
}

int main() {
    stat_t stat;

    init_stat(&stat);

    print_cpu_stat(&stat, -1);
    print_cpu_stat(&stat, 0);
    print_cpu_stat(&stat, 1);
    print_pid_stat(&stat);
    load_stat(&stat, STAT_START);

    for (int i = 0; i < 100000000; i++) { }

    load_stat(&stat, STAT_END);
    printf("cpu usage = %f%%\n", cpu_usage(&stat));
    print_cpu_stat(&stat, -1);
    print_cpu_stat(&stat, 0);
    print_cpu_stat(&stat, 1);
    print_pid_stat(&stat);

    return 0;
}
