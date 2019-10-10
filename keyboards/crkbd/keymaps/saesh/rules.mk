BOOTMAGIC_ENABLE   = no     # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE    = no     # Mouse keys(+4700)
EXTRAKEY_ENABLE    = yes    # Audio control and System control(+450)
CONSOLE_ENABLE     = no     # Console for debug(+400)
COMMAND_ENABLE     = no     # Commands for debug and configuration
NKRO_ENABLE        = no     # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE   = no     # Enable keyboard backlight functionality
MIDI_ENABLE        = no     # MIDI controls
AUDIO_ENABLE       = no     # Audio output on port C6
UNICODE_ENABLE     = no     # Unicode
BLUETOOTH_ENABLE   = no     # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE    = no     # Enable WS2812 RGB underlight. Disable for Matrix support or no underlight.
RGB_MATRIX_ENABLE  = WS2812 # Enable RGB Matrix support
SWAP_HANDS_ENABLE  = no     # Enable one-hand typing
TAP_DANCE_ENABLE   = yes
OLED_DRIVER_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

EXTRAFLAGS += -flto

KEYMAP_BRANCH = $(shell \
 git rev-parse --abbrev-ref HEAD 2>/dev/null)

GIT_HASH = $(shell \
 git log --pretty=format:'%h' -n 1 2>/dev/null)

QMK_VERSION_TAG = $(shell \
 git describe --tags --abbrev=0 2>/dev/null)

BUILD_TIMESTAMP = $(shell \
 date '+%Y-%m-%dT%H:%M:%S' 2>/dev/null)

OPT_DEFS += -DKEYMAP_BRANCH=\"$(KEYMAP_BRANCH)\" \
            -DQMK_VERSION_TAG=\"$(QMK_VERSION_TAG)\" \
            -DBUILD_TIMESTAMP=\"$(BUILD_TIMESTAMP)\" \
            -DGIT_HASH=\"$(GIT_HASH)\"

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
    SRC += tapdances.c
endif

ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
    SRC += oled.c
endif