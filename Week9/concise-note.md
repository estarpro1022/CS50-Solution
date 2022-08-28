## Flask结构

```
app.py /* 事实上，想叫什么都行 */
requirements.txt	/* required libraries */
static/	/* css, javascript and images */
templates/	/* html */
```


```flask
/* app.py */
from flask import Flask, render_template, request

app = Flask(__name__)	/* 把python文件名传给Flask */

@app.route("/")	# 默认为GET
def index():
	name = request.args.get("name")	# 假如网址里提供了name=David
	return render_template("index.html", name=name)	# 第一个name就是指传入index.html的变量
	
# /网址呈现index.html
```

```html
<!DOCTYPE html>

<html lang="en">
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>
    <body>
        hello, {{ name }}
    </body>
</html>
```

通过大括号的方式引用传入的变量 `{{ name }}`



```python
@app.route("/greet")
def greet():
    name = request.args.get("name", "world")
    return render_template("greet.html", name=name)
```

`request.args.get` 里面的 `name` 是 `name="name"` 的第二个name

`world` 是default value，如果没有提供`name=David`

python的函数后面用的是**冒号**，太久不写都记错成大括号了

上述代码可以理解为`/greet?name=David`的网址用`greet.html`渲染

## Layout

一直写`<!DOCTYPE html>`和后面的`html`很麻烦，想要省步骤，怎么办呢？

可以用布局模板

```html
/* layout.html */
<!DOCTYPE html>

<html>
    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>
    <body>
        {% block body %}{% endblock %}
    </body>
</html>
```

### 如何使用模板

```html
/* index.html */
{% extends "layout.html" %}	// extends，双引号
{% block body %}
	<form action="/greet" method="post">
        <input autocomplete="off" type="text" name="name">
        <input type="submit">
	</form>
{% endblock %}
```

这种使用`%`的模板语言叫做 *Jinja*



`get`会让URL包含信息，`post`不会 

```python
@app.route("/greet", methods=["POST"])
def greet():
    return render_template("greet.html", name=request.form.get("name", "world"))
```

`methods` 是复数，和 `form` 的 `method`有区别

后面用列表，即使只有一个元素。且 `POST` 大写

当方法为post时，获取输入用 `request.form.get`



```html
{% extends "layout.html" %}

{% block body %}
    <h1>Register</h1>
    <form action="/register" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <select name="sport">
            {% for sport in sports %}
            	<option value="{{ sport }}">{{ sport }}</option>
            {% endfor %}
        </select>
        // 下拉框
        
        <input type="submit" value="Register">
    </form>
{% endblock %}
```

`request.form.get("sport")` 就能得到所选运动的名称，名称是 `name` 的值，返回的是 `value` 的值

一定不要忘了`name=""`，因为`request.form.get()` 和 `request.args.get()`都是这样得到值的

* Jinja的使用

for循环：`{% for i in list %}` `{% endfor %}`

可以看到，在for循环里，`sports` 就不需要加大括号了，因为本来就包含在大括号中



`return redirect("/greet")`可以重定向

和`return render_template()` 有所不同，前者是重定向到所属route，顺便执行函数

后者是显示html



* 实现`Deregister`，flask与SQL联动
* deregister的本质就是一个表单，然后把一个input隐藏，保留submit

```html
<form action="/deregister" method="post">
    # 注意此处要有value，要不然得不到id
    <input type="hidden" name="id" value="{{ registrant.id }}">
    <input type="submit" value="Deregister">
</form>
```

```python
@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    db.execute("DELETE FROM registrants WHERE id = ?", id)
    return redirect("/")
```



* email



* session

用于web server记住每个user的信息，比如使用户保持登入状态

server返回`Set-Cookie`

```
HTTP/1.1 200 OK
Content-Type: text/html
Set-Cookie: session=value
...
```

下次浏览器访问相同服务器时，就会把相同的session发过去

```python
if not session.get("name"):
    return redirect("/login")
return render_template("index.html")
# 如果有session记录，就会显示index.html
# 如果没有记录，就会跳转到登录界面
```

```html
<input type="text" name="name" placeholder="Name">
<input type="text" name="password" placeholder="Password">
<input type="submit" value="Register">
```





```python
@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # 注册
    else:
        # render html page
        return render_template("register.html")
# methods为get或post时，做的事不一样
# get显示界面
# post
```





MVC

model-view-controller







