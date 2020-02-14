#Samuel Milner
#sjmilner@mtu.edu

# This program reads in one or more vectors of a specified number of dimensions, 
# the program then prints the element-wise sum of the vectors. For example, if the vectors 
# (1, 2, 3) and (4, 5, 6) are read in, adding vector 0 and vector 1 results in the program printing (5, 7, 9).
	.text

	li $t0, 0
	li $t1, 0
	li $t2, 0
	li $t3, 0
	li $t4, 0
	li $t5, 0
	li $t6, 0
	
	li $v0, 5
	syscall #loaded 5 into $v0 for syscall to read in and integer
	move $t0, $v0 #$t0 is where we temporarily keep int for vector size entered
	ble $t0, $zero, Finish #if initialy number is negative jump to none which ends program without doing anything
	li $v0, 5
	syscall
	move $t1, $v0 # $t1 is where we temporarily keep int for vector amount entered
	ble $t1, $zero, Finish
	mult $t0, $t1
	mflo $t4 # this is the int counter will stop at for next loop, this is going to be the size of all the vecotrs together
	li $t5, 4
	mult $t4, $t5
	mflo $t4
	bgt $t4, 1000, Finish # if space needed to store all ou rvectors is more than 1000 end program
	
	li $t3, 0 # $t3 will be our counter for the loop

readloop:
	bge $t3, $t4, VectorsToAdd
	li $v0, 5
	syscall
	sw $v0, VectorSpace($t3) 
	add $t3, $t3, 4
	b readloop
	
VectorsToAdd:
	li $v0, 5
	syscall
	move $t2, $v0 # $t2 will store start index of first vector
	bge $t2, $t1, Finish
	blt $t2, $zero, Finish
	li $v0, 5
	syscall
	move $t3, $v0 # $t3 will store start index of second vector
	bge $t2, $t1, Finish
	blt $t2, $zero, Finish
	
	li $t4, 4
	mult $t2, $t0
	mflo $t2
	mult $t3, $t0
	mflo $t3
	mult $t2, $t4
	mflo $t2
	mult $t3, $t4
	mflo $t3
	
	li $t4, 0 # this will be counter for next loop
	li $t7, 0
	
AdditionLoop:
	li $t5, 0 # temp place for addition of nth elemtn from both vectors
	bgt $t4, $t0, Results
	lw $t6, VectorSpace($t2) # gets nth element out of vector 1
	add $t5, $t5, $t6
	lw $t6, VectorSpace($t3) # gets nth element out of vecotr 2
	add $t5, $t5, $t6 
	sw $t5, Result($t7) # stores resulting addion into new vector for result
	
	add $t2, $t2, 4
	add, $t3, $t3, 4
	add, $t4, $t4, 1
	add, $t7, $t7, 4
	b AdditionLoop
	
Results:
	li $t4, 0
	li $t5, 0
	b ResultLoop

ResultLoop:
	bge $t4, $t0, AddSecond
	lw $a0, Result($t5)
	li $v0, 1
	syscall 
	
	li      $v0, 11      # syscall 11 prints character in $a0
    addi    $a0, $0, 32  # ASCII code 32 is a space
    syscall    
    add, $t5, $t5, 4
    add, $t4, $t4, 1
	b ResultLoop
	
AddSecond:
	li      $v0, 11      # syscall 11 prints character in $a0
    addi    $a0, $0, 10  # ASCII code 10 is a line feed
    syscall
    b VectorsToAdd
    
Finish:
	li      $v0, 11      # syscall 11 prints character in $a0
    addi    $a0, $0, 10  # ASCII code 10 is a line feed
    syscall
    
	li $v0, 10
	syscall
	
	.data
VectorSpace:	.space 1000
Result:			.space 1000