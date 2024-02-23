/*******************************************************************************
* @version    V1.12
* @date       Sun Jan 21 18:01:45 2024
* @copyright  YHFT Compiler Group, School of Computer Science ,NUDT. 
********************************************************************************/ 
	.file	"daxpy_l4.dev.c"
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
	|	SMOVI24		1024, R50
	[!R0]	SBR		.L1
	|	SMOVI24		-16, R61
		SADDA.M2		R61,AR9,AR9
		SADD.M1		-1,R10,R10
	|	SMOVI24		128, R58
		SSHFLR		3,R10, R1
	|	SADD.M2		R50,R14,R2
		SSHFLL		10,R1, R3
		SADD.M2		R2,R3,R4
	|	SMOVI24		256, R57
		SMOVI24		384, R56
	;; condjump to .L1 occurs
		VLDW 		*+AR0,VR1
	|	SMOVI24		512, R55
		SMOVI24		640, R54
		SMOVI24		768, R53
		SMOVI24		896, R52
		SMOVI24		1024, R51
		SNOP		4
.L3:
		SMOVI24		128, R6
	|	SMVAGA.M1		R14, AR1
	|	SMVAGA.M2		R16, AR4
		SMOVI24		256, R11
		SADD.M1		R58,R16,R5
	|	SADD.M2		R6,R14,R7
	|	VLDW 		*+AR1,VR9
	|	VLDW 		*+AR4,VR17
	|	SMOVI24		384, R18
		SMVAGA.M2		R5, AR6
	|	SADD.M1		R57,R16,R59
	|	SMOVI24		512, R22
		SMVAGA.M2		R7, AR2
	|	SSTW		R59, *+AR9
	|	SADD.M1		R56,R16,R8
	|	SMOVI24		640, R24
		VLDW 		*+AR6,VR16
	|	SLDW		*+AR9, R13
	|	SADD.M1		R11,R14,R12
	|	SMOVI24		768, R26
		VLDW 		*+AR2,VR8
	|	SSTW		R8, *+AR9[1]
	|	SMVAGA.M2		R12, AR0
	|	SADD.M1		R18,R14,R19
	|	SMOVI24		896, R28
		SLDW		*+AR9[1], R20
	|	SADD.M1		R22,R14,R23
		VLDW 		*+AR0,VR7
	|	SMVAGA.M1		R23, AR5
	|	SMVAGA.M2		R19, AR0
		SNOP		1
		SADD.M1		R24,R14,R25
	|	SADD.M2		R26,R14,R27
	|	VLDW 		*+AR0,VR6
	|	VLDW 		*+AR5,VR5
		VFMULAD.M3 		VR9,VR1,VR17,VR18
	|	SMVAGA.M1		R25, AR4
	|	SMVAGA.M2		R27, AR5
		SMVAGA.M1		R13, AR1
		SADD.M2		R55,R16,R9
	|	VLDW 		*+AR4,VR4
	|	VLDW 		*+AR5,VR3
	|	SMVAGA.M1		R16, AR5
		VLDW 		*+AR1,VR15
	|	SMVAGA.M1		R20, AR0
	|	SADD.M2		R54,R16,R15
		VFMULAD.M1 		VR8,VR1,VR16,VR19
	|	SADD.M2		R53,R16,R17
	|	SMVAGA.M1		R9, AR3
		SADD.M2		R52,R16,R21
	|	VLDW 		*+AR0,VR14
	|	SMVAGA.M1		R15, AR2
		SADD.M2		R28,R14,R29
	|	SMVAGA.M1		R17, AR1
	|	VLDW 		*+AR3,VR13
		SMVAGA.M1		R21, AR0
	|	SMVAGA.M2		R29, AR4
	|	VLDW 		*+AR2,VR12
		VLDW 		*+AR1,VR11
		VLDW 		*+AR4,VR2
	|	VLDW 		*+AR0,VR10
	|	SADD.M1		R51,R14,R14
	|	SADD.M2		R51,R16,R16
		VSTW 		VR18,*+AR5
	|	SEQ		R4, R14, R0
		VSTW 		VR19,*+AR6
		SLDW		*+AR9, R30
	|	VFMULAD.M3 		VR7,VR1,VR15,VR20
		SNOP		1
		VFMULAD.M1 		VR6,VR1,VR14,VR21
		VFMULAD.M1 		VR5,VR1,VR13,VR22
		VFMULAD.M1 		VR4,VR1,VR12,VR23
		VFMULAD.M1 		VR3,VR1,VR11,VR24
		VFMULAD.M1 		VR2,VR1,VR10,VR25
		SMVAGA.M2		R30, AR6
		SNOP		1
		VSTW 		VR20,*+AR6
		SLDW		*+AR9[1], R31
		SNOP		6
		SMVAGA.M2		R31, AR4
		SNOP		1
		VSTW 		VR21,*+AR4
	[!R0]	SBR		.L3
	|	VSTW 		VR22,*+AR3
		VSTW 		VR23,*+AR2
		VSTW 		VR24,*+AR1
		VSTW 		VR25,*+AR0
		SNOP		3
	;; condjump to .L3 occurs
.L1:
		SBR		R63
	|	SMOVI24		-16, R61
		SSUBA.M2		R61, AR9, AR9
		SNOP		5
	;; return occurs
	.size	daxpy_cache, .-daxpy_cache
	.global	__udivdi3
	.global	__umoddi3
	.section	.global,"ax",@progbits
	.global	daxpy_kernel
	.type	daxpy_kernel, @function
