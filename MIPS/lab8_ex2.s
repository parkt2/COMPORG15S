# This MAL program will find the average value of an
# integer array of size 12 (elements)

            .data
intarr:     .word     1, 2048, 4, 512, 16, 64, 32, 128, 8, 512, 1024, 2
length:     .word     12
average:    .double   0.0
outstr:     .asciiz   "The average value in the array is: "

            .text
            .globl main
main:       move  $t0, $0        # $t0 is a loop index
            lw    $s1, length    # $s1 holds max # elements
            la    $s0, intarr    # $s0 holds the start addr of arr
            move  $t1, $0        # $t1 holds the sum of values from array

            # Sum the elements in the array
loop:       beq   $t0, $s1, compute # When $t0 = $s1, we hit end of array
            # TODO
            b     loop

            # Compute the average using the FP coprocessor
            #    and store the result in average
compute:
            # TODO

            # Print out average value
            la      $a0, outstr     # Output string
            li      $v0, 4
            syscall

            li      $v0, 10         # To the bat mobile
            syscall
