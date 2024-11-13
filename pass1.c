#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
int locctr=0,length,err=1;
char label[100],opcode[100],operand[100],code[20],value[20];
FILE *symtab,*optab,*intermediate,*input;
symtab=fopen("symtab.txt","w");
optab = fopen("optab.txt","r");
intermediate=fopen("intermediate.txt","w");
input=fopen("input.txt","r");
for(fscanf(input,"%s\t%s\t%s",label,opcode,operand);;fprintf(intermediate,"\t%s\t%s\t%s\n",label,opcode,operand),fscanf(input,"%s\t%s\t%s",label,opcode,operand))
{
 if(strcmp(opcode,"START")==0)
    {
        locctr=atoi(operand);
        length = locctr;
    }
 
 else if(feof(input)){
                fprintf(intermediate,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                printf("program length : %d",locctr-length);
                break;}
 else
    {   fprintf(intermediate,"%d",locctr);
        if(strcmp(label,"**")!=0)   
            fprintf(symtab,"%s\t%d\n",label,locctr);
        if(strcmp(opcode,"**")!=0)
            {   
                for(fscanf(optab,"%s\t%s",code,value);;fscanf(optab,"%s\t%s",code,value))
                    {   if(strcmp(opcode,code)==0){err=0;
                                                    break;}
                        if(feof(optab)){
                                    err=1;                                   
                                    break;}}
                if(err==0)locctr+=3;   
                else if(strcmp(opcode,"RESB")==0)locctr+= atoi(operand);
                else if(strcmp(opcode,"RESW")==0)locctr+= 3*atoi(operand);
                else if(strcmp(opcode,"BYTE")==0)locctr+= strlen(operand)-3;
                else if(strcmp(opcode,"WORD")==0)locctr+= 3;
                else
                    printf("error\n");
            }
            
    }
 
}

}