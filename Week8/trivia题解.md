## Multiple Choice

点击正确答案，显示绿色，底部correct

点击错误答案，显示红色，底部incorrect

通过对每一个按钮都添加监听，来判断是否点击正确答案

```html
document.querySelector('.true').addEventListener('click', function() {
...
})
```

是`querySelector` 不是`querySelect`，得到一个对象后，有后缀`style` `innerHTML` `value`

比如选到了正确答案，就用`.style.color='green'`

调整下方文本需要提前写`<p id='check'></p>`，然后`document.getElementById('check').innerHTML = "correct!"`



==对这些后缀很不熟悉==，cs50没有提示简直痛苦。改用IDEA开发



## Free response

找到`form`(不能找submit)，监听`submit`

```html
document.querySelector('form').addEventListener('submit', function() {
...
})
```

读用户输入的内容

`document.getElementById('formCheck').value`

