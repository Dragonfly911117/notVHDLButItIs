#include <linux/kernel.h>
#include <linux/module.h>

static int __init tx2HelloModeuleINIT(void){
  printk("Module installed\n");
  return 0;
}

static void __exit tx2HelloModeuleCleanup(void){
  printk("Module uninstalled\n");
}

module_init(tx2HelloModeuleINIT);
module_exit(tx2HelloModeuleCleanup);
MODULE_LICENSE("GPL");