SRC += saesh.c

TAP_DANCE_ENABLE=yes

ifneq ($(strip $(NO_SECRETS)), yes)
    SRC += secrets.c
endif
