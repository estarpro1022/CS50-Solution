# Html CSS JavaScript

## The Internet

* 服务器端(server-side)：在服务器或云服务上跑
* 客户端(client-side)：在用户本地跑

客户端发送请求，服务器端接收并做出回应，提供服务

* 路由器(router)：接受数据并传送数据，有很多传输方向，由算法决定数据传输方向

* IP(Internet Protocol)地址：`#.#.#.#`，一个`#` 代表数字0到255，即8bit。一个IPv4的地址4字节，32位，最多存储40亿个地址（地球人口都70亿了），但是IPv6存储的地址更多 `s:t:u:v:w:x:y:z` 128位，每个字母代表[0, ffff]，2字节，使用十六进制
  * 有时IPv6不会表示全，`::`代表中间省略了0
* DHCP(Dynamic Host Configuration Protocol): 分给你IP地址。（DHCP普及之前，IP地址由系统管理员手动分配）
* TCP(Transmission Control Protocol)：发送和接受数据的协议。通过**端口**的使用，提供大量服务（HTTP: 80, HTTPS: 443)
  * 当发送体积较大的数据时，会将其拆成多个小块并标序号。如果接收端发现少了小块，就可以再询问。所以要么接受完整的数据，要么干脆不接受
  * UDP：即使少了某块数据，也不影响接受数据。直播、通话时可能会用
* DNS(Domain Name System)：将域名转为IP地址

