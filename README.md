Hello World, Linux Kernel Module
================================

A simple examples for Linux kernel module programming.


Build
-----

`/lib/modules/$(shell uname -r)/build` directory should be prepared.  If ready,
move to subdirectory containing Makefile and:

```
$ make
```


Load & Unload
-------------

To load the module, `$ make load`.  To unload, `$ make unload`.  If the module
is not built yet, `$ make load` will do the build for you.


References
==========

For more information, read the kernel documentation about this topic:
https://www.kernel.org/doc/Documentation/kbuild/modules.txt


License
=======

GPL v3


Author
======

SeongJae Park (sj38.park@gmail.com)
