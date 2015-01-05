#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

struct input_dev *ex1_dev;

void ex1_timeout(unsigned long unused/*UNUSED*/)
{
    int x;

    for (x=0;x<4;x++) {
				/* letter a or A */
				input_report_key(ex1_dev, KEY_A, 1);
				input_sync(ex1_dev);
				input_report_key(ex1_dev, KEY_A, 0);
				input_sync(ex1_dev);
    }
    for (x=0;x<4;x++) {
				/* letter b or B */
				input_report_key(ex1_dev, KEY_B, 1);
				input_sync(ex1_dev);
				input_report_key(ex1_dev, KEY_B, 0);
				input_sync(ex1_dev);
    }
    
    /* set timer for four seconds */
    mod_timer(&ex1_dev->timer,jiffies+4*HZ );	
}


static int __init ex1_init(void)
{
    printk("%s: [mark]\n", __func__ );   		
    /* extra safe initialization */
    memset(&ex1_dev, 0, sizeof(struct input_dev));
    //init_input_dev(&ex1_dev);   // for kernel 2.5
    //for kernel up tp 3.2 
    ex1_dev= input_allocate_device();
    
    /* set up descriptive labels */
    ex1_dev->name = "Example 2 device";
    /* phys is unique on a running system */
    ex1_dev->phys = "A/Fake/Path";
    ex1_dev->id.bustype = BUS_HOST;
    ex1_dev->id.vendor = 0x0001;
    ex1_dev->id.product = 0x0001;
    ex1_dev->id.version = 0x0100;
    
    /* this device has two keys (A and B) */
    set_bit(EV_KEY, ex1_dev->evbit);
    set_bit(KEY_B, ex1_dev->keybit);
    set_bit(KEY_A, ex1_dev->keybit);
    
    /* and finally register with the input core */
    input_register_device(ex1_dev);
    
    /* setup a repeating timer*/
    init_timer(&ex1_dev->timer);
    ex1_dev->timer.function=ex1_timeout;
    ex1_dev->timer.expires = jiffies + HZ;
    add_timer(&ex1_dev->timer);
    /*end */
    return 0;
}

static void __exit ex1_exit(void)
{
    printk("%s: [mark]\n", __func__ );   	
    del_timer_sync(&ex1_dev->timer);
    input_unregister_device(ex1_dev);
}

module_init(ex1_init);
module_exit(ex1_exit);

MODULE_AUTHOR("YPSCLUB <yps.gamer@gmail.com>");
MODULE_DESCRIPTION("Virtual input Driver");
MODULE_LICENSE("GPL");
