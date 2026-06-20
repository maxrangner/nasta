#include "unity.h"

void test_display_boot_animation_runs_full_length_before_rendering_state(void);
void test_display_direction_animation_finishes_after_state_changes(void);
void test_display_shows_minutes_for_numeric_departure_text(void);
void test_display_shows_minutes_for_nu_departure_text(void);
void test_display_turns_green_after_fixed_orange_band(void);
void test_display_turns_red_at_walk_time_plus_buffer(void);
void test_display_uses_orange_just_above_red_cutoff(void);
void test_display_skips_orange_band_at_low_brightness(void);
void test_display_uses_low_brightness_setting_for_far_departure_colors(void);
void test_display_shows_clock_for_clock_departure_text(void);
void test_display_shows_question_for_unknown_departure_text(void);
void test_display_shows_no_departures_for_empty_selected_direction(void);

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_display_boot_animation_runs_full_length_before_rendering_state);
    RUN_TEST(test_display_direction_animation_finishes_after_state_changes);
    RUN_TEST(test_display_shows_minutes_for_numeric_departure_text);
    RUN_TEST(test_display_shows_minutes_for_nu_departure_text);
    RUN_TEST(test_display_turns_green_after_fixed_orange_band);
    RUN_TEST(test_display_turns_red_at_walk_time_plus_buffer);
    RUN_TEST(test_display_uses_orange_just_above_red_cutoff);
    RUN_TEST(test_display_skips_orange_band_at_low_brightness);
    RUN_TEST(test_display_uses_low_brightness_setting_for_far_departure_colors);
    RUN_TEST(test_display_shows_clock_for_clock_departure_text);
    RUN_TEST(test_display_shows_question_for_unknown_departure_text);
    RUN_TEST(test_display_shows_no_departures_for_empty_selected_direction);

    return UNITY_END();
}
