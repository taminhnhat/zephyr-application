/*
 * Copyright (c) 2022 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/drivers/gpio.h>
#include <string.h>
#include "SEGGER_RTT.h"


/* change this to any other UART peripheral if desired */
#define UART_DEVICE_NODE DT_CHOSEN(zephyr_shell_uart)

#define MSG_SIZE 32

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch))
#error "Overlay for power output node not properly defined."
#endif

#if !DT_NODE_EXISTS(DT_NODELABEL(input_capture))
#error "Overlay for input capture node not properly defined."
#endif

/* queue to store up to 10 messages (aligned to 4-byte boundary) */
K_MSGQ_DEFINE(uart_msgq, MSG_SIZE, 10, 4);

static const struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);

/* receive buffer used in UART ISR callback */
static char rx_buf[MSG_SIZE];
static int rx_buf_pos;

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec load_switch = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(load_switch), gpios, {0});
static const struct gpio_dt_spec user_button = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(user_button), gpios, {0});
static const struct gpio_dt_spec user_capture = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(input_capture), gpios, {0});
static struct gpio_callback button_cb_data;
static struct gpio_callback capture_cb_data;

uint64_t user_button_lastcall = 0;
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	uint64_t user_button_now = k_uptime_get();
	if (user_button_now - user_button_lastcall < 200)
		return;
	user_button_lastcall = user_button_now;
	printk("Button pressed at %" PRIu64 "\n", user_button_lastcall);
	gpio_pin_toggle_dt(&load_switch);
	gpio_pin_toggle_dt(&led1);
	gpio_pin_toggle_dt(&led2);
}

uint64_t user_capture_lastcall = 0;
int user_capture_laststate = 0;
void user_capture_change_edge()
{
	uint64_t user_capture_now = k_uptime_get();
	int user_capture_state = gpio_pin_get_dt(&user_capture);
	user_capture_lastcall = user_capture_now;
	printk("Input capture at %" PRIu64 " state:%d\n", user_capture_lastcall, user_capture_state);
}

int my_DI_init()
{
	int ret;
	/*setup for user_button*/
	if (!gpio_is_ready_dt(&user_button))
	{
		printk("Error: button device %s is not ready\n",
			   user_button.port->name);
		return 0;
	}
	ret = gpio_pin_configure_dt(&user_button, GPIO_INPUT);
	if (ret != 0)
	{
		printk("Error %d: failed to configure %s pin %d\n",
			   ret, user_button.port->name, user_button.pin);
		return 0;
	}

	ret = gpio_pin_interrupt_configure_dt(&user_button,
										  GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0)
	{
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			   ret, user_button.port->name, user_button.pin);
		return 0;
	}

	gpio_init_callback(&button_cb_data, button_pressed, BIT(user_button.pin));
	gpio_add_callback(user_button.port, &button_cb_data);
	printk("Set up button at %s pin %d\n", user_button.port->name, user_button.pin);

	/*setup for user_capture*/
	printk("Setting up user capture at pin %d\n", user_capture.pin);
	if (!gpio_is_ready_dt(&user_capture))
	{
		printk("Error: button device %s is not ready\n",
			   user_capture.port->name);
		return 0;
	}
	ret = gpio_pin_configure_dt(&user_capture, GPIO_INPUT);
	if (ret != 0)
	{
		printk("Error %d: failed to configure %s pin %d\n",
			   ret, user_capture.port->name, user_capture.pin);
		return 0;
	}
	ret = gpio_pin_interrupt_configure_dt(&user_capture, GPIO_INT_EDGE_BOTH);
	if (ret != 0)
	{
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			   ret, user_capture.port->name, user_capture.pin);
		return 0;
	}
	gpio_init_callback(&capture_cb_data, user_capture_change_edge, BIT(user_capture.pin));
	gpio_add_callback(user_capture.port, &capture_cb_data);
	printk("Set up capture at %s pin %d\n", user_capture.port->name, user_capture.pin);

	return 1;
}

int my_DO_init(const struct gpio_dt_spec *led)
{
	if (!gpio_is_ready_dt(led))
	{
		return 0;
	}

	int ret = gpio_pin_configure_dt(led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0)
	{
		return 0;
	}

	return 1;
}

/*
 * Read characters from UART until line end is detected. Afterwards push the
 * data to the message queue.
 */
void serial_cb(const struct device *dev, void *user_data)
{
	uint8_t c;

	if (!uart_irq_update(uart_dev))
	{
		return;
	}

	if (!uart_irq_rx_ready(uart_dev))
	{
		return;
	}

	/* read until FIFO empty */
	while (uart_fifo_read(uart_dev, &c, 1) == 1)
	{
		if ((c == '\n' || c == '\r') && rx_buf_pos > 0)
		{
			/* terminate string */
			rx_buf[rx_buf_pos] = '\0';

			/* if queue is full, message is silently dropped */
			k_msgq_put(&uart_msgq, &rx_buf, K_NO_WAIT);

			/* reset the buffer (it was copied to the msgq) */
			rx_buf_pos = 0;
		}
		else if (rx_buf_pos < (sizeof(rx_buf) - 1))
		{
			rx_buf[rx_buf_pos++] = c;
		}
		/* else: characters beyond buffer size are dropped */
	}
}

/*
 * Print a null-terminated string character by character to the UART interface
 */
void print_uart(char *buf)
{
	int msg_len = strlen(buf);

	for (int i = 0; i < msg_len; i++)
	{
		uart_poll_out(uart_dev, buf[i]);
	}
}

int main(void)
{
	char tx_buf[MSG_SIZE];

	if (!device_is_ready(uart_dev))
	{
		printk("UART device not found!");
		return 0;
	}

	my_DO_init(&led0);
	my_DO_init(&led1);
	my_DO_init(&led2);
	my_DO_init(&led3);
	my_DO_init(&load_switch);

	my_DI_init();

	/* configure interrupt and callback to receive data */
	int ret = uart_irq_callback_user_data_set(uart_dev, serial_cb, NULL);
	if (ret < 0)
	{
		if (ret == -ENOTSUP)
		{
			printk("Interrupt-driven UART API support not enabled\n");
		}
		else if (ret == -ENOSYS)
		{
			printk("UART device does not support interrupt-driven API\n");
		}
		else
		{
			printk("Error setting UART callback: %d\n", ret);
		}
		return 0;
	}
	uart_irq_rx_enable(uart_dev);

	print_uart("Hello! I'm your echo bot.\r\n");
	print_uart("Tell me something and press enter:\r\n");

	/* indefinitely wait for input from the user */
	while (k_msgq_get(&uart_msgq, &tx_buf, K_FOREVER) == 0)
	{
		print_uart("Echo: ");
		print_uart(tx_buf);
		print_uart("\r\n");
		gpio_pin_toggle_dt(&led0);
		gpio_pin_toggle_dt(&led3);
	}
	return 0;
}
