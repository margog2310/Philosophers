set height unlimited
set pagination off
set confirm off

set trace-commands on
set print inferior-events on

set sysroot /

br main

set mem inaccessible-by-default off
set follow-fork-mode parent
#set follow-fork-mode child
#set follow-exec-mode new
set follow-exec-mode old
set detach-on-fork off
catch fork

#Links:
#  - https://sourceware.org/gdb/onlinedocs/gdb/Forks.html
#  - https://sourceware.org/gdb/onlinedocs/gdb/Inferiors-and-Programs.html