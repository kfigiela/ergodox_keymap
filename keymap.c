#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "timer.h"

#define BASE  0 // default layer
#define SYMB  1 // symbols
#define SYM2  2
#define MDIA  3 // media keys
#define DENON 4
#define KEYMAP LAYOUT_ergodox

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  `     |   1  |   2  |   3  |   4  |   5  | ENT  |           | BTN2 |   6  |   7  |   8  |   9  |   0  |  ESC   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |  TAB   |   Q  |   W  |   D  |   P  |   G  | ESC  |           | L3   |   J  |   L  |   U  |   Y  |   ;  |  RCTL  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  L1    |   A  |   R  |   S  |   T  |   F  |------|           |------|   M  |   N  |   E  |   I  |   O  |   L1   |
 * |--------+------+------+------+------+------|  L2  |           | L2   |------+------+------+------+------+--------|
 * |  LALT  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   H  |   ,  |   .  | ENT  |  RALT  |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCTL | LALT | LEFT | RIGHT|  SPC |                                       | BSPC | UP   | DOWN | RALT | RCTL |
 *   `----------------------------------'                                       `----------------------------------'
 * OSX:
 *                                        ,-------------.       ,-------------.
 *                                        | RALT |      |       |      | RALT |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      | LCTL |       | RCTL |      |      |
 *                                 |LSHFT | LGUI |------|       |------| RGUI |RSHFT |
 *                                 |      |      | LALT |       | RALT |      |      |
 *                                 `--------------------'       `--------------------'
 *
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*

[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,      KC_2,    KC_3,    KC_4,   KC_5,    KC_BTN1,
        KC_TAB,         KC_Q,      KC_W,    KC_D,    KC_P,   KC_G,    KC_ESC,
        MO(SYMB),       KC_A,      KC_R,    KC_S,    KC_T,   KC_F,
        MO(SYM2),       KC_Z,      KC_X,    KC_C,    KC_V,   KC_B,    MO(MDIA),
        KC_LCTL,        KC_LALT,   KC_LEFT, KC_RGHT, KC_SPC,
                                                       KC_F16,  KC_F17,
                                                                KC_LCTL,
                                              KC_LSFT, KC_LGUI, KC_LALT,
        // right hand
             KC_BTN2,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_ESC,
             MO(DENON),   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_RCTL,
                          KC_M,    KC_N,    KC_E,    KC_I,    KC_O,       MO(SYMB),
             MO(MDIA),    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_ENT,     MO(SYM2),
                                   KC_BSPC, KC_UP,   KC_DOWN, KC_RALT,    KC_RCTL,
             KC_F18,  KC_F19,
             KC_RCTL,
             KC_RALT, KC_RGUI, KC_RSFT
    ),

/*
 *
  !@#$%^&*()
  `~-_;:<>?/\|'"

    >>=     bind
    >>      then
    *>      then
    ->      to                a -> b: a to b
    <-      bind              (as it desugars to >>=)
    <$>     (f)map
    <$      map-replace by    0 <$ f: "f map-replace by 0"
    <*>     ap(ply)           (as it is the same as Control.Monad.ap)
    $                         (none, just as " " [whitespace])
    .       pipe to           a . b: "b pipe-to a"
    !!      index
    !       index / strict    a ! b: "a index b", foo !x: foo strict x
    <|>     or / alternative  expr <|> term: "expr or term"
    ++      concat / plus / append
    []      empty list
    :       cons
    ::      of type / as      f x :: Int: f x of type Int
    \       lambda
    @       as                go ll@(l:ls): go ll as l cons ls
    ~       lazy              go ~(a,b): go lazy pair a, b
 */

