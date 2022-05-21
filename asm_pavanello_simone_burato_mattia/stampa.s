.section .data
P_A:
     .long 0
P_B:
    .long 0
P_C: 
    .long 0
I: 
    .long 0
.section .text
    .global INPUT
.type INPUT, @function
    INPUT:
    # carico i valori dei registri della precedente funzione nelle nuove variabili
    leal P_A, %edx
    movl %eax, (%edx)
    leal P_B, %edx
    movl %ebx,(%edx)
    leal P_C, %edx
    movl %ecx,(%edx)

    xor %ecx,%ecx # azzero ecx che userò come contatore

    LETTURA: # leggo bufferin
    cmpb $73,(%esi)
    jne OUT
    cmpb $78,1(%esi)
    jne STAMPA_CC
    cmpb $45,2(%esi)
    jne STAMPA_CC
    cmpb $65,3(%esi)
    je INC_A
    cmpb $66,3(%esi)
    je INC_B
    cmpb $67,3(%esi)
    je INC_C
    jmp STAMPA_CC
    
    # incremento il parcheggio A
    INC_A:
    leal P_A,%edx
    movl (%edx),%eax
    cmpl $31,%eax
    jge STAMPA_CC
    addl $1,P_A
    jmp STAMPA_OC
   # incremento il parcheggio B
    INC_B:
    leal P_B,%edx
    movl (%edx),%eax
    cmpl $31,%eax
    jge STAMPA_CC
    addl $1,P_B
    jmp STAMPA_OC
    # incremento il parcheggio C
    INC_C:
    leal P_C,%edx
    movl (%edx),%eax
    cmpl $24,%eax
    jge STAMPA_CC
    addl $1,P_C
    jmp STAMPA_OC
    
    OUT:
    cmpb $79,(%esi)
    jne STAMPA_CC
    cmpb $85,1(%esi)
    jne STAMPA_CC
    cmpb $84,2(%esi)
    jne STAMPA_CC
    cmpb $45,3(%esi)
    jne STAMPA_CC
    cmpb $65,4(%esi)
    je DEC_A
    cmpb $66,4(%esi)
    je DEC_B
    cmpb $67,4(%esi)
    je DEC_C
    jmp STAMPA_CC

    DEC_A: # decremento il parcheggio A
    leal P_A,%edx
    movl (%edx),%eax
    cmpl $0,%eax
    jle STAMPA_CC
    subl $1,P_A
    jmp STAMPA_CO

    DEC_B: # decremento il parcheggio A
    leal P_B,%edx
    movl (%edx),%eax
    cmpl $0,%eax
    jle STAMPA_CC
    subl $1,P_B
    jmp STAMPA_CO

    DEC_C: # decremento il parcheggio A
    leal P_C,%edx
    movl (%edx),%eax
    cmpl $0,%eax
    jle STAMPA_CC
    subl $1,P_C
    jmp STAMPA_CO
    
    STAMPA_OC:
    movb $79,(%ecx,%edi)
    addl $1,%ecx
    movb $67,(%ecx,%edi)
    addl $1,%ecx
    movb $45,(%ecx,%edi)
    addl $1,%ecx
    jmp STAMPA_PARK
    
    STAMPA_CC:
    movb $67,(%ecx,%edi)
    addl $1,%ecx
    movb $67,(%ecx,%edi)
    addl $1,%ecx
    movb $45,(%ecx,%edi)
    addl $1,%ecx
    jmp STAMPA_PARK
    
    STAMPA_CO:
    movb $67,(%ecx,%edi)
    addl $1,%ecx
    movb $79,(%ecx,%edi)
    addl $1,%ecx
    movb $45,(%ecx,%edi)
    addl $1,%ecx
    jmp STAMPA_PARK
    
    
    
    STAMPA_PARK: # stampo i valori dei parcheggi aggiornati
    movb $0,%ah
    movb P_A,%al
    movb $10,%bl
    divb %bl
    addb $48,%al
    addb $48,%ah
    movb %al,(%ecx,%edi)
    addl $1,%ecx
    movb %ah,(%ecx,%edi)  
    addl $1,%ecx
    movb $45,(%ecx,%edi)
    addl $1,%ecx
       
    movb $0,%ah
    movb P_B,%al  
    divb %bl
    addb $48,%al
    addb $48,%ah
    movb %al,(%ecx,%edi)
    addl $1,%ecx
    movb %ah,(%ecx,%edi)
    addl $1,%ecx  
    movb $45,(%ecx,%edi)
    addl $1,%ecx
    
    movb $0,%ah
    movb P_C,%al
    divb %bl
    addb $48,%al
    addb $48,%ah
    movb %al,(%ecx,%edi)
    addl $1,%ecx
    movb %ah,(%ecx,%edi)
    addl $1,%ecx 
    movb $45,(%ecx,%edi)
    addl $1,%ecx
    
    STAMPA_PARCHEGGI_PIENI: # stampo 1 se i parcheggi sono pieni, 0 se c'è ancora posto
    movl P_A,%eax
    cmpl $31,%eax
    je STAMPA_UNO_A
    movb $48,(%ecx,%edi)
    addl $1,%ecx
    
    STAMPA_B:
    movl P_B,%eax
    cmpl $31,%eax
    je STAMPA_UNO_B
    movb $48,(%ecx,%edi)
    addl $1,%ecx
    
    STAMPA_C:
    movl P_C,%eax
    cmpl $24,%eax
    je STAMPA_UNO_C
    movb $48,(%ecx,%edi) 
    addl $1,%ecx
    jmp LOOP
 
    STAMPA_UNO_A:
    movb $49,(%ecx,%edi)
    addl $1,%ecx
    jmp STAMPA_B
    
    STAMPA_UNO_B:
    movb $49,(%ecx,%edi)
    addl $1,%ecx
    jmp STAMPA_C
    
    STAMPA_UNO_C:
    movb $49,(%ecx,%edi)
    addl $1,%ecx


    LOOP: # continuo a leggere bufferin(%esi) finche non trovo un carattere terminante /0($0), se invece trovo una nuova riga vado a capo
    cmpb $10,(%esi)
    je ACAPO
    cmpb $0,(%esi)
    je FINE
    addl $1,%esi
    jmp LOOP
    
    ACAPO:
    addl $1,%esi # scorro la stringa 
    cmpb $0,(%esi) # controllo se è presente il carattere terminante e quindi salto alla fine
    je FINE
    movb $10,(%ecx,%edi) # altrimenti metto la nuova riga
    addl $1,%ecx # aumento il contatore che mi dice dove sto scrivendo
    jmp LETTURA
    
    FINE:
    movb $10,(%ecx,%edi)
    addl $1,%ecx
    movb $0,(%ecx,%edi) # metto il carattere terminante nell'ultima posizione di bufferout(edi)
    ret
