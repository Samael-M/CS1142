	.text
	la	$t0, first	 # Get pointer to first node
loop:
	lw	$a0, 0($t0)	 # De-reference to get the value	

	li	$v0, 1		 # Print the integer
	syscall

	lw	$t0, 4($t0)	 # Get pointer to next node
	bne	$t0, -1, loop    # Loop if not end of list

	.data
node2:	.word 2
		.word node3
first:	.word 1
		.word node2
node3:	.word 3
		.word -1