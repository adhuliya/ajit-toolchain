//Ajit_serial.c
//
//Ajit serial driver (derived from uartlite.c)
//Neha Karanjkar
//April 2016
//Modified: January 2017


#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/slab.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <asm/Ajit_irq.h>
#include <asm/oplib_32.h> //for prom printf
#include <asm/prom.h> //to access the device tree




#define AJIT_SERIAL_MAJOR	TTY_MAJOR //this is the standard value for ttyS0
#define AJIT_SERIAL_MINORS	64	  //this is the standard value for ttyS0
#define AJIT_UART_NR		1	  // only use one port 
#define AJIT_SERIAL_NAME	"ttyS"
#define AJIT_DRIVER_NAME	"Ajit_serial"
#define AJIT_REGION		128	//give plenty of memory space


//Offsets for serial device registers 
#define CONTROL_REG	0x0
#define TX_REG		0x10
#define RX_REG		0x20

//Bit positions in the serial control register
#define BIT_TX_EN	0x0
#define BIT_RX_EN	0x1
#define BIT_RX_INT_EN   0x2
#define BIT_TX_FULL	0x3
#define BIT_RX_FULL	0x4

//Masks for obtaining bits in the control register
#define MASK_TX_EN	(((u32) 0x1)<<BIT_TX_EN )
#define MASK_RX_EN	(((u32) 0x1)<<BIT_RX_EN )
#define MASK_RX_INT_EN  (((u32) 0x1)<<BIT_RX_INT_EN )
#define MASK_TX_FULL	(((u32) 0x1)<<BIT_TX_FULL )
#define MASK_RX_FULL	(((u32) 0x1)<<BIT_RX_FULL )



//The following information is read from the device tree:
//
//1. Register base address:
//	 The serial device's registers are memory mapped.
//	 We pick up the base address from the device tree. 
//	 The individual registers can then be addressed by
//	 adding offsets to the base address value.
//
//2. Serial IRQ :
//	The hardware interrupt (number) used by the
//	serial device.
//
static int AJIT_SERIAL_IRQ = 0;
static int ADDR_SERIAL_REGISTER_BASE =0; 



//Routines for reads/writes to device registers
static u8 Ajit_in8(void __iomem *addr)
{
	return ioread8(addr);
}

static void Ajit_out8(u8 val, void __iomem *addr)
{
	iowrite8(val, addr);
}

static u32 Ajit_in32(void __iomem *addr)
{
	return ioread32be(addr);
}

static void Ajit_out32(u32 val, void __iomem *addr)
{
	iowrite32be(val, addr);
}

struct Ajit_register_ops 
{
	u8 (*in8)(void __iomem *addr);
	void (*out8)(u8 val, void __iomem *addr);
	u32 (*in32)(void __iomem *addr);
	void (*out32)(u32 val, void __iomem *addr);
};

static struct Ajit_register_ops Ajit_reg_ops = 
{
	.in8   = Ajit_in8,
	.out8  = Ajit_out8,
	.in32  = Ajit_in32,
	.out32 = Ajit_out32,
};

static inline void uart_out8(u8 val, u32 offset, struct uart_port *port)
{
	struct Ajit_register_ops *reg_ops = port->private_data;

	reg_ops->out8(val, port->membase + offset);
}


static inline u8 uart_in8(u32 offset, struct uart_port *port)
{
	struct Ajit_register_ops *reg_ops = port->private_data;

	return reg_ops->in8(port->membase + offset);
}

static inline void uart_out32(u32 val, u32 offset, struct uart_port *port)
{
	struct Ajit_register_ops *reg_ops = port->private_data;

	reg_ops->out32(val, port->membase + offset);
}


static inline u32 uart_in32(u32 offset, struct uart_port *port)
{
	struct Ajit_register_ops *reg_ops = port->private_data;

	return reg_ops->in32(port->membase + offset);
}


//stop Tx 
static void Ajit_stop_Tx(struct uart_port *port)
{
	u32 control_word = uart_in32(CONTROL_REG, port);
	control_word = control_word & (~ MASK_TX_EN);
	uart_out32(control_word, CONTROL_REG, port);
}

//stop Rx
static void Ajit_stop_Rx(struct uart_port *port)
{
	//Reset Rx_en, and Rx_int_en bits
	u32 control_word = uart_in32(CONTROL_REG, port);
	control_word = control_word & (~ MASK_RX_EN);
	control_word = control_word & (~ MASK_RX_INT_EN);
	uart_out32(control_word, CONTROL_REG, port);
}

//enable Tx
static void Ajit_enable_Tx(struct uart_port *port)
{
	u32 control_word = uart_in32(CONTROL_REG, port);
	control_word = control_word | (MASK_TX_EN);
	uart_out32(control_word, CONTROL_REG, port);
}

