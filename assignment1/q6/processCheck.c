
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/kallsyms.h>

MODULE_AUTHOR("Sagar Venkatesh");
MODULE_DESCRIPTION("Prints all processes with their PID, State and Name");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static void show_prcs(void)
{
        struct task_struct *p;
#define MAXLEN 128
        char tmp[MAXLEN];
        int n = 0;

        rcu_read_lock();
        for_each_process(p) {
                memset(tmp, 0, 128);
                n = snprintf(tmp, 128, "PID: %-10d State: %-8ld Name: %s\n", p->pid, p->state, p->comm);
                pr_info("%s", tmp);

                cond_resched();
        }
        rcu_read_unlock();
}

static int __init show_process_init(void)
{
        show_prcs();

        return 0;

}

static void __exit show_process_exit(void)
{
        pr_info();
}

module_init(show_process_init);
module_exit(show_process_exit);