daxpy_kernel:
		SMOVI24		256, R61
		SSUBA.M2		R61, AR7, AR7
	|	SMOVI24		-112, R61
		SADDA.M1		R61,AR9,AR9
		SNOP		1
		SSTW		R63, *+AR9[12]
		SSTDW		R33:R32, *+AR9[1]
		SBR		get_thread_id
	|	SSTDW		R35:R34, *+AR9[2]
		SSTDW		R37:R36, *+AR9[3]
	|	SMOVI.M1		.L23, R63
		SSTDW		R39:R38, *+AR9[4]
		SSTDW		R41:R40, *+AR9[5]
		SMOV.M1		R12, R34
	|	SMOV.M2		R14, R40
		SMOV.M1		R16, R41
	|	SMOV.M2		R10, R35
		SNOP		1
	;; call to get_thread_id occurs, with return value
.L23:
		SBR		get_group_size
	|	SMOV.M2		R10, R32
		SMOVI.M1		.L24, R63
		SNOP		5
	;; call to get_group_size occurs, with return value
.L24:
		SSHFLL		32,R32, R0
		SSHFLL		32,R10, R10
		SSHFAR		32,R0, R38
		SSHFAR		32,R10, R33
	|	SMOV.M2		R35, R10
		SLT		R38, R33, R1
	|	SMOV.M2		R33, R12
	[!R1]	SBR		.L10
	[R1]	SBR		__udivdi3
		SMOVI.M1		.L25, R63
		SNOP		5
	;; condjump to .L10 occurs
	;; call to __udivdi3 occurs, with return value
.L25:
		SBR		__umoddi3
	|	SMOV.M1		R33, R12
	|	SMOV.M2		R10, R36
		SMOV.M2		R35, R10
	|	SMOVI24		0, R35
	|	SMOVI.M1		.L26, R63
		SADD.M2		1,R36,R37
		SMULIS.M2		R37,R38,R39
		SNOP		3
	;; call to __umoddi3 occurs, with return value
.L26:
		SBR		vector_malloc
	|	SLTU		R38, R10, R2
	[!R2]	SSUB.M2		R38, R10, R10
	|	SMOVI.M1		.L27, R63
	[!R2]	SMOV.M2		R36, R37
	[!R2]	SADD.M2		R10,R39,R39
	|	SMOVI24		262144, R10
		SNOP		3
	;; call to vector_malloc occurs, with return value
.L27:
		SBR		vector_malloc
	|	SMOV.M2		R10, R38
	|	SMOVI24		262144, R10
		SMOVI.M1		.L28, R63
		SNOP		5
	;; call to vector_malloc occurs, with return value
.L28:
		SMOV.M1		R37, R3
	|	SVBCAST.M2 		 R34,VR1
	[!R3]	SBR		.L15
	|	SMOV.M1		R10, R36
		SNOP		6
	;; condjump to .L15 occurs
		VSTW 		VR1,*+AR7[16]
		SNOP		3
.L13:
		SBR		vector_load
	|	SSUB.M1		R35, R37, R4
	|	SMOVI24		32768, R6
	|	SADD.M2		R35,R39,R5
		SMINU		R4, R6, R33
	|	SADD.M2		R5,R5,R7
	|	SMOVI.M1		.L29, R63
		SADD.M2		R33,R33,R8
		SADD.M1		R7,R7,R9
	|	SADD.M2		R8,R8,R11
		SADD.M1		R11,R11,R34
	|	SADD.M2		R9,R9,R13
		SADD.M1		R13,R41,R32
	|	SADD.M2		R13,R40,R10
		SMOV.M1		R38, R12
	|	SMOV.M2		R34, R14
	;; call to vector_load occurs, with return value
.L29:
		SBR		vector_load
	|	SMOV.M1		R34, R14
	|	SMOV.M2		R36, R12
		SMOV.M2		R32, R10
	|	SMOVI.M1		.L30, R63
		SADD.M2		R33,R35,R35
		SNOP		4
	;; call to vector_load occurs, with return value
.L30:
		VLDW 		*+AR7[16],VR2
	|	SAND		15, R33, R0
	|	SMVAAG.M2		AR7, R12
	|	SMOV.M1		R36, R16
		SSHFLR		4,R33, R10
	|	SMOV.M1		R38, R14
	[R0]	SADD.M2		1,R10,R10
		SNOP		3
		SBR		daxpy_cache
		SMOVI.M1		.L31, R63
		SNOP		1
		VSTW 		VR2,*+AR7
		SNOP		3
	;; call to daxpy_cache occurs, with return value
.L31:
		SBR		vector_store
	|	SMOV.M1		R34, R14
	|	SMOV.M2		R32, R12
		SMOV.M2		R36, R10
	|	SMOVI.M1		.L32, R63
		SNOP		5
	;; call to vector_store occurs, with return value
.L32:
		SLTU		R35, R37, R1
	[R1]	SBR		.L13
		SNOP		6
	;; condjump to .L13 occurs
.L15:
		SBR		vector_free
	|	SMOV.M2		R38, R10
		SMOVI.M1		.L33, R63
		SNOP		5
	;; call to vector_free occurs, with return value
.L33:
		SMOVI24		256, R61
	|	SMOV.M2		R36, R10
	|	SLDDW		*+AR9[1], R33:R32
		SADDA.M2		R61,AR7,AR7
	|	SMOVI24		-112, R61
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
	|	SMOVI24		256, R61
		SLDDW		*+AR9[1], R33:R32
	|	SADDA.M2		R61,AR7,AR7
	|	SMOVI24		-112, R61
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
