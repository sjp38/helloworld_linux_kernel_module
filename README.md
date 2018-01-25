Hello World, Linux Kernel Module
================================


Build
-----

```
$ make -C <path to linux build directory> M=$PWD
```

`path to linux build directory` is a path to the directory that you used for
build or `make modules_prepare` of the linux on your system.  It could be
different with linux source code directory if you used `make` with `O=` option.
Or, it can be simply be altered with `/lib/modules/$(shell uname -r)/build` if
the directory is not changed after build and installation.


Load & Unload
-------------

To load the module, `# insmod ./hello.ko.  To unload, `# rmmod hello`.


For more information, read the kernel documentation about this topic:
https://www.kernel.org/doc/Documentation/kbuild/modules.txt
