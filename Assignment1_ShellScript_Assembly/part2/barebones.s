ld an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
					# (1) What are we setting up here?
					# Ans:
	pushq %rbp			# rsp keeps track of where stack is by pointing to top of stack.
	movq  %rsp, %rbp		# the rsp stack pointer is moved into rbp, so rbp contains stack pointer.
					# So when we add to stack we offset rbp. RBP remembers where we came from
					# when calling a function bc it is the previous stack pointer so we know
					# where to go back to.

					# (2) What is going on here
					# Ans:
	movq $1, %rax			# RDI is the first argument of function. we expect a function since we have rbb
					# value 1 is moved to rax and rdi.
	movq $1, %rdi			# the string address is moved to rsi second argument
	leaq .hello.str,%rsi		# leaq moves contents of string to register rsi.


					# (3) What is syscall? We did not talk about this
					# in class.
					# Ans: The syscall instruction transfers control to the operating system which then performs the requested service. Then control (usually) returns to the program. This service is being requested from a kernel.
	syscall				# Which syscall is being run?
					# Ans: write
			

					# (4) What would another option be instead of 
					# using a syscall to achieve this?
					# Ans:using functions from a  C library?

	movq	$60, %rax		# (5) We are again setting up another syscall
	movq	$0, %rdi		# What command is it?
					# Ans:	exit
	syscall

	popq %rbp			# (Note we do not really need
					# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans: its a byte for each ASII character of the string and the \n is 13th.
