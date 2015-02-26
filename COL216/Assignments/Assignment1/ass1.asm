@r0,r9, r8, are temp
@r1=i
@r2=j
@r3=dimension 
@r4=k
@r5= sum of elements for given i,j
@r6=position of element in mat1
@r7=position of element in mat2
@r10=sumofmatrix
@r11=dim*dim

@TODO: Make dimension general things
@TODO: Do memory in C file 

.main:
	@mov r0, 1
	@st r0, [sp]
	@mov r0, 2
	@st r0, 4[sp]
	@@ld r0, 4[sp]
	@@.print r0
	@mov r0, 3
	@st r0, 8[sp]
	@mov r0, 4
	@st r0, 12[sp]
	@mov r0, 5
	@st r0, 16[sp]
	@mov r0, 6
	@st r0, 20[sp]
	@mov r0, 7
	@st r0, 24[sp]
	@mov r0, 8
	@st r0, 28[sp]

	mov r1, 0				@ i =0
	mov r3, r0 				@ dim =2
	b .istep

.initmat1:
	mov r1, 0				@ i=0
	b .iloop

.iloop:
	cmp r1, r3				@ check if i=dim
	beq .initmat2			@ done with mat 1

	mov r2, 0				@ init r2
	b .jloop				@ start loop for j

.jloop:
	cmp r2, r3				@ check if j = dim
	beq .jinitequal			@ j=n

	add r12, r2, r3 		@ r12= i+ j
	mod r12, r12, 17		@ r12= i+j %17
	st r12, [r6]			@ storing value for mat1 i j
	add r6, r6, 4 			@ position in mat1 increment

	add r2, r2, 1  			@ increment j
	b .jloop

.jinitequal:
	add r1, r1, 1 			@ increment i
	mul r6, r3, 4 			@ 4* n
	mul r6, r6, r1 			@ 4*n*i
	b .iloop 				@ start loop of i

.initmat2:
	mul r7,r3, r3			@ position in mat2
	mul r7, r7, 16 			@ 16*n*n

.i2loop:
	cmp r1, r3				@ check if i = dim
	beq .reset				@ start multiplication

	mov r2, 0
	b .j2loop

.j2loop:
	cmp r2, r3 				@ check j = dim
	b .j2equal
	@ TODO
	add 
	add r2, r2, 1


.j2equal:
	add r1, r1, 1 			@ i +=1


	b .i2loop


.reset:
	mov r1, 0
	b .istep

.istep:
	cmp r1, r3 				@ checking if i=dim
	beq .result				@ done with multiplication

	mov r2, 0 				@ j =0
	b .jstep 				@ start work on j loop

.jstep:
	cmp r2, r3 				@ checking if j=dim
	beq .jequal				@ complete j loop

	mov r4, 0				@ k = 0  
	mov r5, 0				@ sum = 0
	mul r6, r1, 8			@ position in mat1
	mul r7, r2, 4 			@ position in mat2
	add r7, r7, 16          @ position in mat2  
	mov r8, 1  				@ product value
	mov r9, 1 				@ temp storage
	b .kstep				@ starting loop on k

.jequal:
	add r1, r1, 1 			@ increment i by 1
	b .istep				@ resume i loop

.kstep:
	cmp r4, r3				@ k becomes equal to n
	beq .kequalreached		@ done with k loop
	
	add sp, sp, r6 			@ sp set to mat1 value
	ld  r8, [sp]			@ loaded mat1 value in r8
	.print r8	
	@ mul r8, r8, r9			
	@.print r8
	sub sp, sp, r6			@ reset sp

	add sp, sp, r7			@ setting sp for mat 2
	ld r9, [sp]				@ load value in r9
	.print r9
	mul r8, r8, r9 			@ multiply value in r8
	sub sp, sp, r7			@ reset sp

	add r6, r6,  4 			@ Increment value of mat1 pos
	add r7, r7,  8 			@ Increment val of mat2 position
	add r5, r5, r8			@ Add to sum 
	add r4, r4,  1 			@ increment k
	b .kstep				@ loop repeat

.kequalreached:
	mul r8, r1, 8 			@ 8i will change
	add r9, r8, 32			@ 8i +32 will change
	mul r8, r2, 4 			@ 4j wont change
	add r9, r8, r9			@ 8i +32 +4j
	add sp , sp , r9		@ sp set to i, j location
	.print r5
	st r5, [sp]				@ storing value in i,j
	@mov r5, 0				@ sum=0
	sub sp, sp, r9			@ reset sp
	add r2, r2, 1 			@ increment j
	b .jstep				@ Calling j functions

.addmatrix:
	add sp, sp, 32			@ setting up sp for location
	mov r10, 0 				@ sum of matrix is 0
	mul r11, r3, r3 		@ limit value is dim*dim
	mov r8, 0
	b .loop	

.loop:
	cmp r8, r11				@ counter <dim*dim dim*dim
	beq .doneaddition		@ done addition 
	ld r9, [sp]				@ load memory value to r9
	add r10, r10, r9		@ add memory value to sum
	add sp, sp, 4 			@ set sp for new location
	add r8, r8, 1 			@ increment r8
	b .loop		

.result:
	b .addmatrix 			@Add the results of matrix

.doneaddition:
	sub sp, sp, 48 			@reset sp will change
	.print r10	