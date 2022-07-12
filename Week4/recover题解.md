fwrite的重写是在文件最后开始添加内容

jpg可能会占很多block，**而不是单个block**，所以需要多判断一下

`char str[3]` 直接取代 `char *str = malloc(3)` 好了，省事

判断第四个字节的时候直接用位运算，更加简洁

