## filter题解

### round函数——四舍五入

包含在`#include <math.h>` 中，返回一个**double**值

括号里记得提供一个**浮点数**，`round(10 / 3)` 就没什么用

保存到一个int类型的值时，可以直接省略前缀`(int)` `int a = round(10 / 3.0)` 

### 连等

赋值语句是有返回值的

`a = b = 3` 而不用拆开来写

### reflect的实现

最初是创建一个新的二维数组，然后修改原数组

但是发现别人的方法更好

```C
for (int i = 0; i < height; i++) {
    for (int j = 0; j < (width + 1) / 2; j++) {
        RGBTRIPLE tmp = image[i][width - 1 - j];
        image[i][width - 1 - j] = image[i][j];
        image[i][j] = tmp;
    }
}
```

### 结构体可以直接赋值，参考上述代码



