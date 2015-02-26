@ r0 = N @ r1 = i@ r2 = j@ r3 = pos in mat1@ r4 = pos in mat2@ r13 = temp
.main:
	mul r13, r0, r0
	mul r13, r13, 4

.alloc 0 r13 

.iloop:
	cmp r1, r0					@ i=n
	beq .initmat2				@ start for matrix 2

	mod r13, r1, 17				@ store i in temp
	mov r2, 0 					@ j=0
	b .jloop					@ start loop for j

.jloop:
	cmp r2, r0 					@ check j=n
	beq .jcomplete

	st r13, [r3]				@ store value in mat1
	add r3, r3, 4 				@ increment position in mat1
	add r13, r13, 1 			@ increment i+j
	mod r13, r13, 17 			@ i+j%17
	add r2, r2, 1 				@ j+=1
	b .jloop

.jcomplete:
	add r1, r1 , 1 				@ i += 1
	b .iloop

.initmat2:
	mov r1, 0 					@ i = 0
	mov r2, 0  					@ j = 0
	mul r4, r0, r0 				@ position in mat 2 = n^2
	mul r4, r4, 4 				@ position in mat 2 = 4n*n
	b .i2loop 					@ starting for loop i 

.i2loop:
	cmp r1, r0 					@ check if i=n
	beq .matrixmult

	add r13, r1, 64 			@ setting 1st part 
	@ mod r13, r13, 6 			@ setting 1st part
	mov r12, 0 					@ 2nd part is 0
	mov r2 , 0 					@ j = 0
	b .j2loop

.j2loop:
	cmp r2, r0 					@ check if j =n
	beq .j2equal 			

	mod r15, r13, 6
	add r11, r12, r15 			@ compute value to store
	st r11, [r4] 				@ store value
	sub r13, r13, 1 			@ 
	@mod r13, r13, 6 			@ get next 1st value
	add r12, r12, r1 			@
	mod r12, r12, 8  			@ get next 2nd value
	add r2, r2, 1 				@ j +=1
	add r4, r4, 4 				@ next memory address
	b .j2loop

.j2equal:
	add r1, r1, 1 				@ i +=1
	b .i2loop

.matrixmult:
	mov r1, 0 					@ i = 0
	mov r3, 0 					@ pos1 = 0
	mul r4, r0, r0 				@ pos2 = n^2
	mul r4, r4, 4 				@ pos2= 4n^2				
	mul r5, r4, 2 				@ pos3= 8n*n
	b .istep

.istep:
	cmp r1, r0  				@ check i =n
	beq .addmatrix

	mov r2, 0  					@ j = 0 
	mul r4, r0, r0 				@ pos2 = n^2
	mul r4, r4, 4 				@ pos2= 4n^2					

	b .jstep

.jstep:
	cmp r2, r0 					@ check j = n
	beq .jequal

	mul r3, r0, r1 				
	mul r3, r3, 4 				@ mat1 position set
	mul r4, r0, r0 
	add r4, r4, r2
	mul r4, r4, 4
	mov r6, 0 					@ k = 0
	mov r7, 0 					@ sum = 0
	b .kstep

.kstep:
	cmp r6, r0
	beq .kequal

	ld r8, [r3] 				@ r8 = matrix 1 value
	ld r9, [r4] 				@ r9 = matrix 2 value
	mul r9, r9, r8 				@ r= r8*r9
	add r7, r7, r9 				@ sum += mat1*mat2 vals

	add r6, r6, 1 				@ k+=1
	add r3, r3, 4 				@ mat1 position incremented
	add r4, r4, r0 
	add r4, r4, r0 
	add r4, r4, r0 
	add r4, r4, r0 				@ mat2 position incremented

	b .kstep


.kequal:
	st r7, [r5] 				@ storing value to mat3
	add r4, r4, 4 				@ incremement mat2 position
	add r5, r5, 4				@ incremment mat 3 position
	add r2, r2, 1 				@ j += 1

	b .jstep

.jequal:
	add r1, r1, 1 				@ increment i
	add r3, r3, r0
	add r3, r3, r0
	add r3, r3, r0
	add r3, r3, r0 				@ new mat1 position
	b .istep

.addmatrix:						@TODO: change sp for mat 3
	mov r13, 0 					@ temp sum =0
	mul r12, r0, r0 			@ limit is n*n
	mov r11, 0 					@ counter = 0
	@ mov sp, 0
	@ mul sp, r12, 4 				@ sp = 8* n*n
	mul r14, r12, 8
	b .matrixaddstep

.matrixaddstep:
	cmp r11, r12				@ checking if complete
	beq .result 				@ done with addition
	
	ld r10, [sp]				@ loading value from matrix
	add sp, sp, 4 				@ increment in matrix position
	add r11, r11, 1 			@ increment loop counter
	add r13, r13, r10 			@ add value to sum
	b .matrixaddstep

.result:
	.print r13	 