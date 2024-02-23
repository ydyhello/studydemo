/*******************************************************************************
* @version    V1.12
* @date       Fri Jan 19 01:41:30 2024
* @copyright  YHFT Compiler Group, School of Computer Science ,NUDT. 
********************************************************************************/ 
	.file	"te.c"
.text;
	.section	.text.func,"ax",@progbits
	.global	func
	.type	func, @function
func:
		SMVAGA.M1		R10, AR14
	|	SFADDD.M2		R16, R18, R18
		SFADDD.M1		R12, R14, R10
	|	SFSUBD.M2	R14, R12, R12
		SLDW		*+AR14, R50
		SNOP		1
		SFMULD.M2		R10, R18, R0
		SNOP		4
		SFMULD.M2		R12, R50, R1
		SBR		R63
		SNOP		2
		SFMULD.M2		R0, R1, R10
		SNOP		3
	;; return occurs
	.size	func, .-func
	.section	.text.complex_mul_real,"ax",@progbits
	.global	complex_mul_real
	.type	complex_mul_real, @function
complex_mul_real:
		SFMULD.M2		R12, R16, R12
		SNOP		2
		SBR		R63
		SFMULBD.M2	R10, R14, R12, R10
		SNOP		5
	;; return occurs
	.size	complex_mul_real, .-complex_mul_real
	.ident	"GCC: (GNU) 8.3.0"
