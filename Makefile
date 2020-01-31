#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES =

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm

# define the C source files
# SRCS = main.c graph.c pq.c dijkstra.c general.c hashmap.c airports.c
SRCS = weight.c graph.c pq.c general.c hashmap.c airports.c sp_algorithms.c shortest_path.c

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file
MAIN = ap sp

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all:    $(MAIN)

$(MAIN): $(OBJS)

$(MAIN): %: %.o
	$(CC) $(CFLAGS) $(INCLUDES) $< $(OBJS) $(LFLAGS) $(LIBS) -o $@

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN) Makefile.bak

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

weight.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
weight.o: /usr/include/sys/_symbol_aliasing.h
weight.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
weight.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
weight.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
weight.o: /usr/include/i386/_types.h
weight.o: /usr/include/sys/_pthread/_pthread_types.h
weight.o: /usr/include/sys/_types/_va_list.h
weight.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
weight.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
weight.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
weight.o: /usr/include/secure/_common.h /usr/include/stdlib.h
weight.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
weight.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
weight.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
weight.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
weight.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
weight.o: /usr/include/sys/_pthread/_pthread_attr_t.h
weight.o: /usr/include/sys/_types/_sigaltstack.h
weight.o: /usr/include/sys/_types/_ucontext.h
weight.o: /usr/include/sys/_types/_sigset_t.h
weight.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
weight.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
weight.o: /usr/include/sys/_types/_int16_t.h
weight.o: /usr/include/sys/_types/_int32_t.h
weight.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
weight.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
weight.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
weight.o: /usr/include/sys/_types/_uintptr_t.h
weight.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
weight.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
weight.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
weight.o: /usr/include/libkern/_OSByteOrder.h
weight.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
weight.o: /usr/include/sys/_types/_ct_rune_t.h
weight.o: /usr/include/sys/_types/_rune_t.h
weight.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
weight.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
weight.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
weight.o: /usr/include/sys/_types/_rsize_t.h
weight.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
weight.o: /usr/include/secure/_string.h /usr/include/assert.h
weight.o: /usr/include/limits.h /usr/include/machine/limits.h
weight.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
weight.o: /usr/include/sys/syslimits.h /usr/include/math.h general.h weight.h
graph.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
graph.o: /usr/include/sys/_symbol_aliasing.h
graph.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
graph.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
graph.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
graph.o: /usr/include/i386/_types.h
graph.o: /usr/include/sys/_pthread/_pthread_types.h
graph.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
graph.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
graph.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
graph.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
graph.o: /usr/include/stdlib.h /usr/include/sys/wait.h
graph.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
graph.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
graph.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
graph.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
graph.o: /usr/include/mach/i386/_structs.h
graph.o: /usr/include/sys/_pthread/_pthread_attr_t.h
graph.o: /usr/include/sys/_types/_sigaltstack.h
graph.o: /usr/include/sys/_types/_ucontext.h
graph.o: /usr/include/sys/_types/_sigset_t.h /usr/include/sys/_types/_uid_t.h
graph.o: /usr/include/sys/resource.h /usr/include/stdint.h
graph.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
graph.o: /usr/include/sys/_types/_int32_t.h
graph.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
graph.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
graph.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
graph.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
graph.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
graph.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
graph.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
graph.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
graph.o: /usr/include/sys/_types/_ct_rune_t.h
graph.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
graph.o: /usr/include/machine/types.h /usr/include/i386/types.h
graph.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
graph.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
graph.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
graph.o: /usr/include/secure/_string.h /usr/include/assert.h
graph.o: /usr/include/limits.h /usr/include/machine/limits.h
graph.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
graph.o: /usr/include/sys/syslimits.h /usr/include/math.h general.h graph.h
graph.o: weight.h
pq.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
pq.o: /usr/include/sys/_symbol_aliasing.h
pq.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
pq.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
pq.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
pq.o: /usr/include/i386/_types.h /usr/include/sys/_pthread/_pthread_types.h
pq.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
pq.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
pq.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
pq.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
pq.o: /usr/include/stdlib.h /usr/include/sys/wait.h
pq.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
pq.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
pq.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
pq.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
pq.o: /usr/include/mach/i386/_structs.h
pq.o: /usr/include/sys/_pthread/_pthread_attr_t.h
pq.o: /usr/include/sys/_types/_sigaltstack.h
pq.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/_types/_sigset_t.h
pq.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
pq.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
pq.o: /usr/include/sys/_types/_int16_t.h /usr/include/sys/_types/_int32_t.h
pq.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
pq.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
pq.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
pq.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
pq.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
pq.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
pq.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
pq.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
pq.o: /usr/include/sys/_types/_ct_rune_t.h /usr/include/sys/_types/_rune_t.h
pq.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
pq.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
pq.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
pq.o: /usr/include/sys/_types/_rsize_t.h /usr/include/sys/_types/_errno_t.h
pq.o: /usr/include/strings.h /usr/include/secure/_string.h
pq.o: /usr/include/assert.h general.h graph.h /usr/include/limits.h
pq.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
pq.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h weight.h pq.h
general.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
general.o: /usr/include/sys/_symbol_aliasing.h
general.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
general.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
general.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
general.o: /usr/include/i386/_types.h
general.o: /usr/include/sys/_pthread/_pthread_types.h
general.o: /usr/include/sys/_types/_va_list.h
general.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
general.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
general.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
general.o: /usr/include/secure/_common.h /usr/include/stdlib.h
general.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
general.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
general.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
general.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
general.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
general.o: /usr/include/sys/_pthread/_pthread_attr_t.h
general.o: /usr/include/sys/_types/_sigaltstack.h
general.o: /usr/include/sys/_types/_ucontext.h
general.o: /usr/include/sys/_types/_sigset_t.h
general.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
general.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
general.o: /usr/include/sys/_types/_int16_t.h
general.o: /usr/include/sys/_types/_int32_t.h
general.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
general.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
general.o: /usr/include/_types/_uint64_t.h
general.o: /usr/include/sys/_types/_intptr_t.h
general.o: /usr/include/sys/_types/_uintptr_t.h
general.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
general.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
general.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
general.o: /usr/include/libkern/_OSByteOrder.h
general.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
general.o: /usr/include/sys/_types/_ct_rune_t.h
general.o: /usr/include/sys/_types/_rune_t.h
general.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
general.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
general.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
general.o: /usr/include/sys/_types/_rsize_t.h
general.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
general.o: /usr/include/secure/_string.h /usr/include/assert.h general.h
hashmap.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
hashmap.o: /usr/include/sys/_symbol_aliasing.h
hashmap.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
hashmap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
hashmap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
hashmap.o: /usr/include/i386/_types.h
hashmap.o: /usr/include/sys/_pthread/_pthread_types.h
hashmap.o: /usr/include/sys/_types/_va_list.h
hashmap.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
hashmap.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
hashmap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
hashmap.o: /usr/include/secure/_common.h /usr/include/stdlib.h
hashmap.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
hashmap.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
hashmap.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
hashmap.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
hashmap.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
hashmap.o: /usr/include/sys/_pthread/_pthread_attr_t.h
hashmap.o: /usr/include/sys/_types/_sigaltstack.h
hashmap.o: /usr/include/sys/_types/_ucontext.h
hashmap.o: /usr/include/sys/_types/_sigset_t.h
hashmap.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
hashmap.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
hashmap.o: /usr/include/sys/_types/_int16_t.h
hashmap.o: /usr/include/sys/_types/_int32_t.h
hashmap.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
hashmap.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
hashmap.o: /usr/include/_types/_uint64_t.h
hashmap.o: /usr/include/sys/_types/_intptr_t.h
hashmap.o: /usr/include/sys/_types/_uintptr_t.h
hashmap.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
hashmap.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
hashmap.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
hashmap.o: /usr/include/libkern/_OSByteOrder.h
hashmap.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
hashmap.o: /usr/include/sys/_types/_ct_rune_t.h
hashmap.o: /usr/include/sys/_types/_rune_t.h
hashmap.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
hashmap.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
hashmap.o: /usr/include/sys/_types/_mode_t.h /usr/include/ctype.h
hashmap.o: /usr/include/runetype.h /usr/include/sys/_types/_wint_t.h
hashmap.o: /usr/include/assert.h /usr/include/string.h
hashmap.o: /usr/include/sys/_types/_rsize_t.h
hashmap.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
hashmap.o: /usr/include/secure/_string.h /usr/include/math.h hashmap.h
hashmap.o: general.h
airports.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
airports.o: /usr/include/sys/_symbol_aliasing.h
airports.o: /usr/include/sys/_posix_availability.h
airports.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
airports.o: /usr/include/_types.h /usr/include/sys/_types.h
airports.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
airports.o: /usr/include/sys/_pthread/_pthread_types.h
airports.o: /usr/include/sys/_types/_va_list.h
airports.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
airports.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
airports.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
airports.o: /usr/include/secure/_common.h /usr/include/stdlib.h
airports.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
airports.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
airports.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
airports.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
airports.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
airports.o: /usr/include/sys/_pthread/_pthread_attr_t.h
airports.o: /usr/include/sys/_types/_sigaltstack.h
airports.o: /usr/include/sys/_types/_ucontext.h
airports.o: /usr/include/sys/_types/_sigset_t.h
airports.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
airports.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
airports.o: /usr/include/sys/_types/_int16_t.h
airports.o: /usr/include/sys/_types/_int32_t.h
airports.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
airports.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
airports.o: /usr/include/_types/_uint64_t.h
airports.o: /usr/include/sys/_types/_intptr_t.h
airports.o: /usr/include/sys/_types/_uintptr_t.h
airports.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
airports.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
airports.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
airports.o: /usr/include/libkern/_OSByteOrder.h
airports.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
airports.o: /usr/include/sys/_types/_ct_rune_t.h
airports.o: /usr/include/sys/_types/_rune_t.h
airports.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
airports.o: /usr/include/i386/types.h /usr/include/sys/_types/_dev_t.h
airports.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
airports.o: /usr/include/sys/_types/_rsize_t.h
airports.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
airports.o: /usr/include/secure/_string.h /usr/include/assert.h
airports.o: /usr/include/math.h hashmap.h general.h graph.h
airports.o: /usr/include/limits.h /usr/include/machine/limits.h
airports.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
airports.o: /usr/include/sys/syslimits.h weight.h airports.h
sp_algorithms.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
sp_algorithms.o: /usr/include/sys/_symbol_aliasing.h
sp_algorithms.o: /usr/include/sys/_posix_availability.h
sp_algorithms.o: /usr/include/Availability.h
sp_algorithms.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
sp_algorithms.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
sp_algorithms.o: /usr/include/i386/_types.h
sp_algorithms.o: /usr/include/sys/_pthread/_pthread_types.h
sp_algorithms.o: /usr/include/sys/_types/_va_list.h
sp_algorithms.o: /usr/include/sys/_types/_size_t.h
sp_algorithms.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
sp_algorithms.o: /usr/include/sys/_types/_off_t.h
sp_algorithms.o: /usr/include/sys/_types/_ssize_t.h
sp_algorithms.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
sp_algorithms.o: /usr/include/stdlib.h /usr/include/sys/wait.h
sp_algorithms.o: /usr/include/sys/_types/_pid_t.h
sp_algorithms.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
sp_algorithms.o: /usr/include/sys/appleapiopts.h
sp_algorithms.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
sp_algorithms.o: /usr/include/machine/_mcontext.h
sp_algorithms.o: /usr/include/i386/_mcontext.h
sp_algorithms.o: /usr/include/mach/i386/_structs.h
sp_algorithms.o: /usr/include/sys/_pthread/_pthread_attr_t.h
sp_algorithms.o: /usr/include/sys/_types/_sigaltstack.h
sp_algorithms.o: /usr/include/sys/_types/_ucontext.h
sp_algorithms.o: /usr/include/sys/_types/_sigset_t.h
sp_algorithms.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
sp_algorithms.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
sp_algorithms.o: /usr/include/sys/_types/_int16_t.h
sp_algorithms.o: /usr/include/sys/_types/_int32_t.h
sp_algorithms.o: /usr/include/sys/_types/_int64_t.h
sp_algorithms.o: /usr/include/_types/_uint8_t.h
sp_algorithms.o: /usr/include/_types/_uint16_t.h
sp_algorithms.o: /usr/include/_types/_uint32_t.h
sp_algorithms.o: /usr/include/_types/_uint64_t.h
sp_algorithms.o: /usr/include/sys/_types/_intptr_t.h
sp_algorithms.o: /usr/include/sys/_types/_uintptr_t.h
sp_algorithms.o: /usr/include/_types/_intmax_t.h
sp_algorithms.o: /usr/include/_types/_uintmax_t.h
sp_algorithms.o: /usr/include/sys/_types/_timeval.h
sp_algorithms.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
sp_algorithms.o: /usr/include/sys/_endian.h
sp_algorithms.o: /usr/include/libkern/_OSByteOrder.h
sp_algorithms.o: /usr/include/libkern/i386/_OSByteOrder.h
sp_algorithms.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
sp_algorithms.o: /usr/include/sys/_types/_rune_t.h
sp_algorithms.o: /usr/include/sys/_types/_wchar_t.h
sp_algorithms.o: /usr/include/machine/types.h /usr/include/i386/types.h
sp_algorithms.o: /usr/include/sys/_types/_dev_t.h
sp_algorithms.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
sp_algorithms.o: /usr/include/sys/_types/_rsize_t.h
sp_algorithms.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
sp_algorithms.o: /usr/include/secure/_string.h /usr/include/assert.h graph.h
sp_algorithms.o: /usr/include/limits.h /usr/include/machine/limits.h
sp_algorithms.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
sp_algorithms.o: /usr/include/sys/syslimits.h weight.h pq.h general.h
sp_algorithms.o: sp_algorithms.h shortest_path.h
shortest_path.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
shortest_path.o: /usr/include/sys/_symbol_aliasing.h
shortest_path.o: /usr/include/sys/_posix_availability.h
shortest_path.o: /usr/include/Availability.h
shortest_path.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
shortest_path.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
shortest_path.o: /usr/include/i386/_types.h
shortest_path.o: /usr/include/sys/_pthread/_pthread_types.h
shortest_path.o: /usr/include/sys/_types/_va_list.h
shortest_path.o: /usr/include/sys/_types/_size_t.h
shortest_path.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
shortest_path.o: /usr/include/sys/_types/_off_t.h
shortest_path.o: /usr/include/sys/_types/_ssize_t.h
shortest_path.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
shortest_path.o: /usr/include/stdlib.h /usr/include/sys/wait.h
shortest_path.o: /usr/include/sys/_types/_pid_t.h
shortest_path.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
shortest_path.o: /usr/include/sys/appleapiopts.h
shortest_path.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
shortest_path.o: /usr/include/machine/_mcontext.h
shortest_path.o: /usr/include/i386/_mcontext.h
shortest_path.o: /usr/include/mach/i386/_structs.h
shortest_path.o: /usr/include/sys/_pthread/_pthread_attr_t.h
shortest_path.o: /usr/include/sys/_types/_sigaltstack.h
shortest_path.o: /usr/include/sys/_types/_ucontext.h
shortest_path.o: /usr/include/sys/_types/_sigset_t.h
shortest_path.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
shortest_path.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
shortest_path.o: /usr/include/sys/_types/_int16_t.h
shortest_path.o: /usr/include/sys/_types/_int32_t.h
shortest_path.o: /usr/include/sys/_types/_int64_t.h
shortest_path.o: /usr/include/_types/_uint8_t.h
shortest_path.o: /usr/include/_types/_uint16_t.h
shortest_path.o: /usr/include/_types/_uint32_t.h
shortest_path.o: /usr/include/_types/_uint64_t.h
shortest_path.o: /usr/include/sys/_types/_intptr_t.h
shortest_path.o: /usr/include/sys/_types/_uintptr_t.h
shortest_path.o: /usr/include/_types/_intmax_t.h
shortest_path.o: /usr/include/_types/_uintmax_t.h
shortest_path.o: /usr/include/sys/_types/_timeval.h
shortest_path.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
shortest_path.o: /usr/include/sys/_endian.h
shortest_path.o: /usr/include/libkern/_OSByteOrder.h
shortest_path.o: /usr/include/libkern/i386/_OSByteOrder.h
shortest_path.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
shortest_path.o: /usr/include/sys/_types/_rune_t.h
shortest_path.o: /usr/include/sys/_types/_wchar_t.h
shortest_path.o: /usr/include/machine/types.h /usr/include/i386/types.h
shortest_path.o: /usr/include/sys/_types/_dev_t.h
shortest_path.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
shortest_path.o: /usr/include/sys/_types/_rsize_t.h
shortest_path.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
shortest_path.o: /usr/include/secure/_string.h /usr/include/assert.h graph.h
shortest_path.o: /usr/include/limits.h /usr/include/machine/limits.h
shortest_path.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
shortest_path.o: /usr/include/sys/syslimits.h weight.h pq.h general.h
shortest_path.o: shortest_path.h sp_algorithms.h
