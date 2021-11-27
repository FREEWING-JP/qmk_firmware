# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = yes          # Audio output

# JOYSTICK_ENABLE = yes       # Joystick Game controller HID Interface
# JOYSTICK_DRIVER = analog    # Stick mode analog or digital
POINTING_DEVICE_ENABLE = yes # Generic Pointer
SRC += analog.c

OLED_ENABLE = yes           # Display Feature
OLED_DRIVER = SSD1306       # OLED SSD1306 128x32
#ifeq ($(strip $(OLED_ENABLE)), yes)
#    OLED_DRIVER_ENABLE = yes
#endif

# LINK_TIME_OPTIMIZATION_ENABLE = yes
LTO_ENABLE = yes # Config Option Link Time Optimization
