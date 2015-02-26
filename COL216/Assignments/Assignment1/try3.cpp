.main:	mul r14,r0,r0
		lsl r1,r14,4
		.alloc 4, r1  
		mov r1, 0 	@ r1 is memory pointer
@ r2 and r3 are i and j for M1
.loopaa:cmp r0,r2
		bgt .loopab
		beq .startb
.loopab:add r1,r1,4
		add r4,r2,r3 	@result in r4 of M1
		mod r4,r4,17
		st r4, [r1]
		add r3,r3,1
		add r1,r1,4
		add r4,r2,r3 	@result in r4 of M1
		mod r4,r4,17
		st r4, [r1]
		add r3,r3,1
		add r1,r1,4
		add r4,r2,r3 	@result in r4 of M1
		mod r4,r4,17
		st r4, [r1]
		add r3,r3,1
		add r1,r1,4
		add r4,r2,r3 	@result in r4 of M1
		mod r4,r4,17
		st r4, [r1]
		add r3,r3,1
		cmp r0, r3
		bgt .loopab
		add r2,r2,1
		mov r3,0
		cmp r0,r2
		bgt .loopab
.startb:mov r2, 0
		mov r3, 0
.loopbb:add r1,r1,4
		sub r5, r2,r3 @r5 and r6 contain (i-j+64)%6 and (i*j)%8
		add r5, r5,64
		mod r5, r5,6
		mul r6,	r2,r3
		mod r6,r6,8
		add r4, r5,r6
		st r4, [r1]
		add r3,r3,1
		add r1,r1,4
		sub r5, r2,r3 @r5 and r6 contain (i-j+64)%6 and (i*j)%8
		add r5, r5,64
		mod r5, r5,6
		mul r6,	r2,r3
		mod r6,r6,8
		add r4, r5,r6
		st r4, [r1]
		add r3,r3,1
		add r1,r1,4
		sub r5, r2,r3 @r5 and r6 contain (i-j+64)%6 and (i*j)%8
		add r5, r5,64
		mod r5, r5,6
		mul r6,	r2,r3
		mod r6,r6,8
		add r4, r5,r6
		st r4, [r1]
		add r3,r3,1
		add r1,r1,4
		sub r5, r2,r3 @r5 and r6 contain (i-j+64)%6 and (i*j)%8
		add r5, r5,64
		mod r5, r5,6
		mul r6,	r2,r3
		mod r6,r6,8
		add r4, r5,r6
		st r4, [r1]
		add r3,r3,1
		cmp r0, r3
		bgt .loopbb
		add r2,r2,1
		mov r3,0
		cmp r0,r2
		bgt .loopbb
.matmul:mov r2,0	@i,j of the resultant matrix
		mov r3,0
		b .loop
.matmulb:add r1,r1,4
		st r13 ,[r1]
		@.print r13
		add r3, r3 ,1
		cmp r0, r3
		bgt .loop
		beq .matmulc
.matmulc:mov r3,0
		add r2,r2,1
		cmp r0,r2
		bgt .loop
		mov r13,0
		beq .exit
.loop:mov r9, 0 @ counter till r0
		mul r7, r0,r2
		add r7, r7,1 
		lsl r7 ,r7,2	@r7 has the first element of the row. Add 4 to get next(r0 times).
		mul r8, r0,r0
		add r8,r8,1
		add r8, r8, r3 
		lsl r8, r8, 2 @r8 has the first element of the column. Add 4*r0 to get next(r0 times).
		mov r13,0 @r13 has the sum
		b .loopmul
.loopmul:ld r10, [r7]
		ld r11, [r8]
		mul r12, r10,r11
		add r13, r13,r12 @r13 has the sum
		add r9,r9,1
		cmp r0,r9
		bgt .loopmulb
		beq .matmulb	
.loopmulb:add r7,r7,4
		mov r10,0
		mul r10, r0,4
		add r8, r8,r10
		b .loopmul
.exit:	mov r9,0 @counter till r0
		mov r2,r14
		lsl r2,r2,1
		add r2,r2,1 @r2 points to memory location of ans.r3=4*r2
		b .exitb
.exitb:	lsl r3,r2,2
		ld r4,[r3]
		add r13,r13,r4 @r13 contains the sum of ans.
		add r2,r2,1
		add r9,r9,1
		cmp r9,r14
		bgt .done
		b .exitb
.done:.print r13
