#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("Sagar");
MODULE_DESCRIPTION("Hello Linux LKM");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init hellolinux_lkm_init(void)
{
        printk(KERN_INFO "Hello Linux, my love >3\n");
        return 0;              
}

static void __exit hellolinux_lkm_exit(void)
{
        printk(KERN_INFO "\n");
}

module_init(hellolinux_lkm_init);
module_exit(hellolinux_lkm_exit);