#Samuel Milner
#sjmilner@mtu.edu


	.text
	li $t1, 0 # $t1 stores min value
	li $t2, 0 # $t2 stores max value
	li $t3, 0 # $t3 stores count of even
	li $t4, 0 # $t4 stores count of odd
	li $t5, 0 # $t5 stores sum of sqaures
	li $s1, 1 # value for division to check if even/odd
	li $s2, 2 # value for division to check if even/odd
	
	li $v0, 5
	syscall #loaded 5 into $v0 for syscall to read in and integer
	move $t0, $v0 #$t0 is where we temporarily keep int entered
	blt $t0, 0, none #if initialy number is negative jump to none which ends program without doing anything
	move $t1, $t0 #initialize min to first int entered so min doesnt stay at 0

readloop:
	blt $t0, 0, Finish # test of int entered is negative
	#next 3 lines deal with sum of sqaures
	mult $t0, $t0 #square value
	mflo $t6 #temp var for square of int entered
	add $t5, $t5, $t6 # adds square of int entered to rest of sum of squares
	b mainloop
	
mainloop:
	
	bgt $t1, $t0, min # branch off to min to check if new value is smaller than any previous
	blt $t2, $t0, max # branch off to max to check if new value is bigger than any previous
	b counteven
	
#divide number by 2 and test remainder if 1 its odd if 0 its even, this is used for counteven and countodd
counteven:
	div $t0, $s2 
	mfhi $t6
	beq $t6, $zero, EvenCount #branch if number was even
	b OddCount #else skip to odd count
countodd:
	div $t0, $s2
	mfhi $t6
	beq $t6, $s1, EvenCount #branch if number was odd
	b finishloop
finishloop:
	li $v0, 5
	syscall #syscall gets new int from user
	move $t0, $v0
	b readloop #goes back to start of loop for new integer entered
	
min:
	move $t1, $t0 #set new min number
	b mainloop
max:
	move $t2, $t0 #set new max number
	b mainloop
EvenCount:
	add $t3, $t3, 1 #add to even count
	b countodd
OddCount:
	add $t4, $t4, 1 #add to odd count
	b finishloop
Finish:
	move $a0, $t1
	li $v0, 1
	syscall # prints min value
	
	li $a0, 10 # 10 is the ascii code for line feed which is a new line
	li $v0, 11 # 11 is syscall argument for printing a character stored in $a0 which is a new line
	syscall
	
	move $a0, $t2
	li $v0, 1
	syscall # prints max value
	
	li $a0, 10
	li $v0, 11
	syscall
	
	move $a0, $t3
	li $v0, 1
	syscall  # prints count of even
	
	li $a0, 10
	li $v0, 11
	syscall
	
	move $a0, $t4
	li $v0, 1
	syscall  # prints count of odd
	
	li $a0, 10
	li $v0, 11
	syscall
	
	move $a0, $t5
	li $v0, 1
	syscall  # prints sum of squares
none:
	#nothin to see here