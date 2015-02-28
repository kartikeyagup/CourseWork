.main:
	mov r14, r0,r0
	lsl r14,r14,4
	.alloc 0, r14
	mul r5, r0, r0
	mul r5, r5, 4 					
	mul r6, r0, r0
	mul r6, r6, 4
	add r6, r6, r5 					
	b .makingmatrices1
.makingmatrices1:
	cmp r0, r1 						
	beq .makingmatrices2 			
	mov r2, 0 						
	b .makingmatrices12 			
.makingmatrices12:
	cmp r0, r2 						
	beq .incrementmatrices1
	add r3, r1, r2 					
	mod r3, r3, 17 					
	mul r4, r1, r0 					
	add r4, r4, r2	 				
	mul r4, r4, 4
	sub r4, sp, r4 					
	st r3, [r4] 					
	add r2, r2, 1 					
	b .makingmatrices12
	
.incrementmatrices1:
	add r1, r1, 1 					
	b .makingmatrices1
.makingmatrices2:
	cmp r0, r7 						
	beq .restore 					
	mov r8, 0 						
	b .makingmatrices2loop1 		
.makingmatrices2loop1:
	cmp r0, r8 						
	beq .incrementmatrices2
	sub r3, r7, r8 					
	add r3, r3, 64 					
	mod r3, r3, 6 					
	mul r4, r7, r8 					
	mod r4, r4, 8 					
	add r3, r3, r4 					
	@.print r3
	mul r9, r7, r0 					
	add r9, r9, r8 					
	mul r9, r9, 4 					
	add r9, r9, r5 					
	sub r9, sp, r9 					
	st r3, [r9]
	add r8, r8, 1 					
	b .makingmatrices2loop1
.incrementmatrices2:
	add r7, r7, 1
	b .makingmatrices2
.restore:
	mov r1, 0 						
	b .loop1
.loop1:
	cmp r0, r1 	 					
	beq .sum 						
	mov r2, 0 						
	b .loop2	 					
.incrementr1:
	add r1, r1, 1										 
	b .loop1 						
.loop2:
	cmp r0, r2 						
	beq .incrementr1 				
	mov r3, 0 						
	mov r4, 0 						
	b .loop3 						
.incrementr2:
	mul r11, r1, r0 					
	add r11, r11, r2 				
	mul r11, r11, 4 				
	add r11, r11, r6 				
	sub r11, sp, r11 				
	st r4, [r11] 					
	add r2, r2, 1 					
	b .loop2 						
.loop3:
	cmp r0, r3 						
	beq .incrementr2 				
	mul r7, r1, r0 					
	add r7, r7, r3 					
	mul r7, r7, 4 					
	sub r7, sp, r7 					
	mul r8, r3, r0 					
	add r8, r8, r2 					
	mul r8, r8, 4 					
	add r8, r8, r5 					
	sub r8, sp, r8 					
	ld r9, [r7] 					
	ld r10, [r8] 					
	mul r9, r9, r10 				
	add r4, r4, r9 					 
	add r3, r3, 1
	b .loop3
.sum:
	sub sp, sp, r6
	mul r1, r0, r0 	 					
	mov r2, 0
	mov r4, 0 						
	b .sum1
.sum1:
	cmp r2, r1 						
	beq .exit
	ld r3, [sp] 					
	add r4, r4, r3 					
	sub sp, sp, 4
	add r2, r2, 1 					
	b .sum1
.exit:
	@ld r13, [sp]
	.print r4
