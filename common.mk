# trying to make a better/cleaner makefile

include config.mk

# command to remove files and folders
RM = rm -rf
# command to create folders recursively
MKDIR = mkdir -p
# source files
SRCEXTS = .c .C .cc .cpp .CPP .c++ .cxx .cp
# header files
HDREXTS = .h .H .hh .hpp .HPP .h++ .hxx .hp

ifeq ($(SRCDIRS),)
	SRCDIRS = $(shell find * -type d)
	SRCDIRS += .
endif

# Add debug flag if DEBUG is defined
ifdef DEBUG
  EXTRA_CFLAGS += -D DEBUG -g
  BUILD_PATH := $(BUILD_PATH)/debug
  OBJ_DIR := $(OBJ_DIR)/debug
else
  EXTRA_CFLAGS += -D NDEBUG
  BUILD_PATH := $(BUILD_PATH)/release
  OBJ_DIR := $(OBJ_DIR)/release
endif

#Actually $(INCLUDE) is included in $(CPPFLAGS).
CPPFLAGS += $(INCLUDE)

SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
SRC_CXX = $(filter-out %.c,$(SOURCES))
HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
OBJS    = $(foreach d,$(SOURCES),$(addsuffix .o, $(subst /./,/,$(basename $(OBJ_DIR)/$(d)))))
DEPS    = $(OBJS:.o=.d)

DEPEND.d    = $(CC)  $(EXTRA_CFLAGS) $(CFLAGS)   $(CPPFLAGS)
COMPILE.c   = $(CC)  $(EXTRA_CFLAGS) $(CFLAGS)   $(CPPFLAGS) -c
COMPILE.cxx = $(CXX) $(EXTRA_CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c
LINK.c      = $(CC)  $(EXTRA_CFLAGS) $(CFLAGS)   $(CPPFLAGS) $(LDFLAGS)
LINK.cxx    = $(CXX) $(EXTRA_CFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# no default rules
.SUFFIXES:
# all phony targets
.PHONY: all objs clean distclean help show

all: $(BUILD_PATH)/$(PROJECT_NAME)

# Rules for creating dependency files (.d).
#------------------------------------------
DEPEND_HEADER      = echo -n Creating dependencies for $<...
PRE_DEPEND_COMMAND = $(MKDIR) "$(OBJ_DIR)/$(dir $<)"; printf "$(OBJ_DIR)/$(dir $<)" > $@
DEPEND_COMMAND     = $(DEPEND.d) -MM $< >> $@
DEPEND_FOOTER      = echo Done.

# yup, all uses the same rules
$(OBJ_DIR)/%.d:%.c
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.C
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.cc
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.cpp
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.CPP
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.c++
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.cp
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

$(OBJ_DIR)/%.d:%.cxx
	@$(DEPEND_HEADER)
	@$(PRE_DEPEND_COMMAND)
	@$(DEPEND_COMMAND)
	@$(DEPEND_FOOTER)

# Rules for generating object files (.o).
#----------------------------------------
objs:$(OBJS)

OBJ_HEADER = echo -n Compiling $<...
CREATE_OBJ_FOLDER = $(MKDIR) $(@D)
COMPILE_WITH = $(1) $< -o $@
OBJ_FOOTER = echo Done.

# yup, they're all the same
$(OBJ_DIR)/%.o:%.c
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.c))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.C
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.cc
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.cpp
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.CPP
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.c++
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.cp
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)

$(OBJ_DIR)/%.o:%.cxx
	@$(OBJ_HEADER)
	@$(CREATE_OBJ_FOLDER)
	@$(call COMPILE_WITH,$(COMPILE.cxx))
	@$(OBJ_FOOTER)


# Rules for generating the executable.
#-------------------------------------
ifeq ($(SRC_CXX),)  # C program
  LINKER = $(LINK.c)
else  # C++ program
  LINKER = $(LINK.cxx)
endif

$(BUILD_PATH)/$(PROJECT_NAME):$(OBJS)
	@$(MKDIR) $(BUILD_PATH)
	@echo -n Linking...
	@$(LINKER) $(OBJS) $(EXTRA_LDFLAGS) -o $@
	@echo Done.

clean::
	@echo -n Cleaning up binaries...
	@$(RM) $(OBJS) "$(BUILD_PATH)/$(PROJECT_NAME)" "$(BUILD_PATH)/$(PROJECT_NAME).exe"
	@echo Done.

distclean: clean
	@echo -n Cleaning dependencies data...
	@$(RM) $(DEPS)
	@echo Done.

# don't import deps if we won't use them
ifndef NODEP
  ifneq ($(MAKECMDGOALS), clean)
    ifneq ($(MAKECMDGOALS), distclean)
      ifneq ($(MAKECMDGOALS), show)
        ifneq ($(MAKECMDGOALS), help)
          ifneq ($(DEPS),)
            sinclude $(DEPS)
          endif
        endif
      endif
    endif
  endif
endif


# Show help.
help:
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  NODEP=yes make without generating dependencies.'
	@echo '  objs      compile only (no linking).'
	@echo '  clean     clean objects and the executable file.'
	@echo '  distclean clean objects, the executable and dependencies.'
	@echo '  show      show variables (for debug use only).'
	@echo '  help      print this message.'


# Show variables (for debug use only.)
show:
	@echo 'PROJECT_NAME:' $(PROJECT_NAME)
	@echo 'SRCDIRS     :' $(SRCDIRS)
	@echo 'HEADERS     :' $(HEADERS)
	@echo 'SOURCES     :' $(SOURCES)
	@echo 'SRC_CXX     :' $(SRC_CXX)
	@echo 'OBJS        :' $(OBJS)
	@echo 'DEPS        :' $(DEPS)
	@echo 'DEPEND      :' $(DEPEND)
	@echo 'DEPEND.d    :' $(DEPEND.d)
	@echo 'COMPILE.c   :' $(COMPILE.c)
	@echo 'COMPILE.cxx :' $(COMPILE.cxx)
	@echo 'link.c      :' $(LINK.c)
	@echo 'link.cxx    :' $(LINK.cxx)
	@echo 'BUILD_PATH  :' $(BUILD_PATH)
