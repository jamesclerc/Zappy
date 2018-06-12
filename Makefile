##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile, duh.
##

TARGETS		= server

define rules =
$(1):
	$(MAKE) -C $(1)

clean::
	$(MAKE) -C $(1) clean

fclean::
	$(MAKE) -C $(1) fclean

endef

all: $(TARGETS)

re: fclean all

.PHONY: all re clean fclean $(TARGETS)

.SILENT: all re clean fclean $(TARGETS)

$(foreach target,$(TARGETS),$(eval $(call rules,$(target))))
