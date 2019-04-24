CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUDIO_ENABLE = yes
MOUSEKEY_ENABLE = yes
TAP_DANCE_ENABLE = yes

CTPC=yes

EXTRAFLAGS += -flto # see: https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/#link-time-optimization-and-disabling-core-functionality
