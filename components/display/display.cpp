#include "display.h"

#include "led_matrix.h"

static constexpr uint8_t kBootAnimationFrames_ = 8;
static constexpr uint8_t kDirectionAnimationFrames_ = 5;
static constexpr uint8_t kPixelBrightness_ = 1;

static LedMatrix matrix_ {};
static DisplayState current_display_state {};
static DisplayAnimation active_animation_ = DisplayAnimation::NONE;
static DisplayAnimation looping_animation_ = DisplayAnimation::NONE;
static uint32_t display_frame_ = 0;
static uint32_t animation_frame_ = 0;
static bool is_initialized_ = false;

static void renderDisplay();
static void renderState();
static void renderAnimation(DisplayAnimation animation, uint32_t frame);
static bool isOneShotAnimation(DisplayAnimation animation);
static uint32_t oneShotFrameCount(DisplayAnimation animation);
static void finishAnimationFrame();

void displayInit() {
    if (is_initialized_) {
        return;
    }

    matrix_.init();
    is_initialized_ = true;
}

void displaySetState(const DisplayState& display_state) {
    if (!is_initialized_) {
        return;
    }

    current_display_state = display_state;
}

void displayPlayAnimation(DisplayAnimation animation) {
    if (!is_initialized_) {
        return;
    }

    if (animation == DisplayAnimation::NONE) {
        active_animation_ = DisplayAnimation::NONE;
        looping_animation_ = DisplayAnimation::NONE;
        animation_frame_ = 0;
        return;
    }

    if (animation == DisplayAnimation::CONNECTING) {
        looping_animation_ = animation;

        if (active_animation_ == DisplayAnimation::NONE ||
            active_animation_ == DisplayAnimation::CONNECTING) {
            active_animation_ = animation;
            animation_frame_ = 0;
        }
        return;
    }

    active_animation_ = animation;
    animation_frame_ = 0;
}

void displayUpdate() {
    if (!is_initialized_) {
        return;
    }

    renderDisplay();
    display_frame_++;
    finishAnimationFrame();
}

static void renderDisplay() {
    if (active_animation_ != DisplayAnimation::NONE) {
        renderAnimation(active_animation_, animation_frame_);
        return;
    }

    renderState();
}

static void renderState() {
    switch (current_display_state.system_state) {
        case SystemState::BOOT:
            matrix_.clear();
            break;

        case SystemState::CONNECTING:
            matrix_.setColor(0, 0, kPixelBrightness_);
            matrix_.connectionAnimation(display_frame_);
            break;

        case SystemState::CONNECTED:
            matrix_.setColor(0, kPixelBrightness_, 0);
            matrix_.displayIcon(MatrixIcon::OK);
            break;

        case SystemState::SETUP:
            matrix_.setColor(0, kPixelBrightness_, kPixelBrightness_);
            matrix_.displayIcon(MatrixIcon::HEART);
            break;

        case SystemState::DEPARTURES:
            matrix_.setColor(0, kPixelBrightness_, 0);

            if (!current_display_state.has_departure_for_active_direction) {
                matrix_.displayIcon(MatrixIcon::QUESTION);
                break;
            }

            matrix_.displayDeparture(
                current_display_state.departure_text,
                display_frame_
            );
            break;

        case SystemState::NO_DEPARTURES:
            matrix_.setColor(kPixelBrightness_, kPixelBrightness_, 0);
            matrix_.displayIcon(MatrixIcon::QUESTION);
            break;

        case SystemState::API_ERROR:
            matrix_.setColor(kPixelBrightness_, 0, 0);
            matrix_.displayIcon(MatrixIcon::QUESTION);
            break;

        case SystemState::NETWORK_ERROR:
            matrix_.setColor(kPixelBrightness_, 0, 0);
            matrix_.displayIcon(MatrixIcon::CROSS);
            break;
    }
}

static void renderAnimation(DisplayAnimation animation, uint32_t frame) {
    switch (animation) {
        case DisplayAnimation::NONE:
            renderState();
            break;

        case DisplayAnimation::BOOT:
            matrix_.bootAnimation(frame);
            break;

        case DisplayAnimation::CONNECTING:
            matrix_.setColor(0, 0, kPixelBrightness_);
            matrix_.connectionAnimation(frame);
            break;

        case DisplayAnimation::DIRECTION_LEFT:
            matrix_.setColor(0, kPixelBrightness_, 0);
            matrix_.displayIcon(MatrixIcon::ARROW_LEFT);
            break;

        case DisplayAnimation::DIRECTION_RIGHT:
            matrix_.setColor(0, kPixelBrightness_, 0);
            matrix_.displayIcon(MatrixIcon::ARROW_RIGHT);
            break;
    }
}

static bool isOneShotAnimation(DisplayAnimation animation) {
    return animation == DisplayAnimation::BOOT ||
        animation == DisplayAnimation::DIRECTION_LEFT ||
        animation == DisplayAnimation::DIRECTION_RIGHT;
}

static uint32_t oneShotFrameCount(DisplayAnimation animation) {
    switch (animation) {
        case DisplayAnimation::BOOT:
            return kBootAnimationFrames_;

        case DisplayAnimation::DIRECTION_LEFT:
        case DisplayAnimation::DIRECTION_RIGHT:
            return kDirectionAnimationFrames_;

        case DisplayAnimation::NONE:
        case DisplayAnimation::CONNECTING:
            return 0;
    }

    return 0;
}

static void finishAnimationFrame() {
    if (active_animation_ == DisplayAnimation::NONE) {
        return;
    }

    animation_frame_++;

    if (!isOneShotAnimation(active_animation_)) {
        return;
    }

    if (animation_frame_ < oneShotFrameCount(active_animation_)) {
        return;
    }

    if (looping_animation_ != DisplayAnimation::NONE) {
        active_animation_ = looping_animation_;
        animation_frame_ = 0;
        return;
    }

    active_animation_ = DisplayAnimation::NONE;
    animation_frame_ = 0;
}
