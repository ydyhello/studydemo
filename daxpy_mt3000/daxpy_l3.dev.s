/*******************************************************************************
* @version    V1.12
* @date       Wed Jan 17 08:38:44 2024
* @copyright  YHFT Compiler Group, School of Computer Science ,NUDT. 
********************************************************************************/ 
	.file	"daxpy_l3.dev.c"
.text;
	; ;APP 
	.section ._gsm,"aw",%nobits
	; ;NO_APP 
	.section	.text.daxpy_cache,"ax",@progbits
	.global	daxpy_cache
	.type	daxpy_cache, @function
daxpy_cache:
		SMVAGA.M2		R12, AR0
	|	SMOV.M1		R10, R0
	|	SSHFLL		7,R10, R10
	[!R0]	SBR		.L1
	|	SMVAGA.M2		R16, AR2
	|	SADD.M1		R10,R14,R1
	|	SMOVI24		128, R50
		SNOP		6
	;; condjump to .L1 occurs
		VLDW 		*+AR0,VR3
		SNOP		8
.L3:
		SMVAGA.M2		R14, AR1
	|	VLDW 		*+AR2,VR2
	|	SADD.M1		R50,R14,R14
		SEQ		R1, R14, R2
		VLDW 		*+AR1,VR1
		SNOP		8
		VFMULAD.M3 		VR1,VR3,VR2,VR4
		SNOP		2
	[!R2]	SBR		.L3
		SNOP		2
		VSTW 		VR4,*+AR2
	|	SADDA.M2		R50,AR2,AR2
		SNOP		3
	;; condjump to .L3 occurs
.L1:
		SBR		R63
		SNOP		6
	;; return occurs
	.size	daxpy_cache, .-daxpy_cache
	.global	__udivdi3
	.global	__umoddi3
	.section	.global,"ax",@progbits
	.global	daxpy_kernel
	.type	daxpy_kernel, @function
daxpy_kernel:
		SMOVI24		128, R61
		SSUBA.M2		R61, AR7, AR7
	|	SMOVI24		-128, R61
		SADDA.M1		R61,AR9,AR9
		SNOP		1
		SSTW		R63, *+AR9[12]
		SSTW		R16, *+AR9[15]
		SSTDW		R33:R32, *+AR9[1]
		SBR		get_thread_id
	|	SSTDW		R35:R34, *+AR9[2]
		SSTDW		R37:R36, *+AR9[3]
	|	SMOVI.M1		.L24, R63
		SSTDW		R39:R38, *+AR9[4]
		SSTDW		R41:R40, *+AR9[5]
		SMOV.M1		R12, R34
	|	SMOV.M2		R14, R41
	|	SMOVI24		128, R39
		SMOV.M2		R10, R35
		SNOP		1
	;; call to get_thread_id occurs, with return value
.L24:
		SBR		get_group_size
	|	SMOV.M2		R10, R32
		SMOVI.M1		.L25, R63
		SNOP		5
	;; call to get_group_size occurs, with return value
.L25:
		SSHFLL		32,R32, R0
		SSHFLL		32,R10, R10
		SSHFAR		32,R0, R38
		SSHFAR		32,R10, R33
	|	SMOV.M2		R35, R10
		SLT		R38, R33, R1
	|	SMOV.M2		R33, R12
	[!R1]	SBR		.L10
	[R1]	SBR		__udivdi3
		SMOVI.M1		.L26, R63
		SNOP		5
	;; condjump to .L10 occurs
	;; call to __udivdi3 occurs, with return value
.L26:
		SBR		__umoddi3
	|	SMOV.M1		R33, R12
	|	SMOV.M2		R10, R36
		SMOV.M2		R35, R10
	|	SMOVI24		0, R35
	|	SMOVI.M1		.L27, R63
		SADD.M2		1,R36,R37
		SMULIS.M2		R37,R38,R40
		SNOP		3
	;; call to __umoddi3 occurs, with return value
.L27:
		SBR		vector_malloc
	|	SLTU		R38, R10, R2
	[!R2]	SSUB.M2		R38, R10, R10
	|	SMOVI.M1		.L28, R63
	[!R2]	SMOV.M2		R36, R37
	[!R2]	SADD.M2		R10,R40,R40
	|	SMOVI24		262144, R10
		SNOP		3
	;; call to vector_malloc occurs, with return value
.L28:
		SBR		vector_malloc
	|	SMOV.M2		R10, R38
	|	SMOVI24		262144, R10
		SMOVI.M1		.L29, R63
		SNOP		5
	;; call to vector_malloc occurs, with return value