![](https://pic1.zhimg.com/80/v2-871decb395975926b6721afb80f04118_1440w.png)

有small local DNS，如果真有40亿条信息，那检索很费事

large DNS server就像图书馆，有很多small local DNS，分散管理

* Access Point：简单理解为where to connect to the Internet

解决IPv4不够用的方法有将IP地址给router，然后多台设备连同一个router，避免了IP地址的过度分配



![](https://picx.zhimg.com/80/v2-39f437f39af9ea3aaba438708793ab88_1440w.png)



### IP详解(Internet Protocol)

不要老是记成IP地址

getting information from one machine to another

#### wire

对于network数量少的情况，可以用电线将它们连接。但是数量多或距离远时，wire就不可行了

#### router(intermediate step)

将network与router相连，而不是network之间直接相连

规模小：router比不上wire

规模大：router比wire更节约成本

![](https://pica.zhimg.com/80/v2-5e1588f0a5c0a00e56e3f6f21732262c_1440w.png)

#### connectionless

sender到receiver没有固定的path，正如条条大路通罗马，可以有很多种传输路径的选择



### TCP详解

guarantee delivery of information

TCP常和IP联系在一起

#### port number

每一个机器上的服务、程序都分配一个端口

通过IP address + port，能够识别是什么服务

常见端口：

* FTP(File Transfer Protocol): 21
* SMTP(e-mail): 25
* DNS: 53
* HTTP: 80
* HTTPS: 443

#### TCP/IP process

1. TCP split data and wrap information (like what port) on each packet(TCP layer)
2. IP get data chunks and wrap more information where packet should go(IP layer).
3. destination arrives. take off IP layer and take off TCP layer. 

![image-20220804102412545](C:/Users/estar/AppData/Roaming/Typora/typora-user-images/image-20220804102412545.png)

如果少了packet，TCP会让receiver向sender发送请求，只需要重新发送缺少的packet

## The Web

* HTTP(Hyper Text Transfer Protocol)：规范浏览器和服务器的交流

* HTTPS：HTTP的secure version，将内容加密、
* URL，如 `https://www.example.com/`
  * `https://` 协议
  * 末尾的 `/` ，a request for the default file。有点类似C盘的`/`，也就是说类似根目录
  * `example.com` domain name. `.com` top-level domain name
  * `www` **hostname** or **subdomain**，指向域名的特定服务器，像web server `www`, email server `mail`
  * ``www.example.com` fully qualified domain name



### GET POST

客户端通过HTTP协议发送的两个请求，post是将数据从url中隐去

GET request

```
GET / HTTP/1.1
Host: www.example.com
...
```

successful response

```
HTTP/1.1 200 OK
Content-Type: text/html
...
```

### HTTP headers

`Host: www.example.com` 和 `Content-Type: text/html` 其实是键值对，也是HTTP header

#### 谷歌演示

打开F12开发者模式，输入网址

![](https://pica.zhimg.com/80/v2-e8bc1618424181eb218c1770dbbeaa86_1440w.png)



#### 终端操作

```
$ curl -I -X GET http://harvard.edu/
HTTP/1.1 301 Moved Permanently
Retry-After: 0
Content-Length: 0
Server: Pantheon
Location: https://www.harvard.edu/
...
```

#### 一些状态码

- `200 OK`
- `301 Moved Permanently`
- `302 Found`
- `304 Not Modified`
- `307 Temporary Redirect`
- `401 Unauthorized`
- `403 Forbidden`
- `404 Not Found`
- `418 I'm a Teapot`
  * An April Fool’s joke years ago
- `500 Internal Server Error`
  - Buggy code on a server might result in this status code, like segfaults we might have seen in C.
- `503 Service Unavailable`



## HTML(Hyper Text Markup Language)

html is not a programming language, but rather used to format web pages and tell the browser how to display them.



双击空白处产生新文件，然后ctrl+s保存

简单的示范：

```html
<!DOCTYPE html>

<html lang="en">
    <head>
        <title>
            hello, title
        </title>
    </head>
    <body>
        hello, body
    </body>
</html>
```

`<!DOCTYPE html>` 声明网页遵循html标准

`lang="en"` 是 **attribute**，键值对

![](https://cs50.harvard.edu/x/2022/notes/8/html_structure.png)

rectangular nodes are tags, oval ones are text



在 online vscode 中，run our own web server by `http-server`.

由于port 80已经被vscode占了，新的web server将listen on port 8080

进入如下网址

![](https://pic4.zhimg.com/80/v2-fb77a6f9782d74ee4f07e86df63e2af8_1440w.png)

* 检验html文件是否有效 https://validator.w3.org/



### 语法介绍

* `<p>` `</p>` ：段落

* `<h1>` `<h2>` ... `<h6>` ：标题

* `<ul>` `</ul>` (unordered list)：无序列表
  * `<li>` `</li>` 单个条目

```html
<body>
    <ul>
        <li>foo</li>
        <li>bar</li>
        <li>baz</li>
    </ul>
</body>
```

* `<ol>` `</ol>` (order list)：有序列表
* `<table>` `</table>`：表格
  * `<thead>` `</thead>` 
    * `<tr>` `</tr>`
      * `<th>` `</th>`
  * `<tbody>` `</tbody>`
    * `<tr>` `</tr`
      * `<td>` `</td>`

```html
<body>
    <table>
        <thead>
        	<tr>
            	<th>Name</th>
                <th>Number</th>
            </tr>
        </thead>
        
        <tbody>
        	<tr>
            	<td>Carter</td>
                <td>123</td>
            </tr>
            
            <tr>
            	<td>David</td>
                <td>456</td>
            </tr>
        </tbody>
    </table>
</body>
```

* `<img alt="harvard university" src="harvard.jpg">` 其中 `harvard.jpg` 在当前目录，`src` 也可以指向网址。可以加 `alt` 属性，(acronym: alternative text)  `alt="harvard university"`

* `<video>` `</video>` 

```html
<video autoplay loop muted width="1280">
       <source src="halloween.mp4" type="video/mp4">
</video>
```

* `<iframe src=""></iframe>`: embed another page in ours with an inline frame

```html
<iframe allowfullscreen src="https://www.youtube.com/embed/xvFZjo5PgG0"></iframe>
```

* `<a href="">Name</a> `  hypertext reference

```html
<a href="https://www.harvard.edu">Harvard</a>
```

Name是显示的内容，鼠标悬浮上方，浏览器左下角出现网址。点击Name即可进入连接的网址。警惕网络钓鱼：Name和实际网址并无关联

也可以连接到当前服务器的一些图片`image.html`



## DOM（Document Object Model）

`ctrl+shift+j` 打开控制台窗口

输入 `console.dir(document)` 即可查看文件结构，然后找到children, html, children

![image-20220804105314110](https://picx.zhimg.com/80/v2-3d44a61dadc485cd06a28eedc4a5b559_1440w.png)

![](https://pic1.zhimg.com/80/v2-d37b3f8fbaf0a612895a651381a2e93f_1440w.png)



### jQuery

传统写法

```javascript
document.getElementById('colorDiv').style.backgroundC = 'green'
```

jQuery写法

```jquery
$('#colorDiv').css('background-color', green);
```

















