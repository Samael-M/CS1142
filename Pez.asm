# Samuel Milner
# sjmilner@mtu.edu

# Program gets int from user, 0 returns part number descriptiona and quanitiy of given node, 1 list out all contents of all nodes and 2 edits quanatity of items
# -1 terminates program

### START MAIN, DO NOT MODIFY ###
			.text
mainLoop:			
			li			$v0, 5						# Read integer command from user
			syscall

			bltz		$v0, mainDone				# Negative number ends program
			beq 		$v0, $0, mainFirst			# Command 0 = print first node 	
			addi		$v0, $v0, -1
			beq 		$v0, $0, mainList			# Command 1 = print entire list
			addi		$v0, $v0, -1
			beq 		$v0, $0, mainUpdate			# Command 2 = update item
			
			la			$a0, strInvalid				# Print linked list from first node
			li			$v0, 4
			syscall		
			
mainEnd:
			li      	$v0, 11      				# Print a linefeed
			addi    	$a0, $0, 10 
			syscall
			
			b			mainLoop

mainFirst:
			# Print just the first node
			la			$a0, strFirst				
			li			$v0, 4
			syscall		
			
			la			$a0, first					
			jal			printNode
			b			mainEnd
									
mainList:
			# Print linked list from the first node
			la			$a0, strList				
			li			$v0, 4
			syscall		
			
			la			$a0, first					
			jal			printList
			b			mainEnd
			
mainUpdate:
			# Update a specific item
			li			$v0, 5						# Read part number
			syscall
			move		$a1, $v0					
			
			li			$v0, 5						# Read quantity delta
			syscall
			move		$a2, $v0
			
			la			$a0, strUpdate				
			li			$v0, 4
			syscall		

			la			$a0, first
			jal			updateItem
			
			move		$a0, $v0					# Print result from update procedure
			li			$v0, 1
			syscall
			
			b			mainEnd

mainDone:
			# Terminate execution
			li			$v0, 10						
			syscall
			
			.data
strInvalid:	.asciiz "Invalid command!"
strFirst:   .asciiz "First  : "
strList:    .asciiz "Items  : "
strUpdate:	.asciiz "Update : "
			
			.text
### END MAIN ###

############################################################
# Prints the part number, description, and quantity
# of a given node in the list. Example output: 
#  "#955288 Buzz Lightyear (21)"
# Parameters : $a0 - address of node to print
# Returns    : n/a
############################################################
printNode:
			li $t0, 0
			la $t0, 0($a0)
			
			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 35  # ASCII code 35 is a #
    		syscall
			lw $a0, 4($t0) # get part number
			li $v0, 1
			syscall
			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 32  # ASCII code 32 is a space
   			syscall
			la $a0, 12($t0) # get item description
			li $v0, 4
			syscall 
			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 32  # ASCII code 32 is a space
   			syscall
   			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 40  # ASCII code 40 is (
    		syscall
			lw $a0, 8($t0)# get quantity of item
			li $v0, 1
			syscall
			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 41  # ASCII code 41 is )
    		syscall
    		
    		jr $ra
						
############################################################
# Prints list of items from given starting node in null 
# terminated linked list. Each node is printed via printNode
# procedure. Items separated by a comma and space.
#  
# Parameters : $a0 - address of node to start printing from
# Returns    : n/a
############################################################
printList:
			li $s0, 0
			
			addi $s0, $ra, 0 # save ra because we are jumping in a jump
			jal printNode
   			lw $a0, 0($t0) # pointer to node
   			jal comma
			addi $ra, $s0, 0 # get back ra we saved earlier
   			bne $a0, -1, printList
			jr 		  	$ra	
comma:
			beq $a0, -1, ra
			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 44  # ASCII code 44 is a ,
    		syscall
			li $v0, 11      # syscall 11 prints character in $a0
    		li $a0, 32  # ASCII code 32 is a space
    		syscall
    		lw $a0, 0($t0)
    		jr $ra
ra:
			jr $ra
############################################################
# Finds the first item in the list matching a part  
# number and changes its quanity by a certain amount.
# Quantity is not allowed to go below 0.
#
# Parameters : $a0 - address of first node in list
#              $a1 - part number to match
#              $a2 - delta to apply to quantity
# Returns    : $v0 - new quantity, -1 if item not found
############################################################
updateItem:
			addi $s0, $ra, 0 # save $ra before doing another jump
			jal loop
			addi $ra, $s0, 0 # restore $ra
			beq $a0, -1, return2 # if $v0 is -1 return as part number isnt found
			add $t0, $s1, 0 # get address of node where item is
			li $v0, 0
			lw $t1, 8($t0) # get current quantity
			add $v0, $t1, $a2 # add $a2(change in quantity) + $t0(current qaunity) to $v0
			blt $v0, 0, return3
			sw $v0, 8($t0)
			jr $ra
loop:
			lw $t0, 4($a0) # get part number
			addi $s1, $a0, 0 #save address of node for later
			lw $a0, 0($a0) # got to next node
			beq $t0, $a1, return #test to see if part number matches that entered
			bne $a0, -1, loop # if we get to -1 then part number isnt valid
			li $v0, -1
			jr $ra
return:
			li $a0, 1
			jr $ra
return2:
			li $v0, -1
			jr $ra
return3:
			li $v0, 0
			sw $v0, 8($t0)
			jr $ra
.data									
### START DATA ###
# You can (and should!) modify the linked list in order to test your procedures.
# However, the first node should retain the label first.
first:  	.word     	node2       				# Next pointer
			.word     	955288	     				# Part number
			.word     	21							# Quantity
        	.asciiz   	"Buzz Lightyear" 			# Description
        
node2:		.word     	node3
			.word     	955285
			.word     	2
        	.asciiz   	"Genie"

node3:  	.word     	-1
			.word     	951275
			.word     	5
        	.asciiz   	"Chick-Fil-A Cow"
### END DATA ###
