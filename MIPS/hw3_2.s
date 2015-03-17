# text and variables
.data
    mnstr1: .asciiz "Enter a input line: "
    mnstr2: .asciiz "Enter a pattern to search for: "
    res0: .asciiz "Results:\n"
    res1: .asciiz "# of whitespace characters: "
    res2: .asciiz "# of non-whitespace characters: "
    res3: .asciiz "# of words: "
    cho1: .asciiz "The user pattern was foud within the input line\n"
    cho2: .asciiz "The user pattern was NOT found within the input line\n"
    err: .asciiz "Line contains whitespace characters only!\n"
    endl: .asciiz "\n"
    strvar: .space 100  # string variable
    serstr: .space 100  # search string variable
.text
# function main
.globl main
main:
    # initialize some registers 
    addi $s0, $0, 0
    addi $s1, $0, 0
    addi $s2, $0, 0
    addi $s3, $0, 0
    la $a0, mnstr1      # print mnstr1
    li $v0, 4
    syscall
    li $v0, 8           # take in input
    la $a0, strvar      # load "strvar" byte space
    move $s0, $a0       # save to s0
    syscall
    jal count           # call count
    beq $s1, 0, error   # error: all whitespace
    la $a0, mnstr2      # print mnstr2
    li $v0, 4
    syscall
    li $v0, 8           # take in input
    la $a0, serstr      # load "serstr" byte space
    move $s3, $a0       # save to $s3
    la $a0, res1        # print first set of results
    li $v0, 4
    syscall
    move $a0, $s1       # print # of whitespace
    li $v0, 1
    syscall
    la $a0, endl        # print newline
    li $v0, 4
    syscall
    la $a0, res2        # print second set of results
    li $v0, 4
    syscall
    move $a0, $s1       # print # of non-whitespace
    li $v0, 1
    syscall
    la $a0, endl        # print newline
    li $v0, 4
    syscall
    #jal countwords
    #jal searchstring
    li $v0, 10          # quit
    syscall
# error, quit program
error:
    la $a0, err         # print err
    li $v0, 4
    syscall
    li $v0, 10          # quit
    syscall
# function count
#   assigns to $s1 the number of whitespace
#   assigns to $s2 the number of nonwhitespace
count:
    addi $t0, $0, 0
# loop through $s0 (input string)
loop:
    #add $t0, $t0, $s0
    move $t0, $s0
    lb $t1, 0($t0)
    beq $t1, 'o', exit
    # check for equality here - if white then restart
    beq $t1, ' ', white
    beq $t1, '\t', white
    beq $t1, '\n', white
    # if we reached this point, it must have been non-whitespace
    addi $s2, $s2, 1    # increment $s2
    addi $s1, $s1, -1   # decrement $s1 since it's incremented again
# case white
white:
    addi $s1, $s1, 1    # increment $s1
    addi $s0, $s0, 1    # point to next character
    j loop              # jump to _loop
# exit case
exit:
    jr $31              # return to main
