	.section .text
	.global	start
start:
	! set vbr address
	mov.l	vec_k, r0
	ldc	r0, vbr

	! copy data
	mov.l	data_dst_k, r0
	mov.l	data_dst_e_k, r1

	cmp/eq	r0, r1		! needless copy
	bt	bss_start
	mov.l	data_src_k, r2
	cmp/eq	r0, r2		! needless copy
	bt	bss_start
	nop

data_l:
	mov.l	@r2+, r3
	mov.l	r3, @r0
	add	#4, r0
	cmp/gt	r0, r1
	bt	data_l
	nop

bss_start:
	! zero out bss
	mov.l	bss_s_k, r0
	mov.l	bss_e_k, r1
	cmp/eq	r0, r1		! needless copy
	bt	main_start
	mov	#0, r2
bss_l:
	mov.b	r2, @r0
	add	#1, r0
	cmp/ge	r0, r1
	bt	bss_l
	nop

main_start:
	mov.l	stack_k, r15

	! call the mainline
	mov.l	main_k, r0
	jsr	@r0
	nop

inf_loop:
	! change to sleep
	bra	inf_loop
	nop

	.align 4
vec_k:
	.long	_vec_top
stack_k:
	.long	_stack
main_k:
	.long	_main

data_dst_k:
	.long	__data_start
data_dst_e_k:
	.long	_edata
data_src_k:
	.long	_dynamic_end
bss_s_k:
	.long	__bss_start
bss_e_k:
	.long	_end
