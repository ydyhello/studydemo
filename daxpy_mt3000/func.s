/*******************************************************************************
* @version    V1.12
* @date       Fri Jan 19 11:20:13 2024
* @copyright  YHFT Compiler Group, School of Computer Science ,NUDT. 
********************************************************************************/ 
	.file	"func.c"
.text;
	.section	.text.exampleFunc,"ax",@progbits
	.global	exampleFunc
	.type	exampleFunc, @function
exampleFunc:
		SFADDD.M1		R10, R12, R50
	|	SBR		R63
	|	SFSUBD.M2	R12, R10, R10
		SNOP		2
		SFMULD.M2		R50, R10, R10
		SNOP		3
	;; return occurs
	.size	exampleFunc, .-exampleFunc
	.ident	"GCC: (GNU) 8.3.0"
