<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/b/b4/Hello_World_Brainfuck.png" width="150" title="Hello_World_Brainfuck (from wikipedia)">
</p>

# urbanmi

A simple [brainfuck language](https://en.wikipedia.org/wiki/Brainfuck) interpreter written in C11.    

### Purpose

Noting serious.     
I'm trying to refresh my C. An _etude_ as Peter Norvig would say. 

### How to use urbanmi

You can build the interpreter and execute `.bf` script as follows: 
```bash
$ make
$ build/urbanmi examples/hello.bf
Hello World!
```
Notes: You can find brainfuck script examples in the examples/ directory.   


### About the name

The language was created by Urban Müller.       
☞ urban m[uller] i[terpreter]  


### Liscence

This is free and unencumbered software released into the public domain.     
See the LISCENCE file for more information.

----

```
----[-->+++++<]>-.---.++++[->+++<]>.-.+++++++++++++.-.----.----[->+++<]>-.--[--->+<]>-.[--->+<]>-.-[--->++<]>-.++++++++++.+[---->+<]>+++.[->+++<]>+.+[--->+<]>+.[->+++<]>.[--->+<]>----.----.--.--------.-[->+++<]>.------------.[->+++<]>+.+++++++++++++.----------.-[--->+<]>-.---[->++++<]>-.----.[--->+<]>-----.[->+++<]>+.--[--->+<]>---.-------------.--[--->+<]>-.--[->++++<]>+.----------.++++++.-[++>---<]>.
```
