Hello World, Linux Kernel Module
================================


Prepare
-------

Get the linux kernel source code that is used for your current running system.
After that, move to the directory and do `$ make modules_preapre`.


Build
-----

To build this module, you need linux source code that is used for your current
running system.  Also, you should do `$ make modules_prepare` on the path.

Once To build this module, use the command below.

```
$ make -C <path to linux source code> M=$PWD
```


Load & Unload
-------------

To load the module, `# insmod ./hello.ko.  To unload, `# rmmod hello`.


For more information, read the kernel documentation about this topic:
https://www.kernel.org/doc/Documentation/kbuild/modules.txt
