	.arch armv7-a
	.fpu neon
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"neon_core.cpp"
	.text
	.align	1
	.p2align 2,,3
	.global	_Z18neon_process_chunkPKi
	.syntax unified
	.thumb
	.thumb_func
	.type	_Z18neon_process_chunkPKi, %function
_Z18neon_process_chunkPKi:
	.fnstart
.LFB2136:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	vld1.32	{d16-d17}, [r0]
	vmov.i32	q11, #0  @ v4si
	vshr.s32	q12, q8, #31
	vclt.s32	q0, q8, q11
	vcgt.s32	q9, q8, q11
	veor	q10, q12, q8
	vbif	q8, q11, q9
	vsub.i32	q10, q10, q12
	vbsl	q0, q10, q11
	vorr	q0, q8, q0
	bx	lr
	.cantunwind
	.fnend
	.size	_Z18neon_process_chunkPKi, .-_Z18neon_process_chunkPKi
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",%progbits
