#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lvgl/examples/lv_examples.h"
#include "evdev_mouse.h"
#include "lvgl/demos/lv_demos.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <linux/vt.h>
#include <linux/kd.h>
#include <linux/fb.h>

#define EVDEV_MOUSE_NAME "/dev/input/event2"
#define TTY_DEVICE_NAME "/dev/tty0"

static int s_vt_fd = -1;
static lv_color_t* s_buf1 = NULL;
static lv_color_t* s_buf2 = NULL;

/**
 * Print the memory usage periodically
 * @param param
 */
// static void memory_monitor(lv_task_t *param)
// {
// 	(void)param; /*Unused*/

// 	lv_mem_monitor_t mon;
// 	lv_mem_monitor(&mon);
// 	printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n",
// 		(int)mon.total_size - mon.free_size, mon.used_pct, mon.frag_pct,
// 		(int)mon.free_biggest_size);
// }

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics
 * library
 */
static void hal_init(void)
{
/*
	if (!access(TTY_DEVICE_NAME, F_OK))
	{
		int fd = open(TTY_DEVICE_NAME, O_RDWR | O_SYNC);
		if(fd < 0)
		{
			printf("open %s faield!\n", TTY_DEVICE_NAME);
			return;
		}

		if(ioctl(fd, KDSETMODE, (void*) KD_GRAPHICS))
		{
			printf("set %s to graphics mode faield!\n", TTY_DEVICE_NAME);
			close(fd);
			return;
		}
		
		s_vt_fd = fd;
	}
*/
	/* Use the 'fbdev' driver */
	fbdev_init();
	
	uint32_t disp_width = LV_HOR_RES_MAX; 
	uint32_t disp_height = LV_VER_RES_MAX;
	fbdev_get_sizes(&disp_width, &disp_height);
	
	uint32_t size_in_px_cnt = disp_width * disp_height;
	s_buf1 = (lv_color_t*)malloc(size_in_px_cnt * sizeof(lv_color_t));
	assert(s_buf1);
	s_buf2 = (lv_color_t*)malloc(size_in_px_cnt * sizeof(lv_color_t));
	assert(s_buf2);
	
	/*Create a display buffer*/
	static lv_disp_draw_buf_t disp_buf;
	lv_disp_draw_buf_init(&disp_buf, s_buf1, s_buf2, size_in_px_cnt);

	/*Create a display*/
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.draw_buf = &disp_buf;
	disp_drv.hor_res = disp_width;
	disp_drv.ver_res = disp_height;
	disp_drv.flush_cb = fbdev_flush;
	lv_disp_drv_register(&disp_drv);
#if 1
	evdev_mouse_set_file(EVDEV_MOUSE_NAME);
#else
	evdev_set_file(EVDEV_MOUSE_NAME);
#endif
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
#if 1
	indev_drv.read_cb = evdev_mouse_read;
#else
	indev_drv.read_cb = evdev_read;
#endif
	lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);
	
	/*Set a cursor for the mouse*/
#if 1
	LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
	lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
	lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
#else
	lv_obj_t * cursor_obj = lv_label_create(lv_scr_act());
	lv_label_set_recolor(cursor_obj, true);
	lv_label_set_text(cursor_obj, "#ff0000 .cursor");
#endif
	lv_indev_set_cursor(mouse_indev, cursor_obj);
	
	/* Optional:
	 * Create a memory monitor task which prints the memory usage in
	 * periodically.*/
	//lv_task_create(memory_monitor, 5000, LV_TASK_PRIO_MID, NULL);
}

int main(void)
{
	/*Initialize LVGL*/
	lv_init();

	/*Initialize the HAL (display, input devices, tick) for LVGL*/
	hal_init();

	//lv_demo_widgets();
	//lv_demo_benchmark();
	//lv_demo_keypad_encoder();
	//lv_demo_printer();
	//lv_demo_stress();
	//lv_demo_music();
	//lv_ex_get_started_1();
	//lv_ex_get_started_2();
	//lv_ex_get_started_3();

	//lv_example_style_1();
	//lv_example_style_2();
	//lv_example_style_3();
	//lv_example_style_4();
	//lv_example_style_5();
	//lv_example_style_6();
	//lv_example_style_7();
	//lv_example_style_8();
	//lv_example_style_9();
	//lv_example_style_10();
	//lv_example_style_11();

	//lv_example_colorwheel_1();

	//lv_example_meter_1();
	//lv_example_meter_2();
	//lv_example_meter_3();
	//lv_example_meter_4();

	// lv_example_label_1();
	// lv_example_label_2();
	// lv_example_label_3();
	// lv_example_label_4();

	lv_example_meter_5();
	//lv_example_spinner_1();

	while (1)
	{
		/* Periodically call the lv_task handler.
		 * It could be done in a timer interrupt or an OS task too.*/
		lv_task_handler();
		
		usleep(5 * 1000);
	}
	
	if (s_vt_fd != -1)
	{
		if (ioctl(s_vt_fd, KDSETMODE, KD_TEXT) < 0)
		{
		    perror("KDSETMODE");
		}
		close(s_vt_fd);
		s_vt_fd = -1;
        }
        
        free(s_buf1);
        s_buf1 = NULL;
        free(s_buf2);
        s_buf2 = NULL;
	

	return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0)
    {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
