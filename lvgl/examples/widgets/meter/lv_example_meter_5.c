#include "../../lv_examples.h"
#if LV_USE_METER && LV_BUILD_EXAMPLES

static lv_obj_t * meter;

static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

/**
 * A clock from a meter
 */
void lv_example_meter_5(void)
{
    lv_obj_t *screen = lv_scr_act();

    meter = lv_meter_create(screen);
    lv_obj_set_size(meter, 260, 260);
    lv_obj_center(meter);

    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    /*Create a scale for the minutes*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t * scale_min = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_min, 61, 2, 10, lv_palette_main(LV_PALETTE_RED));
    lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);

    /*Create an other scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t * scale_hour = lv_meter_add_scale(meter);
    //lv_meter_set_scale_ticks(meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    //lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 2, 20, lv_color_black(), 10);    /*Every tick is major*/
    //lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/
    lv_meter_set_scale_ticks(meter, scale_hour, 12 + 1, 2, 22, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_range(meter, scale_hour, 0, 60, 360, 270);

    lv_meter_scale_t * scale_hours = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_hours, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    lv_meter_set_scale_major_ticks(meter, scale_hours, 1, 2, 20, lv_color_black(), 10);    /*Every tick is major*/
    lv_meter_set_scale_range(meter, scale_hours, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/


    //时间标签
    lv_obj_t *lv_time_label = lv_label_create(screen);
    lv_label_set_long_mode(lv_time_label, LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_size(lv_time_label, 72, 36);
    lv_label_set_text(lv_time_label,"23 : 59 : 59");
    lv_obj_set_align(lv_time_label, LV_ALIGN_CENTER);
    lv_obj_align(lv_time_label, LV_ALIGN_CENTER, 0, 0);

    //日期标签
    lv_obj_t *lv_date_label = lv_label_create(screen);
    lv_label_set_long_mode(lv_date_label, LV_LABEL_LONG_SCROLL_CIRCULAR );
    lv_obj_set_size(lv_date_label, 60, 24);
    lv_label_set_text(lv_date_label,"21/01/01");
    lv_obj_set_align(lv_date_label, LV_ALIGN_CENTER);
    lv_obj_align(lv_date_label, LV_ALIGN_CENTER, 0, 6);

    // LV_IMG_DECLARE(img_hand)

    // /*Add a the hands from images*/
    // lv_meter_indicator_t * indic_min = lv_meter_add_needle_img(meter, scale_min, &img_hand, 5, 5);
    // lv_meter_indicator_t * indic_hour = lv_meter_add_needle_img(meter, scale_min, &img_hand, 5, 5);

    // /*Create an animation to set the value*/
    // lv_anim_t a;
    // lv_anim_init(&a);
    // lv_anim_set_exec_cb(&a, set_value);
    // lv_anim_set_values(&a, 0, 60);
    // lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    // lv_anim_set_time(&a, 600*60);     /*2 sec for 1 turn of the minute hand (1 hour)*/
    // lv_anim_set_var(&a, indic_min);
    // lv_anim_start(&a);

    // lv_anim_set_var(&a, indic_hour);
    // lv_anim_set_time(&a, 600*720);    /*24 sec for 1 turn of the hour hand*/
    // lv_anim_set_values(&a, 0, 60);
    // lv_anim_start(&a);
}

#endif
