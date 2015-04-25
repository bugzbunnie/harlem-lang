Raf lolcode translator-compiler-runner

Lolcode to Ast translator: 
RafLang2Ast.exe code.file ast.file


AST to RafAsm translator: 
RafAst2Asm.exe ast.file asm.file


Virtual machine: 
RafVM.exe asm.file


Ast to language translator:
RafAst2Lang.exe ast.file back.file


Bat files help execute the parts without writing all the stuff in the command line every time.

z0_compile_run does all of the above, but not lang2ast translation
code.txt -> ast.txt -> asm.txt

z1_2ast translates the lolcode file to the Ast format
code.txt -> ast.txt

z2_2asm translates the Ast file to the RafAsm file
ast.txt -> asm.txt

z3_run runs the assembler file
asm.txt

z4_back translates the Ast format back to lolcode
ast.txt -> back.txt

Dotter2.exe creates an image of the ast.txt file