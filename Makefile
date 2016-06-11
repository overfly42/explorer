SHELL=/bin/bash

.PHONY: all
.PHONY: cleanAll
.PHONY: help
.PHONY: create
.PHONY: doc

all:
	@echo Build recursive
cleanAll:
	@echo clean recursive
help:
	@grep -e "^[^\.]*:" Makefile | cut -d":" -f1 | sort
#	a=$(LS)
#	$(MAKE) -C $(a)
create:
	@scripts/create.sh

doc:
	@echo Creating Documentation
