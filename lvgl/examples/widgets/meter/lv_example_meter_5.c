#include "../../lv_examples.h"
#if LV_USE_METER && LV_BUILD_EXAMPLES

static lv_obj_t * meter;

lv_obj_t * lv_main;


LV_IMG_DECLARE(img_benchmark_cogwheel_indexed16);
LV_IMG_DECLARE(img_benchmark_cogwheel_argb);

static lv_style_t style_common;
static bool opa_mode = true;

void GUI_Setting_Init(lv_obj_t *pmain, lv_group_t *group);
void GUI_Heart_Init(lv_obj_t *pmain, lv_group_t *group);
static void set_value(void * indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

static void event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");

        GUI_Heart_Init(lv_main, NULL);
        GUI_Setting_Init(lv_main, NULL);
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}
/**
 * A clock from a meter
 */
void GUI_Main_Init(lv_obj_t *pmain, lv_group_t *group)
{
    lv_obj_t *screen = pmain;
	//lv_obj_set_size(screen, 300, 300);
	lv_obj_set_pos(screen, 0, 0);
	//lv_obj_align(m_main, NULL, LV_ALIGN_CENTER, 0, 0);
	// lv_obj_add_style(screen, LV_OBJ_PART_MAIN, &page_style);

	lv_group_add_obj( group, screen );


    meter = lv_meter_create(screen);
    lv_obj_set_size(meter, 280, 280);
	lv_obj_add_event_cb( meter, event_cb, LV_EVENT_ALL, NULL);
    lv_obj_center(meter);
    //删除中心点
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

#define APP_HEART	"HeartBeat"

void GUI_Heart_Init(lv_obj_t *pmain, lv_group_t *group)
{
	lv_obj_t *m_heart = lv_obj_create(pmain);
	lv_obj_set_style_bg_color(m_heart, lv_color_hex(0x343247), 0);
    lv_obj_set_pos(m_heart, 0, 300);
	lv_obj_set_size(m_heart, 280, 280);
	lv_group_add_obj( group, m_heart );
	lv_obj_add_event_cb( m_heart, event_cb, LV_EVENT_ALL, NULL);

	lv_obj_t *lv_title_heart_label = lv_label_create(m_heart);
	lv_label_set_text(lv_title_heart_label,APP_HEART);
	lv_obj_center(lv_title_heart_label);

	// lv_obj_t *lv_title_heart_label = lv_label_create(pmain);
 //    lv_obj_set_pos(lv_title_heart_label, 0, 300);
	// lv_obj_set_size(lv_title_heart_label, 300, 300);
	// lv_obj_add_event_cb( lv_title_heart_label, event_cb, LV_EVENT_ALL, NULL);
	// lv_label_set_text(lv_title_heart_label,APP_HEART);

}

#define APP_SETTING   "Setting"

#define IMG_WIDH        100
#define IMG_HEIGHT      100
#define IMG_NUM         LV_MAX((LV_HOR_RES * LV_VER_RES) / 5 / IMG_WIDH / IMG_HEIGHT, 1)
#define IMG_ZOOM_MIN    128
#define IMG_ZOOM_MAX    (256 + 64)



void GUI_Setting_Init(lv_obj_t *pmain, lv_group_t *group)
{
    lv_obj_t *m_setting = lv_obj_create(pmain);
    lv_obj_set_style_bg_color(m_setting, lv_color_hex(0x343247), 0);
    lv_obj_set_pos(m_setting, 0, 0);//位置
    lv_obj_set_size(m_setting, 280, 280);//大小
    lv_group_add_obj( group, m_setting );
    lv_obj_add_event_cb( m_setting, event_cb, LV_EVENT_ALL, NULL);

    // lv_style_reset(&style_common);
    // lv_style_set_img_opa(&style_common, opa_mode ? LV_OPA_50 : LV_OPA_COVER);

    lv_obj_t * obj = lv_img_create(m_setting);
    //lv_obj_set_size(obj, 200, 200);
    // lv_obj_remove_style_all(obj);
    // lv_obj_add_style(obj, &style_common, 0);
    lv_img_set_src(obj, &img_benchmark_cogwheel_argb);
    lv_obj_center(obj);

    lv_obj_t *lv_title_setting_label = lv_label_create(m_setting);
    lv_obj_remove_style_all(lv_title_setting_label);

    //引用样式会加载新的样式颜色
    lv_obj_add_style(lv_title_setting_label, &style_common, 0);

    lv_label_set_text(lv_title_setting_label,APP_SETTING);
    lv_obj_set_pos(lv_title_setting_label,90,180);//位置
    // lv_obj_t *lv_title_heart_label = lv_label_create(pmain);
 //    lv_obj_set_pos(lv_title_heart_label, 0, 300);
    // lv_obj_set_size(lv_title_heart_label, 300, 300);
    // lv_obj_add_event_cb( lv_title_heart_label, event_cb, LV_EVENT_ALL, NULL);
    // lv_label_set_text(lv_title_heart_label,APP_HEART);

}


void lv_example_meter_5(void)
{
    lv_main = lv_obj_create(lv_scr_act());
    lv_obj_set_size(lv_main, 324, 324);
    lv_obj_center(lv_main);

    //定义样式颜色，引用样式会加载新的样式颜色
    lv_style_init(&style_common);
    //lv_style_set_text_opa(&style_common, LV_OPA_30);//透明度
    lv_style_set_text_color(&style_common, lv_color_white());//字体颜色

    lv_obj_set_style_bg_color(lv_main, lv_color_hex(0x343247), 0);

    GUI_Main_Init(lv_main,NULL);
    //GUI_Heart_Init(lv_main, NULL);
}

#endif
