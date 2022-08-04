.data
seed:
	.string "seed:\n"
msg:
	.string "overflow:\n"

.bss
.align 0x400
cookie:
	.quad 0x00

.text

.globl _start
_start:

	mov $1, %rax
	mov $1, %rdi
	movabs $seed, %rsi
	mov $6, %rdx
	syscall

	xor %rax, %rax
	xor %rdi, %rdi
	movabs $cookie, %rbx
	mov %rbx, %rsi
	mov $8, %rdx
	syscall

	rdtsc
	xor %rdx, %rax
	mov %rbx, %rdi
	mov $0, %rcx

loop:

	mov %rbx, %rdi
	add %rcx, %rdi
	xorb %al, (%rdi)
	inc %rcx
	cmp $8, %rcx
	jl loop

	mov (%rbx), %rax
	push %rax
	sub $32, %rsp

	mov $1, %rax
	mov $1, %rdi
	movabs $msg, %rsi
	mov $10, %rdx
	syscall

	xor %rax, %rax
	xor %rdi, %rdi
	mov %rsp, %rsi
	mov $256, %rdx
	syscall

	add $32, %rsp
	mov $1,  %rdi
	mov $3,  %rsi
	mov $3,  %rdx
	mov $7,  %rcx

	cmp $32, %rax
	jle  exit

	pop %r11
	xor (%rbx), %r11
	jnz  exit

	movq $0x23, 8(%rsp)
	retfq

exit:

	mov $60, %rax
	mov $0,  %rbx
	syscall