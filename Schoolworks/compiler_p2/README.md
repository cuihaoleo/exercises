# 编译原理 实验2

## 问题描述

对正规式进行词法分析和语法分析，输出分析树和语法树。

这里所说的正规式，字母表包含大小写拉丁字母、阿拉伯数字和句点（``[0-9a-zA-Z.]``）。运算包括**闭包**（``R*``）、**连接**（``RS``）和**选择**（``R|S``），这些运算都是左结合且优先级依次递减。另外**圆括号**可以用来调整运算顺序。

## 程序使用

装好 bison、flex 和 gcc，直接 make 即可。生成的可执行文件为 ``bin/regex``。

### 示例
```
$ echo "a|(bc)*" | bin/regex
Parse Tree:
|-regex
  |-concat
  | |-atom
  |   |-CHAR(a)
  |-OP_OR
  |-regex
    |-concat
      |-atom
        |-atom
        | |-OP_LPAREN
        | |-regex
        | | |-concat
        | |   |-atom
        | |   | |-CHAR(b)
        | |   |-OP_CONCAT
        | |   |-concat
        | |     |-atom
        | |       |-CHAR(c)
        | |-OP_RPAREN
        |-OP_STAR

Syntax Tree:
|-OP_OR
  |-CHAR(a)
  |-OP_STAR
    |-OP_CONCAT
      |-CHAR(b)
      |-CHAR(c)
```

## 代码说明

### 数据结构
``src/tree_node.{c,h}`` 实现了一个简单的树。以下是树节点的定义：

```c
typedef struct st_tree_node {
    char *name;  // 输出中显示的节点名称
    int n_children;  // 子节点数量
    struct st_tree_node **children;  // 到子节点的指针组成的数组
} TreeNode;
```

为树实现了构造节点、递归销毁节点和打印操作：

- ``TreeNode* mkNode(const char* name, int n_children, ...)`` **构造新节点**
  形式参数与 ``TreeNode`` 成员一一对应。最后的可变参数，应给出 ``n_children`` 个指针 ``TreeNode*``，表示各子节点。
- ``TreeNode* mkLeaf(const char* name)`` **构造新的叶节点**
  实际上是 ``mkNode(name, 0)`` 的一个缩略写法。
- ``void destroyTree(TreeNode *node)`` **销毁节点**
  将递归地释放节点及其所有子节点占用的内存。
- ``printTree(const TreeNode root)`` **输出树**
  以一种代码简单又保证可读性的形式打印以 ``root`` 为根的树。

### 词法分析

定义以下终结符：

- **EOL**: 行结束符
- **LPAREN**, **RPAREN**: 左右圆括号
- **CHARACTOR**: 正规式字母表中的字符
- **OR**: 选择运算符
- **STAR**: 闭包运算符
- **UNKNOWN**: 其他未知字符

相应的 lex 规则：
```c
%%
[a-zA-Z0-9.] {
    yylval.charactor = *yytext;
    return CHARACTOR;
}
"|"        return OR;
"*"        return STAR;
"("        return LPAREN;
")"        return RPAREN;
\n         return EOL;
<<EOF>>    return EOL;
.          return UNKNOWN;
%%
```

### 语法制导翻译

#### 文法
使用无二义的右递归文法：

- *input*: *regex* **EOL**
- *regex*: *concat* **OR** *regex*
- *regex*: *concat*
- *concat*: *atom* *concat*
- *concat*: *atom*
- *atom*: *atom* **STAR**
- *atom*: **LPAREN** *regex* **RPAREN**
- *atom*: **CHARACTOR**

#### 属性

为终结符 **CHARACTOR** 记录 ``char`` 型的综合属性 ``charactor``，以区别不同的字符。

为了同时生成解析树和语法树，为非终结符对应的节点记录综合属性 ``nodes``：
```c
struct {
    TreeNode *pt_node;
    TreeNode *st_node;
} nodes;
```

#### yacc 翻译方案

为了生成解析树，每次实施归约时，用产生式右部每个符号对应的解析树节点作为子节点生成新的节点，作为右部符号的解析树节点即可。

为了生成语法树，只需要在生成解析树的过程中跳过子节点不含运算符的中间节点，并移动运算符位置即可。

```c
%%
input   : regex EOL {
    TreeNode *pt = $1.pt_node, *st = $1.st_node;

    if (pt) {
        printf("Parse Tree:\n");
        printTree(*pt);
        destroyTree(pt);
    }

    if (st) {
        printf("\nSyntax Tree:\n");
        printTree(*st);
        destroyTree(st);
    }

    YYACCEPT;
};

regex   : concat OR regex {
    $$.pt_node = mkNode("regex", 3, $1.pt_node, mkLeaf("OP_OR"), $3.pt_node);
    $$.st_node = mkNode("OP_OR", 2, $1.st_node, $3.st_node);
}
        | concat {
    $$.pt_node = mkNode("regex", 1, $1.pt_node);
    $$.st_node = $1.st_node;
};

concat  : atom concat {
    $$.pt_node = mkNode("concat", 3, $1.pt_node, \
                        mkLeaf("OP_CONCAT"), $2.pt_node);
    $$.st_node = mkNode("OP_CONCAT", 2, $1.st_node, $2.st_node);
}
        | atom {
    $$.pt_node = mkNode("concat", 1, $1.pt_node);
    $$.st_node = $1.st_node;
};

atom    : atom STAR {
    $$.pt_node = mkNode("atom", 2, $1.pt_node, mkLeaf("OP_STAR"));
    $$.st_node = mkNode("OP_STAR", 1, $1.st_node);
}
        | LPAREN regex RPAREN {

    $$.pt_node = mkNode("atom", 3, mkLeaf("OP_LPAREN"), \
                        $2.pt_node, mkLeaf("OP_RPAREN"));
    $$.st_node = $2.st_node;
}
        | CHARACTOR {
    char tmp[] = "CHAR(?)";
    tmp[5] = $1;
    $$.pt_node = mkNode("atom", 1, mkLeaf(tmp));
    $$.st_node = mkLeaf(tmp);
};

%%
```

目前的一个问题是，**缺乏良好的错误处理**。遇到错误内存也没有释放就直接退出了。

本来想增加错误恢复规则，但最后并没有弄清楚规则怎么写、放在哪里比较好，就放弃了。当然也可以绕过 bison 做内存释放，比如自己记录内存分配。不过那就和语法分析完全无关了。

## 实验过程

bison 和 flex 的代码是按照 bison-examples 里面的例子照葫芦画瓢改的。

树的代码是自己写的。加起来70来行，也并不复杂。

树的打印部分，开始只是用空格缩进表示层次，后来加上了连接。许多同学问树怎么打印，我觉得这里并不是重点，就建议用空格缩进。

这次实验都是自己写的代码，所以就放到 [GitHub 上面](https://github.com/cuihaoleo/exercises/tree/master/Schoolworks/compiler_p2)了。