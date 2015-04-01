# Program to calculate the surface area
# and volume of a sphere given the radius

# Data Declarations
         .data
pi:      .float 3.14159
four:    .float 4.0
three:   .float 3.0
prompt:  .asciiz "Enter an input radius: "
saprmpt: .asciiz "The surface area of the sphere is: "
vlprmpt: .asciiz "The volume of the sphere is: "
newline: .asciiz "\n"

# text/code section
         .text
         .globl main

main:
# Compute: (4.0 * pi) which is used for both equations

# Prompt the user for an input radius

# Calculate surface area of a sphere
#   surface_area = 4.0 * pi * radius^2

# Print surface area to user

# Calculate volume of a sphere:
#   volume = (4.0 * pi / 3.0) * radius^3

# Print surface area to user

# Exit program
         li      $v0, 10         # To the bat mobile
         syscall