/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |   ?  |   @  |   #  |   %  |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   &  |   |  |   \  |   ~  | INS  |           | WH_D |      |   "  |   [  |   ]  |   !  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  ESC   |   /  |   =  |   -  |   :  |   +  |------|           |------|   _  |   '  |   (  |   )  |   ?  |   Tab  |
 * |--------+------+------+------+------+------|      |           | WH_U |------+------+------+------+------+--------|
 * |        |   <  |   *  |   $  |   >  |   ^  |      |           |      |      |   `  |   {  |   }  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      | Home | End  |      |                                       |  Del | PgUp | PgDn |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |  -   |  -   |       |  -   |  -   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 |  -   |  -   |------|       |------|  -   |  -   |
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_NO,   KC_QUES, KC_AT,   KC_HASH, KC_PERC, KC_NO,   KC_NO,
       KC_NO,   KC_EXLM, KC_AMPR, KC_PIPE, KC_BSLS, KC_TILD, KC_INS,
       KC_ESC,  KC_SLSH, KC_EQL,  KC_MINS, KC_COLN, KC_PLUS,
       KC_NO,   KC_LABK, KC_ASTR, KC_DLR,  KC_RABK, KC_CIRC, KC_NO,
       KC_TRNS, KC_TRNS, KC_HOME, KC_END,  KC_TRNS,
                                        KC_TRNS, KC_TRNS,
                                                 KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
       KC_WH_D, KC_PERC, KC_DQUO, KC_LBRC, KC_RBRC, KC_EXLM, KC_NO,
                KC_UNDS, KC_QUOT, KC_LPRN, KC_RPRN, KC_QUES, KC_TAB,
       KC_WH_U, KC_NO,   KC_GRV,  KC_LCBR, KC_RCBR, KC_TRNS, KC_NO,
                         KC_DELT, KC_PGUP, KC_PGDN, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),


/* Keymap 2: Symbol 2 Layer (for Polish Programmers macOS layout)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |   ‚  |   ’  |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  ⌘ [ |  ⌘ ] |  ≥   |  »   |      |      |           |      |      |   ł  |   „  |   ”  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ą  |  ≠   |  ś   |      |      |------|           |------|  «   |   ń  |   ę  |   ≤  |   ó  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   ź  |  ź   |  ć   |      |      |      |           |      |      |   –  |   —  |   …  |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------
 *                                        |  -   |  -   |       |  -   |  -   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 |  -   |  -   |------|       |------|  -   |  -   |
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYM2] = KEYMAP(
       // left hand
       KC_TRNS,   KC_NO,         KC_NO,         KC_NO,         KC_NO,                KC_NO, KC_NO,
       KC_TRNS,   RGUI(KC_LBRC), RGUI(KC_RBRC), RALT(KC_DOT),  RSFT(RALT(KC_BSLS)),  KC_NO, KC_NO,
       KC_NO,     RALT(KC_A),    RALT(KC_EQL),  RALT(KC_S),    KC_NO,                KC_NO,
       KC_NO,     RALT(KC_Z),    RALT(KC_X),    RALT(KC_C),    KC_NO,                KC_NO, KC_NO,
       KC_TRNS,   KC_TRNS,       RALT(KC_LEFT), RALT(KC_RGHT), KC_TRNS,
                                        KC_TRNS,  KC_TRNS,
                                                  KC_TRNS,
                               KC_TRNS, KC_TRNS,  KC_TRNS,
       // right hand
       KC_NO,   KC_NO,         KC_NO,         RALT(KC_RBRC),        RSFT(RALT(KC_RBRC)), KC_NO,         KC_TRNS,
       KC_NO,   KC_NO,         RALT(KC_L),    RALT(KC_LBRC),        RSFT(RALT(KC_LBRC)), KC_NO,         KC_TRNS,
                RALT(KC_BSLS), RALT(KC_N),    RALT(KC_E),           RALT(KC_COMM),       RALT(KC_O),    KC_NO,
       KC_NO,   KC_NO,         RALT(KC_MINS), RSFT(RALT(KC_MINS)),  RALT(KC_SCLN),       KC_NO,         KC_NO,
                               RALT(KC_BSPC), RALT(KC_UP),          RALT(KC_DOWN),       KC_TRNS,       KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,---------------------------------------------------.
 * | NumLk  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10  |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+-------+--------|
 * | PrScr  |      | Lclk | MsUp | Rclk | WhlD |      |           |      |      | ⌥ UP |⌥ LEFT|⌥RIGHT|⌥ DOWN|   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+-------+--------|
 * | Caps   | Play |MsLeft|MsDown|MsRght| WhlU |------|           |------|   +  |   UP |  LEFT| RIGHT|   DOWN|    =   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+-------+--------|
 * |        | Mute | WhlL |      | WhlR |      |      |           |      |   -  | ⌘ UP |⌘ LEFT|⌘RIGHT|⌘ DOWN|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+-------+--------'
 *   |      |      | Prev | Next |  -   |                                       |      |   ,  |   .  |       |      |
 *   `----------------------------------'                                       `-----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | ScLk | Pause|       |  -   |  -   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 |  -   |  -   |------|       |------|  -   |  -   |
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,
       KC_PSCR, KC_NO,   KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_D, KC_NO,
       KC_CAPS, KC_MPLY, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,
       KC_NO, KC_MUTE, KC_WH_L, KC_NO,   KC_WH_R, KC_NO,   KC_NO,
       KC_NO, KC_NO, KC_MPRV, KC_MNXT, KC_TRNS,
                                           KC_SLCK, KC_PAUS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_NO,    KC_F6,   KC_F7,         KC_F8,   KC_F9,  KC_F10,  KC_F11,
       KC_NO,    KC_UP,   LALT(KC_UP),      LALT(KC_LEFT),      LALT(KC_RIGHT),    LALT(KC_DOWN), KC_F12,
                 KC_PLUS, KC_UP,    KC_LEFT,    KC_RIGHT,   KC_DOWN,    KC_EQL,
       KC_NO,    KC_MINS, LGUI(KC_UP),    LGUI(KC_LEFT),    LGUI(KC_RIGHT),   LGUI(KC_DOWN), KC_NO,
                          KC_TRNS, KC_COMM, KC_DOT, KC_NO,   KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 4: Denon
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           | pwr  | net  | radio| opt  | an1  | an2  | cd     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | vol- | vol+ | mute |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| prev | play | next |      |      |        |
 * |--------+------+------+------+------+------|      |           | play |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | pralb| nxalb| disp |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |   ,  |   .  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | br++ | br-- |       |  -   |  -   |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 |  -   |  -   |------|       |------|  -   |  -   |
 *                                 |      |      |  -   |       |  -   |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Denon


