#---------------------------------------------------------------------------------
target		:=	CyberQuest
build		:=	build
sources		:=	source
data		:=	data
includes	:=	include
#---------------------------------------------------------------------------------
topdir ?= $(CURDIR)
include $(DEVKITPRO)/libnds/Makefile.nds