//enable Rx
static void Ajit_enable_Rx(struct uart_port *port)
{
	//Set Rx_en and Rx_int_en bits
	u32 control_word = uart_in32(CONTROL_REG, port);
	control_word = control_word | (MASK_RX_EN);
	control_word = control_word | (MASK_RX_INT_EN);
	uart_out32(control_word, CONTROL_REG, port);
}

//returns 1 if Tx is empty
static unsigned int Ajit_Tx_empty(struct uart_port *port)
{
	u32 control_word = uart_in32(CONTROL_REG, port);
	control_word = control_word & (MASK_TX_FULL);
	if(control_word) return 0;
	else return 1;
}

//another version of Tx_empty
static unsigned int Ajit_Tx_empty_locking(struct uart_port *port)
{
	unsigned long flags;
	unsigned int ret;

	spin_lock_irqsave(&port->lock, flags);
	ret = Ajit_Tx_empty(port);
	spin_unlock_irqrestore(&port->lock, flags);

	return ret ? TIOCSER_TEMT : 0;
}

//returns 1 if Tx is full
static int Ajit_Tx_full(struct uart_port *port)
{
	if(Ajit_Tx_empty(port)) return 0;
	else return 1;
}

//returns 1 if Rx is full
//static int Ajit_Rx_full(struct uart_port *port)
//{
//	u32 control_word = uart_in32(CONTROL_REG, port);
//	control_word = control_word & (MASK_RX_FULL);
//	if(control_word) return 1;
//	else return 0;
//}

//returns 1 if Rx is empty
static int Ajit_Rx_empty(struct uart_port *port)
{
	u32 control_word = uart_in32(CONTROL_REG, port);
	control_word = control_word & (MASK_RX_FULL);
	if(control_word) return 0;
	else return 1;
}

//send a character to Tx
static void Ajit_send_Tx(u8 c, struct uart_port *port)
{
	//wait until tx is empty
	while(Ajit_Tx_full(port)) { }
	//write a char into Tx register
	uart_out8(c, TX_REG, port);
}

static void Ajit_enable_ms(struct uart_port *port)
{
	//modem stuff. We don't need
}


static int Ajit_Tx_chars(struct uart_port *port)
{
	//circular buffer holding 
	//characters to be transmitted
	struct circ_buf *xmit = &port->state->xmit;

	//return 0 if Tx is full
	//if(Ajit_Tx_full()) return 0;
	

	//Enable Tx
	Ajit_enable_Tx(port);

	if (port->x_char) 
	{
		//send character to Tx 
		Ajit_send_Tx(port->x_char, port);
		port->x_char = 0;
		port->icount.tx++;
		return 1;
	}
	
	if (uart_circ_empty(xmit) || uart_tx_stopped(port)) 
	{
		return 0;
	}

	//In uartlite, this function transmits
	//just one character and returns.
	//We transmit all characters in the buffer.
	while (uart_circ_chars_pending(xmit))
	{
		//send a char
		Ajit_send_Tx(xmit->buf[xmit->tail], port);
		//redundant print for debugging:
		//prom_printf("[%c]", xmit->buf[xmit->tail]);
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		port->icount.tx++;
	}
	
	//schedule a wakeup for transmitting the remaining chars
	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		Ajit_stop_Tx(port);
	return 1;
}

static void Ajit_start_Tx(struct uart_port *port)
{
	Ajit_Tx_chars(port);
}


static int Ajit_receive(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	unsigned char ch = 0;
	char flag = TTY_NORMAL;

	//If Rx_full==0, return 0
	if (Ajit_Rx_empty(port))
	{
		//prom_printf(" ... Ajit_Rx_empty()==1 . returning");
		return 0;
	}
	else
	{
		port->icount.rx++;
		//read character from Rx register
		ch = uart_in8(RX_REG, port);
		//prom_printf(" ...read char = %c",ch);
		tty_insert_flip_char(tport, ch, flag);
		return 1;
	}
}

// ISR is only called upon receive
static irqreturn_t Ajit_isr(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	int busy, n = 0;

	//prom_printf("\nAjit_isr()");
	
	//Disable IRC
	Ajit_write_IRC_control_word(0x00);
	do {
		busy  = Ajit_receive(port);
		n++;
	} while (busy);
	
	//prom_printf("\nReturned from Ajit_receive(). n = %d",n);
	//Enable IRC
	Ajit_write_IRC_control_word(0x01);

	// work done? 
	if (n >= 1) 
	{
		tty_flip_buffer_push(&port->state->port);
		//prom_printf("\nReturn IRQ_HANDLED");
		return IRQ_HANDLED;
	}
	else 
	{
		//prom_printf("\nReturn IRQ_NONE");
		return IRQ_NONE;
	}
}


