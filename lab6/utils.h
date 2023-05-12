#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <unistd.h>

#define MAJOR_NUM 60
#define MODULE_NAME "demo"

static int iCount = 0;
static char userChar[100];

typedef struct {
  int read, write, unlock_ioctl, open, release;
} file_operations;

static int demo_init(void);
static void demo_exit(void) ;
static ssize_t drv_read(struct file *filp, char *buf, size_t count,
                        loff_t *ppos) ;
static ssize_t drv_write(struct file *filp, char *buf, size_t count,
                        loff_t *ppos) ;
long drv_ioctl(struct file* filp, unsigned int cmd, unsigned  long arg);
  static int drv_open(struct inode* inode, struct file* filp);
  drv_release(struct inode* inodem struct file* filp);