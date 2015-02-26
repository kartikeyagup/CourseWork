.main:
	
	mul r1, r0, r0					
	
	mov r10, sp						
	mul r9, r1, 4					 
	
	
	sub r12, r10, r9				
	
	
	sub r13, r12, r9				
	sub r11, r13, r9				

	




	mov r2, 0
	b label1
	label1:
		

		cmp r2, r0
		
		beq label2
		
		mov r3, 0
		b .loop1
		.loop1:
			cmp r3, r0
			beq label3
			add r4, r2, r3
			mod r4, r4, 17   	    
			
			st r4, 0[r12]
			add r12, r12, 4
			
			add r3, r3, 1
			
			b .loop1
			label3:

				add r2, r2, 1
				b label1
		
	
	label2:
		
		mov r2, 0
		b label4
		label4:
			cmp r2, r0
			beq label5
			mov r3, 0
			b .loop2
			.loop2:
				cmp r3, r0
				beq label6
				sub r4, r2, r3		
				add r4, r4, 64
				mod r4, r4, 6   	
				mul r7, r2, r3		
				mod r7, r7, 8
				add r4, r4, r7		
				st r4, 0[r13]
				
				add r13, r13, 4
				add r3, r3, 1
				b .loop2
				label6:
					add r2, r2, 1
					b label4




label7:	
							
	mul r4, r1, 4					
	sub r11, r11, r4				
	mov r3, 0						
	mov r2, 0						
	label10:
		cmp r2, r1 					
		beq finallabel				
		b .loop7
		.loop7:
			ld r5, 0[r11]			
			add r11, r11, 4			
			add r3, r3, r5			
			add r2, r2, 1 		
			b label10


label8:
	add r2, r2, 1
	add r6, r6, r0
	b .loop3
				

label5:								
									
	sub r12, r12, r9				
	
	sub r13, r13, r9				
	
	
	mov r2, 0						
	mov r6, 0
	b .loop3						
	.loop3:
		cmp r2, r0					
		beq label7					
		mov r3, 0					
		


		b .loop4					
		.loop4:	
			
			cmp r3, r0				
			beq label8				
			mov r4, 0				
			mov r9, 0
			mov r5, 0				
			b .loop5				
			.loop5:
				cmp r4, r0			
				beq label9
			
				mov r7, r6
				add r7, r6, r4		
				
				lsl r7, r7, 2
				add r7, r7, r12
				
				
				ld r8, 0[r7]

				mov r7, r9
				add r7, r7, r3
				
				lsl r7, r7, 2
				add r7, r7, r13
				
				ld r10, 0[r7]		
				
				mul r8, r8, r10		
				
				add r5, r5, r8		
				
				add r4, r4, 1 		
				add r9, r9, r0
				b .loop5

label9:								
	st r5, 0[r11]
	
	add r11, r11, 4				
	add r3, r3, 1
	b .loop4					

finallabel:
	.print r3
	
