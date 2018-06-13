Hello World, Linux Kernel Module
================================

A simple example code for Linux kernel module programming.


Build
-----

`/lib/modules/$(shell uname -r)/build` directory should be prepared.  If ready,
just use the command:

```
$ make
```


Load & Unload
-------------

To load the module, `# insmod ./hello.ko`.  To unload, `# rmmod hello`.


For more information, read the kernel documentation about this topic:
https://www.kernel.org/doc/Documentation/kbuild/modules.txt


License
=======

GPL v3


Author
======

SeongJae Park (sj38.park@gmail.com)