.L29:
		SMOV.M1		R37, R3
	|	SVBCAST.M2 		 R34,VR1
	[!R3]	SBR		.L16
	|	SMOV.M1		R10, R36
		SNOP		6
	;; condjump to .L16 occurs
		VSTW 		VR1,*+AR7
		SNOP		3
.L13:
		SBR		vector_load
	|	SSUB.M1		R35, R37, R4
	|	SMOVI24		32768, R5
	|	SADD.M2		R35,R40,R6
		SMINU		R4, R5, R34
	|	SADD.M2		R6,R6,R7
	|	SMOVI.M1		.L30, R63
		SADD.M2		R34,R34,R8
		SADD.M1		R7,R7,R9
	|	SADD.M2		R8,R8,R11
		SADD.M1		R11,R11,R33
	|	SADD.M2		R9,R9,R32
		SMOV.M1		R38, R12
	|	SMOV.M2		R33, R14
		SADD.M2		R32,R41,R10
	;; call to vector_load occurs, with return value
.L30:
		SLDW		*+AR9[15], R50
	|	SMOV.M1		R33, R14
	|	SMOV.M2		R36, R12
		SNOP		1
		SBR		vector_load
		SMOVI.M1		.L31, R63
		SNOP		3
		SADD.M2		R32,R50,R32
		SMOV.M2		R32, R10
	;; call to vector_load occurs, with return value
.L31:
		SAND		15, R34, R1
	[R1]	SBR		.L15
	|	SSHFLR		4,R34, R0
	[R1]	SADD.M2		1,R0,R0
		SNOP		5
	;; condjump to .L15 occurs
	[!R0]	SBR		.L18
		SNOP		6
	;; condjump to .L18 occurs
.L15:
		SMVAGA.M2		R36, AR0
	|	SMOV.M1		R38, R51
	|	SMOVI24		0, R12
		SNOP		1
.L17:
		SMVAGA.M2		R51, AR1
	|	VLDW 		*+AR0,VR2
	|	VLDW 		*+AR7,VR3
	|	SADD.M1		1,R12,R12
		SLTU		R12, R0, R2
	|	SADD.M1		R39,R51,R51
		VLDW 		*+AR1,VR4
		SNOP		8
		VFMULAD.M3 		VR4,VR3,VR2,VR5
		SNOP		2
	[R2]	SBR		.L17
		SNOP		2
		VSTW 		VR5,*+AR0
	|	SADDA.M2		R39,AR0,AR0
		SNOP		3
	;; condjump to .L17 occurs
.L18:
		SBR		vector_store
	|	SMOV.M1		R33, R14
	|	SMOV.M2		R32, R12
		SMOV.M2		R36, R10
	|	SMOVI.M1		.L32, R63
		SADD.M2		R34,R35,R35
		SNOP		4
	;; call to vector_store occurs, with return value
.L32:
		SLTU		R35, R37, R3
	[R3]	SBR		.L13
		SNOP		6
	;; condjump to .L13 occurs
.L16:
		SBR		vector_free
	|	SMOV.M2		R38, R10
		SMOVI.M1		.L33, R63
		SNOP		5
	;; call to vector_free occurs, with return value
.L33:
		SMOVI24		128, R61
	|	SMOV.M2		R36, R10
	|	SLDDW		*+AR9[1], R33:R32
		SADDA.M2		R61,AR7,AR7
	|	SMOVI24		-128, R61
	|	SLDDW		*+AR9[2], R35:R34
		SLDDW		*+AR9[3], R37:R36
		SLDDW		*+AR9[4], R39:R38
		SLDDW		*+AR9[5], R41:R40
		SBR		vector_free
	|	SLDW		*+AR9[12], R63
	|	SSUBA.M2		R61, AR9, AR9
		SNOP		6
	;; sibcall to vector_free occurs
.L10:
		SLDW		*+AR9[12], R63
	|	SMOVI24		128, R61
		SLDDW		*+AR9[1], R33:R32
	|	SADDA.M2		R61,AR7,AR7
	|	SMOVI24		-128, R61
		SLDDW		*+AR9[2], R35:R34
		SLDDW		*+AR9[3], R37:R36
		SLDDW		*+AR9[4], R39:R38
		SLDDW		*+AR9[5], R41:R40
	|	SSUBA.M2		R61, AR9, AR9
		SNOP		1
		SBR		R63
		SNOP		6
	;; return occurs
	.size	daxpy_kernel, .-daxpy_kernel
	.ident	"GCC: (GNU) 8.3.0"
