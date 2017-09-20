编译原理实验

<!-- TOC -->

- [PASCAL语言子集（PL/0）词法分析器](#pascal语言子集pl0词法分析器)
	- [Keyword](#keyword)
	- [COP(Compare Operators)](#copcompare-operators)
	- [AOP(Assignment Operator)](#aopassignment-operator)
	- [OOP(Operation Operators)](#oopoperation-operators)
	- [EOP(End Operator)](#eopend-operator)
	- [SOP(Sperate Operators)](#sopsperate-operators)
	- [Error Warning](#error-warning)
- [Copyright](#copyright)

<!-- /TOC -->

## PASCAL语言子集（PL/0）词法分析器

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
	> [Program ERROR] [1,25] Invalid ID
- 赋值符号错误：
	> [Program ERROR] [1,27] Missing "=" near the ":" ;

## Copyright

版权信息。

Copyright &copy; 2017 [TripleZ](https://github.com/Triple-Z/)

[MIT License](https://github.com/Triple-Z/CP-Homework/blob/master/LICENSE.md)