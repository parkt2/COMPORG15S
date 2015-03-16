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
    strvar: .space 100
.text
# function main
.globl main
main:
    la $a0, mnstr1      # print mnstr1
    li $v0, 4
    syscall
    li $v0, 8           # take in input
    la $a0, strvar      # load variable byte space
    move $t0, $a0       # save to t0
    syscall
    addi $t1, $0, 0     # set $t1 to 0
    jal check           # go to check
    bgez $t1, error     # error: all whitespace
# error, quit program
error:
    la $a0, err         # print err
    li $v0, 4
    syscall
    li $v0, 10          # quit
    syscall
# function check
#   checks whitespace. returns 0 (false, all whitespace) or 1 (true,
#   at least one non-whitespace)
#   0x20, 0x9 0xA
check:
    #addi $sp, $sp, -4   # move stack pointer up 8 bytes
    #sw $31, 0($sp)      # save $ra ($31) on the stack
# loop through $t0 (input string)
_loop:
    bgez $t0, _exit     # loop until null terminate character
    # check for equality here - if white then restart
    beq $t0, 0x20, _white
    beq $t0, 0x9, _white
    beq $t0, 0xA, _white
    # if we reached this point, it must have been non-whitespace
    addi $t1, $0, 1     # set $t1 to 1
    j _exit
# case white
_white:
    addi $t0, $t0, 1    # point to next character
    j _loop             # jump to _loop
# case nonwhite/loop end
_exit:
    jr $31              # return to main
