	.file	"switch.c"
	.section	.rodata
.LC0:
	.string	"Door 1 has 1 million dollars\n"
.LC1:
	.string	"Door 2 has nothing.\n"
.LC2:
	.string	"Door 3 has a toaster.\n"
.LC3:
	.string	"%c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movb	$51, -1(%rbp)
	movsbl	-1(%rbp), %eax
	cmpl	$50, %eax
	je	.L3
	cmpl	$51, %eax
	je	.L4
	cmpl	$49, %eax
	jne	.L2
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L2
.L3:
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	jmp	.L2
.L4:
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	nop
.L2:
	movsbl	-1(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
	.section	.note.GNU-stack,"",@progbits
