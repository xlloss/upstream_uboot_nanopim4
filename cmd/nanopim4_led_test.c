/*
 * Control LED Test
 * slash.linux.c@gmail.com
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <command.h>
#include <errno.h>
#include <dm.h>
#include <log.h>
#include <malloc.h>
#include <asm/gpio.h>
#include <linux/err.h>
#include <linux/delay.h>

static int do_nanopi_led(struct cmd_tbl *cmdtp, int flag, int argc,
		   char *const argv[])
{
	#define DIR_OUT 0
	#define DIR_IN 0
	#define LED_N 4
	#define LED0 "32"
	#define LED1 "33"
	#define LED2 "35"
	#define LED3 "36"
	#define LED_ON 0
	#define LED_OFF 1

	unsigned int gpio[LED_N];
	char *led_gpio[LED_N] = {LED0, LED1, LED2, LED3}, tmp_led_n, tmp_led_v;
	int ret, i, led_num, led_val;

	if (argc <= 1) {
		printf("nanopi_led 0 1\n");
		printf("nanopi_led LED_NUM LED_VALE\n");
		return CMD_RET_FAILURE;
	}

	for (i = 0; i < LED_N; i++) {
		ret = gpio_lookup_name(led_gpio[i], NULL, NULL, &gpio[i]);
		if (ret) {
			printf("GPIO: '%s' not found\n", led_gpio[0]);
			return cmd_process_error(cmdtp, ret);
		}

		ret = gpio_request(gpio[i], "cmd_gpio");
		if (ret && ret != -EBUSY) {
			printf("gpio: requesting pin %u failed\n", gpio[i]);
			return -1;
		}

		gpio_direction_output(gpio[i], DIR_OUT);
		/* printf("gpio: pin %s (gpio[%d] %u) value\n", led_gpio[0], i, gpio[i]); */
	}

	for (i = 0; i < LED_N; i++)
		gpio_set_value(gpio[led_num], LED_OFF);

	for (i = 0; i < LED_N; i++) {
		gpio_set_value(gpio[0], LED_OFF);
		gpio_set_value(gpio[1], LED_OFF);
		gpio_set_value(gpio[2], LED_OFF);
		gpio_set_value(gpio[3], LED_OFF);
		mdelay(100);
		gpio_set_value(gpio[0], LED_ON);
		gpio_set_value(gpio[1], LED_ON);
		gpio_set_value(gpio[2], LED_ON);
		gpio_set_value(gpio[3], LED_ON);
		mdelay(100);
	}

	memcpy(&tmp_led_n, argv[1], 1);
	led_num = tmp_led_n - '0';

	memcpy(&tmp_led_v, argv[2], 1);
	led_val = tmp_led_v - '0';

	if (led_num >= LED_N)
		led_num = LED_N - 1;
	else if (led_num < 0)
		led_num = 0;

	led_val = (led_val == 0) ? LED_OFF : LED_ON;
	gpio_set_value(gpio[led_num], led_val);

	/*
	printf("argv[0] %s led_num %d\n", argv[0], led_num);
	printf("argv[1] %s led_val\n", argv[1], led_val);
	*/

	for (i = 0; i < LED_N; i++)
		gpio_free(gpio[i]);

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(nanopi_led, 2, 0, do_nanopi_led,
	   "nanopi_led 0 1\n",
	   "nanopi_led LED_NUM LED_VALE");
