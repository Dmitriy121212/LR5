#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("Dima Bryzgalov <Bryzgalov174@ukr.net>");
MODULE_DESCRIPTION("Module for lab 5");
MODULE_LICENSE("Dual BSD/GPL");


static uint cnt = 1;
MODULE_PARM_DESC(cnt,"this parameter shows us, how many times Hello world! will be outputted");
module_param(cnt, uint, S_IRUGO);

struct list {
	struct list_head l;
	ktime_t t;
} *ptr;
static LIST_HEAD(head);

__attribute__((__noinline__))
static void add_to_list(struct list_head *node)
{
    BUG_ON(!node);
    list_add_tail(node, &head);
}

static int __init hello_init(void)
{
	/*init function*/
	
	if( (cnt == 0) || (cnt > 4 && cnt < 11) ) {
		printk(KERN_WARNING "Warning!\n");
		int i = 0;
		for(i = 0;i < cnt;i++){
			ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
			if(i == 6) {
				ptr = 0;
			} 
			ptr->t = ktime_get();
			add_to_list(&ptr->l);
			printk(KERN_INFO "Hello, world!\n");
		}
		
}
	if (cnt > 10) {
		BUG_ON(!list_empty(&head));
}
	
	printk(KERN_EMERG "Hello, world!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	struct list *cur, *next;
	list_for_each_entry_safe(cur, next, &head, l) {
	
	long long Event_time = ktime_to_ns(cur->t);
	printk(KERN_INFO "Event time: %lld\n", Event_time);
	list_del(&cur->l);
	kfree(cur);
	}

}

module_init(hello_init);
module_exit(hello_exit);
