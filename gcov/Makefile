TOP=$(abspath ..)
include $(TOP)/defs.mak

CC = $(MUSL_GCC)

TARGET=$(LIBDIR)/libgcov_musl.a

LIBNAME=libgcov_musl.a
CONTAINER_NAME=gcov.myst.apline.122020
CONTAINER_IMAGE_FLAVOR=alpine
CONTAINER_IMAGE_VERSION=3.8
GCOV_GCC_VERSION=7.5.0

CFLAGS = $(DEFAULT_CFLAGS)

LOCAL += fopen
LOCAL += fdopen
LOCAL += fread
LOCAL += fwrite
LOCAL += fseek
LOCAL += ftell
LOCAL += fclose
LOCAL += setbuf
LOCAL += open
LOCAL += close
LOCAL += fcntl
LOCAL += malloc
LOCAL += free
LOCAL += memset
LOCAL += memcpy
LOCAL += strlen
LOCAL += strcpy
LOCAL += getenv
LOCAL += __errno_location
LOCAL += getpid
LOCAL += strtol
LOCAL += access
LOCAL += mkdir
LOCAL += abort
LOCAL += vfprintf
LOCAL += fprintf
LOCAL += atoi
LOCAL += stderr

INCLUDES = $(DEFAULT_INCLUDES)

all: $(TARGET)

compile-gcc:
	@echo Build GCC $(GCOV_GCC_VERSION) in container
	docker build -t $(CONTAINER_NAME) . \
	--build-arg IMAGE_FLAVOR=$(CONTAINER_IMAGE_FLAVOR) \
	--build-arg IMAGE_VERSION=$(CONTAINER_IMAGE_VERSION) \
	--build-arg GCC_VERSION=$(GCOV_GCC_VERSION)

gen-libgcov: compile-gcc
	$(shell sleep 10s)
	$(eval CONTAINER_ID:=$(shell docker run -it --rm --detach $(CONTAINER_NAME))) 
	@echo The container ID is:$(CONTAINER_ID)
	docker cp $(CONTAINER_ID):/gcc-$(GCOV_GCC_VERSION)/host-x86_64-alpine-linux-musl/gcc/libgcov.a $(CURDIR)/$(LIBNAME)
	docker stop $(CONTAINER_ID)

$(TARGET):
ifeq (,$(wildcard $(CURDIR)/$(LIBNAME)))
	$(MAKE) gen-libgcov
endif
	mkdir -p $(LIBDIR)
	mkdir -p $(SUBOBJDIR)
	cp $(LIBNAME) $(TARGET)
	$(CC) $(CFLAGS) $(INCLUDES) -c gcov_libc.c -o $(SUBOBJDIR)/gcov_libc.o
	ar r $(TARGET) $(SUBOBJDIR)/gcov_libc.o
	ar d $(TARGET) _gcov_fork.o
	ar d $(TARGET) _gcov_execl.o
	ar d $(TARGET) _gcov_execlp.o
	ar d $(TARGET) _gcov_execle.o
	ar d $(TARGET) _gcov_execv.o
	ar d $(TARGET) _gcov_execvp.o
	ar d $(TARGET) _gcov_execve.o
	ld -relocatable -o $(SUBOBJDIR)/gcov.o --whole-archive $(TARGET)
	objcopy $(addprefix -L,$(LOCAL)) $(SUBOBJDIR)/gcov.o
	rm -rf $(TARGET)
	ar rv $(TARGET) $(SUBOBJDIR)/gcov.o

clean:
	rm -f $(TARGET) $(SUBOBJDIR)/gcov.o $(SUBOBJDIR)/gcov_libc.o

tests:

nm:
	nm -g $(TARGET)

ar:
	ar tv $(LIBNAME)
