.section .init

.option norvc

.type start, @function
.global start
start:
	.cfi_startproc

.option push
.option norelax
	la gp, global_pointer
.option pop

	/* Reset satp */
	csrw satp, zero

	/* Setup stack */
	la sp, stack_top

	# Only continue if we are core 0
	csrr t0, mhartid
	bnez t0, other_cores
	j main_thread
other_cores:
	la t0, entry_ptr
	lw t1, 0(t0)
	ld t2, 4(t0)
	bnez t1, other_entry
	j other_cores
other_entry:
	jr t2
main_thread:
	la t5, bss_start
	la t6, bss_end
bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bltu t5, t6, bss_clear

	la t0, kmain
	csrw mepc, t0

	# move a1 to a0
	mv a0, a1
	tail kmain

	.cfi_endproc

.section .data
.global entry_ptr
# first val is if it is initialized
# second val is the address of the entry point
entry_ptr:
	.word 0
	.dword 0
