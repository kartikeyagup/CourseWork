.main:
	@mov r14, r0,r0
	@lsl r14,r14,4
	@.alloc 0 , r14
	@mov r0, 2
	mul r5, r0, r0
	mul r5, r5, 4 					@r5 is tarting of second matrix
	mul r6, r0, r0
	mul r6, r6, 4
	add r6, r6, r5 					@r6 would tell start of resulting matrix
	b .makingmatrices1
	@mov r13, 1
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 2
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 3
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 4
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 5
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 6
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 7
	@st r13, [sp]
	@sub sp, sp, 4
	@mov r13, 8
	@st r13, [sp]
	@sub sp, sp, 4
	@add sp, sp, 32

.makingmatrices1:
	cmp r0, r1 						@comparing i with N
	beq .makingmatrices2 			@if equal make second loop
	mov r2, 0 						@make j = 0
	b .makingmatrices1loop1 			@go to j loop

.makingmatrices1loop1:
	cmp r0, r2 						@comparing j with N
	beq .incrementmatrices1
	add r3, r1, r2 					@i+j
	mod r3, r3, 17 					@(i+j)%17
	mul r4, r1, r0 					@2*i
	add r4, r4, r2	 				@2*i+j
	mul r4, r4, 4
	sub r4, sp, r4 					@sp-4*(2*i+j)
	st r3, [r4] 					@store a[i][j] = i+j%17
	add r2, r2, 1 					@increment j
	b .makingmatrices1loop1

.incrementmatrices1:
	add r1, r1, 1 					@i = i+1
	b .makingmatrices1

.makingmatrices2:
	cmp r0, r7 						@r7 is i for second marices r7 = 0 initially
	beq .restore 					@restore value of r1 to 0
	mov r8, 0 						@r8 is j for 2nd matrices
	b .makingmatrices2loop1 		@go to j loop

.makingmatrices2loop1:
	cmp r0, r8 						@comparing j with N
	beq .incrementmatrices2
	sub r3, r7, r8 					@i-j
	add r3, r3, 64 					@i-j+64
	mod r3, r3, 6 					@i-j+64%6
	mul r4, r7, r8 					@i*j
	mod r4, r4, 8 					@i*j%8
	add r3, r3, r4 					@(i-j+64)%6 + i*j%8
	@.print r3
	mul r9, r7, r0 					@storing 2*i in r9
	add r9, r9, r8 					@2*i+j
	mul r9, r9, 4 					@4*(2*i+j)
	add r9, r9, r5 					@2*i+j+starting of second matrices
	sub r9, sp, r9 					@sp-result of earlier step
	st r3, [r9]
	add r8, r8, 1 					@increment j
	b .makingmatrices2loop1

.incrementmatrices2:
	add r7, r7, 1
	b .makingmatrices2

.restore:
	mov r1, 0 						@make i  = 0
	b .loop1
	
.loop1:
	cmp r0, r1 	 					@compare i with n
	beq .sum 						@calculate sum if i == n
	mov r2, 0 						@else make j  = 0
	b .loop2	 					@go to j while loop
							
.incrementr1:
	add r1, r1, 1					@increment ng r1 by 1					 
	b .loop1 						@go to loop1

.loop2:
	cmp r0, r2 						@compare n with j
	beq .incrementr1 				@if j == N increment i and got to i loop
	mov r3, 0 						@r3 store z counter
	mov r4, 0 						@r4 stores sum
	b .loop3 						@go to loop3 or z loop

.incrementr2:
	mul r11, r1, r0 					@2*i
	add r11, r11, r2 				@2*i+j
	mul r11, r11, 4 				@4*(2*i+j)
	add r11, r11, r6 				@32+4*(2*i+j)
	sub r11, sp, r11 				@sp-(32+4*(2*i+j))
	.print r4
	st r4, [r11] 					@store sum in c[i][j]
	add r2, r2, 1 					@increment j by 1
	b .loop2 						@go to loop2

.loop3:
	cmp r0, r3 						@compare z with N
	beq .incrementr2 				@increment r2
	mul r7, r1, r0 					@2*i
	add r7, r7, r3 					@2*i + k
	mul r7, r7, 4 					@4*(2*i+k)
	sub r7, sp, r7 					@sp-4*(2*i+k) stored in r7
	mul r8, r3, r0 					@2*k
	add r8, r8, r2 					@2*k+j
	mul r8, r8, 4 					@4*(2*k+j)
	add r8, r8, r5 					@16+4*(2*k+j)
	sub r8, sp, r8 					@sp-(16+4*(2*k+j))
	ld r9, [r7] 					@load the value a[i][k]
	ld r10, [r8] 					@load the value b[k][j]
	mul r9, r9, r10 				@multiplying  a[i][k]*b[k][j]
	add r4, r4, r9 					@ sum += a[i][k]*b[k][j] 
	add r3, r3, 1
	b .loop3

.sum:
	sub sp, sp, r6
	mul r1, r0, r0 	 					@size of ans matrix
	mov r2, 0
	mov r4, 0 						@counter to add
	b .sum1

.sum1:
	cmp r2, r1 						@compare counter and N*N
	beq .exit
	ld r3, [sp] 					@r3 loads different values
	add r4, r4, r3 					@r4 stores the sum
	sub sp, sp, 4
	add r2, r2, 1 					@increase counter
	b .sum1

.exit:
	@ld r13, [sp]
	.print r4