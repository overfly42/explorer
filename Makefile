
.PHONY: all
.PHONY: cleanAll
.PHONY: help
.PHONY: create

all:
	@echo Build recursive
cleanAll:
	@echo clean recursive
help:
	@grep -e "^[^\.]*:" Makefile | cut -d":" -f1
create:
	@scripts/create.sh
