DC = dmd
MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))
DFLAGS = -unittest -main
