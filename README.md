编译原理实验

<!-- TOC -->

- [PASCAL语言子集（PL/0）语法分析器](#pascal语言子集pl0语法分析器)
	- [Input](#input)
	- [Output](#output)
	- [Error Warning](#error-warning)
		- [Keyword Error](#keyword-error)
		- [Identifier Error](#identifier-error)
		- [Type Error](#type-error)
		- [Character Error](#character-error)
		- [Unknown Error](#unknown-error)
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
- [PASCAL语言子集（PL/0）文法](#pascal语言子集pl0文法)
- [Copyright](#copyright)

<!-- /TOC -->

## PASCAL语言子集（PL/0）语法分析器

### Input

输入。

词法分析结果文件 `la_output`。

> 注释格式：
> ```
> # 我是一条注释
> 我不是注释
> ```
> 词法错误：
> ```
> ^ 错误内容
> 错误输出
> ```


输入样例：`见词法分析器的输出样例`。

### Output

输出。

字符流输出。

输出样例：
```
[Lexical ERROR]  [2,12] Invalid ID: "3er"
[Lexical ERROR]  [2,15] Missing "=" near the ":" ;
[Grammar ERROR]  [1,5] Missing word "program"
[Grammar ERROR]  [1,6] Missing identifier after "program"
[Grammar ERROR]  [2,10] Missing end character ";"
[Grammar ERROR]  [2,14] Cannot resolve type "3er"
[Grammar ERROR]  [3,7] Cannot resolve type "va"
[Grammar ERROR]  [7,22] Missing word "do"
```

### Error Warning

错误提示。

#### Keyword Error

关键字错误。

|关键字|丢失|拼写错误|
|:----:|:----:|:----:|
|program||`supported`|
|const||`supported`|
|var||`supported`|
|procedure||`supported`|
|begin|`supported`||
|if|||
|then|`supported`||
|while|||
|do|`supported`||
|call|||
|read|||
|write|||
|end|`supported`||

#### Identifier Error

标识符错误。

|区域|丢失|拼写错误|
|:----:|:----:|:----:|
|program|`supported`|`supported`|
|const|`supported`|`supported`|
|var|`supported`|`supported`|
|procedure|`supported`|`supported`|
|read|`supported`|`supported`|

#### Type Error

类型错误。

|类型|拼写错误|
|:----:|:----:|
|const|`supported`|
|var|`supported`|

#### Character Error

符号错误。

|区域|符号|丢失|
|:----:|:----:|:----:|
|program|;|`supported`|
|const|:=|`supported`|
|	|,|`supported`|
|	|;|`supported`|
|var|,|`supported`|
|	|;|`supported`|
|procedure|(|`supported`|
|	|)|`supported`|
|	|;|`supported`|
|read|(|`supported`|
|	|)|`supported`|
|write|(|`supported`|
|	|)|`supported`|

#### Unknown Error

未知错误。

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
```
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

`program` , `const` , `var` , `procedure` , `begin` , `if` , `then` , `while` , `call` , `read` , `write` , `end` , `do` .

### COP(Compare Operators)

比较符。

`=` , `<>` , `<` , `<=` , `>` , `>=`

### AOP(Assignment Operator)

赋值符。

`:=`

### OOP(Operation Operators)

操作符。

`*` , `/` , `+` , `-`

### EOP(End Operator)

结束符。

`;`

### SOP(Sperate Operators)

分隔符。

`(` , `)` , `,`

### Error Warning

错误提示。

- 变量名错误：
	> [Lexical ERROR] [1,25] Invalid ID: "12a"
- 赋值符号错误：
	> [Lexical ERROR] [1,27] Missing "=" near the ":"

## PASCAL语言子集（PL/0）文法

```
<prog> → program <id>; <block>
<block> → [<condecl>][<vardecl>][<proc>]<body>
<condecl> → const <const>{,<const>}; // 可以是一个集合
<const> → <id>:=<integer> 
<vardecl> → var <id>{,<id>};
<proc> → procedure <id>（<id>{,<id>}）;<block>{;<proc>}
<body> → begin <statement>{;<statement>}end
<statement> → <id> := <exp>
               |if <lexp> then <statement>[else <statement>]
               |while <lexp> do <statement>
               |call <id>[（<exp>{,<exp>}）]
               |<body>
               |read (<id>{，<id>})
               |write (<exp>{,<exp>})
<lexp> → <exp> <lop> <exp>|odd <exp>
<exp> → [+|-]<term>{<aop><term>}
<term> → <factor>{<mop><factor>}
<factor>→<id>|<integer>|(<exp>)
<lop> → =|<>|<|<=|>|>=
<aop> → +|-
<mop> → *|/
<id> → l{l|d}   （注：l表示字母）
<integer> → d{d}
```

## Copyright

版权信息。

Copyright &copy; 2017 [TripleZ](https://github.com/Triple-Z/)

[MIT License](https://github.com/Triple-Z/CP-Homework/blob/master/LICENSE.md)