static unsigned int Ajit_get_mctrl(struct uart_port *port)
{
	//prom_printf("\nAjit_get_mctrl()");
	return TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;
}

static void Ajit_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	//prom_printf("\nAjit_set_mctrl()");
}

static void Ajit_break_ctl(struct uart_port *port, int break_state)
{
	//prom_printf("\nAjit_break_ctl()");
}

static void Ajit_set_termios(struct uart_port *port,
			     struct ktermios *new, struct ktermios *old)
{
	//No need to do anything here,
	//because our uart model does not
	//have any settings for baud rate, parity,
	//byte size, etc.
}

static int Ajit_startup(struct uart_port *port)
{
	
	/* this is the first time this port is opened */
	/* do any hardware initialization needed here */
	int err;
	int irq=0;

	prom_printf("\nAjit_startup()");
	
	//request irq for the port:
	prom_printf("\n Requesting irq port->irq=%d ",port->irq);
	irq = Ajit_build_device_irq(NULL, port->irq);
	prom_printf("\n Ajit_build_device_irq(NULL, %d) returned %d ",port->irq,irq);
	err = request_irq(irq, Ajit_isr, IRQF_SHARED, AJIT_DRIVER_NAME, port);
	if (err)
	{
		//There was an error
		prom_printf("\n call to request_irq() FAILED, with error = %d",err);
		return err;
	}
	prom_printf("\n call to request_irq() SUCCEEDED");

	//Enable Tx, Rx, Rx_int_en
	Ajit_enable_Tx(port);
	Ajit_enable_Rx(port);
	return 0;
}


static void Ajit_shutdown(struct uart_port *port)
{
	/* The port is being closed by the last user. */
	/* Do any hardware specific stuff here */
	prom_printf("\nAjit_shutdown()");
	
	//Disable Tx and Rx
	Ajit_stop_Tx(port);
	Ajit_stop_Rx(port);
	
	//free the irq
	free_irq(port->irq, port);
}

static const char *Ajit_type(struct uart_port *port)
{
	return port->type == PORT_AJIT ? AJIT_DRIVER_NAME : NULL;
}

static void Ajit_release_port(struct uart_port *port)
{
	prom_printf("\nAjit_release_port()");
	release_mem_region(port->mapbase, AJIT_REGION);
	iounmap(port->membase);
	port->membase = NULL;
}

static int Ajit_request_port(struct uart_port *port)
{
	prom_printf("\nAjit_request_port: port=%p; port->mapbase=%llx\n",
		 port, (unsigned long long) port->mapbase);

	prom_printf("\n entering request_mem_region()");
	if (!request_mem_region(port->mapbase, AJIT_REGION, AJIT_DRIVER_NAME)) 
	{
		dev_err(port->dev, "Memory region busy\n");
		prom_printf("... FAILED ");
		return -EBUSY;
	}

	prom_printf("\n entering ioremap()");
	port->membase = ioremap(port->mapbase, AJIT_REGION);
	if (!port->membase) 
	{
		dev_err(port->dev, "Unable to map registers\n");
		release_mem_region(port->mapbase, AJIT_REGION);
		prom_printf("... FAILED");
		return -EBUSY;
	}
	port->private_data = &Ajit_reg_ops;
	return 0;
}

static void Ajit_config_port(struct uart_port *port, int flags)
{
	prom_printf("\nAjit_config_port()");
	if (!Ajit_request_port(port))
		port->type = PORT_AJIT;
}

static int Ajit_verify_port(struct uart_port *port, struct serial_struct *ser)
{
	//we don't want the core code to modify any port params
	return -EINVAL;
}



//------------------------------------------------------
//Console Functionality
//If CONFIG_SERIAL_AJIT_CONSOLE is defined, the Ajit serial
//device is used as console during boot.

#ifdef CONFIG_SERIAL_AJIT_CONSOLE

static void Ajit_console_write(struct console *co, const char *s,
				unsigned int count)
{
	//simply use prom_printf.
	//the prom_printf in-turn calls a putchar function
	//supplied by the bootloader.
	int char_count=0;
	for(char_count=0;char_count<count;char_count++)
		prom_printf("%c",s[char_count]);
}

//static int Ajit_console_setup(struct console *co, char *options)
//{
//	//do nothing. We're directly using prom_printf
//	return 0;
//}

static struct uart_driver Ajit_serial_driver;

static struct console Ajit_console = {
	.name	= AJIT_SERIAL_NAME,
	.write	= Ajit_console_write,
	.device	= uart_console_device,
	.flags	= CON_PRINTBUFFER,
	.index	= -1, 
	.data	= &Ajit_serial_driver,
};

static int __init Ajit_console_init(void)
{
	register_console(&Ajit_console);
	return 0;
}

