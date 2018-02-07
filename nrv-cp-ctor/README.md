nm ./nrv | c++filt
nm ./no-nrv | c++filt

//The vptr is not copied from the source object, but has to be initialized to point to the virtual table of the destination class. Therefore, a straight "memcpy" copy from source to destination is not possible.

//https://stackoverflow.com/questions/28260322/what-does-a-non-trivial-copy-constructor-do


