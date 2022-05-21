.section .data

NUMERO_A: 
    .ascii "00"    
NUMERO_B: 
    .ascii "00"
NUMERO_C: 
    .ascii "00"
A:
    .long 0
B:
    .long 0
C: 
    .long 0
.section .text
    .global inizializza
inizializza:
    pushl %ebp
    movl %esp , %ebp # prendo lo stack-pointer e lo metto in ebp
    pushl %eax
	pushl %ebx 
	pushl %ecx
	pushl %edi
	pushl %esi
    movl 8(%ebp), %esi # prelevo bufferin dallo stack e lo metto in esi
    movb $0,%cl # conta settori


controllore: # controlla il contatore e ci dice quale valore della stringa stiamo leggendo
cmpb $0,%cl
je primo
cmpb $1,%cl
je secondo
cmpb $2, %cl
je terzo
cmpb $3, %cl
je ATOI_A

primo: # prmia riga del file
cmpb $65, 0(%esi) # controllo se la prima lettera della riga è una A
je SET_A
cmpb $66, 0(%esi) # controllo se la prima lettera della riga è una B
je SET_B
cmpb $67, 0(%esi) # controllo se la prima lettera della riga è una C
je SET_C

secondo: # seconda riga del file
cmpb $65, 0(%esi) # controllo se la prima lettera della riga è una A
je SET_A
cmpb $66, 0(%esi) # controllo se la prima lettera della riga è una B
je SET_B
cmpb $67, 0(%esi) # controllo se la prima lettera della riga è una C
je SET_C

terzo: # terza riga del file
cmpb $65, 0(%esi) # controllo se la prima lettera della riga è una A
je SET_A
cmpb $66, 0(%esi) # controllo se la prima lettera della riga è una B
je SET_B
cmpb $67, 0(%esi) # controllo se la prima lettera della riga è una C
je SET_C


SET_A: 
inc %cl # incremento il contatore
leal NUMERO_A, %edi # carico nel puntatore l'indirizzo della variabile dove andrò a mettere l'ASCII del numero di parcheggi
movb 2(%esi), %dl
cmpb $10,3(%esi) # se il valore è un /n allora vuol dire che il numero ha una cifra dunque salto a dividi1
je DIVIDI_1
movb %dl,0(%edi)
movb 3(%esi), %dl
movb %dl,1(%edi)
jmp DIVIDI_2

SET_B:
inc %cl
leal NUMERO_B, %edi
movb 2(%esi), %dl
cmpb $10,3(%esi) # altrimenti ascii \n
je DIVIDI_1
movb %dl,0(%edi)
movb 3(%esi), %dl
movb %dl,1(%edi)
jmp DIVIDI_2

SET_C:
inc %cl
leal NUMERO_C, %edi
movb 2(%esi), %dl
cmpb $10,3(%esi) # altrimenti ascii \n
je DIVIDI_1
movb %dl,0(%edi)
movb 3(%esi), %dl
movb %dl,1(%edi)
jmp DIVIDI_2

DIVIDI_1: 
movb %dl,1(%edi)
addl $4, %esi # scorro la stringa
jmp controllore

DIVIDI_2:
addl $5, %esi # scorro la stringa
jmp controllore

ATOI_A: # converto il valore ascii del parcheggio prelevato in bufferin in un intero
leal NUMERO_A,%edi
movl (%edi),%eax
subl $48,%eax
movl $10,%ebx
mull %ebx
movl 1(%edi),%ebx
subl $48,%ebx
addl %ebx,%eax
leal A,%edx
movb %al,(%edx)
jmp ATOI_B


ATOI_B: # converto il valore ascii del parcheggio prelevato in bufferin in un intero
leal NUMERO_B,%edi
movl (%edi),%eax
subl $48,%eax
movl $10,%ebx
mull %ebx
movl 1(%edi),%ebx
subl $48,%ebx
addl %ebx,%eax
leal B,%edx
movb %al,(%edx)
jmp ATOI_C

ATOI_C: # converto il valore ascii del parcheggio prelevato in bufferin in un intero
leal NUMERO_C,%edi
movl (%edi),%eax
subl $48,%eax
movl $10,%ebx
mull %ebx
movl 1(%edi),%ebx
subl $48,%ebx
addl %ebx,%eax
leal C,%edx
movb %al,(%edx)


CONTROLLO_A: # controllo se A è pieno
leal A,%edi
movl (%edi),%eax
cmpl $31,%eax
jg SET_MAX


CONTROLLO_B: # controllo se B è pieno
leal B,%edi
movl (%edi),%eax
cmpl $31,%eax
jg SET_MAX
jmp CONTROLLO_C


SET_MAX: # se A o B sono maggiori di 31 allora li imposto a 31
movl $31,%ebx
movl %ebx,(%edi)
jmp CONTROLLO_B

CONTROLLO_C: # controllo se C è pieno
leal C,%edi
movl (%edi),%eax
cmpl $24,%eax
jg SET_MAX_C
jmp STACK

SET_MAX_C: # se C è maggiore di 24 allora lo imposto a 31
movl $24,%ebx
movl %ebx,(%edi)


STACK:
movl 12(%ebp),%edi # bufferout su EDI
movl A,%eax
movl B,%ebx
movl C,%ecx
call INPUT
FINE: # risistemo lo stack
popl %esi
popl %edi
popl %ecx
popl %ebx
popl %eax
popl %ebp
ret

