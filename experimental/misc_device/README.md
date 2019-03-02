misc device example
===================

This module is an example module for usage of misc device that inspired from a
task of the eudyptula challenge.  It creates `a_misc_dev` device file under
`/dev/` when it loaded and  remove it when it is unloaded.  Root user can read
/ write to and from the device file.  When it is read, it returns meaningless
keyworkd, `xxxxxxxxxxxx`.  When it is written, if the user is writing
`xxxxxxxxxxxx`, the writing success.  Else if the user is writing strings other
than `xxxxxxxxxxxx`, the writing fails.
