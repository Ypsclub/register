#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

struct input_dev *ex1_dev;

static int __init ex1_init(void)
{
    printk("%s: [mark]\n", __func__ );   		
    /* extra safe initialization */
    memset(&ex1_dev, 0, sizeof(struct input_dev));
    //init_input_dev(&ex1_dev);   // for kernel 2.5
    //for kernel up tp 3.2 
    ex1_dev= input_allocate_device();
    
    /* set up descriptive labels */
    ex1_dev->name = "Example 1 device";
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
    
    return 0;
}

static void __exit ex1_exit(void)
{
    printk("%s: [mark]\n", __func__ );   	
    input_unregister_device(ex1_dev);
}

module_init(ex1_init);
module_exit(ex1_exit);

MODULE_AUTHOR("YPSCLUB <yps.gamer@gmail.com>");
MODULE_DESCRIPTION("Virtual input Driver");
MODULE_LICENSE("GPL");
