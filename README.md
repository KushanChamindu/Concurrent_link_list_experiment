# Concurrent_link_list_experiment

Implement and test link list in C with concurrent programing.


### Serial linked list
Compile: `gcc -g -Wall -o .\link_list_serial .\link_list_serial.c  .\insert.c .\member.c .\delete.c .\functions.c`
Run: .\link_list_serial

### Mutex based linked list
Compile: `gcc -g -Wall -o .\link_list_mutex .\link_list_mutex.c  .\insert.c .\member.c .\delete.c .\functions.c -Ipthread`
Run: .\link_list_mutex <Thread Count>

### Read-write lock based linked list
Compile: `gcc -g -Wall -o .\link_list_rw_lock .\link_list_rw_lock.c  .\insert.c .\member.c .\delete.c .\functions.c -Ipthread`
Run: .\link_list_rw_lock <Thread Count>
