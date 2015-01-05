#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

struct input_dev *ex1_dev;
int state;

void ex1_timeout(unsigned long unused/*UNUSED*/)
{
	
	    /* move in a small square */
    if (state<30) 
	input_report_rel(ex1_dev, REL_X, 5);
    else if (state < 60)
	input_report_rel(ex1_dev, REL_Y, 5);
    else if (state < 90)
	input_report_rel(ex1_dev, REL_X, -5);
    else
	input_report_rel(ex1_dev, REL_Y, -5);
    
    input_sync(ex1_dev);
    
    if ((state++) >= 120){
	       state = 0;
    }
    /* set timer for 0.02 seconds */
    mod_timer(&ex1_dev->timer, jiffies+HZ/50);
    
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
    ex1_dev->name = "Example 3 device";
    /* phys is unique on a running system */
    ex1_dev->phys = "A/Fake/Path";
    ex1_dev->id.bustype = BUS_HOST;
    ex1_dev->id.vendor = 0x0001;
    ex1_dev->id.product = 0x0001;
    ex1_dev->id.version = 0x0100;

    /* this device has two relative axes */
    set_bit(EV_REL, ex1_dev->evbit);
    set_bit(REL_X, ex1_dev->relbit);
    set_bit(REL_Y, ex1_dev->relbit);
    
    /* it needs a button to look like a mouse */
    set_bit(EV_KEY, ex1_dev->evbit);
    set_bit(BTN_LEFT, ex1_dev->keybit);    
    
    
    /* and finally register with the input core */
    input_register_device(ex1_dev);
    
    /* setup a repeating timer*/
    init_timer(&ex1_dev->timer);
    ex1_dev->timer.function=ex1_timeout;
    ex1_dev->timer.expires =jiffies + HZ/10;
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
