SRC += saesh.c

ifneq ($(strip $(NO_SECRETS)), yes)
    SRC += secrets.c
endif
