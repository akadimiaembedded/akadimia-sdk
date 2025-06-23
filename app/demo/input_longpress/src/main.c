/*
 * Copyright (c) 2025 liangyq <liangyongqincn@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include <string.h>

#include <zephyr/device.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>

static const struct device *const longpress_dev = DEVICE_DT_GET(DT_NODELABEL(longpress));

static int event_count;
static struct input_event last_events[2];

static void test_cb(struct input_event *evt, void *user_data)
{
	printk("%s: event_count: %d evt->code: %x evt->value: %d\n", __func__, event_count,
	       evt->code, evt->value);

	event_count++;
	memcpy(&last_events[1], &last_events[0], sizeof(struct input_event));
	memcpy(&last_events[0], evt, sizeof(struct input_event));
}
INPUT_CALLBACK_DEFINE(longpress_dev, test_cb, NULL);

int main(void)
{
	printf("input longpress test! %s\n", CONFIG_BOARD_TARGET);

	return 0;
}
