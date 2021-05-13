// SPDX-License-Identifier: GPL-2.0+
/*
 * slash.linux.c@gmail.com
 */

#include <common.h>
#include <command.h>
#include <version.h>
#include <linux/compiler.h>

static int do_cadtc_test(struct cmd_tbl *cmdtp, int flag, int argc,
		      char *const argv[])
{
	int count = argc;
	int i;

	printf("%s %d\n", __func__, __LINE__);
	printf("%s %d argc %d\n", __func__, __LINE__, argc);

	for (i = 0; i < count; i++)
		printf("%s %d argv[%d] %s\n", __func__, __LINE__, i, argv[i]);

	run_command(env_get("get_uboot"), 0);
	return 0;
}

U_BOOT_CMD(
	cadtc_test,	3, 1, do_cadtc_test,
	"cadtc test command, this is help",
	"this is userage"
);
