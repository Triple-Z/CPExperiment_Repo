编译原理实验

<!-- TOC -->

- [PASCAL语言子集（PL/0）语法分析器](#pascal语言子集pl0语法分析器)
	- [Input](#input)
	- [Output](#output)
	- [Error Warning](#error-warning)
- [PASCAL语言子集（PL/0）词法分析器](#pascal语言子集pl0词法分析器)
	- [Input](#input-1)
	- [Output](#output-1)
	- [Keyword](#keyword)
	- [COP(Compare Operators)](#copcompare-operators)
	- [AOP(Assignment Operator)](#aopassignment-operator)
	- [OOP(Operation Operators)](#oopoperation-operators)
	- [EOP(End Operator)](#eopend-operator)
	- [SOP(Sperate Operators)](#sopsperate-operators)
	- [Error Warning](#error-warning-1)
- [Copyright](#copyright)

<!-- /TOC -->

## PASCAL语言子集（PL/0）语法分析器

### Input

输入。

词法分析结果文件 `la_output`。

> 注释格式：
> ```makefile
> # 我是一条注释
> 我不是注释
> ```
> 词法错误：
> ```
> ^ 错误的内容
> 错误输出
> ```


输入样例：`见词法分析器的输出样例`。

### Output

输出。

语法分析结果文件 `ga_output`。

### Error Warning

错误提示。




## PASCAL语言子集（PL/0）词法分析器

### Input

输入。

使用 `PL/0` 编写的源程序。

输入样例：

```pascal
progam hhh;
    const er:3, te:=a, tt:=3;
    vr hhh;
begin
    aaa:=26;
end
```

### Output

输出。

词法分析结果文件 `la_output`。

输出样例：
```makefile
# Lexical Analysis Result
# Generate Time: Fri Sep 29 18:40:39 2017
# Program File Name: input
# Language Set: PL/0

progam ID 1 7
hhh ID 1 11
; EOP 1 12
const RESERVED 2 10
er ID 2 13
^ := AOP 2 14
[Lexical ERROR] [2,14] Missing "=" near the ":" ;
3 INT 2 15
, SOP 2 16
te ID 2 19
:= AOP 2 21
a ID 2 22
, SOP 2 23
tt ID 2 26
:= AOP 2 28
3 INT 2 29
; EOP 2 30
vr ID 3 7
hhh ID 3 11
; EOP 3 12
begin RESERVED 4 6
aaa ID 5 8
:= AOP 5 10
26 INT 5 12
; EOP 5 13
end RESERVED 6 4
```

### Keyword

关键字。

`program` | `const` | `var` | `procedure` | `begin` | `if` | `then` | `while` | `call` | `read` | `write` | `end`

### COP(Compare Operators)

比较符。

`=` | `<>` | `<` | `<=` | `>` | `>=`

### AOP(Assignment Operator)

赋值符。

`:=`

### OOP(Operation Operators)

操作符。

`*` | `/` | `+` | `-`

### EOP(End Operator)

结束符。

`;`

### SOP(Sperate Operators)

分隔符。

`(` | `)` | `,`

### Error Warning

错误提示。

- 变量名错误：
	> [Lexical ERROR] [1,25] Invalid ID: "12a"
- 赋值符号错误：
	> [Lexical ERROR] [1,27] Missing "=" near the ":"

## Copyright

版权信息。

Copyright &copy; 2017 [TripleZ](https://github.com/Triple-Z/)

[MIT License](https://github.com/Triple-Z/CP-Homework/blob/master/LICENSE.md)