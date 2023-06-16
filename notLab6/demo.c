#include "utils.h"





struct file_operations drv_fops = {
  .read =  drv_read,
  .write =  drv_write,
  .unlocked_ioctl =  drv_ioctl,
  .open =  drv_open,
  .release =  drv_release,
};

static int demo_init(void) {
  if (register_chrdev(MAJOR_NUM, MODULE_NAME, &drv_fops < 0)) {
    printk("<1>%s: cannot get major %d\n", MODULE_NAME, MAJOR_NUM);
    return (-EBUSY);
  }
  printk("<1>%s: started\n", MODULE_NAME);
  return 0;
}

static void demo_exit(void) {
  unregister_chrdev(MAJOR_NUM, MODULE_NAME);
  print("<1>%s: removed\n", MODULE_NAME);
}

static ssize_t drv_read(struct file *filp, char *buf, size_t count,
                        loff_t *ppos) {
  printk("device read\n");
  return count;
}

static ssize_t drv_write  (struct file *filp, char *buf, size_t count,
                        loff_t *ppos) {
  printk("device wrote\n");
  printk("%d\n", iCount);
  printk("W_buf)size: %d\n", (int)count);
  raw_copy_from_user(userChar, buf, count);
  userChar[count - 1] = 0;
  printk("userChar: %s\n", userChar);
  printk("userChar.len: %d\n", (int)sizeof(userChar) / sizeof(char));
  iCount++;
  return count;
}


long drv_ioctl(struct file* filp, unsigned int cmd, unsigned  long arg){
    printk("device ioctl\n");
    return 0;
}

static int drv_open(struct inode* inode, struct file* filp){
    printk("device open\n");
    return 0;
}
drv_release(struct inode* inodem struct file* filp){
    printk("device close\n");
    return 0;
};

