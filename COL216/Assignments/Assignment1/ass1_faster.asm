.main:
	mul r10, r0, r0
	lsl r13, r10, 2
.alloc 0 r13 
.iloop:
	cmp r1, r0
	beq .initmat2
	mod r13, r1, 17
	mov r2, 0
.jloop:
	cmp r2, r0
	beq .jcomplete
	st r13, [r3]
	add r3, r3, 4
	add r13, r13, 1
	mod r13, r13, 17
	add r2, r2, 1
	b .jloop
.jcomplete:
	add r1, r1 , 1
	b .iloop
.initmat2:
	mov r1, 0
	mov r2, 0
	lsl r4, r10, 2 
.i2loop:
	cmp r1, r0
	beq .matrixmult
	add r13, r1, 64 
	mov r12, 0 	
	mov r2 , 0
.j2loop:
	cmp r2, r0
	beq .j2equal 			
	mod r15, r13, 6
	add r11, r12, r15
	st r11, [r4] 	
	sub r13, r13, 1  
	add r12, r12, r1
	mod r12, r12, 8 
	add r2, r2, 1 	
	add r4, r4, 4 	
	b .j2loop
.j2equal:
	add r1, r1, 1 
	b .i2loop
.matrixmult:
	lsl r15, r0, 2
	mov r1, 0 	
	mov r3, 0 	
	lsl r4, r10, 2				
	lsl r5, r4, 1
.istep:
	cmp r1, r0  
	beq .addmatrix
	mov r2, 0  	
	lsl r4, r10, 2 					
.jstep:
	cmp r2, r0 
	beq .jequal
	mul r3, r0, r1 				
	lsl r3, r3, 2 
	add r4, r10, r2
	lsl r4, r4, 2
	mov r6, 0 
	mov r7, 0
.kstep:
	cmp r6, r0
	beq .kequal
	ld r8, [r3]
	ld r9, [r4]
	mul r9, r9, r8 
	add r7, r7, r9 
	add r6, r6, 1
	add r3, r3, 4
	add r4, r4, r15
	b .kstep
.kequal:
	st r7, [r5] 
	add r4, r4, 4
	add r5, r5, 4
	add r2, r2, 1 
	b .jstep
.jequal:
	add r1, r1, 1 
	add r3, r3, r15
	b .istep
.addmatrix:						
	mov r13, 0 					
	mov r12, r10 			
	mov r11, 0 					
	lsl r14, r12, 3
.matrixaddstep:
	cmp r11, r12		
	beq .result
	ld r10, [sp]
	add sp, sp, 4
	add r11, r11, 1
	add r13, r13, r10
	b .matrixaddstep
.result:
	.print r13	 