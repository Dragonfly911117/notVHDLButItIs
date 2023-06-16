#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <asm/uaccess.h>


#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char userChar[100];
struct file_operations drv_fops;


#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>


#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

// Opening a file (similar to open)
struct file *file_open(const char *path, int flags, int rights) {
  struct file *filp = NULL;
  mm_segment_t oldfs;
  int err = 0;

  oldfs = get_fs();
  set_fs(get_ds());
  filp = filp_open(path, flags, rights);
  set_fs(oldfs);
  if (IS_ERR(filp)) {
    err = PTR_ERR(filp);
    return NULL;
  }
  return filp;
}

// Writing data to a file (similar to pwrite)
int file_write(struct file *file, unsigned long long offset, unsigned char *data, unsigned int size) {
  mm_segment_t oldfs;
  int ret;

  oldfs = get_fs();
  set_fs(get_ds());
  
  ret = vfs_write(file, data, size, &offset);

  set_fs(oldfs);
  return ret;
}

// Closing a file (similar to close)
void file_close(struct file *file) {
  filp_close(file, NULL);
}





static int __init demo_init(void) {
  if (register_chrdev(MAJOR_NUM, MODULE_NAME, &drv_fops) < 0) {
    printk("<1>%s: cannot get major %d\n", MODULE_NAME, MAJOR_NUM);
    return (-EBUSY);
  }
  printk("<1>%s: loaded\n", MODULE_NAME);
  return 0;
}

static void __exit demo_exit(void) {
  unregister_chrdev(MAJOR_NUM, MODULE_NAME);
  printk("<1>%s: removed\n", MODULE_NAME);
}

static ssize_t drv_read(struct file *filp, char *buf, size_t count,
                        loff_t *ppos) {
  printk("Enter Read fn\n");
  return count;
}

static ssize_t drv_write  (struct file *filp, const char *buf, size_t count,
                        loff_t *ppos) {
  printk("Enter Write fn\n");
  printk("%d\n", iCount);
  printk("W_buf)size: %d\n", (int)count);
  __copy_from_user(userChar, buf, count);
  userChar[count - 1] = 0;
  printk("userChar: %s\n", userChar);
  printk("userChar.len: %d\n", (int)sizeof(userChar));
  iCount++;
  
  
  char fileName[1024] = "/sys/class/gpio/gpio";
  strncat(fileName, userChar, 3);
  strcat(fileName, "/value");
  
  printk("Path: %s\n", fileName);
  struct file *f = file_open(fileName, O_CREAT | O_RDWR | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
  
  if ((int)count != 4){
    char str[1024];
    strcpy(str, userChar+4);
    printk("value: %s\n", str);
    if (f != NULL) {
      file_write(f, 0,str , strlen(str));
      file_close(f);
    }
  } else {
    char str[1024];
    strcpy(str, userChar+4);
    printk("value: %s\n", str);
    
  }
  
  return count;
}


long drv_ioctl(struct file* filp, unsigned int cmd, unsigned  long arg){
    printk("Enter ioctl fn\n");
    return 0;
}

static int drv_open(struct inode* inode, struct file* filp){
    printk("Enter open fn\n");
    return 0;
}
drv_release(struct inode* inodem, struct file* filp){
    printk("Enter release fn\n");
};
struct file_operations drv_fops = {
  read : drv_read,
  write: drv_write,
  unlocked_ioctl: drv_ioctl,
  open: drv_open,
  release: drv_release,
};


module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