#define DN_PWR     RSFT(RALT(KC_F8))
#define DN_NETWORK RSFT(RCTL(KC_F6))
#define DN_RADIO   RSFT(RCTL(KC_F5))
#define DN_OPTICAL RSFT(RALT(KC_F4))
#define DN_ANALOG1 RSFT(RCTL(KC_F3))
#define DN_ANALOG2 RSFT(RALT(KC_F3))
#define DN_CD      RSFT(RCTL(KC_F4))

#define DN_VOLUP   RSFT(RCTL(KC_F12))
#define DN_VOLDOWN RSFT(RCTL(KC_F11))
#define DN_MUTE    RSFT(RCTL(KC_F10))

#define DN_PLAY    RSFT(RCTL(KC_F8))
#define DN_PREV    RSFT(RCTL(KC_F7))
#define DN_NEXTALB RSFT(RALT(KC_F9))
#define DN_PREVALB RSFT(RALT(KC_F7))
#define DN_NEXT    RSFT(RCTL(KC_F9))
#define DN_PLAY    RSFT(RCTL(KC_F8))

#define DN_DISP    RSFT(RCTL(KC_F1))

#define DISP_BRIGHTNESS_DOWN RALT(RCTL(KC_F1))
#define DISP_BRIGHTNESS_UP   RALT(RCTL(KC_F2))

[DENON] = KEYMAP(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                DISP_BRIGHTNESS_DOWN, DISP_BRIGHTNESS_UP,
                                               KC_NO,
                                 KC_NO, KC_NO, KC_NO,
// right hand
    DN_PWR,  DN_NETWORK,   DN_RADIO,   DN_OPTICAL, DN_ANALOG1, DN_ANALOG2, DN_CD,
    KC_NO,   DN_VOLDOWN,   DN_VOLUP,   DN_MUTE,    KC_NO,      KC_NO,      KC_NO,
             DN_PREV,      DN_NEXT,    KC_NO,      KC_NO,      KC_NO,      KC_NO,
    DN_PLAY, DN_PREVALB,   DN_NEXTALB, DN_DISP,    KC_NO,      KC_NO,     KC_NO,
    KC_NO,   KC_NO,        KC_NO,      KC_NO,      KC_NO,
    KC_NO,   KC_NO,
    KC_NO,
    KC_NO,   KC_NO,        KC_NO
),
};


const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

#define caps_led_on  ergodox_right_led_2_on
#define caps_led_off ergodox_right_led_2_off

typedef enum onoff_t {OFF, ON} onoff;

const macro_t *action_get_macro_old(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // MACRODOWN only works in this function
    switch(id) {
        case 0:
            if (record->event.pressed) {
              register_code(KC_RSFT);
            } else {
              unregister_code(KC_RSFT);
            }
        break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

#define BLINK_BASE1_ON   1U
#define BLINK_BASE1_OFF 20U

#define BLINK_BASE2_ON  1U
#define BLINK_BASE2_OFF 5U

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    static onoff board_led_state = OFF;
    static uint16_t dt = 0;
    static uint8_t oldlayer = 0;

    if (oldlayer != layer) {
        // Layer was just toggled.
        if (layer == BASE) {
            ergodox_board_led_off();
            board_led_state = OFF;
        }
    } else if (layer == SYMB) {
        if (board_led_state == OFF) {
            if (timer_elapsed(dt) > BLINK_BASE1_OFF) {
                dt = timer_read();
                ergodox_board_led_on();
                board_led_state = ON;
            }
        } else {
            if (timer_elapsed(dt) > BLINK_BASE1_ON) {
                dt = timer_read();
                ergodox_board_led_off();
                board_led_state = OFF;
            }
        }
    } else if (layer >= SYM2) {
        if (board_led_state == OFF) {
            if (timer_elapsed(dt) > BLINK_BASE2_OFF) {
                dt = timer_read();
                ergodox_board_led_on();
                board_led_state = ON;
            }
        } else {
            if (timer_elapsed(dt) > BLINK_BASE2_ON) {
                dt = timer_read();
                ergodox_board_led_off();
                board_led_state = OFF;
            }
        }
    }
    oldlayer = layer;
}