console_initcall(Ajit_console_init);
#endif // CONFIG_SERIAL_AJIT_CONSOLE 
//------------------------------------------------------



static struct uart_ops Ajit_serial_ops = {
	.tx_empty	= Ajit_Tx_empty_locking,
	.set_mctrl	= Ajit_set_mctrl,
	.get_mctrl	= Ajit_get_mctrl,
	.stop_tx	= Ajit_stop_Tx,
	.start_tx	= Ajit_start_Tx,
	.stop_rx	= Ajit_stop_Rx,
	.enable_ms	= Ajit_enable_ms,
	.break_ctl	= Ajit_break_ctl,
	.startup	= Ajit_startup,
	.shutdown	= Ajit_shutdown,
	.set_termios	= Ajit_set_termios,
	.type		= Ajit_type,
	.release_port	= Ajit_release_port,
	.request_port	= Ajit_request_port,
	.config_port	= Ajit_config_port,
	.verify_port	= Ajit_verify_port,
};

static struct uart_port Ajit_port = {
	.fifosize=1,
	.flags   = UPF_BOOT_AUTOCONF,
	.iotype  = UPIO_MEM,
	.mapbase = 0, 
	.membase = NULL,
	.ops	 = &Ajit_serial_ops,
	.irq	 = 0,
};

static struct uart_driver Ajit_serial_driver = {
	.owner		= THIS_MODULE,
	.driver_name	= AJIT_DRIVER_NAME,
	.dev_name	= AJIT_SERIAL_NAME,
	.major		= AJIT_SERIAL_MAJOR,
	.minor		= AJIT_SERIAL_MINORS,
	.nr		= AJIT_UART_NR,
#ifdef CONFIG_SERIAL_AJIT_CONSOLE
	.cons		= &Ajit_console,
#endif
};


static void read_dev_tree(void)
{
	struct device_node *node;
	struct device_node *rootnode;
	struct property* prop;
	int len=0;

	prom_printf("\nReading device tree...");
	//find the root node in device tree
	rootnode = of_find_node_by_path("/");
	if(!rootnode) 
	{
		prom_printf("\nERROR: While reading device tree, could not find root node /.\n");
		return;
	}
	
	//find the node corresponding to the serial device
	node = of_find_node_by_name(rootnode, "ajit_serial");
	if (!node)
	{
		prom_printf("\nERROR: While reading device tree, could not find node ajit_serial.\n");
		return;
	}

	//find the property called "reg"
	//this is the base register address.
	prop = of_find_property(node, "reg", &len);
	if (!prop)
	{
		prom_printf("\nERROR: While reading device tree, could not find property reg in node ajit_serial.\n");
		return;
	}

	ADDR_SERIAL_REGISTER_BASE = *(unsigned int *)prop->value;

	//find the property called "interrupts"
	//this is the HW interrupt number
	prop = of_find_property(node, "interrupts", &len);
	if (!prop)
	{
		prom_printf("\nERROR: While reading device tree, could not find property interrupts in node ajit_serial.\n");
		return;
	}
	AJIT_SERIAL_IRQ = *(unsigned int *)prop->value;

	prom_printf("\nAjit_serial : found base register address = 0x%x",ADDR_SERIAL_REGISTER_BASE);
	prom_printf("\nAjit_serial : found interrupt number = 0x%x",AJIT_SERIAL_IRQ);
	
	//Finally, plug this info into the port struct
	Ajit_port.mapbase = ADDR_SERIAL_REGISTER_BASE;
	Ajit_port.irq = AJIT_SERIAL_IRQ;

}



static int __init Ajit_init(void)
{
	int ret;
	
	//probe the device tree
	read_dev_tree();

	//register driver
	prom_printf("\nRegistering Ajit_serial driver");
	ret = uart_register_driver(&Ajit_serial_driver);
	if (ret) 
		goto err_uart;

	//register port
	prom_printf("\nIn Ajit_serial driver, registering port");
	ret = uart_add_one_port(&Ajit_serial_driver, &Ajit_port);
	if (ret)
	{
		uart_unregister_driver(&Ajit_serial_driver);
		goto err_uart;
	}

	prom_printf("\nRegistration of Ajit_serial driver was successful\n");
	return 0;

err_uart:
	prom_printf("\nRegistering Ajit_serial driver failed: err=%i", ret);
	return ret;
}


static void __exit Ajit_exit(void)
{
	uart_unregister_driver(&Ajit_serial_driver);
}

module_init(Ajit_init);
module_exit(Ajit_exit);

MODULE_AUTHOR("Neha Karanjkar");
MODULE_DESCRIPTION("Ajit serial driver (adapted from uartlite.c)");
MODULE_LICENSE("GPL");

